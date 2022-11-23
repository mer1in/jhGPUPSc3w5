#ifndef IMG_WRITER_H_
#define IMG_WRITER_H_
#include <string>
#include <opencv2/opencv.hpp> 

using namespace std;

class ImgWriter {
    private:
        string file_name;
        int num = 1;
        bool enabled = false;
    public:
        ImgWriter(string input_file_name, string suffix);
        ~ImgWriter(){}
        void save(cv::Mat img);
};

#endif // IMG_WRITER_H_
