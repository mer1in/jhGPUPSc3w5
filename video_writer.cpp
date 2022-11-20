#include "video_writer.hpp"

void VideoWriter::write(cv::Mat img){

}


VideoWriter::VideoWriter(string file_name) : file_name(file_name)
{
    pkt_enc = av_packet_alloc();
    if (!pkt || !pkt_enc) {
        fprintf(stderr, "Could not allocate packet\n");
        ret = AVERROR(ENOMEM);
        goto end;
    }
};
