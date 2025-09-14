#include "word_counter.h"
#include <sstream>
#include <algorithm>

std::vector<std::pair<std::string, std::size_t>>
countTopWords(const std::string& text, std::size_t topK) {
    std::istringstream iss(text);
    std::map<std::string, std::size_t> wordCount;
    std::string word;
    while (iss >> word) ++wordCount[word];

    std::vector<std::pair<std::string, std::size_t>> vec(wordCount.begin(),
                                                         wordCount.end());
    std::sort(vec.begin(), vec.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });
    if (vec.size() > topK) vec.resize(topK);
    return vec;
}