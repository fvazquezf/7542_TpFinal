#include <cstdarg>
#include <cstdio>
#include "Exception.h"

Exception::Exception(const char *fmt, ...) noexcept {
    va_list args;
    va_start(args, fmt);
    vsnprintf(error, ERR_LEN, fmt, args);
    va_end(args);

    error[ERR_LEN - 1] = 0;
}

const char *Exception::what() const noexcept {
    return error;
}

Exception::~Exception() noexcept {
}

Exception::Exception(Exception &&other) {
    for (size_t i = 0; i < ERR_LEN; ++i){
        error[i] = other.error[i];
    }
}

Exception &Exception::operator=(Exception &&other) {
    if (this == &other) {
        return *this;
    }

    for (size_t i = 0; i < ERR_LEN; ++i){
        error[i] = other.error[i];
    }

    return *this;
}
