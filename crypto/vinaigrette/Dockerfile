FROM python:3.11.1-slim-bullseye AS build
WORKDIR /app
RUN apt-get update && apt-get install -y build-essential clang libssl-dev
ADD pqov-paper.tar.gz patch.diff .
RUN patch -p1 < patch.diff && make libpqov.so VARIANT=2

FROM python:3.11.1-slim-bullseye AS app

FROM pwn.red/jail:0.3.1
COPY --from=app / /srv
COPY --from=build /app/libpqov.so /srv/app/libpqov.so
COPY server.py /srv/app/run
COPY flag.txt sk.bin pk.bin /srv/app/
ENV JAIL_MEM=20M JAIL_CPU=500
