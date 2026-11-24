#ifndef COMMIT_HPP
#define COMMIT_HPP

#include <string>
#include <vector>
#include "FileSnapshot.hpp"

class Commit {
private:
    int id;
    std::string message;
    std::string authorName;
    std::string authorEmail;
    std::string timestamp;
    std::vector<FileSnapshot> snapshot;
    int parent1Id;
    int parent2Id;

public:
    Commit();

    Commit(int commitId,
           std::string commitMessage,
           std::string name,
           std::string email,
           std::string time,
           std::vector<FileSnapshot> files,
           int firstParent,
           int secondParent);

    int getId() const;

    std::string getMessage() const;

    std::string getAuthorName() const;

    std::string getAuthorEmail() const;

    std::string getTimestamp() const;

    std::vector<FileSnapshot> getSnapshot() const;

    int getParent1Id() const;

    int getParent2Id() const;
};

#endif