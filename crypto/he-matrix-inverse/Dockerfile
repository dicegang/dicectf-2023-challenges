# syntax=docker/dockerfile:1.4.3
FROM scratch AS data
ADD https://static.dicega.ng/uploads/1155f6ae61808fd32d1885b608762a9e0d93ccacdf9f05466e681fb48e12e92e/data.zip .

FROM python:3.8.16-slim-bullseye AS app
RUN apt-get update && apt-get install -y git build-essential
RUN pip install --no-cache git+https://github.com/ibarrond/Pyfhel@0dee7a77469627c4de4f2dca97cdc68bf006a77d

FROM pwn.red/jail:0.3.1
RUN --mount=from=data,target=/data mkdir -p /srv/app && unzip /data/data.zip -d /srv/app
COPY --link --from=python:3.8.16-slim-bullseye / /srv
COPY --link --from=app /usr/lib/*-linux-gnu/libgomp.so.1 /srv/usr/lib/
COPY --link --from=app /usr/local/lib/python3.8/site-packages /srv/usr/local/lib/python3.8/site-packages
COPY --link server.py /srv/app/run
COPY --link flag.txt sec.key /srv/app/
ENV JAIL_POW=45000 JAIL_MEM=3G JAIL_CPU=1000
