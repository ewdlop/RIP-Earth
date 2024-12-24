#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <iostream>
#include <cmath>

__global__ void calculateGaussianCurvature(float* heightMap, float* curvatureMap, int width, int height, float dx, float dy) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x >= width || y >= height) return;

    // Central differences for first derivatives
    float z_x = (heightMap[y * width + (x + 1)] - heightMap[y * width + (x - 1)]) / (2.0f * dx);
    float z_y = (heightMap[(y + 1) * width + x] - heightMap[(y - 1) * width + x]) / (2.0f * dy);

    // Central differences for second derivatives
    float z_xx = (heightMap[y * width + (x + 1)] - 2.0f * heightMap[y * width + x] + heightMap[y * width + (x - 1)]) / (dx * dx);
    float z_yy = (heightMap[(y + 1) * width + x] - 2.0f * heightMap[y * width + x] + heightMap[(y - 1) * width + x]) / (dy * dy);
    float z_xy = (heightMap[(y + 1) * width + (x + 1)] - heightMap[(y + 1) * width + (x - 1)]
                - heightMap[(y - 1) * width + (x + 1)] + heightMap[(y - 1) * width + (x - 1)]) / (4.0f * dx * dy);

    // First fundamental form coefficients
    float E = 1.0f + z_x * z_x;
    float F = z_x * z_y;
    float G = 1.0f + z_y * z_y;

    // Second fundamental form coefficients
    float L = z_xx;
    float M = z_xy;
    float N = z_yy;

    // Gaussian curvature
    float K = (L * N - M * M) / (E * G - F * F);

    curvatureMap[y * width + x] = K;
}

int main() {
    const int width = 512;
    const int height = 512;
    const float dx = 1.0f;
    const float dy = 1.0f;

    size_t size = width * height * sizeof(float);

    // Allocate host memory
    float* h_heightMap = (float*)malloc(size);
    float* h_curvatureMap = (float*)malloc(size);

    // Initialize height map with some values (for example, a simple paraboloid)
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            h_heightMap[y * width + x] = x * x + y * y;
        }
    }

    // Allocate device memory
    float* d_heightMap;
    float* d_curvatureMap;
    cudaMalloc((void**)&d_heightMap, size);
    cudaMalloc((void**)&d_curvatureMap, size);

    // Copy height map to device
    cudaMemcpy(d_heightMap, h_heightMap, size, cudaMemcpyHostToDevice);

    // Define block and grid sizes
    dim3 blockSize(16, 16);
    dim3 gridSize((width + blockSize.x - 1) / blockSize.x, (height + blockSize.y - 1) / blockSize.y);

    // Launch the kernel
    calculateGaussianCurvature<<<gridSize, blockSize>>>(d_heightMap, d_curvatureMap, width, height, dx, dy);
    cudaDeviceSynchronize();

    // Copy the result back to host
    cudaMemcpy(h_curvatureMap, d_curvatureMap, size, cudaMemcpyDeviceToHost);

    // Print some of the results
    for (int y = 0; y < 10; ++y) {
        for (int x = 0; x < 10; ++x) {
            std::cout << h_curvatureMap[y * width + x] << " ";
        }
        std::cout << std::endl;
    }

    // Free memory
    cudaFree(d_heightMap);
    cudaFree(d_curvatureMap);
    free(h_heightMap);
    free(h_curvatureMap);

    return 0;
}
