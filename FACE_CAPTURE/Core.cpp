#include "headers/Core.hpp"
#include "headers/StreamManager.hpp"
#include <chrono>
#include <thread>
using namespace std::this_thread;
using namespace std::chrono;

void Core::run(){
    isRunning = true;
    streamInit();
}

void Core::streamInit(){
    StreamManager *stmManager = new StreamManager;
    stmManager->openStream();
    //sleep_for(1s);
}

void Core::processorInit(){
}