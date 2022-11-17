#include "video_reader.hpp"
#define err(MSG) throw(Exception(string("VideoReader: ")+MSG))

VideoReader::VideoReader(std::string file_name) {

    int stream_index;
    const AVCodec *dec = NULL;
    AVStream *st;

    err("XXX");
    
    if (avformat_open_input(&fmt_ctx, file_name.c_str(), NULL, NULL) < 0)
        err("Could not open source file " + file_name);

    if (avformat_find_stream_info(fmt_ctx, NULL) < 0)
        err("Could not find stream information");
    
    if (!(codec = avcodec_find_encoder_by_name("libx264")))
        err("Codec libx264 not found");

//    if (open_codec_context(&video_stream_idx, &video_dec_ctx, fmt_ctx, AVMEDIA_TYPE_VIDEO) >= 0)
//        video_stream = fmt_ctx->streams[video_stream_idx];


    if((stream_index = av_find_best_stream(fmt_ctx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0)) < 0)
        err("Could not find "+string(av_get_media_type_string(AVMEDIA_TYPE_VIDEO))+" stream in input file");
    
    st = fmt_ctx->streams[stream_index];
    if(!(dec = avcodec_find_decoder(st->codecpar->codec_id)))
        err("Failed to find "+string(av_get_media_type_string(AVMEDIA_TYPE_VIDEO))+" codec");
                    

}
