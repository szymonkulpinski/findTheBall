#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv; 

    // int hmin = 0, hmax = 19; 
    // int smin = 110, smax = 240;
    // int vmin = 153, vmax = 255;

int hmin = 7, hmax = 71; 
int smin = 48, smax = 158;
int vmin = 102, vmax = 255;
cv::Mat image, imageHSV, outputImage, mask, image3;



static void updateFigure(int, void*){
        cv::Scalar lower (hmin, smin, vmin);
        cv::Scalar upper (hmax, smax, vmax);
        std::cout << "lower" << lower <<  std::endl;
        std::cout << "upper" << upper << std::endl;
        inRange(image, lower, upper, outputImage);
        cvtColor(outputImage, image3, COLOR_GRAY2BGR);
        std::vector<cv::Mat> matrices = {image, image3};
        cv::hconcat( matrices, mask );
        cv::imshow("Trackbars",mask);

}



int main(int, char**) {
    // cv::String imagePath = "/Users/szymon/Documents/coding/Projects/findTheBall2/usa.jpeg";
    // cv::String imagePath = "/Users/szymon/Documents/coding/Projects/findTheBall2/IMG_1317.jpg";
    cv::String imagePath = "/Users/szymon/Documents/coding/Projects/findTheBall2/Photos BBALL/IMG_1344_test.jpg";
    // cv::Mat image, imageHSV, outputImage, mask, image3;
    // cv::Mat outputImage;
    image = cv::imread(imagePath, cv::IMREAD_COLOR);
    cv::Mat image2 = cv::imread(imagePath, cv::IMREAD_COLOR);

    if (!image.data)
        throw std::invalid_argument("No image data, incorrect path!");
    cv::cvtColor(image, imageHSV, cv::COLOR_BGR2HSV);
    // cv::cvtColor(image, imageHSV, cv::COLOR_BGR2GRAY);




    namedWindow("Trackbars");
    int max = 255;
    createTrackbar("Hue Min", "Trackbars", &hmin, max, updateFigure);
    createTrackbar("Hue Max", "Trackbars", &hmax, max, updateFigure);
    createTrackbar("Saturation Min", "Trackbars", &smin, max, updateFigure);
    createTrackbar("Saturation Max", "Trackbars", &smax, max, updateFigure);
    createTrackbar("Value Min", "Trackbars", &vmin, max, updateFigure);
    createTrackbar("Value Max", "Trackbars", &vmax, max, updateFigure);
    // while (cv::waitKey(0) == -1){

    // }
    // while(true){

    //     cv::waitKey(0);
    // }
    return 0;
}






