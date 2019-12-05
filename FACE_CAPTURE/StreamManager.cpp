#include "headers/StreamManager.hpp"
#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <stdlib.h>
#include <unistd.h>



bool StreamManager::openStream(){
    // Construct a pipeline to abstract the device
    rs2::pipeline pipe;

    // Create a configuration for the pipeline with a non-default profile
    rs2::config cfg;

    // Add stream to configuration
    cfg.enable_stream(RS2_STREAM_COLOR, 640, 360, RS2_FORMAT_BGR8, 30);

    // Pipeline starts streaming
    pipe.start(cfg);

    // Window construction
    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE );

    //Start camera streaming
    this->start(pipe);

    return true;
}

void StreamManager::start(rs2::pipeline pipe){

    // Camera warmup (exposure, W balance)
    rs2::frameset frames;
    for(int i = 0; i < 30; i++)
    {
        frames = pipe.wait_for_frames();
    }

    // Getting frames
    while(true){
    frames = pipe.wait_for_frames();
    rs2::frame color_frame = frames.get_color_frame();
    cv::Mat color(cv::Size(640, 360), CV_8UC3, (void*)color_frame.get_data(), cv::Mat::AUTO_STEP);
    this->frame = color;
    analyze(this->frame);
    cv::imshow("Display Image", this->frame);
    cv::waitKey(100);
    std::cout << "\n -----------------";
    }
}

void StreamManager::analyze(cv::Mat frame){
    cv::CascadeClassifier faceDetection;
    if(!faceDetection.load("/home/gaston/Desktop/CRP/FACE_CAPTURE/datas/haarcascade_frontalface_default.xml")){
        std::cout << "\n Model is not loaded" << std::endl;
        exit(0);
    }

    std::vector<cv::Rect> faces;

    //Detecting faces
    faceDetection.detectMultiScale(frame, faces);

    for(int i = 0; i < faces.size(); i++){
        cv::Point pt1(faces[i].x, faces[i].y);
        cv::Point pt2(faces[i].x + faces[i].height, faces[i].y + faces[i].width);
        cv::rectangle(frame, pt1, pt2, cv::Scalar(0, 0, 255), 2, 8, 0);
        std::cout<< "Detected face size : " << faces[i].height << std::endl;
    }
}


void StreamManager::closeStream(){}