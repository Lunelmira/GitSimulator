
#include "Directory.hpp"

Directory::Directory() {
    name = "";
    files = {};
    directories = {};
}

Directory::Directory(std::string directoryName) {
    name = directoryName;
    files = {};
    directories = {};
}

std::string Directory::getName() const {
    return name;
}

std::vector<File> Directory::getFiles() const {
    return files;
}

std::vector<Directory> Directory::getDirectories() const {
    return directories;
}

void Directory::addFile(File file) {
    files.push_back(file);
}

void Directory::addDirectory(Directory directory) {
    directories.push_back(directory);
}
