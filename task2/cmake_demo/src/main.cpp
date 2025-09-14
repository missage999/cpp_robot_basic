#include "word_counter.h"
#include <iostream>

int main() {
    const std::string text = "the quick fox jumps over the lazy dog the fox is quick";
    auto res = countTopWords(text);
    for (auto& [w, c] : res) std::cout << w << ": " << c << '\n';
}