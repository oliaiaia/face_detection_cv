FROM ubuntu:22.04
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential cmake libopencv-dev && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

# Создаем структуру папок для программы
RUN mkdir -p cpp/teacher_dataset cpp/dataset cpp/results && \
    cp teacher_dataset/*.xml cpp/teacher_dataset/ && \
    cp -r dataset/* cpp/dataset/ 2>/dev/null || true

# Собираем из папки cpp
RUN mkdir -p build && cd build \
    && cmake ../cpp \
    && cmake --build .

CMD ["./build/face_detector"]