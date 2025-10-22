#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
#include <unistd.h>
#include <vector>
#include <filesystem>

#include<opencv2/objdetect.hpp>


using namespace std;
using namespace cv;
namespace fs = std::filesystem;

void faseDetection() {
    string datasetPath = "/home/olia/Skoltech/Software/face_detection_cv/dataset/";
    
    //study cascade classifier
    CascadeClassifier faseCascade;
    faseCascade.load("/home/olia/Skoltech/Software/face_detection_cv/teacher_dataset/haarcascade_frontalface_default.xml");
    if(faseCascade.empty()) 
    {
        cerr << "Empty cascade classifier file!" << endl;
        return;
    }

    // Process each image in the dataset folder
    for (const auto & entry : fs::directory_iterator(datasetPath)) {
        string imgPath = entry.path();
        cout << "Processing: " << imgPath << endl;
        
        // Read the image
        Mat img = imread(imgPath);
        if(img.empty()) {
            cerr << "Could not read image: " << imgPath << endl;
            continue;
        }

        vector<Rect> faces;
        faseCascade.detectMultiScale(img, faces, 1.1, 10);
        cout << "Found " << faces.size() << " faces in " << imgPath << endl;

        // Draw rectangles around detected faces
        for(const auto& face : faces) {
            rectangle(img, face.tl(), face.br(), Scalar(255, 0, 255), 3);
        }

        // Show the image with detected faces
        string windowName = "Detected faces - " + fs::path(imgPath).filename().string();
        imshow(windowName, img);
        
        // Save the result
        string outputPath = imgPath.substr(0, imgPath.find_last_of('.')) + "_detected.jpg";
        imwrite(outputPath, img);
        
        // Wait for a key press before processing next image
        waitKey(0);
        destroyWindow(windowName);
    }



}

int main() {
    faseDetection();
    return 0;
}
