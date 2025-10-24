#include "detector.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>

using namespace std;
using namespace cv;
namespace fs = std::filesystem;

int main() {
    try {
        // Paths inside the container
        const string input_dir = "/app/dataset";
        const string output_dir = "/app/results";
        const string cascade_path = "/app/teacher_dataset/haarcascade_frontalface_default.xml";

        // Initialize the cascade
        init_cascade(cascade_path);

        // Check if the input directory exists
        if (!fs::exists(input_dir)) {
            cerr << "Input directory not found: " << input_dir << endl;
            return 1;
        }

        // Create the output directory if it does not exist
        if (!fs::exists(output_dir)) {
            fs::create_directories(output_dir);
        }

        // Process each image in the input directory
        for (const auto& entry : fs::directory_iterator(input_dir)) {
            string img_path = entry.path().string();
            cout << "Processing: " << img_path << endl;

            Mat img = imread(img_path);
            if (img.empty()) {
                cerr << "Could not read image: " << img_path << endl;
                continue;
            }

            // Face detection
            auto faces = detect_faces(img);
            cout << "Found " << faces.size() << " faces in " << img_path << endl;

            // Draw bounding boxes
            Mat result = draw_faces(img, faces);

            // Save the result
            fs::path out_file = fs::path(output_dir) / (fs::path(img_path).stem().string() + "_detected.jpg");
            imwrite(out_file.string(), result);
        }

        cout << "Face detection completed successfully." << endl;
        return 0;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}
