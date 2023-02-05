Tl;dr bash argument injection when invoking openssl s_client allows you to smuggle memcached command via SNI


main bugs: `$host:$port` is not quoted in client.sh:8, so there is argument injection
```
    RESP=$(
      echo "$parsed_url" | timeout 5s openssl s_client -quiet -connect $host:$port 2>/dev/null
    )
```
furthermore, $IFS is re-defined in lib.sh to be "&=", and is never restored



This allows us to inject arbitrary arguments to `openssl s_client` by having & or = in our host param. e.g.
`gemini://blah=-debug`


The -debug flag lets us read the full connection hexdump, so if we are able to send a command to memcached, like `get flag`, we can read the response!


s_client communicates over TLS, so how can we send plaintext data to memcached? The `-servername` flag lets us send an SNI header, which is in plaintext.


However, we can't easily smuggle newlines, because we can't get them in the URL in the first place... so, how do we issue commands?
- Turns out, the bytes immediately following the SNI value are null bytes, and when memcached sees a null byte, it will stop reading the command :) so we luck out there.
- To get the SNI to START on a newline, we simply make it 10 long b/c the bytes immediately preceding it is the length field. We can do this by padding it with spaces (memcached will strip them)


Final payload:
```
gemini://blah=-servername=get flag  =-debug=-connect=127.0.0.1:11211
```


