
#ifndef GITEXCEPTION_HPP
#define GITEXCEPTION_HPP

#include <string>

class GitException {
private:
    std::string message;

public:
    GitException(std::string msg) {
        message = msg;
    }

    std::string getMessage() const {
        return message;
    }
};

#endif
