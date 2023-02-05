# syntax=docker/dockerfile:1.4.3
FROM sagemath/sagemath:9.7
WORKDIR /app
RUN sage --pip install --no-cache pycryptodome
COPY --link challenge.py flag.txt nth_root.py ./
ENV PYTHONUNBUFFERED=1
CMD ["sage", "challenge.py"]
