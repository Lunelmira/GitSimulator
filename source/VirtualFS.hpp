#ifndef VIRTUALFS_HPP
#define VIRTUALFS_HPP

#include <string>
#include <vector>
#include "Directory.hpp"
#include "FileSnapshot.hpp"

class VirtualFS {
private:
    Directory root;
    std::string currentPath;

    void collectSnapshots(
        const Directory& directory,
        std::string path,
        std::vector<FileSnapshot>& snapshots
    ) const;

public:
    VirtualFS();

    std::string getCurrentPath() const;

    void changeDirectory(std::string path);

    void makeDirectory(std::string name);

    void createFile(std::string name);

    void removeFile(std::string name);

    void removeDirectory(std::string name);

    void listContents();

    void displayFile(std::string name);

    void writeFile(std::string name, std::vector<std::string> content);

    void appendFile(std::string name, std::string line);

    std::vector<FileSnapshot> createSnapshot() const;

    void restoreSnapshot(std::vector<FileSnapshot> snapshots);
};

#endif