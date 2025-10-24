#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <filesystem>
#include <opencv2/objdetect.hpp>

using namespace std;
using namespace cv;
namespace fs = std::filesystem;

// Allow both manual file and full dataset folder modes
void FaceDetection(const string& singleImagePath = "") {
    fs::path datasetDir = "cpp/dataset";
    fs::path resultsDir = "cpp/results";

    // Create results directory if it doesn't exist
    if (!fs::exists(resultsDir)) {
        fs::create_directories(resultsDir);
    }

    // Load Haar cascade classifier
    CascadeClassifier faceCascade;
    string cascadePath = "cpp/teacher_dataset/haarcascade_frontalface_default.xml";
    if (!faceCascade.load(cascadePath)) {
        cerr << "Failed to load cascade classifier from: " << cascadePath << endl;
        return;
    }

    // Function to process a single image
    auto processImage = [&](const fs::path& imgPath) -> void {
        Mat img = imread(imgPath.string());
        if (img.empty()) {
            cerr << "Could not read image: " << imgPath << endl;
            return;
        }

        vector<Rect> faces;
        faceCascade.detectMultiScale(img, faces, 1.1, 10); // now accessible
        cout << "Found " << faces.size() << " faces in " << imgPath << endl;

        for (const auto& face : faces) {
            rectangle(img, face.tl(), face.br(), Scalar(255, 0, 255), 3);
        }

        fs::path outFile = resultsDir / (imgPath.stem().string() + "_detected.jpg");
        if (!imwrite(outFile.string(), img)) {
            cerr << "Failed to save output image: " << outFile << endl;
        } else {
            cout << "Saved result to " << outFile << endl;
        }
    };

    if (!singleImagePath.empty()) {
        processImage(singleImagePath);
    } else {
        // Process all images in dataset directory
        if (!fs::exists(datasetDir)) {
            cerr << "Dataset directory does not exist: " << datasetDir << endl;
            return;
        }

        for (const auto& entry : fs::directory_iterator(datasetDir)) {
            if (entry.is_regular_file()) {
                processImage(entry.path());
            }
        }
    }
}

int main(int argc, char** argv) {
    if (argc > 1) {
        // Manual file mode
        FaceDetection(argv[1]);
    } else {
        // Default: process dataset folder
        FaceDetection();
    }
    return 0;
}