#include "video_reader.hpp"

VideoReader::VideoReader(std::string file_name) {
    if (avformat_open_input(&fmt_ctx, file_name, NULL, NULL) < 0)
        throw(Exception("Could not open source file " + file_name));
    
}
