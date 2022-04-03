#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>
#include <unistd.h>
using namespace cv; 



int main(int, char**) {
    cv::Mat src, blured, imageHSV, outputImage, mask, outputImageShow, eroded, dilated;

    // Get Files
    // TODO: Read automatically from directory, boost or C++17 needed
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
    cv::Scalar lower (hmin, smin, vmin);
    cv::Scalar upper (hmax, smax, vmax);


    // Create Window
    cv::String figureName = "Preview";
    namedWindow(figureName, WINDOW_NORMAL);
    resizeWindow(figureName, 600,600);


    for (int i = 0; i < fileList.size(); i++)
    {
    cv::String imagePath = folderPath + fileList[i];

    src = cv::imread(imagePath, cv::IMREAD_COLOR);
    if (!src.data)
        throw std::invalid_argument("No image data, incorrect path!");
    GaussianBlur(src,blured, Size(11, 11), 11, 11);
    cv::cvtColor(blured, imageHSV, cv::COLOR_BGR2HSV);


        // Thresholding
        inRange(imageHSV, lower, upper, outputImage);
        cv::erode(outputImage, outputImage, getStructuringElement(MORPH_RECT, Size(5, 5)));
        cv::dilate(outputImage, outputImage, getStructuringElement(MORPH_RECT, Size(10, 10)));
        std::vector<std::vector<cv::Point>> contours;
        findContours(outputImage,contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        Mat image_copy = src.clone();

        std::vector<cv::Point2f>centers(contours.size());
        std::vector<float>radius(contours.size());
        std::vector<std::vector<cv::Point>> contoursPoly (contours.size());
        cv::String textPostion;
        for (int i = 0; i < contours.size(); i++){
                    approxPolyDP( contours[i], contoursPoly[i], 3, true);
                    int area = contourArea(contours[i]);
                    if (area < 50000) continue; 
                    int areaPoly = contourArea(contoursPoly[i]);

                    // Debugging 
                    std::cout << "Area: " << area << std::endl;
                    std::cout << "areaPoly: " << areaPoly << std::endl;

                    // Draw on image
                    minEnclosingCircle( contoursPoly[i], centers[i], radius[i] );
                    circle( image_copy, centers[i], (int)radius[i], Scalar(0, 255, 0), 3 );
                    textPostion = (cv::String) ((std::string)"Ball center: " + std::to_string((int)centers[i].x) + (std::string)", " + std::to_string((int)centers[i].y)); // TODO: pretify
                    putText(image_copy, textPostion, Point(40,40), FONT_HERSHEY_PLAIN, 3, Scalar(255, 255, 0),3);
                    line(image_copy, Point(centers[i].x-20,centers[i].y), Point(centers[i].x+20,centers[i].y),Scalar(255, 255, 0),3);
                    line(image_copy, Point(centers[i].x,centers[i].y-20), Point(centers[i].x,centers[i].y+20),Scalar(255, 255, 0),3);
        }





        // Combine images and print
        cvtColor(outputImage, outputImage, COLOR_GRAY2BGR);
        std::vector<cv::Mat> matrices = {src, image_copy};
        cv::hconcat( matrices, mask );
        cv::imshow(figureName, mask);
        cv::waitKey(0);

    }
    return 0;
}






