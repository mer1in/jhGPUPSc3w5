#include <string>
#include <opencv2/opencv.hpp> 

using namespace std;
class VideoWriter{
    public:
        VideoWriter(string file_name) : file_name(file_name){};
        void write(cv::Mat img);
    private:
        string file_name;
};
