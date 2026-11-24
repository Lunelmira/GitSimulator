
#ifndef FILE_HPP
#define FILE_HPP

#include <string>
#include <vector>
#include "FileSnapshot.hpp"

class File {
private:
    std::string path;
    std::vector<std::string> content;

public:
    File();

    File(std::string filePath, std::vector<std::string> fileContent);

    std::string getPath() const;

    std::vector<std::string> getContent() const;

    void setContent(std::vector<std::string> newContent);

    void appendLine(std::string line);

    FileSnapshot createSnapshot() const;
};

#endif
