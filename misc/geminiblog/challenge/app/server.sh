#!/bin/bash
source lib.sh

read -e url
#echo "received url: $url"
if parseurl "$url"; then
  #echo "parsed url: $path?$query"
  if [[ $path == "/" ]]; then
    printf "20 text/gemini\r\nWelcome to the DiceGang Gemini server!\r\n\r\n=> gemini://127.0.0.1:1965/create Create a post\r\n=> gemini://127.0.0.1:1965/post View a post\r\n"
  elif [[ $path == "/create" ]]; then
    if [[ -z "$query" ]]; then
      printf "10 Write your post\r\n"
    else
      pid=`openssl rand -hex 6`
      post="$query"
      result=$(
        printf "set %s 0 0 %s\r\n%s\r\n" "$pid" "${#post}" "$post" | timeout 1s nc 127.0.0.1 11211
      )
      if [[ ! $result =~ "STORED" ]]; then
        printf "51 Failed to store post\r\n"
        exit 1
      fi
      printf "20 text/gemini\r\n=> gemini://127.0.0.1:1965/post?%s Post created!\r\n" "$pid"
    fi
  elif [[ $path == "/post" ]]; then
    if [[ -z "$query" ]]; then
      printf "10 Enter post id\r\n"
    else
      pid="$query"
      readonly POST_REGEX='^[a-z0-9]{12}$'
      if [[ ! $pid =~ $POST_REGEX ]]; then
        printf "50 Invalid post id\r\n"
        exit 1
      fi
      result=$(
        printf "get %s\r\n" "$pid" | timeout 1s nc 127.0.0.1 11211
      )
      if [[ ! $result =~ "VALUE" ]]; then
        printf "51 Post not found\r\n"
        exit 1
      fi
      result=$(echo "$result" | tail -n +2 | head -n -1)
      printf "20 text/gemini\r\n%s" "$result"
    fi
  else
    printf "51 Path %s not found\r\n" "$path"
  fi
fi
