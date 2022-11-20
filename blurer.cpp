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

}

