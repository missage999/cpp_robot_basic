// ✅ 4. ranges_example.cpp（需支持 C++20）
// 实现：

// 创建传感器数据 vector<double>。
// 用 Ranges：过滤异常值 → 转换为整数 → 取前 5 个 → 计算平均值。
// 对比传统 STL 写法，体验可读性差异。

#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>

int main() {
    // 创建传感器数据
    std::vector<double> sensor_data = {12.3, 15.7, 1000.0, 14.2, 13.8, -999.0, 16.1, 15.0, 14.9, 13.5};

    // Ranges 写法
    auto filtered = sensor_data 
        | std::views::filter([](double v) { return v > 0 && v < 100; }) // 过滤异常值
        | std::views::transform([](double v) { return static_cast<int>(v); }) // 转换为整数
        | std::views::take(5); // 取前 5 个

    std::vector<int> processed;
    for (int v : filtered) processed.push_back(v);

    double avg = processed.empty() ? 0.0 : std::accumulate(processed.begin(), processed.end(), 0.0) / processed.size();

    std::cout << "Ranges 平均值: " << avg << std::endl;

    // 传统 STL 写法
    std::vector<int> stl_processed;
    for (double v : sensor_data) {
        if (v > 0 && v < 100) {
            stl_processed.push_back(static_cast<int>(v));
            if (stl_processed.size() == 5) break;
        }
    }
    double stl_avg = stl_processed.empty() ? 0.0 : std::accumulate(stl_processed.begin(), stl_processed.end(), 0.0) / stl_processed.size();
    std::cout << "STL 平均值: " << stl_avg << std::endl;

    return 0;
}