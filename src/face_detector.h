#ifndef FACE_DETECTOR_H_
#define FACE_DETECTOR_H_

#include <vector> 
#include <opencv2/dnn.hpp>

class FaceDetector { 
    public:     
        explicit FaceDetector();
        std::vector<cv::Rect> detect(const cv::Mat &frame);
    private:     
        cv::dnn::Net network;     
        const int inputImageWidth;     
        const int inputImageHeight;     
        const double scaleFactor;     
        const cv::Scalar meanValues;     
        const float confidenceThreshold;  
};

#define FACE_DETECTION_CONFIGURATION "assets/deploy.prototxt"
#define FACE_DETECTION_WEIGHTS "assets/res10_300x300_ssd_iter_140000_fp16.caffemodel"

#endif // FACE_DETECTOR_H_
