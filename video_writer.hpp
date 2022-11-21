#include <string>
#include <opencv2/opencv.hpp> 
#include "exception.hpp"
extern "C" {
#include <libavutil/opt.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

using namespace std;
class VideoWriter {
    public:
        VideoWriter(string file_name);
        void init(AVCodecContext* dec_ctx, AVFrame* frame);
        void write(AVFrame* frame);
    private:
        string file_name;
        AVCodec *codec;
        AVPacket *pkt = NULL;
        AVCodecContext *ctx = NULL;
        FILE *file = NULL;
};
