#include "detector.h"
#include <stdexcept>

static cv::CascadeClassifier face_cascade;

void init_cascade(const std::string& path) {
    if (!face_cascade.load(path))
        throw std::runtime_error("Cannot load cascade: " + path);
}

std::vector<cv::Rect> detect_faces(const cv::Mat& img) {
    if (img.empty())
        throw std::invalid_argument("Empty image passed to detect_faces");

    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(img, faces, 1.1, 5, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
    return faces;
}

cv::Mat draw_faces(const cv::Mat& img, const std::vector<cv::Rect>& faces) {
    if (img.empty())
        throw std::invalid_argument("Empty image passed to draw_faces");

    cv::Mat out = img.clone();
    for (const auto& f : faces)
        cv::rectangle(out, f, cv::Scalar(0, 255, 0), 2);
    return out;
}
