#include "decode.hpp"

void usage(char* name)
{
    fprintf(stderr, "usage: %s input_file output_file\n"
        "This program searchs for faces in input video and blurs them\n"
        name);
    exit(1);
}

int main (int argc, char **argv)
{
    if (argc != 3)
        usage(argv[0]);

    return handle_video(argv[1], argv[2]);
}
