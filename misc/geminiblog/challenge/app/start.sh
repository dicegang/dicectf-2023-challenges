#!/bin/bash
service memcached start
sleep 2

FLAG=`cat flag.txt`
printf "set flag 0 0 %s\r\n%s\r\n" "${#FLAG}" "$FLAG" | timeout 2s nc 127.0.0.1 11211
unset FLAG
rm flag.txt

socat \
  openssl-listen:1965,cert=mycert.pem,key=mykey.pem,verify=0,reuseaddr,fork,su=nobody \
  EXEC:"/bin/bash server.sh" &

socat \
  tcp-listen:1337,reuseaddr,fork,su=nobody \
  EXEC:"/bin/bash client.sh" &

wait
