# Face Detection CV

A simple and efficient face detection application using OpenCV and Haar cascades.

## Project Structure

```
face_detection_cv/
├── dataset/           # Input images for face detection
├── teacher_dataset/   # Haar cascade classifier file
├── results/          # Output images with detected faces
├── src/              # Source code
└── Dockerfile        # Container configuration
```

## Features

- Fast face detection using OpenCV's Haar cascade classifier
- Batch processing of multiple images
- Automatic result saving with bounding boxes around detected faces
- Docker containerization for easy deployment

## Usage

### Building the Docker Image

```bash
docker build -t face-detect-cv .
```

### Running the Container

```bash
docker run --rm \
  -v /host/path/to/face_detection_cv/dataset:/app/dataset \
  -v /host/path/to/face_detection_cv/results:/app/results \
  -it face-detect-cv:latest
```

## Output

Processed images are saved in the `results/` directory with `_detected` suffix, containing bounding boxes around all detected faces.

## Technical Details

- Uses OpenCV's pre-trained Haar cascade classifier
- Processes images in batch mode
- No GUI dependencies - runs in headless environments
- Results are automatically saved to disk