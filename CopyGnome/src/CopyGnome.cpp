#include <filesystem>

#include "UserInput.h"
#include "CopyDirectory.h"

namespace fs = std::filesystem;

int main(int argc, char *argv[])
{
    fs::path source = "?";
    fs::path destination = "?";

    int result = GetUserInput(argc, argv, source, destination);
    if (result != 0)
        return result;

    CopyDirectory(source, destination, { {}, {}, {} });
    
    return 0;
}