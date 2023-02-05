FROM pwn.red/jail:0.3.1
COPY --from=debian:bullseye-20230109-slim / /srv
COPY deet_daemon flag.txt ld-linux-x86-64.so.2 /srv/app/
COPY libs /srv/app/libs
COPY sice_supervisor /srv/app/run
ENV JAIL_PIDS=20 JAIL_MEM=10M JAIL_TIME=180
