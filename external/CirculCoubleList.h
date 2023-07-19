#ifndef TASK3_TURING_MACHINE_RIKI_WI_CIRCULDOUBLELIST_H
#define TASK3_TURING_MACHINE_RIKI_WI_CIRCULDOUBLELIST_H

class Null_Pointer_Exception
{
public:
    const char *what()
    {
        return (const char *) "Null pointer dereference";
    }
};

template<typename T>
class Circle_Double_List
{
private:
    struct Node
    {
    private:
        T data;
        Node *next;
        Node *prev;
    public:
        Node();

        explicit Node(const T &data) : data(data), next(nullptr), prev(nullptr)
        {
        };
        friend Circle_Double_List;
    };

    Node *current_;

    long long size_;

public:
    class Iterator
    {
    private:

        Node *node_;

    public:
        explicit Iterator(Node *node);

        T &operator*();

        bool operator==(const Iterator &other) const;

        bool operator!=(const Iterator &other) const;

        void operator++();

        void operator--();

        friend Circle_Double_List;
    };

    Circle_Double_List();

    Circle_Double_List(const Circle_Double_List &other);

    Circle_Double_List(Circle_Double_List &&other) noexcept;

    Circle_Double_List(const T &value, long long size);

    ~Circle_Double_List();

    Circle_Double_List &operator=(const Circle_Double_List &other);

    Circle_Double_List &operator=(Circle_Double_List &&other) noexcept;

    void push(const T &value);

    long long size() const;

    void clear();

    void pop();

    Iterator end() const;

    Iterator begin() const;
};

template<typename T>
Circle_Double_List<T>::Node::Node()
{
}

template<typename T>
Circle_Double_List<T>::Iterator::Iterator(Node *node): node_(node)
{
}

template<typename T>
T &Circle_Double_List<T>::Iterator::operator*()
{
    if(node_)
    {
        return node_->data;
    } else
    {
        throw Null_Pointer_Exception();
    }
}

template<typename T>
bool Circle_Double_List<T>::Iterator::operator==(const Circle_Double_List::Iterator &other) const
{
    if(this == &other)
    {
        return true;
    }
    return node_ == other.node_;
}

template<typename T>
bool Circle_Double_List<T>::Iterator::operator!=(const Circle_Double_List::Iterator &other) const
{
    return !(this->operator==(other));
}

template<typename T>
void Circle_Double_List<T>::Iterator::operator++()
{
    if(node_)
    {
        node_ = node_->next;
    }
}

template<typename T>
void Circle_Double_List<T>::Iterator::operator--()
{
    if(node_)
    {
        node_ = node_->prev;
    }
}

template<typename T>
typename Circle_Double_List<T>::Iterator Circle_Double_List<T>::begin() const
{
    return Iterator(current_);
}

template<typename T>
typename Circle_Double_List<T>::Iterator Circle_Double_List<T>::end() const
{
    return Iterator(current_->prev);
}

template<typename T>
long long Circle_Double_List<T>::size() const
{
    return size_;
}

template<typename T>
Circle_Double_List<T>::Circle_Double_List(): current_(nullptr), size_(0)
{
}

template<typename T>
Circle_Double_List<T>::Circle_Double_List(const T &value, long long int size): current_(nullptr), size_(0)
{
    for(int i = 0; i < size; i++)
    {
        push(value);
    }
}

template<typename T>
void Circle_Double_List<T>::push(const T &value)
{
    Node *node = new Node(value);
    if(node && current_)
    {
        node->next = current_;
        node->prev = current_->prev;
        current_->prev = node;
        node->prev->next = node;
        current_ = node;
        size_++;
    }

    if(node && !current_)
    {
        node->next = node;
        node->prev = node;
        current_ = node;
        size_++;
    }
}

template<typename T>
void Circle_Double_List<T>::clear()
{
    while(current_ && size_ > 0)
    {
        Node *temp = current_;
        current_ = current_->next;
        size_--;
        delete temp;
    }
}

template<typename T>
void Circle_Double_List<T>::pop()
{
    Node *node = current_;
    if(node)
    {
        current_ = current_->next;
        current_->next->prev = current_->prev;
        delete node;
        size_--;
    }
}

template<typename T>
Circle_Double_List<T>::~Circle_Double_List()
{
    clear();
}

template<typename T>
Circle_Double_List<T>::Circle_Double_List(const Circle_Double_List &other): size_(0), current_(nullptr)
{
    for(auto iterator = other.end(); iterator != other.begin(); --iterator)
    {
        push(*iterator);
    }
}

template<typename T>
Circle_Double_List<T>::Circle_Double_List(Circle_Double_List &&other) noexcept: current_(other.current_),
                                                                                size_(other.size_)
{
    other.current_ = nullptr;
    other.size_ = 0;
}

template<typename T>
Circle_Double_List<T> &Circle_Double_List<T>::operator=(const Circle_Double_List &other)
{
    size_ = 0;
    if(this != &other)
    {
        for(auto iterator = other.end(); iterator != other.begin(); --iterator)
        {
            push(*iterator);
        }
    }
    return *this;
}

template<typename T>
Circle_Double_List<T> &Circle_Double_List<T>::operator=(Circle_Double_List &&other) noexcept
{
    if(this != &other)
    {
        this->clear();
        current_ = other.current_;
        size_ = other.size_;
        other.current_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

#endif