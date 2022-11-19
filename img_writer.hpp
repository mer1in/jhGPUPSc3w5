#pragma once
#include <opencv2/opencv.hpp> 

class ImgWriter {
    private:
        string file_name;
        int num = 1;
    public:
        ImgWriter(string file_name);
        ~ImgWriter();
        int save();
}
