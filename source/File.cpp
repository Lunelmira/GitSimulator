
#include "File.hpp"

File::File() {
    path = "";
    content = {};
}

File::File(std::string filePath, std::vector<std::string> fileContent) {
    path = filePath;
    content = fileContent;
}

std::string File::getPath() const {
    return path;
}

std::vector<std::string> File::getContent() const {
    return content;
}

void File::setContent(std::vector<std::string> newContent) {
    content = newContent;
}

void File::appendLine(std::string line) {
    content.push_back(line);
}

FileSnapshot File::createSnapshot() const {
    return FileSnapshot(path, content);
}