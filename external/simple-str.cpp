#include "simple-str.h"

int length_string(const char *str)
{
    if(str == nullptr || str[0] == '\0')
        return 0;
    int count = 0;
    while(str[count] != '\0')
    {
        count++;
    }
    return count;
}

int count_symbol(const char *str, char symbol)
{
    int count = 0;
    int length = length_string(str);
    for(int i = 0; i < length; i++)
    {
        if(str[i] == symbol)
            count++;
    }
    return count;
}

long long my_atoi(const char *str)
{
    long long result = 0;
    long long rank = 1;

    int length = length_string(str);
    for(int i = length - 1; i >= 1; i--)
    {
        if(str[i] < 48)
            throw ArgumentException();
        else if(str[i] == 48);
        else if(str[i] < 58)
            result += rank * (str[i] - 48);
        else
            throw ArgumentException();

        rank *= 10;
    }

    if(str[0] == 45)
        result *= -1;
    else if(str[0] < 48)
        throw ArgumentException();
    else if(str[0] == 48)
        result = 0;
    else if(str[0] < 58)
        result += rank * (str[0] - 48);
    else
        throw ArgumentException();

    return result;
}

char *concat(const char *str_one, const char *str_two)
{
    char *result = new char[length_string(str_one) + length_string(str_two) + 1];

    int length_str_one = length_string(str_one);
    int length_str_two = length_string(str_two);
    for(int i = 0; i < length_str_one; i++)
    {
        result[i] = str_one[i];
    }
    for(int i = 0; i < length_str_two; i++)
    {
        result[length_str_one + i] = str_two[i];
    }
    result[length_str_one + length_str_two] = '\0';
    return result;
}

bool string_eq(const char *str_one, const char *str_two)
{
    if((str_one == nullptr && str_two != nullptr) || (str_one != nullptr && str_two == nullptr))
        return false;

    if(length_string(str_one) != length_string(str_two))
        return false;

    for(int i = 0; i < length_string(str_one); i++)
    {
        if(str_one[i] != str_two[i])
            return false;
    }
    return true;
}

bool string_empty(const char *str)
{
    if(str == nullptr)
        return true;
    return string_eq(str, "");
}

int split_string(const char *str, char symbol, char ***mas)
{
    int word_len = 1;
    int count = count_symbol(str, symbol) + 1;
    int len = length_string(str);
    int j = 0;

    *mas = new char *[count];
    for(int i = 0; i < len; i++)
    {
        if(str[i] == '\0')
            break;
        if(str[i] == symbol)
        {
            (*mas)[j] = new char[word_len];
            word_len = 0;
            j++;
        }
        word_len++;
    }
    (*mas)[j] = new char[word_len];

    j = 0;
    char *temp = (*mas)[j];
    for(int i = 0; i < len; i++)
    {
        if(str[i] != symbol && str[i] != '\0')
        {
            *temp = *(str + i);
            temp++;
        } else
        {
            j++;
            *temp = '\0';
            temp = ((*mas)[j]);
        }
    }
    *temp = '\0';
    return count;
}

long long polynomial_hash(const char *str)
{
    const int k = 255;
    const int mod = 1e9+7;

    long long res = 0;
    long long rank = 1;
    long long len = length_string(str);
    for(int i = 0; i < len; i++)
    {
        int s = (int) (str[i] - 'a' + 1);
        res = (res + rank * s) % mod;
        rank = (rank * k) % mod;
    }

    return res;
}

char *remove_zero_begin(const char *str)
{
    if(length_string(str) == count_symbol(str, '0'))
    {
        return (char *) "";
    } else
    {
        long long index = 0;
        for(long long i = 0; i < length_string(str); i++)
        {
            if(str[i] != '0')
            {
                index = i;
                break;
            }
        }

        char *res = new char[length_string(str) - index + 1];
        for(long long i = index; i < length_string(str); i++)
        {
            res[i - index] = str[i];
        }
        res[length_string(str) - index] = '\0';
        return res;
    }
}

char *remove_zero_end(const char *str)
{
    if(length_string(str) == count_symbol(str, '0'))
    {
        return (char *)"";
    } else
    {
        long long index = 0;
        for(long long i = 0; i < length_string(str); i++)
        {
            if(str[i] != '0')
            {
                index = i;
            }
        }

        char *res = new char[index + 2]{'\0'};
        for(long long i = 0; i < index + 1; i++)
        {
            res[i] = str[i];
        }
        res[index + 1] = '\0';
        return res;
    }
}

char *remove_space_begin(const char *str)
{
    if(length_string(str) == count_symbol(str, ' '))
    {
        return (char *) "";
    } else
    {
        long long index = 0;
        for(long long i = 0; i < length_string(str); i++)
        {
            if(str[i] != ' ')
            {
                index = i;
                break;
            }
        }

        char *res = new char[length_string(str) - index + 1];
        for(long long i = index; i < length_string(str); i++)
        {
            res[i - index] = str[i];
        }
        res[length_string(str) - index] = '\0';
        return res;
    }
}