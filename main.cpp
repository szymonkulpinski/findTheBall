#include <iostream>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>
#include "boost/filesystem.hpp"
using namespace cv; 



int main(int, char**) {
    const std::string path = "/Users/szymon/Documents/coding/Projects/findTheBall2/Photos BBALL/test/";
    // for (const auto & entry : fs::directory_iterator(path))
    //     std::cout << entry.path() << std::endl;
    std::vector<std::string> m_file_list;

    // cv::String imagePath = "/Users/szymon/Documents/coding/Projects/findTheBall2/Photos BBALL/IMG_1344_test.jpg";
    cv::String imagePath = "/Users/szymon/Documents/coding/Projects/findTheBall2/Photos BBALL/test/IMG_1356.jpg";
    cv::Mat src, blured, imageHSV, outputImage, mask, outputImageShow, eroded, dilated;

    src = cv::imread(imagePath, cv::IMREAD_COLOR);
    GaussianBlur(src,blured, Size(11, 11), 11, 11);
    if (!src.data)
        throw std::invalid_argument("No image data, incorrect path!");
    cv::cvtColor(blured, imageHSV, cv::COLOR_BGR2HSV);


    int hmin = 0, hmax = 12; 
    int smin = 65, smax = 203;
    int vmin = 1, vmax = 203;

    // int hmin = 0, hmax = 13; 
    // int smin = 65, smax = 203;
    // int vmin = 1, vmax = 203;

    // int hmin = 7, hmax = 71; 
    // int smin = 48, smax = 158;
    // int vmin = 102, vmax = 255;

    // lower[2, 65, 1, 0]
    // upper[13, 203, 203, 0]

    cv::String figureName = "Preview";
    namedWindow(figureName, WINDOW_FULLSCREEN);
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
        inRange(imageHSV, lower, upper, outputImage);
        cv::erode(outputImage, outputImage, getStructuringElement(MORPH_RECT, Size(5, 5)));
        // cv::erode(eroded, eroded, getStructuringElement(MORPH_RECT, Size(5, 5)));
        cv::dilate(outputImage, outputImage, getStructuringElement(MORPH_RECT, Size(10, 10)));
        std::vector<std::vector<cv::Point>> contours;
        findContours(outputImage,contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        // getContours(contours, cv::RETR_EXTERNAL);

        Mat image_copy = src.clone();
        // drawContours(image_copy, contours, -1, Scalar(0, 255, 0), 2);

        std::vector<cv::Point2f>centers(contours.size());
        std::vector<float>radius(contours.size());
        std::vector<std::vector<cv::Point>> contoursPoly (contours.size());
        for (int i = 0; i < contours.size(); i++){
                    approxPolyDP( contours[i], contoursPoly[i], 3, true );
                    int area = contourArea(contours[i]);
                    if (area < 10000) continue; // 234016 100000
                    std::cout << "Area: " << area << std::endl;
                    int areaPoly = contourArea(contoursPoly[i]);
                    std::cout << "areaPoly: " << areaPoly << std::endl;
                    minEnclosingCircle( contoursPoly[i], centers[i], radius[i] );
                    circle( image_copy, centers[i], (int)radius[i], Scalar(0, 255, 0), 3 );
        }





        // Combine images
        cvtColor(outputImage, outputImage, COLOR_GRAY2BGR);
        // cvtColor(eroded, eroded, COLOR_GRAY2BGR);
        // cvtColor(dilated, dilated, COLOR_GRAY2BGR);
        // std::vector<cv::Mat> matrices = {src, outputImage, eroded, dilated};
        std::vector<cv::Mat> matrices = {src, image_copy, outputImage};
        cv::hconcat( matrices, mask );

        cv::imshow(figureName, mask);
        cv::waitKey(0);
    }
    return 0;
}






