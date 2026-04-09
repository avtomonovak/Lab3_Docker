# Многостадийная сборка для маленького образа

# Этап 1: Сборка
FROM gcc:11 AS builder

RUN apt-get update && apt-get install -y make && rm -rf /var/lib/apt/lists/*

WORKDIR /build

# Копируем ТОЛЬКО нужные для сборки файлы
COPY fibonacci.cpp makefile ./

# Собираем ТОЛЬКО основную программу (не тесты!)
RUN make clean && make fibonacci

# Проверка, что файл создался
RUN ls -la fibonacci

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
