#include "CopyDirectory.h"

void AppendExclusionLists(const fs::path& source, ExclusionLists& exclusions);
std::string AdjustForRegex(std::string& str);
bool IsExcluded(const fs::path& path, ExclusionLists& exclusions);
bool HasMatches(const std::string& text, const std::vector<std::regex>& list);

void CopyDirectory(const fs::path& source, const fs::path& destination, ExclusionLists exclusions) {
    AppendExclusionLists(source, exclusions);

    for (const auto& entry : fs::directory_iterator(source)) {

        if (IsExcluded(entry.path(), exclusions)) {
            continue;
        }

        const auto new_entry = destination / entry.path().filename();
        if (fs::is_directory(entry.path())) {
            fs::create_directory(new_entry);
            CopyDirectory(entry.path(), new_entry, exclusions);
        }
        else {
            fs::copy_file(entry.path(), new_entry, fs::copy_options::update_existing);
        }
    }
}

void AppendExclusionLists(const fs::path& source, ExclusionLists& exclusions) {
    if (fs::exists(source / ".gnomeIgnore") && fs::is_regular_file(source / ".gnomeIgnore")) {
        std::ifstream ignoreFile(source / ".gnomeIgnore");

        std::string line;

        while (!ignoreFile.eof()) {
            getline(ignoreFile, line);
            line = Trim(line);

            if (line[0] != '#' && line != "") {
                line = source.string() + "*" + line;
                AdjustForRegex(line);

                if (line[line.size() - 1] == '$') {
                    std::regex lineReg(line);
                    exclusions.file.push_back(lineReg);
                }
                else if (line[line.size() - 1] == '/') {
                    line.pop_back();
                    line.pop_back();
                    std::regex lineReg(line);
                    exclusions.directory.push_back(lineReg);
                }
                else {
                    std::regex lineReg(line);
                    exclusions.general.push_back(lineReg);
                }
            }
        }
        ignoreFile.close();
    }
}

std::string AdjustForRegex(std::string& str) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '\\') {
            str.insert(str.begin() + i + 1, '/');
            i++;
            continue;
        }
        if (str[i] == '/') {
            str.insert(str.begin() + i, '\\');
            ++i;
            continue;
        }
        if (str[i] == '.') {
            str.insert(str.begin() + i, '\\');
            ++i;
            continue;
        }
        if (str[i] == '*') {
            str.insert(str.begin() + i, '.');
            ++i;
            continue;
        }
    }
    return str;
}

bool IsExcluded(const fs::path& path, ExclusionLists& exclusions) {
    std::string pathStr = path.string();

    for (int i = 0; i < pathStr.length(); i++) {
        if (pathStr[i] == '\\') {
            pathStr[i] = '/';
            continue;
        }
    }

    if (HasMatches(pathStr, exclusions.general))
        return true;

    if (fs::is_directory(path))
        return HasMatches(pathStr, exclusions.directory);

    return HasMatches(pathStr, exclusions.file);
}

bool HasMatches(const std::string& text, const std::vector<std::regex>& list) {
    for (int i = 0; i < list.size(); i++) {
        std::smatch matches;
        if (std::regex_search(text, matches, list[i])) {
            return true;
        }
    }

    return false;
}