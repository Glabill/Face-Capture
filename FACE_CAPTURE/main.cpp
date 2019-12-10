#include <opencv2/highgui.hpp>
#include <iostream>
#include "headers/Core.hpp"

int main(int argc, char** argv){

    Core core; /// Core object, runs everything else

    std::cout << "Hello" << std::endl;
    core.run(); /// Running core
}