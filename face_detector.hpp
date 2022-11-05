#include <vector> 
class FaceDetector { 
    public:     
        explicit FaceDetector();
        std::vector<cv::Rect> detect_face_rectangles(const cv::Mat &frame);
    private:     
        cv::dnn::Net network_;     
        const int input_image_width_;     
        const int input_image_height_;     
        const double scale_factor_;     
        const cv::Scalar mean_values_;     
        const float confidence_threshold_;  
};

#define FACE_DETECTION_CONFIGURATION "assets/deploy.prototxt"
#define FACE_DETECTION_WEIGHTS "assets/res10_300x300_ssd_iter_140000_fp16.caffemodel"
