#include "headers/Core.hpp"
#include "headers/StreamManager.hpp"
#include "headers/ImageProcessor.hpp"
#include "headers/Frame.hpp"


void Core::run(){

    isRunning = true;
    streamInit(); /// Initializing stream
}

void Core::streamInit(){

    std::cout << "Stream Initialization" << std::endl;

    savePath = "/home/gaston/sambashare/face.png"; /// Path to where the output will be saved - image compression format defined by the file extension

    StreamManager stmManager; /// Create Stream Manager
    ImageProcessor imgProcessor; /// Create Image Processor

    imgProcessor.frameHistory = 0;

    stmManager.openStream(); /// Open the stream

    /* Global loop */
    while(isRunning){

        stmManager.start(); /// Start streaming

        /* Processing frame - cropping, saving... */
        if(stmManager.processing){
            std::cout << "Processing frame..." << std::endl;

            imgProcessor.crop(stmManager.frame, stmManager.validX, stmManager.validY, stmManager.validW, stmManager.validH);
            imgProcessor.save(imgProcessor.frame, savePath);
            stmManager.unpauseStream();
        }
    }
}


