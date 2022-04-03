#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>
#include <unistd.h>
using namespace cv; 



int main(int, char**) {

    // TODO: Read automatically from directory  
    std::string folderPath = "/Users/szymon/Documents/coding/Projects/findTheBall2/Photos BBALL/test/";
    std::vector<std::string> fileList;
    fileList.push_back("IMG_1354.jpg");
    fileList.push_back("IMG_1355.jpg");
    fileList.push_back("IMG_1356.jpg");
    fileList.push_back("IMG_1357.jpg");
    fileList.push_back("IMG_1358.jpg");
    fileList.push_back("IMG_1359.jpg");
    fileList.push_back("IMG_1360.jpg");
    fileList.push_back("IMG_1361.jpg");
    fileList.push_back("IMG_1362.jpg");
    fileList.push_back("IMG_1363.jpg");
    fileList.push_back("IMG_1364.jpg");


    int hmin = 0, hmax = 12; 
    int smin = 126, smax = 255;
    int vmin = 1, vmax = 203;
    cv::Mat src, blured, imageHSV, outputImage, mask, outputImageShow, eroded, dilated;

    // std::string figureNameA = (std::string) "Preview" + std::to_string(i);
    // cv::String figureName = (cv::String) figureNameA;
    cv::String figureName = "Preview";
    // namedWindow(figureName, WINDOW_FULLSCREEN);
    // namedWindow(figureName, WINDOW_AUTOSIZE);
    namedWindow(figureName, WINDOW_NORMAL);
    // namedWindow(figureName, WINDOW_KEEPRATIO);
    resizeWindow(figureName, 600,600);


    for (int i = 0; i < fileList.size(); i++)
    {
    cv::String imagePath = folderPath + fileList[i];

    src = cv::imread(imagePath, cv::IMREAD_COLOR);
    if (!src.data)
        throw std::invalid_argument("No image data, incorrect path!");
    GaussianBlur(src,blured, Size(11, 11), 11, 11);
    cv::cvtColor(blured, imageHSV, cv::COLOR_BGR2HSV);

    // if (src.size().width < src.size().height)
    // {
    // }
    





    // createTrackbar("Hue Min", figureName, &hmin, 255);
    // createTrackbar("Hue Max", figureName, &hmax, 255);
    // createTrackbar("Saturation Min", figureName, &smin, 255);
    // createTrackbar("Saturation Max", figureName, &smax, 255);
    // createTrackbar("Value Min", figureName, &vmin, 255);
    // createTrackbar("Value Max", figureName, &vmax, 255);

// while(true){

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
        cv::String textPostion;
        for (int i = 0; i < contours.size(); i++){
                    approxPolyDP( contours[i], contoursPoly[i], 3, true );
                    int area = contourArea(contours[i]);
                    if (area < 50000) continue; // 234016 100000
                    std::cout << "Area: " << area << std::endl;
                    int areaPoly = contourArea(contoursPoly[i]);
                    std::cout << "areaPoly: " << areaPoly << std::endl;
                    minEnclosingCircle( contoursPoly[i], centers[i], radius[i] );
                    circle( image_copy, centers[i], (int)radius[i], Scalar(0, 255, 0), 3 );
                    // std::string figureNameA = (std::string) "Preview" + std::to_string(i);
                    textPostion = (cv::String) ((std::string)"Ball center: " + std::to_string((int)centers[i].x) + (std::string)", " + std::to_string((int)centers[i].y)); // TODO: pretify
                    putText(image_copy, textPostion, Point(40,40), FONT_HERSHEY_PLAIN, 3, Scalar(255, 255, 0),3);
                    line(image_copy, Point(centers[i].x-20,centers[i].y), Point(centers[i].x+20,centers[i].y),Scalar(255, 255, 0),3);
                    line(image_copy, Point(centers[i].x,centers[i].y-20), Point(centers[i].x,centers[i].y+20),Scalar(255, 255, 0),3);
        }





        // Combine images
        cvtColor(outputImage, outputImage, COLOR_GRAY2BGR);
        // cvtColor(eroded, eroded, COLOR_GRAY2BGR);
        // cvtColor(dilated, dilated, COLOR_GRAY2BGR);
        // std::vector<cv::Mat> matrices = {src, outputImage, eroded, dilated};
        std::vector<cv::Mat> matrices = {image_copy, outputImage};
        cv::hconcat( matrices, mask );
        // resizeWindow(figureName, (int) mask.size().width/2, (int) mask.size().height);

        cv::imshow(figureName, mask);
        cv::waitKey(0);
        // cv::destroyAllWindows();
    // }
    }
    return 0;
}






