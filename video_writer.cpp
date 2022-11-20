#include "video_writer.hpp"
#define err(MSG) throw(Exception(string("VideoWriter: ")+MSG))

void VideoWriter::write(cv::Mat img){

}


VideoWriter::VideoWriter(string file_name) : file_name(file_name)
{
    pkt_enc = av_packet_alloc();
    if (!pkt_enc) {
        err("Could not allocate packet");
    }
};
