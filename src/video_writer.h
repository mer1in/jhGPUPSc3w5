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

#include "exception.h"

using namespace std;
class VideoWriter {
    public:
        VideoWriter(string fileName);
        void init(AVCodecContext* decCtx, AVFrame* frame);
        void write(AVFrame* frame);
    private:
        string fileName;
        AVFrame *encFrame = NULL;
        AVCodec *codec;
        AVPacket *pkt = NULL;
        AVCodecContext *ctx = NULL;
        SwsContext* swsCtx = NULL;
        FILE *file = NULL;
};

#endif // VIDEO_WRITER_H_
