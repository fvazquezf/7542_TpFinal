#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#define ERR_LEN 256

class Exception : public std::exception{
private:
    char error[ERR_LEN];
public:
    explicit Exception(const char* fmt, ...) noexcept;
    const char *what() const noexcept override;
    ~Exception() noexcept;

    Exception(const Exception& other) = delete;
    Exception& operator=(const Exception& other) = delete;

    Exception(Exception&& other);
    Exception& operator=(Exception&& other);
    
};


#endif
