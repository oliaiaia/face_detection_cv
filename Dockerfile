FROM python:3.11-slim

ENV DEBIAN_FRONTEND=noninteractive
ENV PYTHONPATH=/face_detection_cv

RUN apt-get update && apt-get install -y \
    build-essential cmake git \
    libopencv-dev pkg-config \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /face_detection_cv

COPY . /face_detection_cv

RUN pip install --no-cache-dir -r python/requirements.txt

RUN mkdir -p build && cd build && cmake .. && make -j$(nproc)

EXPOSE 1616

CMD ["python3", "backend/app/main.py"]