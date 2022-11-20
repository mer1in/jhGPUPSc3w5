#include "video_reader.hpp"
#define err(MSG) throw(Exception(string("VideoReader: ")+MSG))

VideoReader::VideoReader(std::string file_name) {

    string media_type = av_get_media_type_string(AVMEDIA_TYPE_VIDEO);
    const AVCodec *dec = NULL;
    const AVStream *st;

    if (avformat_open_input(&fmt_ctx, file_name.c_str(), NULL, NULL) < 0)
        err("Could not open source file " + file_name);

    if (avformat_find_stream_info(fmt_ctx, NULL) < 0)
        err("Could not find stream information");
    
    /*
     * XXX: move to writer
    AVCodec *codec;
    if (!(codec = avcodec_find_encoder_by_name("libx264")))
        err("Codec libx264 not found");
    */

    if((stream_idx = av_find_best_stream(fmt_ctx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0)) < 0)
        err("Could not find "+media_type+" stream in input file");
    
    st = fmt_ctx->streams[stream_idx];
    if(!(dec = avcodec_find_decoder(st->codecpar->codec_id)))
        err("Failed to find "+media_type+" codec");
                    
    dec_ctx = avcodec_alloc_context3(dec);
    if (!dec_ctx)
        err("Failed to allocate the "+av_get_media_type_string(AVMEDIA_TYPE_VIDEO)+" codec context");

    if (avcodec_parameters_to_context(dec_ctx, st->codecpar) < 0)
        err("Failed to copy "+media_type+" codec parameters to decoder ctx");

    if (avcodec_open2(dec_ctx, dec, NULL) < 0)
        err("Failed to open "+media_type+" codec");

    if (!(video_stream = fmt_ctx->streams[stream_idx]))
        err("Could not find video stream in the input, aborting");

    if (!(frame = av_frame_alloc()))
        err("Could not allocate frame");

    if (!(pBGRFrame = av_frame_alloc()))
        err("Could not allocate BGR frame");
    pBGRFrame->format = AV_PIX_FMT_BGR24;
    pBGRFrame->width = dec->width;
    pBGRFrame->height = dec->height;
    if (av_frame_get_buffer(pBGRFrame, 0) < 0)
        err("Cannot allocate pBGRFrame frame buffer");

    if (!(pkt = av_packet_alloc()))
        err("Couldn't allocate packet");
}


AVFrame* VideoReader::nextFrame()
{
    while (av_read_frame(fmt_ctx, pkt) >= 0) {
        if (pkt->stream_index != stream_idx)
        {
            fprintf(stderr, "skip non video stream\n");
            continue;
        }
        int ret = avcodec_send_packet(dec_ctx, pkt); 
        if (ret < 0)
        {
            fprintf(stderr, "Error submitting a packet for decoding (%i)\n", ret);
            return NULL;
        }
        ret = avcodec_receive_frame(dec_ctx, frame);
        if (ret < 0)
        {
            if (ret == AVERROR_EOF || ret == AVERROR(EAGAIN))
                continue;
            fprintf(stderr, "Error during decoding (%i)\n", ret);
            return NULL;
        }
        fprintf(stderr, "alles gut, return frame\n");
        
        int sts = sws_scale(sws_ctx,                //struct SwsContext* c,
            frame->data,            //const uint8_t* const srcSlice[],
            frame->linesize,        //const int srcStride[],
            0,                      //int srcSliceY, 
            frame->height,          //int srcSliceH,
            pBGRFrame->data,        //uint8_t* const dst[], 
            pBGRFrame->linesize);   //const int dstStride[]);

        return frame;
    }
    fprintf(stderr, "alles gut, no more frames\n");
    return NULL;
}

VideoReader::~VideoReader() {
    avcodec_free_context(&dec_ctx);
    avformat_close_input(&fmt_ctx);
    av_packet_free(&pkt);
    av_frame_free(&frame);
    printf("Bye\n");
}
