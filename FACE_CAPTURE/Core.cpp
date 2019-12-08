#include "headers/Core.hpp"
#include "headers/StreamManager.hpp"
#include "headers/ImageProcessor.hpp"
#include "headers/Frame.hpp"


void Core::run(){
    isRunning = true;
    streamInit();
}

void Core::streamInit(){
    StreamManager *stmManager = new StreamManager;
    ImageProcessor *imgProcessor = new ImageProcessor;
    imgProcessor->frameHistory = 0;
    Frame *validFrame = new Frame;
    stmManager->openStream();
    if(stmManager->ok){
    std::cout << "Processing frame..." << std::endl;
         validFrame->frame = stmManager->frame;
         validFrame->x = stmManager->validX;
         validFrame->y = stmManager->validY;
         validFrame->width = stmManager->validW;
         validFrame->height = stmManager->validH;
         imgProcessor->save(imgProcessor->crop(validFrame->frame, validFrame->x, validFrame->y, validFrame->width, validFrame->height), "/home/gaston/sambashare/Visage/visage.jpg");
         stmManager->frameSaved();
    }
    
}
