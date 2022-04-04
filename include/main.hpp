#pragma once
#include <opencv2/opencv.hpp>

static const cv::Scalar greenColor = cv::Scalar(0, 255, 0);
static const cv::Scalar turquoiseColor = cv::Scalar(255, 255, 0);
static const int hmin = 0, hmax = 12; 
static const int smin = 126, smax = 255;
static const int vmin = 1, vmax = 203;
static const cv::Scalar lower(hmin, smin, vmin);
static const cv::Scalar upper(hmax, smax, vmax);
static const int minBallArea = 50000;