#pragma once

#include <filesystem>
#include <vector>
#include <regex>
#include <fstream>

#include "StringUtils.h"

namespace fs = std::filesystem;

struct ExclusionLists {
    std::vector<std::regex> general;
    std::vector<std::regex> directory;
    std::vector<std::regex> file;
};

void CopyDirectory(const fs::path& source, const fs::path& destination, ExclusionLists exclusions);