#include <iostream>
#include <opencv2/opencv.hpp>
#include <librealsense2/rs.hpp>

class StreamManager{
    public:

    void openStream();
    void start();
    void pauseStream();
    void analyze(cv::Mat);
    void frameSaved();

    bool running;
    bool processing;
    int frameID;
    int validX;
    int validY;
    int validW;
    int validH;

    int capWidth;
    int capHeight;

    cv::Mat frame;
    rs2::pipeline pipe;
};