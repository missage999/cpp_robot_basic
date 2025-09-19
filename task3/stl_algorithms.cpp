// ✅ 2. stl_algorithms.cpp
// 实现：

// 创建 vector<int>，用 generate 填充 1~100。
// 用 remove_if 删除所有偶数。
// 用 accumulate 计算剩余奇数和。
// 用 sort + reverse 将结果降序排列。
// 用范围 for 输出最终结果。

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    // 创建 vector<int>，用 generate 填充 1~100。
    std::vector<int> v(100);
    int n = 1;
    std::generate(v.begin(), v.end(), [&n]() { return n++; });

    // 用 remove_if 删除所有偶数。
    auto it = std::remove_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
    v.erase(it, v.end());

    // 用 accumulate 计算剩余奇数和。
    int sum = std::accumulate(v.begin(), v.end(), 0);

    // 用 sort + reverse 将结果降序排列。
    std::sort(v.begin(), v.end());
    std::reverse(v.begin(), v.end());

    // 用范围 for 输出最终结果。
    std::cout << "奇数和: " << sum << std::endl;
    std::cout << "降序排列的奇数: ";
    for (int x : v) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    return 0;
}