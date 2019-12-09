#include <iostream>
#include <opencv2/opencv.hpp>
#include <librealsense2/rs.hpp>

class StreamManager{
    public:
    
    void openStream();
    void start(rs2::pipeline, bool);
    void pauseStream();
    void analyze(cv::Mat);
    void frameSaved();

    bool running;
    bool ok;
    cv::Mat frame;
    int frameID;
    int validX;
    int validY;
    int validW;
    int validH;
};