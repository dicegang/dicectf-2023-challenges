FROM pwn.red/jail:0.3.1
COPY --from=ubuntu:jammy-20230126 / /srv
COPY bin/term-zelda /srv/app/run
COPY bin/flag.txt /srv/app/
ENV JAIL_CPU=500 JAIL_TIME=120 JAIL_ENV_TERM=linux JAIL_ENV_COLUMNS=70 JAIL_ENV_ROWS=14
