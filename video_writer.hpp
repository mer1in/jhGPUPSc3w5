#include <string>
#include <opencv2/opencv.hpp> 

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
