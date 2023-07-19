#pragma once

#include "List.h"

template<typename T>
class Stack
{
private:
    List<T> stack;

public:
    Stack();

    T top() const;

    void push_stack(const T &value);

    void pop_stack();

    bool is_empty() const;
};

template<typename T>
Stack<T>::Stack() = default;

template<typename T>
T Stack<T>::top() const
{
    return stack.front();
}

template<typename T>
void Stack<T>::push_stack(const T &value)
{
    stack.push_front(value);
}

template<typename T>
void Stack<T>::pop_stack()
{
    stack.pop_front();
}

template<typename T>
bool Stack<T>::is_empty() const
{
    return stack.empty();
}
