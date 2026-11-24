#ifndef BRANCH_HPP
#define BRANCH_HPP

#include <string>

class Branch {
private:
    std::string name;
    int commitId;

public:
    Branch();

    Branch(std::string branchName, int lastCommitId);

    std::string getName() const;

    int getCommitId() const;

    void setCommitId(int newCommitId);
};

#endif