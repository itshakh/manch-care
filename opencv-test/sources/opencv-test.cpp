#include "../headers/common.h"
#include "../headers/image.h"


#include <stdio.h>


int main(int argc, char** argv )
{
    const std::string directory = "../logs";


    const std::string name = "opencv-test";
    auto worker = g3::LogWorker::createLogWorker();
    auto handle = worker->addDefaultLogger(name, directory);
    g3::initializeLogging(worker.get());

    cv::VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    uint32_t nOfFrames = 5;
    std::vector<cv::Mat> frames(nOfFrames);
    cv::Mat output;

    cv::namedWindow("output",1);
    auto frameCounter = 0;
    while(1)
    {

        /** 
         * Calculation with the buffered images before capturing further
        */

        LOG(INFO) << "Capturing frame " << frameCounter;

        try{
            cap >> frames[frameCounter % frames.size()];
            cv::imshow("output", frames.at(frameCounter % frames.size())); 
            cv::waitKey(1);
        }
       
        catch(cv::Exception &e)
        {
            std::cout << e.what() << std::endl;
        }
        
        frameCounter++;    
    }
      // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
