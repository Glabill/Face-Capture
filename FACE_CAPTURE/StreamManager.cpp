#include "headers/StreamManager.hpp"
#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <stdlib.h>
#include <unistd.h>

void StreamManager::openStream(){

    capWidth = 1280;
    capHeight = 720;
    //frameID = 0;
     /// Construct a pipeline to abstract the device

    rs2::config cfg; /// Create a configuration for the pipeline (non-default profile)
    cfg.enable_stream(RS2_STREAM_COLOR, capWidth, capHeight, RS2_FORMAT_BGR8, 30);

    pipe.start(cfg); /// Pipeline starts streaming

    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE ); /// Window construction
    running = true;
    /// Start camera streaming

    
}

void StreamManager::start(){

    rs2::frameset frames;

    /* Camera warmup (for auto exposure) */
    for(int i = 0; i < 30; i++)
    {
        frames = pipe.wait_for_frames();
    }

    std::cout << "StreamManager - streaming..." << std::endl;

    /* Stream Loop */
    while(running){

        frames = pipe.wait_for_frames(); /// Get color frame from realsense pipeline
        rs2::frame color_frame = frames.get_color_frame();

        cv::Mat color(cv::Size(capWidth, capHeight), CV_8UC3, (void*)color_frame.get_data(), cv::Mat::AUTO_STEP); // Constructing an OpenCV Mat out of the color frame

        if(color.data){
            frame = color;
            analyze(frame);
        }
         /// Analyzing frame
        
        cv::imshow("Display Image", frame); /// Displaying frame
        cv::waitKey(1);

        //std::cout << "\n -----------------";
    }
}

/* Analyzing frame */
void StreamManager::analyze(cv::Mat frame){

    cv::CascadeClassifier faceDetection; /// Creating a Cascade Classifier

    /* Loading a model */
    if(!faceDetection.load("/home/gaston/Desktop/CRP/FACE_CAPTURE/datas/haarcascade_frontalface_default.xml")){
        std::cout << "Error : Stream Manager - Model is not loaded" << std::endl;
        exit(0);
    }

    std::vector<cv::Rect> faces;

    if(!frame.data){
        std::cout<< "Error : Stream Manager - Frame to be analyzed is not loaded" << std::endl;
        return;
    }

    faceDetection.detectMultiScale(frame, faces); /// Detecting faces

    /* Drawing bounding box */
    //for(int i = 0; i < faces.size(); i++){
    cv::Point pt1(faces[0].x, faces[0].y); /// Detected face top left corner face
    cv::Point pt2(faces[0].x + faces[0].height, faces[0].y + faces[0].width); /// Detected face bottom right corner

    if(pt1.x < 0 || pt2.x > capWidth || pt1.y - (faces[0].height * 0.3) < 0 || pt2.y + (faces[0].height * 0.3) > capHeight){
        std::cout << "Warning : Stream Manager - Captured face is not totally inside the frame" << std::endl;
        return;
    }
    //cv::rectangle(frame, pt1, pt2, cv::Scalar(0, 0, 255), 2, 8, 0);
    else if(faces[0].height > 100 && faces[0].height < 400){
        
        pauseStream();
        validX = faces[0].x;
        validY = faces[0].y;
        validW = faces[0].width;
        validH = faces[0].height;
    }
    
    else
    {
        return;
    }
        //std::cout<< "Detected face size : " << faces[i].height << std::endl;
    //}
}



void StreamManager::pauseStream(){

    running = false;
    processing = true;
}

void StreamManager::frameSaved(){
    
    processing = false;
    running = true;
    
    
}