#include "headers/Core.hpp"
#include "headers/StreamManager.hpp"

void Core::run(){

    this->isRunning = true;

    this->streamInit();
    // std::string imgName;
    // std::cout << "Enter image path ";
    // std::cin >> imgName;
    // CamFlow *camFlow = new CamFlow;
    // camFlow->displayImg(imgName);
    // delete camFlow;
}

void Core::streamInit(){
    StreamManager *stmManager = new StreamManager;
    stmManager->openStream();
}

void Core::processorInit(){
    
}