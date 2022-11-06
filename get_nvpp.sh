#!/bin/bash

mkdir -p libraries/nvpp
cd libraries/nvpp

BASE_URL=https://developer.download.nvidia.com/compute/cuda/redist/

for file in \
    cuda_cccl/linux-x86_64/cuda_cccl-linux-x86_64-11.6.55-archive.tar.xz \
    cuda_cudart/linux-x86_64/cuda_cudart-linux-x86_64-11.6.55-archive.tar.xz \
    cuda_cuobjdump/linux-x86_64/cuda_cuobjdump-linux-x86_64-11.6.55-archive.tar.xz \
    cuda_cupti/linux-x86_64/cuda_cupti-linux-x86_64-11.6.55-archive.tar.xz \
    cuda_cuxxfilt/linux-x86_64/cuda_cuxxfilt-linux-x86_64-11.6.55-archive.tar.xz \
    cuda_demo_suite/linux-x86_64/cuda_demo_suite-linux-x86_64-11.6.55-archive.tar.xz \
    cuda_documentation/linux-x86_64/cuda_documentation-linux-x86_64-11.6.55-archive.tar.xz \
    cuda_gdb/linux-x86_64/cuda_gdb-linux-x86_64-11.6.55-archive.tar.xz \
    cuda_memcheck/linux-x86_64/cuda_memcheck-linux-x86_64-11.6.55-archive.tar.xz \
    cuda_nsight/linux-x86_64/cuda_nsight-linux-x86_64-11.6.55-archive.tar.xz \
    cuda_nvcc/linux-x86_64/cuda_nvcc-linux-x86_64-11.6.55-archive.tar.xz \
    cuda_nvdisasm/linux-x86_64/cuda_nvdisasm-linux-x86_64-11.6.55-archive.tar.xz \
    cuda_nvml_dev/linux-x86_64/cuda_nvml_dev-linux-x86_64-11.6.55-archive.tar.xz \
    cuda_nvprof/linux-x86_64/cuda_nvprof-linux-x86_64-11.6.55-archive.tar.xz \
    cuda_nvprune/linux-x86_64/cuda_nvprune-linux-x86_64-11.6.55-archive.tar.xz \
    cuda_nvrtc/linux-x86_64/cuda_nvrtc-linux-x86_64-11.6.55-archive.tar.xz \
    cuda_nvtx/linux-x86_64/cuda_nvtx-linux-x86_64-11.6.55-archive.tar.xz \
    cuda_nvvp/linux-x86_64/cuda_nvvp-linux-x86_64-11.6.58-archive.tar.xz \
    cuda_sanitizer_api/linux-x86_64/cuda_sanitizer_api-linux-x86_64-11.6.55-archive.tar.xz \
    fabricmanager/linux-x86_64/fabricmanager-linux-x86_64-510.39.01-archive.tar.xz \
    libcublas/linux-x86_64/libcublas-linux-x86_64-11.8.1.74-archive.tar.xz \
    libcufft/linux-x86_64/libcufft-linux-x86_64-10.7.0.55-archive.tar.xz \
    libcufile/linux-x86_64/libcufile-linux-x86_64-1.2.0.100-archive.tar.xz \
    libcurand/linux-x86_64/libcurand-linux-x86_64-10.2.9.55-archive.tar.xz \
    libcusolver/linux-x86_64/libcusolver-linux-x86_64-11.3.2.55-archive.tar.xz \
    libcusparse/linux-x86_64/libcusparse-linux-x86_64-11.7.1.55-archive.tar.xz \
    libnpp/linux-x86_64/libnpp-linux-x86_64-11.6.0.55-archive.tar.xz \
    libnvidia_nscq/linux-x86_64/libnvidia_nscq-linux-x86_64-510.39.01-archive.tar.xz \
    libnvjpeg/linux-x86_64/libnvjpeg-linux-x86_64-11.6.0.55-archive.tar.xz \
    nsight_compute/linux-x86_64/nsight_compute-linux-x86_64-2022.1.0.12-archive.tar.xz \
    nsight_systems/linux-x86_64/nsight_systems-linux-x86_64-2021.5.2.53-archive.tar.xz \
    nvidia_driver/linux-x86_64/nvidia_driver-linux-x86_64-510.39.01-archive.tar.xz \
    nvidia_fs/linux-x86_64/nvidia_fs-linux-x86_64-2.10.3-archive.tar.xz
do
    fname=`basename $file`
    dname=`basename $file .tar.xz`
    echo "$file -> $fname"
    [ -f $file ] || wget "${BASE_URL}${file}"
    [ -d $dname ] || tar tf $fname 
done
