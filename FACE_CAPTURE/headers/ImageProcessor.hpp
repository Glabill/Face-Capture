#include <iostream>
#include <opencv2/highgui.hpp>

class ImageProcessor{
    
    public :

    void crop(cv::Mat frame, int x, int y, int width, int height);
    void save(cv::Mat frame, std::string savePath, std::string archSavePath);
    cv::Mat frame;

    private :

    int frameHistory = 0;
    
};