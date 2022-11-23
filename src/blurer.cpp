#include "blurer.h"
#define cudaCall(F) { \
    cudaError_t err = F; \
    if (err != cudaSuccess){ \
        throw(Exception(string("Blurer: ")+cudaGetErrorString(err))); \
    } \
}

void Blurer::blur(std::vector<cv::Rect> faces, cv::Mat img)
{
    auto width = img.size().width;
    auto height = img.size().height;
    size_t size = 3 * width * height;
    if (!dev_mem)
        cudaCall(cudaMalloc(&dev_mem, size));
    
    cudaCall(cudaMemcpy(dev_mem, img.data, size, cudaMemcpyHostToDevice));

    for(const auto & r : faces){

        NppiSize isize = {r.width, r.height};
        Npp8u *face_addr = dev_mem + (r.y * width * 3 + r.x * 3);
        nppiFilterGauss_8u_C3R(face_addr, width*3, face_addr, width*3, isize, NPP_MASK_SIZE_15_X_15);

    }

    cudaCall(cudaMemcpy(img.data, dev_mem, size, cudaMemcpyDeviceToHost));
}

