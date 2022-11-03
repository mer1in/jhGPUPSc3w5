#include <sstream> 
#include <vector> 
#include <string> 
//#include <FaceDetector.h> 
#include <opencv2/opencv.hpp>  
#include <opencv2/dnn.hpp>

#define FACE_DETECTION_CONFIGURATION "assets/deploy.prototxt"
#define FACE_DETECTION_WEIGHTS "assets/res10_300x300_ssd_iter_140000_fp16.caffemodel"

class FaceDetector { 
public:     
explicit FaceDetector();
    std::vector<cv::Rect> detect_face_rectangles(const cv::Mat &frame);
private:     
/// Face detection network     
cv::dnn::Net network_;     
/// Input image width     
const int input_image_width_;     
/// Input image height     
const int input_image_height_;     
/// Scale factor when creating image blob     
const double scale_factor_;     
/// Mean normalization values network was trained with     
const cv::Scalar mean_values_;     
/// Face detection confidence threshold     
const float confidence_threshold_;  
};


