#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

int main() {
    std::string text = "the quick fox jumps over the lazy dog the fox is quick";
    std::istringstream iss(text);
    std::map<std::string, std::size_t> wordCount;

    // 1. 切词并统计
    std::string word;
    while (iss >> word) {
        // 请填空：wordCount[???]++
        wordCount[word]++;
    }

    // 2. 转 vector 并排序（次数降序）
    std::vector<std::pair<std::string, int>> vec(wordCount.begin(), wordCount.end());
    std::sort(vec.begin(), vec.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });

    // 3. 输出 Top 3
    for (std::size_t i = 0; i < vec.size() && i < 3; ++i) {
        std::cout << vec[i].first << ": " << vec[i].second << '\n';
    }
    return 0;
}