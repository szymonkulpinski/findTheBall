#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>
#include <unistd.h>

void getDescription(std::string *textPostion, cv::Point2f *centers)
{
    std::string temp = static_cast<std::string>("Ball center: ") +
                       std::to_string(static_cast<int>((*centers).x)) +
                       static_cast<std::string>(", ") +
                       std::to_string((static_cast<int>((*centers).y)));
    *textPostion = static_cast<cv::String>(temp);
}

int main(int, char **)
{
    cv::Mat src, blured, srcCopy, imageHSV, outputImage, mask;

    // Get Files
    // TODO: Read automatically from directory use boost or C++17
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

    // Create Window
    cv::String figureName = "Preview";
    cv::namedWindow(figureName, cv::WINDOW_NORMAL);
    cv::resizeWindow(figureName, 600, 600);

    int hmin = 0, hmax = 12; // TODO: what's the best practice: header files, oustisde of main as params?
    int smin = 126, smax = 255;
    int vmin = 1, vmax = 203;
    cv::Scalar lower(hmin, smin, vmin);
    cv::Scalar upper(hmax, smax, vmax);
    int area;
    cv::String textPostion;
    std::vector<std::vector<cv::Point>> contours;

    for (int i = 0; i < fileList.size(); i++)
    {
        cv::String imagePath = folderPath + fileList[i];
        src = cv::imread(imagePath, cv::IMREAD_COLOR);
        if (!src.data)
            throw std::invalid_argument("No image data, incorrect path!");
        srcCopy = src.clone();

        // Get contours
        GaussianBlur(src, blured, cv::Size(11, 11), 11, 11);
        cv::cvtColor(blured, imageHSV, cv::COLOR_BGR2HSV);
        inRange(imageHSV, lower, upper, mask);
        cv::erode(mask, mask, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5)));
        cv::dilate(mask, mask, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(10, 10)));
        findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        std::vector<cv::Point2f> centers(contours.size()); // inits in each loop but with correct size, no need to recopy the array
        std::vector<float> radius(contours.size());

        for (int i = 0; i < contours.size(); i++)
        {
            // Filter out too small objects (noise)
            area = contourArea(contours[i]);
            if (area < 50000)
                continue;

            // Draw on image
            cv::minEnclosingCircle(contours[i], centers[i], radius[i]);
            cv::circle(srcCopy, centers[i], (int)radius[i], cv::Scalar(0, 255, 0), 3);
            getDescription(&textPostion, &centers[i]);
            cv::putText(srcCopy, textPostion, cv::Point(40, 40), cv::FONT_HERSHEY_PLAIN, 3, cv::Scalar(255, 255, 0), 3);
            cv::line(srcCopy, cv::Point(centers[i].x - 20, centers[i].y), cv::Point(centers[i].x + 20, centers[i].y), cv::Scalar(255, 255, 0), 3);
            cv::line(srcCopy, cv::Point(centers[i].x, centers[i].y - 20), cv::Point(centers[i].x, centers[i].y + 20), cv::Scalar(255, 255, 0), 3);
        }
        contours.clear();

        // Combine images and print
        std::vector<cv::Mat> matrices = {src, srcCopy};
        cv::hconcat(matrices, outputImage);
        cv::imshow(figureName, outputImage);
        cv::waitKey(0);
    }
    return 0;
}
