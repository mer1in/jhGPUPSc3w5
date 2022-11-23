#include "video_writer.h"
#define err(MSG) throw(Exception(string("VideoWriter: ")+MSG))

void VideoWriter::write(AVFrame* frame){
    int ret = 0;
    if (!frame)
        return;

    sws_scale(swsCtx, frame->data, frame->linesize, 0, frame->height, encFrame->data, encFrame->linesize);

    if (avcodec_send_frame(ctx, encFrame) < 0)
        err("Error sending a frame for encoding");

    while (ret >= 0) {
        ret = avcodec_receive_packet(ctx, pkt);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
            return;
        else if (ret < 0)
            err( "Error during encoding");
        fwrite(pkt->data, 1, pkt->size, file);
        av_packet_unref(pkt);
    }
}

VideoWriter::VideoWriter(string fileName) : fileName(fileName)
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

void VideoWriter::init(AVCodecContext* decCtx, AVFrame* frame)
{
    ctx->bit_rate = decCtx->bit_rate;
    ctx->width = decCtx->width;
    ctx->height = decCtx->height;
    ctx->time_base = (AVRational){1, 25};
    ctx->framerate = decCtx->framerate;
    ctx->max_b_frames = decCtx->max_b_frames;
    ctx->pix_fmt = AV_PIX_FMT_YUV420P;
    av_opt_set(ctx->priv_data, "preset", "slow", 0);

    if (avcodec_open2(ctx, codec, NULL) < 0)
        err("Could not open codec");

    swsCtx = sws_getContext(decCtx->width, decCtx->height, AV_PIX_FMT_BGR24, decCtx->width,
         decCtx->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);
    if(!swsCtx)
        err("Cannot create sws ctx");

    if (!(file = fopen(fileName.c_str(), "wb")))
        err("Could not open "+fileName);

    encFrame = frame;
}
