#include "video_processor.hpp"

int VideoProcessor::run(){
    AVFrame *frame;
    int count = 0;
    while(frame = reader.nextFrame())
    {
        cout<<"processing"<<endl;
        if (count++>1000)
            return -1;
    }

    cout<<"processing got NULL "<<endl;
    return 0; 
};

VideoProcessor:: VideoProcessor(std::string src_filename, std::string dst_filename)
try :
    src_filename(src_filename),
    dst_filename(dst_filename),
    reader(src_filename)
{ }
catch(Exception& e) {
    cout<<e.what()<<endl;
}

VideoProcessor::~VideoProcessor()
{
    delete(&reader);
}
