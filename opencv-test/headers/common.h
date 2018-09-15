/**************************************************
 *                      Include
**************************************************/

//STL
#include <chrono>
#include <thread>
#include <memory>

//CUDA
#include <cuda_runtime.h>

//opencv
#include <opencv2/opencv.hpp>
#include "opencv2/core/cuda.hpp"
#include "opencv2/core/cuda_stream_accessor.hpp"

//G3Log
#include <g3log/g3log.hpp>
#include <g3log/logworker.hpp>

/**************************************************
 *                      definitions
 *************************************************/

#define ALGOS_CV_2D_BEGIN namespace algo{ namespace cv2D {
#define ALGOS_CV_2D_END                                     }}


#ifdef EXPORT_ALGOS_API
    #define EXPORT_ALGOS_CV_2D __declspec(dllexport)
#else
    #define EXPORT_ALGOS_CV_2D __declspec(dllimport)
#endif


