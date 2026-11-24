#include "Branch.hpp"

Branch::Branch() {
    name = "";
    commitId = -1;
}

Branch::Branch(std::string branchName, int lastCommitId) {
    name = branchName;
    commitId = lastCommitId;
}

std::string Branch::getName() const {
    return name;
}

int Branch::getCommitId() const {
    return commitId;
}

void Branch::setCommitId(int newCommitId) {
    commitId = newCommitId;
}