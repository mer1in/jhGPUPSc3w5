#include "img_writer.h"

ImgWriter::ImgWriter(string inputFileName, string suffix)
{
    if (!inputFileName.length())
        return;
    size_t pos = inputFileName.find('.');
    if (pos == string::npos)
        pos = inputFileName.length() - 1;
    fileName = inputFileName.substr(0, pos) + "-" +suffix + "-";
    enabled = true;
}

void ImgWriter::save(cv::Mat img)
{
    if(!enabled)
        return;
    string fn = fileName + to_string(num++) + ".jpg";
    cv::imwrite(fn.c_str(), img);
}
