FROM python:3.10.9-slim AS app
RUN pip install --no-cache pycryptodome cryptography

FROM pwn.red/jail:0.3.1
COPY --from=app / /srv
COPY server.py /srv/app/run
RUN chmod 755 /srv/app/run
COPY flag.txt /srv/app/
ENV JAIL_MEM=20M JAIL_CPU=500 JAIL_TIME=1800
