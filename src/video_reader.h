#ifndef VIDEO_READER_H_
#define VIDEO_READER_H_

#include <string>
#include "exception.h"

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
    public:
        VideoReader(std::string file_name);
        ~VideoReader();
        AVFrame* nextFrame();
        AVCodecContext* getCodecCtx(){return decCtx;}
        AVFrame* getCleanFrame(){return frame;}
    private:
        AVFormatContext *fmtCtx = NULL;
        AVStream *videoStream;
        AVCodecContext *decCtx = NULL;
        int streamIdx = -1;
        AVFrame *frame = NULL;
        AVFrame *pBGRFrame = NULL;
        AVPacket *pkt = NULL;
        SwsContext* swsCtx = NULL;
};

#endif // VIDEO_READER_H_ 
