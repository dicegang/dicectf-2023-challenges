- the basic idea: smuggle flag cookie into notes cookie, use XSS to read the rendered contents on the page


- jetty webserver does weird shit with cookie parsing. if a cookie starts with an open quote, it will continue reading the cookie string until it reaches an end quote
- we can abuse this to smuggle the flag cookie into the note cookie and get it to render on the page
- e.g. if we have 3 cookies: 
  - note=`"a`
  - flag=`dice{flag}`
  - end=`b"`
- and the browser sends the cookie header: `note="a; flag=dice{flag}; end=b";`
- jetty will parse it as a single cookie: note=`a; flag=dice{flag}; end=b"`


- So, the idea is to use our XSS to tamper with the cookies, but the problem is - how do we get the cookies to be in that order?
- we need to abuse chrome's cookie ordering behavior to smuggle it correctly!
  - chrome orders cookies by longest path length first, then least recently updated first. We can figure this out by reading some chromium source code
- So, to get our note cookie to appear first, we simply create a new note cookie with the path `//`

- js payload becomes smth like:
```
document.cookie = `note="a; path=//`; // use double slash path to get it to appear at start (longest path)
document.cookie = `end=ok;"`; // last cookie (most recently updated)
w = window.open('https://jnotes.mc.ax//')
```

- this results in the sent cookiestr being something like
```
note="a; note=Hello+world%21; flag=dice{test}; end=b" 
```
- and from there, we can read the textarea on the page to retrieve the flag

