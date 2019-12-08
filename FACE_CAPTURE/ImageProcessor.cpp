#include "headers/ImageProcessor.hpp"
#include "headers/StreamManager.hpp"
#include "headers/Frame.hpp"
#include "headers/Core.hpp"

cv::Mat ImageProcessor::crop(cv::Mat fullFrame, int x, int y, int width, int height){
    return fullFrame(cv::Rect(x, y, width, height));
}

void ImageProcessor::save(cv::Mat frame, std::string savePath){
    cv::imwrite(savePath, frame);
}

void ImageProcessor::archive(std::string sourcePath, int frameHistory){}
