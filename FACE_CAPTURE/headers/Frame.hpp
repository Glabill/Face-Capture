#include <iostream>
#include <opencv2/highgui.hpp>

class Frame {
    public:
    Frame(cv::Mat image, int x, int y, int width, int height);
};