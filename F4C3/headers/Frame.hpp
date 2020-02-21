#include <iostream>
#include <opencv2/highgui.hpp>

class Frame {
    public :
    
    cv::Mat frame;
    int x;
    int y;
    int width;
    int height;
};