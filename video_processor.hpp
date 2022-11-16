#include "video_reader.hpp"
#include "video_writer.hpp"
#include "face_detector.hpp"
#include "blurer.hpp"

using namespace std;

class VideoProcessor {
    private:
        VideoReader reader;
        VideoWriter writer;
        FaceDetector detector;
        Blurer painter;
        string src_filename;
        string dst_filename;
    public:
        VideoProcessor(std::string src_filename, std::string dst_filename):
            src_filename(src_filename), dst_filename(dst_filename){};
        int run();
};
