#include "img_writer.hpp"

using namespace std;

ImgWriter::ImgWriter(string input_file_name, string suffix)
{
    size_t pos = input_file_name.find('.');
    if (pos == npos)
        pos = input_file_name.length() - 1;
    file_name = input_file_name.substr(0, pos) + "-" +suffix;
}

int ImgWriter::save(cv::Mat img)
{
    string fn = file_name;

}
