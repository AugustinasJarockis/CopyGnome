#pragma once

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int GetUserInput(int argc, char *argv[], fs::path &source, fs::path &destination);