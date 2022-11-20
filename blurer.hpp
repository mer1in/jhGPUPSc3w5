#include <opencv2/opencv.hpp> 
class Blurer {
    public:
        void blur(std::vector<cv::Rect> faces, cv::Mat img);
};
