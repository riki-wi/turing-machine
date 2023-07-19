#ifndef SIMPLE_STR
#define SIMPLE_STR

#pragma once

class ArgumentException
{
private:
    const char *msg;

public:
    ArgumentException()
    {
        msg = (const char *)"Argument exception";
    }

    explicit ArgumentException(const char *error_msg)
    {
        msg = error_msg;
    }

    const char *what()
    {
        return msg;
    }
};

int length_string(const char *str);

int count_symbol(const char *str, char symbol);

long long my_atoi(const char *str);

char *concat(const char *str_one, const char *str_two);

bool string_eq(const char *str_one, const char *str_two);

bool string_empty(const char *str);

int split_string(const char *str, char symbol, char ***mas);

long long polynomial_hash(const char *str);

char *remove_zero_begin(const char *str);

char *remove_space_begin(const char *str);

char *remove_zero_end(const char *str);

#endif