// ✅ 1. move_semantics.cpp
// 实现：

// 一个 ImageBuffer 类（含数据指针、宽、高），实现移动构造和移动赋值。
// 对比拷贝 vs 移动的性能（用 chrono 计时创建 1000 个大图像对象）。
// 使用 std::move 显式移动一个对象，并验证源对象状态。

#include <iostream>
#include <chrono>
#include <cstring>
#include <vector>

class ImageBuffer {
public:
    int width, height;
    unsigned char* data;

    // 构造函数
    ImageBuffer(int w, int h)
        : width(w), height(h), data(new unsigned char[w * h]) {
        std::memset(data, 255, w * h); // 填充数据
    }

    // 拷贝构造
    ImageBuffer(const ImageBuffer& other)
        : width(other.width), height(other.height), data(new unsigned char[other.width * other.height]) {
        std::memcpy(data, other.data, width * height);
    }

    // 移动构造
    ImageBuffer(ImageBuffer&& other) noexcept
        : width(other.width), height(other.height), data(other.data) {
        other.data = nullptr;
        other.width = 0;
        other.height = 0;
    }

    // 拷贝赋值
    ImageBuffer& operator=(const ImageBuffer& other) {
        if (this != &other) {
            delete[] data;
            width = other.width;
            height = other.height;
            data = new unsigned char[width * height];
            std::memcpy(data, other.data, width * height);
        }
        return *this;
    }

    // 移动赋值
    ImageBuffer& operator=(ImageBuffer&& other) noexcept {
        if (this != &other) {
            delete[] data;
            width = other.width;
            height = other.height;
            data = other.data;
            other.data = nullptr;
            other.width = 0;
            other.height = 0;
        }
        return *this;
    }

    ~ImageBuffer() {
        delete[] data;
    }

    bool isEmpty() const {
        return data == nullptr;
    }
};

int main() {
    const int W = 100, H = 200, N = 300;

    // 拷贝性能测试
    std::vector<ImageBuffer> images;
    images.reserve(N);
    auto start_copy = std::chrono::high_resolution_clock::now();
    ImageBuffer src(W, H);
    for (int i = 0; i < N; ++i) {
        images.push_back(src); // 拷贝构造
    }
    auto end_copy = std::chrono::high_resolution_clock::now();
    std::cout << "Copy time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end_copy - start_copy).count()
              << " ms\n";

    // 移动性能测试
    std::vector<ImageBuffer> images_move;
    images_move.reserve(N);
    auto start_move = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        images_move.push_back(ImageBuffer(W, H)); // 移动构造
    }
    auto end_move = std::chrono::high_resolution_clock::now();
    std::cout << "Move time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end_move - start_move).count()
              << " ms\n";

    // 显式 std::move
    ImageBuffer img1(W, H);
    ImageBuffer img2 = std::move(img1);
    std::cout << "After move, img1 is empty? " << std::boolalpha << img1.isEmpty() << "\n";
    std::cout << "img2 is empty? " << std::boolalpha << img2.isEmpty() << "\n";

    return 0;
}