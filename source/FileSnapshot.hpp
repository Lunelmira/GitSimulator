
#ifndef FILESNAPSHOT_HPP
#define FILESNAPSHOT_HPP

#include <string>
#include <vector>

class FileSnapshot {
private:
    std::string path;
    std::vector<std::string> content;

public:
    FileSnapshot();

    FileSnapshot(std::string filePath, std::vector<std::string> fileContent);

    std::string getPath() const;

    std::vector<std::string> getContent() const;
};

#endif
