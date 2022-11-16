#include "video_reader.hpp"

VideoReader::VideoReader(std::string file_name) {

    if (avformat_open_input(&fmt_ctx, file_name.c_str(), NULL, NULL) < 0)
        throw(Exception("Could not open source file " + file_name));

    if (avformat_find_stream_info(fmt_ctx, NULL) < 0)
        throw(Exception("Could not find stream information"));
    
    if (!( codec = avcodec_find_encoder_by_name("libx264") ))
        throw(Exception("Codec libx264 not found"));

}
