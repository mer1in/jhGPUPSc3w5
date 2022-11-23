#ifndef VIDEO_READER_H_
#define VIDEO_READER_H_

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
    public:
        VideoReader(std::string file_name);
        ~VideoReader();
        AVFrame* nextFrame();
        AVCodecContext* getCodecCtx(){return dec_ctx;}
        AVFrame* getCleanFrame(){return frame;}
    private:
        AVFormatContext *fmt_ctx = NULL;
        AVStream *video_stream;
        AVCodecContext *dec_ctx = NULL;
        int stream_idx = -1;
        AVFrame *frame = NULL;
        AVFrame *pBGRFrame = NULL;
        AVPacket *pkt = NULL;
        SwsContext* sws_ctx = NULL;
};

#endif // VIDEO_READER_H_ 
