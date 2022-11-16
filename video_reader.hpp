#pragma once
#include <string>
#include "exception.hpp"

extern "C" {
#include <libavutil/samplefmt.h>
#include <libswscale/swscale.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

class VideoReader {
    private:
        
    public:
        VideoReader(std::string file_name);
        AVFrame* nextFrame();
};
