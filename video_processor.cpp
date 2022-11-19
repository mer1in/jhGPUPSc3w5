#include "video_processor.hpp"

int VideoProcessor::run(){
    while(frame = reader->nextFrame())
    {
        cout<<"processing"<<endl;
    }
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
