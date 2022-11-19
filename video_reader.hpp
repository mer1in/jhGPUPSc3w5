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
        AVFormatContext *fmt_ctx = NULL;
        AVStream *video_stream;
        AVCodecContext *dec_ctx = NULL;
        int video_stream_idx = -1;
        AVFrame *frame = NULL;
        AVPacket *pkt = NULL;
        
    public:
        VideoReader(std::string file_name);
        ~VideoReader();
        AVFrame* nextFrame();
};
