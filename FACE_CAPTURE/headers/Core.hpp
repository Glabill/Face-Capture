#include <opencv2/highgui.hpp>
#include <iostream>

class Core{

    public:
    
    void run();
    void streamInit();
    void processorInit();

    private:

    bool isRunning;
    std::string savePath;
    std::string archSavePath;
    
};