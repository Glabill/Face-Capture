#include <opencv2/highgui.hpp>
#include <iostream>
#include "headers/Core.hpp"

int main(int argc, char** argv){
    Core *core = new Core;
    while(core->isRunning){
        core->run();
    }
}