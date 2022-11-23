#ifndef VIDEO_PROCESSOR_H_
#define VIDEO_PROCESSOR_H_

#include "video_reader.h"
#include "video_writer.h"
#include "face_detector.h"
#include "blurer.h"
#include "img_writer.h"

using namespace std;

class VideoProcessor {
    public:
        VideoProcessor(string src_filename, string dst_filename, string dump_input, string dump_blured);
        int run();
    private:
        VideoReader reader;
        VideoWriter writer;
        FaceDetector detector;
        Blurer painter;
        string srcFilename;
        string dstFilename;
        ImgWriter inputImgWriter;
        ImgWriter bluredImgWriter;
};

#endif // VIDEO_PROCESSOR_H_
