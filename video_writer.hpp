#include <string>

class VideoWriter{
    public:
        VideoWriter(string file_name) : file_name(file_name){};
        void write(cv::Mat img);
    private:
        string file_name;
};
