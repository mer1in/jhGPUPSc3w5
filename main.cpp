#include "decode.hpp"

int main (int argc, char **argv)
{
    static const char *src_filename = NULL;
    static const char *video_dst_filename = NULL;

    if (argc != 3) {
        fprintf(stderr, "usage: %s  input_file video_output_file audio_output_file\n"
                "API example program to show how to read frames from an input file.\n"
                "This program reads frames from a file, decodes them, and writes decoded\n"
                "video frames to a rawvideo file named video_output_file, and decoded\n"
                "audio frames to a rawaudio file named audio_output_file.\n",
                argv[0]);
        exit(1);
    }
    src_filename = argv[1];
    video_dst_filename = argv[2];

    return handle_video(src_filename, video_dst_filename);
}
