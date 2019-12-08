#include <opencv2/highgui.hpp>
#include <iostream>
#include "headers/Core.hpp"

int main(int argc, char** argv){
    Core *core = new Core;
    std::cout << "Hello" << std::endl;
    while(core->isRunning){
        core->run();
    }
}