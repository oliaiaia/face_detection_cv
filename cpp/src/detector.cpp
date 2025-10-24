#include "detector.h"
#include <opencv2/opencv.hpp>
#include <stdexcept>
#include <vector>

using namespace cv;

static CascadeClassifier face_cascade;

void init_cascade(const std::string& path) {
    if (!face_cascade.load(path)) {
        throw std::runtime_error("Failed to load cascade: " + path);
    }
}

std::vector<Rect> detect_faces(const Mat& img) {
    if (img.empty()) return {};
    std::vector<Rect> faces;
    face_cascade.detectMultiScale(img, faces, 1.1, 10);
    return faces;
}

Mat draw_faces(const Mat& img, const std::vector<Rect>& faces) {
    Mat out = img.clone();
    for (const auto& f : faces) {
        rectangle(out, f, Scalar(255, 0, 255), 2);
    }
    return out;
}
