#include "headers/Core.hpp"
#include "headers/StreamManager.hpp"
#include "headers/ImageProcessor.hpp"
#include "headers/Frame.hpp"


void Core::run(){
    isRunning = true;
    streamInit();
}

void Core::streamInit(){
    std::cout << "Stream Initialization" << std::endl;
    savePath = "/home/gaston/sambashare/face.png";

    StreamManager stmManager;
    ImageProcessor imgProcessor;

    imgProcessor.frameHistory = 0;

    stmManager.openStream();

    while(isRunning){

        stmManager.start(); 

        if(stmManager.processing){
            std::cout << "Processing frame..." << std::endl;

            imgProcessor.crop(stmManager.frame, stmManager.validX, stmManager.validY, stmManager.validW, stmManager.validH);
            imgProcessor.save(imgProcessor.frame, savePath);
            stmManager.frameSaved();
        }
    }
}


