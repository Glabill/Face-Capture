/*
F4C3
.crp / Gaston Gougeon
https://crp.wtf
2019-2020
*/

#include "../headers/StreamManager.hpp"
#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <stdlib.h>
#include <unistd.h>

void StreamManager::openStream(){

    capWidth = 1280; /// Input width
    capHeight = 720; /// Input height

    rs2::config cfg; /// Create a configuration for the pipeline (non-default profile)
    cfg.enable_stream(RS2_STREAM_COLOR, capWidth, capHeight, RS2_FORMAT_BGR8, 30);

    pipe.start(cfg); /// Pipeline starts streaming

    cv::namedWindow("F4C3", cv::WINDOW_AUTOSIZE ); /// Window construction

    running = true; 
}

void StreamManager::start(){

    /* Camera warmup (for auto exposure) */
    for(int i = 0; i < 30; i++)
    {
        frames = pipe.wait_for_frames();
    }

    std::cout << "streaming..." << std::endl;

    /* Stream Loop */
    while(running){

        frames = pipe.wait_for_frames(); /// Get color frame from realsense pipeline
        rs2::frame color_frame = frames.get_color_frame();

        cv::Mat color(cv::Size(capWidth, capHeight), CV_8UC3, (void*)color_frame.get_data(), cv::Mat::AUTO_STEP); /// Constructing an OpenCV Mat out of the color frame

        if(color.data){

            procFrame = color;

            dispFrame = color.clone();
            
            analyze(); /// Analyzing frame

            
            cv::imshow("F4C3", dispFrame); /// Display bounding box); /// Displaying frame
            cv::waitKey(5); /// Wait for... (ms), needed by openCV to update
        }
    }
}

/* Analyzing frame */
void StreamManager::analyze(){

    /* Loading a model */
    if(!faceDetection.load("/home/gaston/Desktop/CRP/FACE_CAPTURE/datas/haarcascade_frontalface_default.xml")){

        std::cout << "Error : Model is not loaded" << std::endl;
        exit(0);
    }

    std::vector<cv::Rect> faces; /// Storing faces

    if(!procFrame.data){

        std::cout<< "Error : Frame to be analyzed is not loaded" << std::endl;
        return;
    }

    faceDetection.detectMultiScale(procFrame, faces); /// Detecting faces

    /* Drawing bounding box */
    if (faces.size() > 0){

        pt1 = cv::Point(faces[0].x, faces[0].y); /// Detected face top left corner face
        pt2 = cv::Point(faces[0].x + faces[0].height, faces[0].y + faces[0].width); /// Detected face bottom right corner

        pt1_1 = cv::Point(pt1.x, pt1.y - (faces[0].height * 0.3));
        pt2_2 = cv::Point(pt2.x, pt2.y + (faces[0].height * 0.5));

		enum LineTypes
		{
    		FILLED  = -1,
    		LINE_4  = 4,
    		LINE_8  = 8,
    		LINE_AA = 16,
		};

        cv::rectangle(dispFrame, pt1, pt2, cv::Scalar(0, 255, 0), 2, 0, 0);
        cv::rectangle(dispFrame, pt1_1, pt2_2, cv::Scalar(0,255,0), 2, 0, 0);

    }else{

        return;
    }
    
    /* Making sure final image can be cropped out of the current frame */
    if(pt1.x < 0 || pt2.x > capWidth || pt1.y - (faces[0].height * 0.3) < 0 || pt2.y + (faces[0].height * 0.5) > capHeight){

        //std::cout << "Warning : Captured face is not totally inside the frame" << std::endl;

        return;
    }
    
    if(faces[0].height > 100 && faces[0].height < 400){

        pauseStream(); /// Pause the stream

        /* Passing detected face's bounding box to be handled by the Image Processor*/
        validX = faces[0].x;
        validY = pt1_1.y;
        validW = faces[0].width;
        validH = pt2_2.y - pt1_1.y;

    }else{

        return;
    }
    
}


/* Pause the stream */
void StreamManager::pauseStream(){
    running = false;
    processing = true;
}

/* Unpause the stream*/
void StreamManager::unpauseStream(){
    processing = false;
    running = true;
}