#pragma once
#include <string>
#include "exception.hpp"

extern "C" {
#include <libavutil/opt.h>
#include <libavutil/imgutils.h>
#include <libavutil/samplefmt.h>
#include <libavutil/timestamp.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

class VideoReader {
    private:
        AVFormatContext *fmt_ctx;
        AVCodec *codec;
        AVCodecContext *video_dec_ctx;
        int video_stream_idx = -1;
        
    public:
        VideoReader(std::string file_name);
        AVFrame* nextFrame();
};
