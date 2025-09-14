#pragma once
#include <map>
#include <string>
#include <vector>

std::vector<std::pair<std::string, std::size_t>>
countTopWords(const std::string& text, std::size_t topK = 3);