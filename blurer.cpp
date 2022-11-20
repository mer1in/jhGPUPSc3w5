#include "blurer.hpp"
void Blurer::blur(std::vector<cv::Rect> faces, cv::Mat img)
{

    if (!dev_mem)
    {
        size_t size = 3 * img.size().width * img.size().height;
        cudaError_t err = cudaMalloc(&dev_mem, size);
        if (err != cudaSuccess)
        {
            fprintf(stderr, "Failed to allocate device vector memory (error code %s)!\n", cudaGetErrorString(err));
            exit(EXIT_FAILURE);
        }
    }

    
    cudaError_t err = cudaMemcpy(dev_mem, pBGRFrame->data[0], size, cudaMemcpyHostToDevice);
    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to copy video frame from host to device (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    for(const auto & r : rectangles){

        NppiSize isize = {r.width, r.height};
        Npp8u *face_addr = dev_mem + (r.y * pBGRFrame->width * 3 + r.x * 3);
        printf("face_addr x = %d y = %d\n", r.x, r.y);
        nppiFilterGauss_8u_C3R(face_addr, pBGRFrame->width*3, face_addr, pBGRFrame->width*3, isize, NPP_MASK_SIZE_15_X_15);

    }

    err = cudaMemcpy(pBGRFrame->data[0], dev_mem, size, cudaMemcpyDeviceToHost);
    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to copy video frame from device to host (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }


}

