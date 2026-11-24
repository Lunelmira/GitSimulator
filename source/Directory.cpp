
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

std::vector<File>& Directory::getFiles() {
    return files;
}

std::vector<Directory>& Directory::getDirectories() {
    return directories;
}

void Directory::addFile(File file) {
    files.push_back(file);
}

void Directory::addDirectory(Directory directory) {
    directories.push_back(directory);
}

bool Directory::hasFile(std::string fileName) const {
    for (int i = 0; i < files.size(); i++) {
        if (files[i].getPath() == fileName) {
            return true;
        }
    }

    return false;
}

bool Directory::hasDirectory(std::string directoryName) const {
    for (int i = 0; i < directories.size(); i++) {
        if (directories[i].getName() == directoryName) {
            return true;
        }
    }

    return false;
}
