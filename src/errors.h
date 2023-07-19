#ifndef TASK3_TURING_MACHINE_RIKI_WI_ERRORS_H
#define TASK3_TURING_MACHINE_RIKI_WI_ERRORS_H

#include <exception>

class ParserException : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return (const char *) "Rule parsing error";
    }
};

class ArgumentExceptionConsole : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return (const char *) "Wrong number of arguments";
    }
};

class OpenFileException : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return (const char *) "Error opening file";
    }
};

#endif
