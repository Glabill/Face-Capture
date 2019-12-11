#include <iostream>
#include <opencv2/opencv.hpp>
#include <librealsense2/rs.hpp>

class StreamManager{
    
    public:

    void openStream();
    void start();
    void pauseStream();
    void analyze();
    void unpauseStream();

    bool running;
    bool processing;
    int frameID;
    int validX;
    int validY;
    int validW;
    int validH;

    int capWidth;
    int capHeight;

    cv::Mat procFrame;

    private:

    cv::Point pt1;
    cv::Point pt2;
    rs2::pipeline pipe; /// Construct a pipeline to abstract the device
    rs2::frameset frames;
    cv::CascadeClassifier faceDetection; /// Creating a Cascade Classifier
    std::vector<cv::Rect> faces;    /// Storing faces
};