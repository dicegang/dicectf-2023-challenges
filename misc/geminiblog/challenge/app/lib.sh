#!/bin/bash

# from https://www.rfc-editor.org/rfc/rfc3986#appendix-B
readonly URI_REGEX='^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\?([^#]*))?(#(.*))?'
readonly AUTHORITY_REGEX='^((([^/?#]+)@)?([^:/?#]+)(:([0-9]+))?)'
readonly RESP_REGEX='^([0-9]{1,2}) (.*)'

function parseurl() {
  if [[ ! $1 =~ $URI_REGEX ]]; then
    return 1
  fi
  scheme=${BASH_REMATCH[2]:-gemini}
  authority=${BASH_REMATCH[4]:-127.0.0.1:1965}
  path=${BASH_REMATCH[5]:-/}
  query=${BASH_REMATCH[7]}
  fragment=${BASH_REMATCH[9]}
  # fix path
  if [[ ! $path =~ ^/ ]]; then
    path="/$path"
  fi
  # parse authority
  if [[ ! $authority =~ $AUTHORITY_REGEX ]]; then
    return 1
  fi
  host=${BASH_REMATCH[4]:-127.0.0.1}
  port=${BASH_REMATCH[6]:-1965}

  # parse query string
  IFS='=&'
  local parm=($query)
  declare -gA query_params
  for ((i=0; i<${#parm[@]}; i+=2))
  do
      query_params[${parm[i]}]=${parm[i+1]}
  done

  if [[ $scheme != gemini ]]; then
    return 1
  fi
  return 0
}

function parseresp() {
  headers=`echo "$1" | head -1`
  body=`echo "$1" | tail -n +2`

  if [[ ! $headers =~ $RESP_REGEX ]]; then
    return 1
  fi
  status=${BASH_REMATCH[1]}
  meta=${BASH_REMATCH[2]}
  return 0
}
