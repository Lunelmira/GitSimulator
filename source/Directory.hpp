#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP

#include <string>
#include <vector>
#include "File.hpp"

class Directory {
private:
    std::string name;
    std::vector<File> files;
    std::vector<Directory> directories;

public:
    Directory();
    Directory(std::string directoryName);

    std::string getName() const;

    std::vector<File>& getFiles();
    const std::vector<File>& getFiles() const;

    std::vector<Directory>& getDirectories();
    const std::vector<Directory>& getDirectories() const;

    void addFile(File file);
    void addDirectory(Directory directory);

    bool hasFile(std::string fileName) const;
    bool hasDirectory(std::string directoryName) const;
};

#endif
