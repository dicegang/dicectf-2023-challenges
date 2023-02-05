#!/bin/bash
source lib.sh

function processurl() {
  if parseurl "$1"; then
    parsed_url="$scheme://$host:$port$path?$query"
    echo "Requesting $parsed_url..."
    RESP=$(
      echo "$parsed_url" | timeout 5s openssl s_client -quiet -connect $host:$port 2>/dev/null
    )
    #echo "Received raw response: $RESP"
    if [[ -z "$RESP" ]]; then
      echo No response
      exit 1
    fi

    # read response code
    parseresp "$RESP"
    # echo "response parsed! status: $status, meta: $meta"
    case $status in
      1[0-9])
        # 1x - input
        # <META> line is a prompt which should be displayed to the user. The same resource should then be requested again with the user's input included as a query component
        echo "Input requested: $meta"
        read -e input
        processurl "$scheme://$host:$port$path?$input"
        ;;
      2[0-9])
        # 2x - success
        # <META> line is a MIME media type which applies to the response body.
        echo "-----"
        echo "$body"
        ;;
      3[0-9])
        # 3x - redirect
        # There is no response body. <META> is a new URL for the requested resource. The URL may be absolute or relative. If relative, it should be resolved against the URL used in the original request. If the URL used in the original request contained a query string, the client MUST NOT apply this string to the redirect URL, instead using the redirect URL "as is".
        echo "Redirecting to $meta..."
        # TODO handle relative - processurl "$scheme://$host:$port$meta"
        processurl "$meta"
        ;;
      [4-5][0-9])
        # 4x - temp failure
        # 5x - permanent failure
        # no response body, <META> may provide additional information
        echo "-----"
        echo "Error response: $meta"
        exit 1
        ;;
      6[0-9])
        # 6x - certificate required
        # TODO implement client certificates
        echo Certificate unimplemented
        exit 1
        ;;
      *)
        echo Unknown status code
        echo "-----"
        echo "$RESP"
        exit 1
        ;;
    esac
  else
    echo Invalid URL
    exit 1
  fi
}

echo "Welcome to the DiceGang Gemini client!
Sample URLs: gemini://gemini.circumlunar.space/docs/faq.gmi, gemini://localhost/

Please enter a URL to request:"
read -e url
processurl "$url"
