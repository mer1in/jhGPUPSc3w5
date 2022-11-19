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
        bool dump_input;
        bool dump_blured;
    public:
        VideoProcessor(std::string src_filename, std::string dst_filename);
        ~VideoProcessor();
        int run();
        void setDumpInput(bool val){dump_input = val;}
        void setDumpBlured(bool val){dump_blured = val;}
};
