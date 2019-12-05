#include <iostream>
#include <opencv2/opencv.hpp>
#include <librealsense2/rs.hpp>

class StreamManager{
    public:
    bool running;
    bool openStream();
    void start(rs2::pipeline, bool);
    cv::Mat frame;
    void closeStream();
    void analyze(cv::Mat);
    void validFrame(cv::Mat, int x, int y, int width, int height, int frameID);
    int frameID;
};