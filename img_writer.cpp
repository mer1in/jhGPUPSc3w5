#include "img_writer.hpp"

ImgWriter::ImgWriter(string input_file_name, string suffix)
{
    if (!input_file_name.length())
        return;
    size_t pos = input_file_name.find('.');
    if (pos == string::npos)
        pos = input_file_name.length() - 1;
    file_name = input_file_name.substr(0, pos) + "-" +suffix + "-";
    enabled = true;
}

void ImgWriter::save(cv::Mat img)
{
    if(!enabled)
    {
        cout<<"writer not enabled"<<endl;
        return;
    }
    string fn = file_name + to_string(num) + ".jpg";
    cout<<"saving"<<fn<<endl;
    cv::imwrite(fn.c_str(), img);
}
