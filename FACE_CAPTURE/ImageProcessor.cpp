/*
F4C3
.crp / Gaston Gougeon
https://crp.wtf
2019-2020
*/

#include "headers/ImageProcessor.hpp"
#include "headers/StreamManager.hpp"
#include "headers/Frame.hpp"
#include "headers/Core.hpp"

void ImageProcessor::crop(cv::Mat fullFrame, int x, int y, int width, int height){

    if(!fullFrame.data){
        std::cout << "Error : Source image not loaded" << std::endl;
        return;
    }

    frame = fullFrame(cv::Rect(x, y, width, height)); /// Cropping the current frame
}

void ImageProcessor::save(cv::Mat frame, std::string savePath, std::string archSavePath){

    std::string calcArchSavePath = std::string(archSavePath) + "face_archive_" + std::to_string(frameHistory) + ".png";

    if(!frame.data){
        std::cout << "Error : Cropped image not loaded" << std::endl;
        return;
    }
    else
    {
        cv::imwrite(savePath, frame); /// Saving the cropped frame

        cv::imwrite(calcArchSavePath, frame); /// Archiving frame

        std::cout << "Frame saved" << std::endl;

        frameHistory ++;
    }
}
