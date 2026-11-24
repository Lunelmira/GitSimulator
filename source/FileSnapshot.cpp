
#include "FileSnapshot.hpp"

FileSnapshot::FileSnapshot() {
    path = "";
    content = {};
}

FileSnapshot::FileSnapshot(std::string filePath, std::vector<std::string> fileContent) {
    path = filePath;
    content = fileContent;
}

std::string FileSnapshot::getPath() const {
    return path;
}

std::vector<std::string> FileSnapshot::getContent() const {
    return content;
}
