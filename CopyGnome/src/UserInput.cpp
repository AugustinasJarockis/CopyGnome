#include "UserInput.h"

bool IsPathASubfolder(fs::path outerPath, fs::path innerPath);

int GetUserInput(int argc, char* argv[], fs::path &source, fs::path &destination) {
    source = "?";
    destination = "?";

    for (int i = 2; i < argc; i++) {
        if (argv[i] == "-s" && i + 1 < argc) {
            source = argv[i + 1];
            if (!fs::exists(source) || !fs::is_directory(source)) {
                std::cout << "ERROR: Specified source folder does not exist" << std::endl;
                return 2;
            }

            if (destination != "?" && IsPathASubfolder(source, destination)) {
                std::cout << "ERROR: Specified destination folder cannot be within source folder" << std::endl;
                return 4;
            }
        }
        else if (argv[i] == "-d" && i + 1 < argc) {
            destination = argv[i + 1];
            if (!fs::exists(destination) || !fs::is_directory(destination)) {
                std::cout << "ERROR: Specified destination folder does not exist" << std::endl;
                return 3;
            }

            if (source != "?" && IsPathASubfolder(source, destination)) {
                std::cout << "ERROR: Specified destination folder cannot be within source folder" << std::endl;
                return 4;
            }
        }
        else {
            std::cout << "ERROR: Unrecognized argument: " << argv[i] << std::endl;
            continue;
        }
        i++;
    }

    if (source == "?") {
        std::cout << "Please specify the source path: " << std::endl << "> ";
        std::cin >> source;

        while (!fs::exists(source) || !fs::is_directory(source)) {
            std::cout << "ERROR: Specified source folder does not exist" << std::endl;
            std::cout << "Please specify the source path again: " << std::endl << "> ";
            std::cin >> source;
        }
    }

    if (destination == "?") {
        std::cout << "Please specify the destination path: " << std::endl << "> ";
        std::cin >> destination;

        while (!fs::exists(destination) || !fs::is_directory(destination)) {
            std::cout << "ERROR: Specified destination folder does not exist" << std::endl;
            std::cout << "Please specify the destination path again: " << std::endl << "> ";
            std::cin >> destination;
        }

        while (IsPathASubfolder(source, destination)) {
            std::cout << "ERROR: Specified destination folder cannot be within source folder" << std::endl;
            std::cout << "Please specify the destination path again: " << std::endl << "> ";
            std::cin >> destination;
        }
    }

    source = source.lexically_normal();
    destination = destination.lexically_normal();

    return 0;
}

bool IsPathASubfolder(fs::path outerPath, fs::path innerPath) {
    outerPath = fs::absolute(outerPath).lexically_normal();
    innerPath = fs::absolute(innerPath).lexically_normal() / "";

    if (innerPath.string().length() < outerPath.string().length())
        return false;

    auto [outerDif, nothing] = std::mismatch(outerPath.begin(), outerPath.end(), innerPath.begin());
    return outerDif == outerPath.end();
}