#include <iostream>
#include <opencv2/opencv.hpp>
#include <librealsense2/rs.hpp>

class StreamManager{
    public:
    bool running;
    bool ok;
    void openStream();
    void start(rs2::pipeline, bool);
    cv::Mat frame;
    void pauseStream();
    void analyze(cv::Mat);
    int frameID;
    void frameSaved();
    int validX;
    int validY;
    int validW;
    int validH;
};