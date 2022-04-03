# Find the basketball ball
Goal of this project is to find a basketball ball in an image using classical computer vision methods that is without usage of machine learning in any form. 

# Results
TODO: add video: 

# Setup

## Prerequesitions
* [OpenCV library] (https://opencv.org/) (tested for 4.5.5 on macOS)



# Other
 #### Known problems and reasons why detection cannot work as good as using machine learning
 * occlussion
 * background has the same color as the ball

#### Methods to be try out for the detection:
 [x] Canny Edge detector (standalone doesn't work well) 
 [x] HSV Color filtering (works well enough for provided images)
 [ ] SIFT keypoints
 [ ] Template matching algorithm

 ### Future TODOs: 
 [ ] Expand to ball tracking
    [ ] Try out Kalman filter 
    [ ] Try out optical flow
