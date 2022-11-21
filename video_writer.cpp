#include "video_writer.hpp"
#define err(MSG) throw(Exception(string("VideoWriter: ")+MSG))

void VideoWriter::write(AVFrame* frame){
    int ret = 0;
    if (!frame)
        return;
    if (!enc_frame)
    {
        enc_frame = av_frame_alloc();
        enc_frame->format = AV_PIX_FMT_YUV420P;
        enc_frame->width = frame->width;
        enc_frame->height = frame->height;
        if (av_frame_get_buffer(enc_frame, 0) < 0)
            err("Cannot allocate frame buffer");
    }
    
    cout<<"sws scale"<<endl;
    sws_scale(sws_ctx, frame->data, frame->linesize, 0, frame->height, enc_frame->data, frame->linesize);
    cout<<"sws scale done"<<endl;

    if (avcodec_send_frame(ctx, enc_frame) < 0)
        err("Error sending a frame for encoding");

    while (ret >= 0) {
        ret = avcodec_receive_packet(ctx, pkt);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
            return;
        else if (ret < 0)
            err( "Error during encoding\n");
        fwrite(pkt->data, 1, pkt->size, file);
        av_packet_unref(pkt);
    }
}


VideoWriter::VideoWriter(string file_name) : file_name(file_name)
{
    pkt = av_packet_alloc();
    if (!pkt)
        err("Could not allocate packet");

    codec = avcodec_find_encoder_by_name("libx264");
    if (!codec)
        err("Codec libx264 not found");
    if (!(ctx = avcodec_alloc_context3(codec)))
        err("Could not allocate video codec context");

};

void VideoWriter::init(AVCodecContext* dec_ctx)
{
    ctx->bit_rate = dec_ctx->bit_rate;
    ctx->width = dec_ctx->width;
    ctx->height = dec_ctx->height;
    ctx->time_base = (AVRational){1, 25};
    ctx->framerate = dec_ctx->framerate;
    ctx->max_b_frames = dec_ctx->max_b_frames;
    ctx->pix_fmt = AV_PIX_FMT_YUV420P;
    av_opt_set(ctx->priv_data, "preset", "slow", 0);

    if (avcodec_open2(ctx, codec, NULL) < 0)
        err("Could not open codec");

    sws_ctx = sws_getContext(dec_ctx->width, dec_ctx->height, AV_PIX_FMT_BGR24, dec_ctx->width,
         dec_ctx->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);
    if(!sws_ctx)
        err("Cannot create sws ctx");

    if (!(file = fopen(file_name.c_str(), "wb")))
        err("Could not open "+file_name);
}
