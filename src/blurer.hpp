#include <opencv2/opencv.hpp> 
#include <string>
#include <npp.h>
#include "exception.hpp"
class Blurer {
    public:
        void blur(std::vector<cv::Rect> faces, cv::Mat img);
    private:
        Npp8u *dev_mem = NULL;
};
