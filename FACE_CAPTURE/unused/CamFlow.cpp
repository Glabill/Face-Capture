#include <opencv2/highgui.hpp>
#include <iostream>
#include "unused/CamFlow.hpp"

// Get image data
bool CamFlow::getData(std::string imgName)
{
    // Write image into OpenCV material
    this->image = cv::imread(imgName , CV_LOAD_IMAGE_COLOR);

    // Error handling
    if(! this->image.data ){
        std::cout << "ERROR! Could not open or find image" << std::endl;
        return false;
    } else {
        return true;
    }
}

// Display image in a new window
void CamFlow::displayImg(std::string imgName)
{
    // Error handling
    if (! this->getData(imgName)){
       std::cout << "ERROR! Could not display image" << std::endl;
        return;
    }

    // Display image on a new named window
    cv::namedWindow( "Display window", cv::WINDOW_AUTOSIZE );
    cv::imshow( "Display window", this->image );
    cv::waitKey(0);
}



    



