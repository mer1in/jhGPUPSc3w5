//#include "decode.hpp"
#include <sstream> 
#include "video_processor.hpp"

void usage(char* name)
{
    fprintf(stderr, "usage: %s <input_file> <output_file> [--verbose] [--dump-input] [--dump-blured]\n"
        "This program searchs for faces in input video and blurs them\n"
        "  input_file     video file to be processed, required\n"
        "  output_file    name of a file to write results to, required\n"
        "  --verbose      verbose output"
        "  --dump-input   write each input frame to a file named <output_file>-input-<frame-number>.jpg"
        "  --dump-blured  write each blured frame to a file named <output_file>-blured-<frame-number>.jpg",
        name);
    exit(1);
}

int main (int argc, char **argv)
{
    if (argc != 3)
        usage(argv[0]);

    auto processor = new VideoProcessor(argv[1], argv[2]);
    processor->run();
    delete(processor);
//    return handle_video(argv[1], argv[2]);
}
