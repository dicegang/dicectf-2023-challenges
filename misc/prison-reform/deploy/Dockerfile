FROM pwn.red/jail:0.3.1

COPY --from=python:3.10.9-slim / /srv
COPY flag.txt /srv/
RUN chmod 444 /srv/flag.txt && mv /srv/flag.txt /srv/flag.`tr -dc A-Za-z0-9 < /dev/urandom | head -c 20`.txt
COPY prison.py /srv/app/run
RUN chmod 755 /srv/app/run

ENV JAIL_PIDS=20
ENV JAIL_MEM=20M
