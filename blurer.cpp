#include "blurer.hpp"
#define catchCudaErr(F) { \
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
        catchCudaErr(cudaMalloc(&dev_mem, size));
    
    cudaError_t err = cudaMemcpy(dev_mem, img.data, size, cudaMemcpyHostToDevice);
    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to copy video frame from host to device (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    for(const auto & r : faces){

        NppiSize isize = {r.width, r.height};
        Npp8u *face_addr = dev_mem + (r.y * width * 3 + r.x * 3);
        printf("face_addr x = %d y = %d\n", r.x, r.y);
        nppiFilterGauss_8u_C3R(face_addr, width*3, face_addr, width*3, isize, NPP_MASK_SIZE_15_X_15);

    }

    err = cudaMemcpy(img.data, dev_mem, size, cudaMemcpyDeviceToHost);
    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to copy video frame from device to host (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }


}

