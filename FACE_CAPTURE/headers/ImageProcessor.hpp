#include <iostream>
#include <opencv2/highgui.hpp>

class ImageProcessor{
    cv::Mat crop(cv::Mat frame, int boundingBox[]);
    void save(std::string savePath);
    void archive(std::string savePath, int frameHistory);
    int frameHistory;
};