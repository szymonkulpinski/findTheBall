#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv; 

// cv::Mat combineHorizontally(Mat matSrc, Mat matGray){
//     Mat matDst(Size(matSrc.cols*2,matSrc.rows),matSrc.type(),Scalar::all(0));
// Mat matRoi = matDst(Rect(0,0,matSrc.cols,matSrc.rows));
// matSrc.copyTo(matRoi);
// matRoi = matDst(Rect(matSrc.cols,0,matSrc.cols,matSrc.rows));
// matGray.copyTo(matRoi);
// }


int main(int, char**) {
    // cv::String imagePath = "/Users/szymon/Documents/coding/Projects/findTheBall2/usa.jpeg";
    // cv::String imagePath = "/Users/szymon/Documents/coding/Projects/findTheBall2/IMG_1317.jpg";
    cv::String imagePath = "/Users/szymon/Documents/coding/Projects/findTheBall2/Photos BBALL/IMG_1344_test.jpg";
    cv::Mat imageHSV, outputImage, mask;
    // cv::Mat outputImage;
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);
    if (!image.data)
        throw std::invalid_argument("No image data, incorrect path!");
    cv::cvtColor(image, imageHSV, cv::COLOR_BGR2HSV);
    // cv::cvtColor(image, imageHSV, cv::COLOR_BGR2GRAY);

    // std::vector<cv::Mat> matrices = {image, imageHSV};
    // cv::hconcat( matrices, outputImage );

    // hconcat(image,imageHSV,outputImage);
    // int hmin = 0, hmax = 19; 
    // int smin = 110, smax = 240;
    // int vmin = 153, vmax = 255;

    int hmin = 7, hmax = 71; 
    int smin = 48, smax = 158;
    int vmin = 102, vmax = 255;



//         mein : 0
//         lower[0, 0, 47, 0]
// upper[36, 255, 255, 0]



    namedWindow("Trackbars");
    createTrackbar("Hue Min", "Trackbars", &hmin, 255);
    createTrackbar("Hue Max", "Trackbars", &hmax, 255);
    createTrackbar("Saturation Min", "Trackbars", &smin, 255);
    createTrackbar("Saturation Max", "Trackbars", &smax, 255);
    createTrackbar("Value Min", "Trackbars", &vmin, 255);
    createTrackbar("Value Max", "Trackbars", &vmax, 255);
    // while (cv::waitKey(0) == -1){

    // }
    while(true){
        cv::Scalar lower (hmin, smin, vmin);
        cv::Scalar upper (hmax, smax, vmax);
        std::cout << "lower" << lower <<  std::endl;
        std::cout << "upper" << upper << std::endl;

        // 
        // lower[7, 48, 102, 0]
        // upper[71, 158, 255, 0]

        inRange(image, lower, upper, outputImage);

        // cv::Canny(outputImage,image);
        // cv::imshow("imageHSV", imageHSV);
        cv::imshow("image", image);
        cv::imshow("outputImage", outputImage);
        cv::waitKey(0);
    }
    return 0;
}






