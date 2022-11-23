#include "video_processor.h"

int VideoProcessor::run(){
    AVFrame *frame;
    try{
        while(frame = reader.nextFrame())
        {
            cv::Mat img = cv::Mat(frame->height, frame->width,
                CV_8UC3, frame->data[0], frame->linesize[0]);
            inputImgWriter.save(img);
            auto v = detector.detect(img);
            painter.blur(v, img);
            bluredImgWriter.save(img);
            writer.write(frame);
        }
    } catch(Exception& e){
        cout<<e.what()<<endl;
    }
    return 0; 
};

VideoProcessor::VideoProcessor(string srcFilename, string dstFilename, string dumpInput, string dumpBlured)
try :
    srcFilename(srcFilename),
    dstFilename(dstFilename),
    reader(srcFilename),
    writer(dstFilename),
    inputImgWriter(dumpInput, "input"),
    bluredImgWriter(dumpBlured, "blured")
{
    av_log_set_level(AV_LOG_FATAL);
    writer.init(reader.getCodecCtx(), reader.getCleanFrame());
}
catch(Exception& e) {
    cout<<e.what()<<endl;
}
