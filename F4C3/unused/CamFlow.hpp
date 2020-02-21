#include <opencv2/highgui.hpp>
#include <iostream>

class CamFlow {
    public:
    bool getData(std::string imgName);
    void displayImg(std::string imgName);

    private:
    cv::Mat image;
    int deviceID;
    std::string imgName;
};