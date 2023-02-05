FROM debian:bullseye
RUN apt-get update && apt-get install -y \
  socat \
  netcat \
  libssl-dev \
  openssl \
  memcached \
  && rm -rf /var/lib/apt/lists/*

RUN mkdir -p /usr/src/app
WORKDIR /usr/src/app
RUN openssl req -x509 -nodes -days 365 -sha256 -newkey rsa:4096 -keyout mykey.pem -out mycert.pem -subj "/C=US/ST=WY/L=Sheridan/O=DiceGang/OU=DiceGang/CN=dicega.ng"

COPY flag.txt .
COPY *.sh .
RUN chmod -R 555 /usr/src/app

CMD bash start.sh
EXPOSE 1965
