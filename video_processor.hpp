#include "video_reader.hpp"
#include "video_writer.hpp"
#include "face_detector.hpp"
#include "blurer.hpp"
#include "img_writer.hpp"

using namespace std;

class VideoProcessor {
    private:
        VideoReader reader;
        VideoWriter writer;
        FaceDetector detector;
        Blurer painter;
        string src_filename;
        string dst_filename;
        ImgWriter input_img_writer;
        ImgWriter blured_img_writer;
    public:
        VideoProcessor(string src_filename, string dst_filename, string dump_input, string dump_blured);
        ~VideoProcessor();
        int run();
};
