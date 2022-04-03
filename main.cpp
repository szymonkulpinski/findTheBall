#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv; 


int main(int, char**) {
    cv::String imagePath = "/Users/szymon/Documents/coding/Projects/findTheBall2/Photos BBALL/IMG_1344_test.jpg";
    cv::Mat image, imageHSV, outputImage, mask, image3;

    image = cv::imread(imagePath, cv::IMREAD_COLOR);
    if (!image.data)
        throw std::invalid_argument("No image data, incorrect path!");
    cv::cvtColor(image, imageHSV, cv::COLOR_BGR2HSV);

    int hmin = 7, hmax = 71; 
    int smin = 48, smax = 158;
    int vmin = 102, vmax = 255;

    cv::String figureName = "Preview";
    namedWindow(figureName);
    createTrackbar("Hue Min", figureName, &hmin, 255);
    createTrackbar("Hue Max", figureName, &hmax, 255);
    createTrackbar("Saturation Min", figureName, &smin, 255);
    createTrackbar("Saturation Max", figureName, &smax, 255);
    createTrackbar("Value Min", figureName, &vmin, 255);
    createTrackbar("Value Max", figureName, &vmax, 255);

    while(true){

        // Thresholding
        cv::Scalar lower (hmin, smin, vmin);
        cv::Scalar upper (hmax, smax, vmax);
        std::cout << "lower" << lower <<  std::endl;
        std::cout << "upper" << upper << std::endl;
        inRange(image, lower, upper, outputImage);

        // Combine for images
        cvtColor(outputImage, image3, COLOR_GRAY2BGR);
        std::vector<cv::Mat> matrices = {image, image3};
        cv::hconcat( matrices, mask );

        cv::imshow(figureName, mask);
        cv::waitKey(0);
    }
    return 0;
}






