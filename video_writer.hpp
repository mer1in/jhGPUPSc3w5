#include <string>
#include <opencv2/opencv.hpp> 
#include "exception.hpp"
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

using namespace std;
class VideoWriter{
    public:
        VideoWriter(string file_name);
        void init(AVCodecContext* ctx, AVFrame* frame);
        void write(cv::Mat img);
    private:
        string file_name;
        AVPacket *pkt_enc = NULL;
};
