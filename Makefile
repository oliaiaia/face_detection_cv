# Face Detection CV Makefile
IMAGE_NAME = face-detect-cv

.PHONY: build run stop clean help

build:
	docker build -t $(IMAGE_NAME) .

run:
	docker run --rm \
	-v $(PWD)/dataset:/app/dataset \
	-v $(PWD)/results:/app/results \
	-it $(IMAGE_NAME)

stop:
	docker stop $$(docker ps -q --filter "ancestor=$(IMAGE_NAME)") 2>/dev/null || true

clean:
	docker rmi $(IMAGE_NAME) 2>/dev/null || true

help:
	@echo "Available commands:"
	@echo "  make build    - Build Docker image"
	@echo "  make run      - Run container"
	@echo "  make stop     - Stop running containers"
	@echo "  make clean    - Remove Docker image"