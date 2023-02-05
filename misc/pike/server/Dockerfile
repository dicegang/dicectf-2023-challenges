FROM python:3.11.1-slim-bullseye
WORKDIR /app
RUN pip install --no-cache rpyc==4.1.0
COPY server.py flag.txt ./
USER nobody
CMD ["python", "server.py"]
