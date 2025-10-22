#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
#include <unistd.h>
#include <vector>

#include<opencv2/objdetect.hpp>


using namespace std;
using namespace cv;

void faseDetection() {

    VideoCapture video(0); //id of webcam
    // load webcam image
    cv::Mat webcam;
 
    //study cascade classifier
    CascadeClassifier faseCascade;
    faseCascade.load("/home/olia/CLionProjects/opencv_base/Resources/haarcascade_frontalface_default.xml");
    if(faseCascade.empty()) 
    {
        cerr << "Empty file!" << endl;
        return;
    }

    vector<Rect> faces;

    while(true) {
        video.read(webcam);
        faseCascade.detectMultiScale(webcam, faces, 1.1, 10);
        if(faces.size() > 0) std::cout << "face amount: " << faces.size() << std::endl;
        for(int t = 0; t < faces.size(); t++) {
            rectangle(webcam, faces[t].tl(), faces[t].br(), Scalar(255, 0, 0), 3); 
        }
        cv::imshow("Image", webcam);
        cv::waitKey(20); //delay in ms
    }



}

int main() {
    faseDetection();
    return 0;
}
