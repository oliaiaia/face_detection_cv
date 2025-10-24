#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

// Initialize the face detection cascade
void init_cascade(const std::string& path);

// Detect faces in the given image
std::vector<cv::Rect> detect_faces(const cv::Mat& img);

// Draw bounding boxes on a copy of the image
cv::Mat draw_faces(const cv::Mat& img, const std::vector<cv::Rect>& faces);
