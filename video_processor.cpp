#include "video_processor.hpp"

int VideoProcessor::run(){
    AVFrame *frame;
    while(frame = reader.nextFrame())
    {
        cout<<"processing"<<endl;
        
    }

    cout<<"processing got NULL "<<endl;
    return 0; 
};

VideoProcessor:: VideoProcessor(string src_filename, string dst_filename, string dump_input, string dump_blured)
try :
    src_filename(src_filename),
    dst_filename(dst_filename),
    reader(src_filename),
    input_img_writer(dump_input, "input"),
    dump_blured(dump_blured, "blured")
{ }
catch(Exception& e) {
    cout<<e.what()<<endl;
}

VideoProcessor::~VideoProcessor()
{
    delete(&reader);
}
