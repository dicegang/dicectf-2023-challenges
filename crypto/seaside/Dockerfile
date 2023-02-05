FROM python:3.11.1-slim-bullseye AS build
WORKDIR /app
RUN apt-get update && apt-get install -y build-essential
ADD csidh-latest.tar.xz .
RUN cd csidh-* && make libcsidh.so

FROM python:3.11.1-slim-bullseye AS app
RUN pip install --no-cache pycryptodome

FROM pwn.red/jail:0.3.1
COPY --from=app / /srv
COPY --from=build /app/csidh-*/libcsidh.so /srv/app/libcsidh.so
COPY server.py /srv/app/run
COPY flag.txt /srv/app/
ENV JAIL_MEM=20M JAIL_CPU=500
