#include "headers/StreamManager.hpp"
#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <stdlib.h>
#include <unistd.h>



bool StreamManager::openStream(){

    rs2::pipeline pipe; // Construct a pipeline to abstract the device

    rs2::config cfg; // Create a configuration for the pipeline (non-default profile)
    cfg.enable_stream(RS2_STREAM_COLOR, 640, 360, RS2_FORMAT_BGR8, 30);

    pipe.start(cfg); // Pipeline starts streaming

    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE ); // Window construction

    this->start(pipe, this); //Start camera streaming

    return true;
}

void StreamManager::start(rs2::pipeline pipe, bool open){

    /* Camera warmup (for auto exposure) */
    rs2::frameset frames;
    for(int i = 0; i < 30; i++)
    {
        frames = pipe.wait_for_frames();
    }

    
    /* Stream Loop */
    while(open){

        frames = pipe.wait_for_frames(); // Get color frame from realsense pipeline
        rs2::frame color_frame = frames.get_color_frame();

        cv::Mat color(cv::Size(640, 360), CV_8UC3, (void*)color_frame.get_data(), cv::Mat::AUTO_STEP); // Constructing an OpenCV Mat out of the color frame
        this->frame = color;

        analyze(this->frame); // Analyzing frame
        
        cv::imshow("Display Image", this->frame); // Displaying frame
        cv::waitKey(100);
        std::cout << "\n -----------------";
    }
}

/* Analyzing frame */
void StreamManager::analyze(cv::Mat frame){

    cv::CascadeClassifier faceDetection; // Creating a Cascade Classifier

    /* Loading a model */
    if(!faceDetection.load("/home/gaston/Desktop/CRP/FACE_CAPTURE/datas/haarcascade_frontalface_default.xml")){
        std::cout << "\n Model is not loaded" << std::endl;
        exit(0);
    }

    std::vector<cv::Rect> faces;
    faceDetection.detectMultiScale(frame, faces); // Detecting faces

    /* Drawing bounding box */
    for(int i = 0; i < faces.size(); i++){
        cv::Point pt1(faces[i].x, faces[i].y);
        cv::Point pt2(faces[i].x + faces[i].height, faces[i].y + faces[i].width);
        cv::rectangle(frame, pt1, pt2, cv::Scalar(0, 0, 255), 2, 8, 0);
        //std::cout<< "Detected face size : " << faces[i].height << std::endl;
    }
}


void StreamManager::closeStream(){
    delete this;
}