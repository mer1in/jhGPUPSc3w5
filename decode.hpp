#include <sstream> 
#include <vector> 
#include <string> 
#include <opencv2/opencv.hpp>  

#include "face_detector.hpp"

#include <npp.h>
#include <nppi_filtering_functions.h>

int handle_video(const char *src_filename, const char *video_dst_filename);
