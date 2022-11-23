#ifndef VIDEO_WRITER_H_
#define VIDEO_WRITER_H_

#include <string>
#include <opencv2/opencv.hpp> 

extern "C" {
#include <libavutil/opt.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

#include "exception.hpp"

using namespace std;
class VideoWriter {
    public:
        VideoWriter(string file_name);
        void init(AVCodecContext* dec_ctx, AVFrame* frame);
        void write(AVFrame* frame);
    private:
        string file_name;
        AVFrame *enc_frame = NULL;
        AVCodec *codec;
        AVPacket *pkt = NULL;
        AVCodecContext *ctx = NULL;
        SwsContext* sws_ctx = NULL;
        FILE *file = NULL;
};

#endif // VIDEO_WRITER_H_