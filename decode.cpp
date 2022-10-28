// stolen from https://stackoverflow.com/questions/71422496/how-to-save-avframe-as-image-in-c-using-ffmpeg
// (git pull ; cat decode.cpp > ffmpeg/decode.cpp ; cd ffmpeg/ ; gcc decode.cpp -Llib -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lswresample -lswscale -lpthread -lz -llzma -lm )
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
}

#define INBUF_SIZE 1024

//static void pgm_save(unsigned char* buf, int wrap, int xsize, int ysize, char* filename)
//{
//    FILE* f;
//    int i;
//
//    f = fopen(filename, "wb");
//    fprintf(f, "P5\n%d %d\n%d\n", xsize, ysize, 255);
//    for (i = 0; i < ysize; i++)
//        fwrite(buf + i * wrap, 1, xsize, f);
//    fclose(f);
//}


//Save RGB image as PPM file format
static void ppm_save(unsigned char* buf, int wrap, int xsize, int ysize, char* filename)
{
    FILE* f;
    int i;

    f = fopen(filename, "wb");
    fprintf(f, "P6\n%d %d\n%d\n", xsize, ysize, 255);

    for (i = 0; i < ysize; i++)
    {
        fwrite(buf + i * wrap, 1, xsize*3, f);
    }

    fclose(f);
}


static void decode(AVCodecContext* dec_ctx, AVFrame* frame, AVPacket* pkt, const char* filename)
{
    struct SwsContext* sws_ctx = NULL;
    char buf[1024];
    int ret;
    int sts;

    fprintf(stderr, "decode start\n");
    ret = avcodec_send_packet(dec_ctx, pkt);
    fprintf(stderr, "avcodec_send_packet\n");
    if (ret < 0)
    {
        fprintf(stderr, "Error sending a packet for decoding\n");
        exit(1);
    }

    //Create SWS Context for converting from decode pixel format (like YUV420) to RGB
    ////////////////////////////////////////////////////////////////////////////
    sws_ctx = sws_getContext(dec_ctx->width,
                             dec_ctx->height,
                             dec_ctx->pix_fmt,
                             dec_ctx->width,
                             dec_ctx->height,
                             AV_PIX_FMT_RGB24,
                             SWS_BICUBIC,
                             NULL,
                             NULL,
                             NULL);

    if (sws_ctx == nullptr)
    {
        return;  //Error!
    }
    ////////////////////////////////////////////////////////////////////////////


    //Allocate frame for storing image converted to RGB.
    ////////////////////////////////////////////////////////////////////////////
    AVFrame* pRGBFrame = av_frame_alloc();

    pRGBFrame->format = AV_PIX_FMT_RGB24;
    pRGBFrame->width = dec_ctx->width;
    pRGBFrame->height = dec_ctx->height;

    sts = av_frame_get_buffer(pRGBFrame, 0);

    if (sts < 0)
    {
        return;  //Error!
    }
    ////////////////////////////////////////////////////////////////////////////


    while (ret >= 0) 
    {
        ret = avcodec_receive_frame(dec_ctx, frame);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
        {
            fprintf(stderr, "EAGAIN\n");
            return;
        }
        else if (ret < 0) 
        {
            fprintf(stderr, "Error during decoding\n");
            exit(1);
        }

        printf("saving frame %3d\n", dec_ctx->frame_number);
        fflush(stdout);

        /* the picture is allocated by the decoder. no need to
           free it */
        //snprintf(buf, sizeof(buf), "%s_%03d.pgm", filename, dec_ctx->frame_number);
        // pgm_save(frame->data[0], frame->linesize[0],
        //    frame->width, frame->height, buf);
         
        //Convert from input format (e.g YUV420) to RGB and save to PPM:
        ////////////////////////////////////////////////////////////////////////////
        sts = sws_scale(sws_ctx,                //struct SwsContext* c,
                        frame->data,            //const uint8_t* const srcSlice[],
                        frame->linesize,        //const int srcStride[],
                        0,                      //int srcSliceY, 
                        frame->height,          //int srcSliceH,
                        pRGBFrame->data,        //uint8_t* const dst[], 
                        pRGBFrame->linesize);   //const int dstStride[]);

        if (sts != frame->height)
        {
            return;  //Error!
        }

        snprintf(buf, sizeof(buf), "%s_%03d.ppm", filename, dec_ctx->frame_number);
        ppm_save(pRGBFrame->data[0], pRGBFrame->linesize[0], pRGBFrame->width, pRGBFrame->height, buf);
        ////////////////////////////////////////////////////////////////////////////
    }

    //Free
    sws_freeContext(sws_ctx);
    av_frame_free(&pRGBFrame);
}

int main(int argc, char** argv)
{
    const char* filename, * outfilename;
    const AVCodec* codec;
    AVCodecParserContext* parser;
    AVCodecContext* c = NULL;
    FILE* f;
    AVFrame* frame;
    uint8_t inbuf[INBUF_SIZE + AV_INPUT_BUFFER_PADDING_SIZE];
    uint8_t* data;
    size_t   data_size;
    int ret;
    AVPacket* pkt;    

    filename = argv[1];
    outfilename = argv[2];

    fprintf(stdout, "Decode is starting\n");
    pkt = av_packet_alloc();
    if (!pkt)
    {
        exit(1);
    }

    //memset(inbuf + INBUF_SIZE, 0, AV_INPUT_BUFFER_PADDING_SIZE);
    memset(inbuf, 0, sizeof(inbuf));

    codec = avcodec_find_decoder(AV_CODEC_ID_HEVC);
    if (!codec)
    {
        fprintf(stderr, "Codec not found\n");
        exit(1);
    }

    parser = av_parser_init(codec->id);
    if (!parser)
    {
        fprintf(stderr, "parser not found\n");
        exit(1);
    }

    c = avcodec_alloc_context3(codec);
    if (!c)
    {
        fprintf(stderr, "Could not allocate video codec context\n");
        exit(1);
    }

    if (avcodec_open2(c, codec, NULL) < 0)
    {
        fprintf(stderr, "Could not open codec\n");
        exit(1);
    }

    f = fopen(filename, "rb");
    if (!f)
    {
        fprintf(stderr, "Could not open %s\n", filename);
        exit(1);
    }

    frame = av_frame_alloc();
    if (!frame)
    {
        fprintf(stderr, "Could not allocate video frame\n");
        exit(1);
    }

    while (!feof(f))
    {
        /* read raw data from the input file */
        data_size = fread(inbuf, 1, INBUF_SIZE, f);

        if (!data_size)
        {
            break;
        }

        /* use the parser to split the data into frames */
        data = inbuf;
        while (data_size > 0) 
        {
            ret = av_parser_parse2(parser, c, &pkt->data, &pkt->size, data, (int)data_size, AV_NOPTS_VALUE, AV_NOPTS_VALUE, 0);

            if (ret < 0)
            {
                fprintf(stderr, "Error while parsing\n");
                exit(1);
            }

            data += ret;
            data_size -= ret;


            if (pkt->data) 
            {
                printf("NICE\n");
                decode(c, frame, pkt, outfilename);
            }
        }
    }

    /* flush the decoder */
    decode(c, frame, NULL, outfilename);

    fclose(f);

    av_parser_close(parser);
    avcodec_free_context(&c);
    av_frame_free(&frame);
    av_packet_free(&pkt);

    return 0;
}

