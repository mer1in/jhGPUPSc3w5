#include "face_detector.h"

FaceDetector::FaceDetector() :
    confidenceThreshold(0.5),
    inputImageHeight(300),
    inputImageWidth(300),
    scaleFactor(1.0),
    meanValues({104., 177.0, 123.0})
{
    network = cv::dnn::readNetFromCaffe(FACE_DETECTION_CONFIGURATION, FACE_DETECTION_WEIGHTS);
    if (network.empty()) {
        std::ostringstream ss;
        ss << "Failed to load network with the following settings:\n"
            << "Configuration: " + std::string(FACE_DETECTION_CONFIGURATION) + "\n"            
            << "Binary: " + std::string(FACE_DETECTION_WEIGHTS) + "\n";
        throw std::invalid_argument(ss.str());
    }
}

std::vector<cv::Rect> FaceDetector::detect(const cv::Mat &frame)
{
    cv::Mat inputBlob = cv::dnn::blobFromImage(frame, scaleFactor,
        cv::Size(inputImageWidth, inputImageHeight), meanValues,
        false, false);
    network.setInput(inputBlob, "data");
    cv::Mat detection = network.forward("detection_out");
    cv::Mat detectionMatrix(detection.size[2], detection.size[3], CV_32F,
        detection.ptr<float>());
    std::vector<cv::Rect> faces;

    for (int i = 0; i < detectionMatrix.rows; i++)
    {
        float confidence = detectionMatrix.at<float>(i, 2);
        if (confidence < confidenceThreshold)
            continue;
        
        int xLeftBottom = static_cast<int>(
            detectionMatrix.at<float>(i, 3) * frame.cols);

        int yLeftBottom = static_cast<int>(
            detectionMatrix.at<float>(i, 4) * frame.rows);

        int xRightTop = static_cast<int>(
            detectionMatrix.at<float>(i, 5) * frame.cols);

        int yRightTop = static_cast<int>(
            detectionMatrix.at<float>(i, 6) * frame.rows);

        faces.emplace_back(xLeftBottom, yLeftBottom,
            (xRightTop - xLeftBottom), (yRightTop - yLeftBottom));
    }

    return faces;
}
