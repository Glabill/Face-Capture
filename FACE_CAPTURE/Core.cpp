/*
F4C3
.crp / Gaston Gougeon
https://crp.wtf
2019-2020
*/

#include "headers/Core.hpp"
#include "headers/StreamManager.hpp"
#include "headers/ImageProcessor.hpp"


void Core::run(){

    StreamManager stmManager;
    ImageProcessor imgProcessor;

    isRunning = true;

    streamInit(); /// Initializing stream
    processorInit(); /// Initializing processor

    stmManager.openStream(); /// Open the stream

    /* Global loop */
    while(isRunning){

        stmManager.start(); /// Start streaming

        /* Processing frame - cropping, saving... */
        if(stmManager.processing){
            std::cout << "Processing frame..." << std::endl;

            imgProcessor.crop(stmManager.procFrame, stmManager.validX, stmManager.validY, stmManager.validW, stmManager.validH);
            imgProcessor.save(imgProcessor.frame, savePath, archSavePath);

            stmManager.unpauseStream(); /// Restart the stream
        }
    }
}

void Core::streamInit(){

    std::cout << "Stream Manager Initialization" << std::endl;
}

void Core::processorInit(){

    std::cout << "Image Processor Initialization" << std::endl;
    savePath = "./output/face.png"; /// Path to where the output will be saved - image compression format defined by the file extension
    archSavePath = "./output/arch/"; /// Path to where the archived images will be saved - don't precise file name or extension here
}


