#include "Commit.hpp"

Commit::Commit() {
    id = 0;
    message = "";
    authorName = "";
    authorEmail = "";
    timestamp = "";
    snapshot = {};
    parent1Id = -1;
    parent2Id = -1;
}

Commit::Commit(int commitId,
               std::string commitMessage,
               std::string name,
               std::string email,
               std::string time,
               std::vector<FileSnapshot> files,
               int firstParent,
               int secondParent) {

    id = commitId;
    message = commitMessage;
    authorName = name;
    authorEmail = email;
    timestamp = time;
    snapshot = files;
    parent1Id = firstParent;
    parent2Id = secondParent;
}

int Commit::getId() const {
    return id;
}

std::string Commit::getMessage() const {
    return message;
}

std::string Commit::getAuthorName() const {
    return authorName;
}

std::string Commit::getAuthorEmail() const {
    return authorEmail;
}

std::string Commit::getTimestamp() const {
    return timestamp;
}

std::vector<FileSnapshot> Commit::getSnapshot() const {
    return snapshot;
}

int Commit::getParent1Id() const {
    return parent1Id;
}

int Commit::getParent2Id() const {
    return parent2Id;
}