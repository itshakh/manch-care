cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
project( opencv-test )

find_package(CUDA)
find_package( OpenCV REQUIRED )

include_directories( 

    ${OpenCV_INCLUDE_DIRS} 
    )

CUDA_ADD_EXECUTABLE( opencv-test "sources/opencv-test.cpp" )

add_definitions("-DEXPORT_ALGOS_API")

target_link_libraries( opencv-test 
${OpenCV_LIBS} 
"libg3logger.so"
)


