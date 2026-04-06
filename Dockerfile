# Многостадийная сборка для маленького образа

# Этап 1: Сборка
FROM gcc:11 AS builder

RUN apt-get update && apt-get install -y make && rm -rf /var/lib/apt/lists/*

WORKDIR /build

COPY fibonacci.cpp makefile ./

RUN make clean && make

# Этап 2: Финальный образ
FROM debian:bookworm-slim

RUN apt-get update && apt-get install -y libstdc++6 && rm -rf /var/lib/apt/lists/*

RUN useradd -m -s /bin/bash fibonacci

COPY --from=builder /build/fibonacci /usr/local/bin/

RUN chmod 755 /usr/local/bin/fibonacci

USER fibonacci

ENTRYPOINT ["/usr/local/bin/fibonacci"]

LABEL maintainer="avtomonovak" \
      version="1.0.0" \
      description="Fibonacci calculator - Лабораторная работа №3"
