# Find the ball
Goal of this C++11 project is to find a basketball ball in an image using classical computer vision methods that is without usage of machine learning in any form. 


# Results

https://user-images.githubusercontent.com/39861049/161453870-5fbd49fa-f95f-4c62-9dbb-cb1ff419a38f.mov


# Setup
* Adjust the absolut `folderPath` in `main.cpp` 
 

## Prerequesitions
* [OpenCV library](https://opencv.org/) (tested for 4.5.5 on macOS)
* [CMake](https://cmake.org/)



# Other
 #### Known problems and reasons why detection cannot work as good as using machine learning
 * occlussion
 * background has the same color as the ball

#### Methods to be try out for the detection:



- [x]  Canny Edge detector (standalone doesn't work well) 
 
- [x]  HSV Color filtering (works well enough for provided images)
 
- [ ] SIFT keypoints
 
- [ ]  Template matching algorithm

 ### Future TODOs: 
- [ ]  Expand to ball tracking
 
- [ ]  Try out Kalman filter 

- [ ]  Try out optical flow
