# Face Detection CV Makefile
IMAGE_NAME = face-detect-cv

.PHONY: build run stop clean help

# Build Docker image
build:
	docker build -t $(IMAGE_NAME) .

# Run container
run:
	docker run --rm \
	-v $(PWD)/dataset:/app/dataset \
	-v $(PWD)/results:/app/results \
	-v $(PWD)/teacher_dataset:/app/teacher_dataset \
	$(IMAGE_NAME)

# Stop all containers
stop:
	docker stop $$(docker ps -q --filter "ancestor=$(IMAGE_NAME)") 2>/dev/null || true

# Clean up
clean:
	docker rmi $(IMAGE_NAME) 2>/dev/null || true

# Help
help:
	@echo "Available commands:"
	@echo "  make build    - Build Docker image"
	@echo "  make run      - Run container"
	@echo "  make stop     - Stop running containers"
	@echo "  make clean    - Remove Docker image"