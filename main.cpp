//#include "decode.hpp"
#include <sstream> 
#include "video_processor.hpp"

void usage(char* name)
{
    fprintf(stderr, "usage: %s <input_file> <output_file> [--dump-input] [--dump-blured]\n"
        "This program searchs for faces in input video and blurs them\n"
        "  input_file     video file to be processed, required\n"
        "  output_file    name of a file to write results to, required\n"
        "  --dump-input   write each input frame to a file named <output_file>-input-<frame-number>.jpg"
        "  --dump-blured  write each blured frame to a file named <output_file>-blured-<frame-number>.jpg",
        name);
    exit(1);
}

int main (int argc, char **argv)
{
    bool dumpInput = false;
    bool dumpBlured = false;

    if (argc < 3)
        usage(argv[0]);
    
    for (int i=3; i<argc; i++)
    {
        if (!string(argv[i]).compare("--dump-input"))
            dumpInput = true;
        if (!string(argv[i]).compare("--dump-blured"))
            dumpBlured = true;
    }

    cout<<"dumpInput"<<dumpInput<<endl;
    exit(1);
    VideoProcessor processor(argv[1], argv[2], dumpInput ? argv[2] : "", dumpBlured ? argv[2] : "");

    processor.run();
//    return handle_video(argv[1], argv[2]);
}
