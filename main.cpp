#include <opencv2/opencv.hpp>

static const std::string folderPath = "/Users/szymon/Documents/coding/Projects/findTheBall2/images/test/";


cv::String getDescription(const cv::Point2f& centers)
{
    std::string temp = static_cast<std::string>("Ball center: ") +
                       std::to_string(static_cast<int>(centers.x)) +
                       static_cast<std::string>(", ") +
                       std::to_string((static_cast<int>(centers.y)));
    return static_cast<cv::String>(temp);
}

int main(int, char **)
{   
    int area;
    cv::Mat src, blured, srcCopy, imageHSV, outputImage, mask;
    std::vector<std::vector<cv::Point>> contours;

    const cv::Scalar greenColor = cv::Scalar(0, 255, 0);
    const cv::Scalar turquoiseColor = cv::Scalar(255, 255, 0);
    const int hmin = 0, hmax = 12; 
    const int smin = 126, smax = 255;
    const int vmin = 1, vmax = 203;
    const cv::Scalar lower(hmin, smin, vmin);
    const cv::Scalar upper(hmax, smax, vmax);
    const int minBallArea = 50000;

    // Get Files
    // TODO: Read automatically from directory use boost or C++17 (caused so far some weird problems on the M1 Mac)
    std::vector<std::string> fileList;
    fileList.reserve(11);
    fileList.emplace_back("IMG_1354.jpg");
    fileList.emplace_back("IMG_1355.jpg");
    fileList.emplace_back("IMG_1356.jpg");
    fileList.emplace_back("IMG_1357.jpg");
    fileList.emplace_back("IMG_1358.jpg");
    fileList.emplace_back("IMG_1359.jpg");
    fileList.emplace_back("IMG_1360.jpg");
    fileList.emplace_back("IMG_1361.jpg");
    fileList.emplace_back("IMG_1362.jpg");
    fileList.emplace_back("IMG_1363.jpg");
    fileList.emplace_back("IMG_1364.jpg");

    // Create Window
    cv::String figureName = "Preview";
    cv::namedWindow(figureName, cv::WINDOW_NORMAL);
    cv::resizeWindow(figureName, 600, 600);

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
            if (area < minBallArea)
                continue;

            // Draw on image
            cv::minEnclosingCircle(contours[i], centers[i], radius[i]);
            cv::circle(srcCopy, centers[i], (int)radius[i], greenColor, 3);
            cv::putText(srcCopy, getDescription(centers[i]), cv::Point(40, 40), cv::FONT_HERSHEY_PLAIN, 3, turquoiseColor, 3);
            cv::line(srcCopy, cv::Point(centers[i].x - 20, centers[i].y), cv::Point(centers[i].x + 20, centers[i].y), turquoiseColor, 3);
            cv::line(srcCopy, cv::Point(centers[i].x, centers[i].y - 20), cv::Point(centers[i].x, centers[i].y + 20), turquoiseColor, 3);
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
