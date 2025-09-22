#include <iostream>
#include "math_utils.h"
#include "librobot.h"
#include <opencv2/opencv.hpp>

int main() {
    move_robot();
    int sum = add(3, 4);
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "OpenCV version: " << CV_VERSION << std::endl;
    return 0;
}