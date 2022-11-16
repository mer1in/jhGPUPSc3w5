#pragma once
#include <string>
#include "exception.hpp"

extern "C" {
#include <libswscale/swscale.h>
}

class VideoReader {
    private:
        
    public:
        VideoReader(std::string file_name);
        AVFrame* nextFrame();
};
