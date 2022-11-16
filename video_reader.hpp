#pragma once
#include <string>

extern "C" {
#include <libswscale/swscale.h>
}

class VideoReader {
    private:
        
    public:
        VideoReader(std::string file_name);
        AVFrame* nextFrame();
};
