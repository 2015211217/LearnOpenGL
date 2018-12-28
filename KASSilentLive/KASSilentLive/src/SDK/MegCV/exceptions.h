#pragma once

#include <exception>
#include <string>

namespace megcv {

class MegCVException: std::exception {
    protected:
        std::string m_content;
    public:
        MegCVException(const std::string &content);
        const char *what() const noexcept override;
};

}
