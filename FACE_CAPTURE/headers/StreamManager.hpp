#include <iostream>
#include <opencv2/opencv.hpp>
#include <librealsense2/rs.hpp>

class StreamManager{
    public:
    bool openStream();
    void start(rs2::pipeline, bool);
    cv::Mat frame;
    void closeStream();
    void analyze(cv::Mat);
    cv::Mat saveFrame();
};