FROM python:3.11.1-slim-bullseye AS seccomp
WORKDIR /app
RUN apt-get update && \
  apt-get install -y build-essential git autoconf libtool gperf && \
  pip install --no-cache cython
RUN git clone --depth 1 --branch v2.5.4 https://github.com/seccomp/libseccomp . && \
  ./autogen.sh && ./configure && make -j && \
  cd src/python && make install -j && VERSION_RELEASE=2.5.4 python setup.py install

FROM pwn.red/jail:0.3.1
COPY --from=python:3.11.1-slim-bullseye / /srv
COPY --from=seccomp /usr/local/lib/python3.11/site-packages /srv/usr/local/lib/python3.11/site-packages
COPY util.py /srv/app/
COPY tests /srv/app/tests/
COPY --chmod=755 runner.py /srv/app/run
ENV JAIL_MEM=30M JAIL_CPU=200
