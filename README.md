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


## Testing

This project includes a complete unit and integration test suite implemented with **GoogleTest** and executed using **CTest**.

### Test coverage

- Cascade initialization and error handling
- Face detection on real and empty images
- Drawing and visualization consistency
- Performance validation
- CLI integration test (verifies that output images are generated)


### Build and run tests

#### 1. Open a terminal in the project root (```/app``` inside Docker).

#### 2. Configure and build the project:

```bash
mkdir -p build && cd build
cmake ..
make -j
```

#### 3. Run the tests:

```bash
ctest --output-on-failure
```

### Expected output

If everything is configured correctly, you should see:

```bash
Test project /app/build
    Start 1: Detector.InitCascadeOk
1/8 Test #1: Detector.InitCascadeOk ............ Passed
...
8/8 Test #8: Integration.FaceDetectCreatesOutputFiles ... Passed

100% tests passed, 0 tests failed
```

### List of Implemented Tests
#### 1. ```Detector.InitCascadeOk``` - Verifies that the Haar cascade file loads correctly
#### 2. ```Detector.InitCascadeBadPath``` - Ensures an exception is thrown when the cascade path is invalid
#### 3. ```Detector.EmptyImageNoDetections``` - Confirms that no faces are detected on an empty image
#### 4. ```Detector.FaceImageHasDetections``` - Validates that the detector finds at least one face in a real image
#### 5. ```Detector.DrawFacesKeepsSize``` - Checks that drawing rectangles does not change image dimensions
#### 6. ```Detector.CascadeReinit``` - Tests that reinitializing the cascade multiple times works without errors
#### 7. ```Detector.PerformanceCheck``` - Ensures that face detection completes within 0.5 seconds
#### 8. ```Integration.FaceDetectCreatesOutputFiles``` - Integration test verifying that the CLI program generates output files in /app/results

### Continuous Integration

All tests are automatically executed on every **push** or **pull** request using GitHub Actions.
The workflow configuration is available in ```.github/workflows/ci.yml.```

## Technical Details

- Uses OpenCV's pre-trained Haar cascade classifier
- Processes images in batch mode
- No GUI dependencies - runs in headless environments
- Results are automatically saved to disk
