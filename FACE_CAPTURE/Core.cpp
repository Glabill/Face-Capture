#include "headers/Core.hpp"
#include "headers/StreamManager.hpp"
#include "headers/ImageProcessor.hpp"
#include "headers/Frame.hpp"


void Core::run(){
    isRunning = true;
    streamInit();
}

void Core::streamInit(){
    StreamManager stmManager;
    ImageProcessor imgProcessor;
    imgProcessor.frameHistory = 0;
    stmManager.openStream();
    if(stmManager.ok){
        imgProcessor.crop(stmManager.frame, stmManager.validX, stmManager.validY, stmManager.validW, stmManager.validH);
        std::cout << "Processing frame..." << std::endl;
        imgProcessor.save(imgProcessor.frame, "home/gaston/sambashare/Visage/visage.jpg");
        stmManager.frameSaved();
    }
    
}
