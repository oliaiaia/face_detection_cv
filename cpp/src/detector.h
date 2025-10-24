#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

// Initializes Haar cascade classifier
void init_cascade(const std::string& path);

// Detects faces on the given image
std::vector<cv::Rect> detect_faces(const cv::Mat& img);

// Draws rectangles around detected faces and returns a copy
cv::Mat draw_faces(const cv::Mat& img, const std::vector<cv::Rect>& faces);
