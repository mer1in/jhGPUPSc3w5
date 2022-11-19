#pragma once
#include <string>
#include <opencv2/opencv.hpp> 

class ImgWriter {
    private:
        std::string file_name;
        int num = 1;
    public:
        ImgWriter(std::string input_file_name);
        ~ImgWriter(){}
        int save();
}
