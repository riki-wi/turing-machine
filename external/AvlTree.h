#pragma once
#include "Stack.h"

template<typename T>
class AvlTree
{
protected:
    class AvlNode
    {
    public:
        T value_;
        int height_;
        AvlNode *left_;
        AvlNode *right_;

        explicit AvlNode(T value);

        int get_height();

        int balance_factor();

        void fix_height();
    };

    long long size_;

    AvlNode *root_;

    AvlNode *rotate_right(AvlNode *node);

    AvlNode *rotate_left(AvlNode *node);

    AvlNode *balance(AvlNode *node);

    AvlNode *add_recurse(AvlNode *node, const T &value);

    AvlNode *remove_recurse(AvlNode *node, const T &value);

    AvlNode *remove_min(AvlNode *node);

public:
    AvlTree();

    explicit AvlTree(T value);

    AvlTree(const AvlTree &other);

    AvlTree(AvlTree &&other) noexcept;

    ~AvlTree();

    AvlTree &operator=(const AvlTree &other);

    AvlTree &operator=(AvlTree &&other) noexcept;

    class Iterator
    {
    protected:
        AvlNode *node_;

        Stack<AvlNode *> stack;

        AvlNode *travel_left(AvlNode *node);

        enum flag
        {
            TRAVEL, NO_TRAVEL
        };

        flag flag_travel_;

    public:
        explicit Iterator(AvlNode *node, flag flag_travel = TRAVEL);

        T &operator*();

        bool operator==(const Iterator &other) const;

        bool operator!=(const Iterator &other) const;

        void operator++();

        friend AvlTree;
    };

    void add(const T &value);

    T get_root() const;

    long long get_size() const;

    void remove(const T &value);

    void clear(AvlNode *node);

    Iterator find(const T &value) const;

    Iterator begin() const;

    Iterator end() const;
};

template<typename T>
AvlTree<T>::AvlNode::AvlNode(T value): value_(value), height_(1), left_(nullptr), right_(nullptr)
{
}

template<typename T>
int AvlTree<T>::AvlNode::balance_factor()
{
    return (right_->get_height() - left_->get_height());
}

template<typename T>
int AvlTree<T>::AvlNode::get_height()
{
    if(this == nullptr)
    {
        return 0;
    } else
    {
        return this->height_;
    }
}

template<typename T>
void AvlTree<T>::AvlNode::fix_height()
{
    if(right_->get_height() > left_->get_height())
    {
        height_ = right_->get_height() + 1;
    } else
    {
        height_ = left_->get_height() + 1;
    }
}

template<typename T>
AvlTree<T>::AvlTree(): root_(nullptr), size_(0)
{
}

template<typename T>
AvlTree<T>::AvlTree(T value): root_(new AvlNode(value)), size_(1)
{
}

template<typename T>
AvlTree<T>::AvlTree(const AvlTree &other): root_(nullptr), size_(0)
{
    for(auto iterator = other.begin(); iterator != other.end(); ++iterator)
    {
        add(*iterator);
    }
}

template<typename T>
AvlTree<T>::AvlTree(AvlTree &&other) noexcept: root_(other.root_), size_(other.size_)
{
    other.root_ = nullptr;
    other.size_ = 0;
}

template<typename T>
AvlTree<T>::~AvlTree()
{
    clear(root_);
}

template<typename T>
AvlTree<T> &AvlTree<T>::operator=(const AvlTree &other)
{
    if(this != &other)
    {
        for(auto iterator = other.begin(); iterator != other.end(); ++iterator)
        {
            add(*iterator);
        }
    }
    return *this;
}

template<typename T>
AvlTree<T> &AvlTree<T>::operator=(AvlTree &&other) noexcept
{
    if(this != &other)
    {
        clear(root_);
        root_ = other.root_;
        size_ = other.size_;
        other.root_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

template<typename T>
AvlTree<T>::Iterator::Iterator(AvlTree::AvlNode *node, flag flag_travel): node_(node), flag_travel_(flag_travel)
{
    if(flag_travel_ == 0)
    {
        node_ = travel_left(node);
    }
}

template<typename T>
T &AvlTree<T>::Iterator::operator*()
{
    if(node_)
    {
        return node_->value_;
    } else
    {
        throw NullPointerException();
    }
}

template<typename T>
bool AvlTree<T>::Iterator::operator==(const AvlTree::Iterator &other) const
{
    if(this == &other)
    {
        return true;
    }
    return node_ == other.node_;
}

template<typename T>
bool AvlTree<T>::Iterator::operator!=(const AvlTree::Iterator &other) const
{
    return !(this->operator==(other));
}

template<typename T>
void AvlTree<T>::Iterator::operator++()
{
    if(node_->right_ != nullptr)
    {
        node_ = travel_left(node_->right_);
    } else if(!stack.is_empty())
    {
        node_ = stack.top();
        stack.pop_stack();
    } else
    {
        node_ = nullptr;
    }
}

template<typename T>
typename AvlTree<T>::AvlNode *AvlTree<T>::Iterator::travel_left(AvlTree::AvlNode *node)
{
    if(node == nullptr)
    {
        return nullptr;
    }
    while(node->left_ != nullptr)
    {
        stack.push_stack(node);
        node = node->left_;
    }
    return node;
}

template<typename T>
T AvlTree<T>::get_root() const
{
    if(this->root_)
    {
        return this->root_->value_;

    } else
    {
        throw NullPointerException();
    }
}

template<typename T>
typename AvlTree<T>::AvlNode *AvlTree<T>::rotate_right(AvlTree::AvlNode *node)
{
    AvlNode *current = node->left_;
    node->left_ = current->right_;
    current->right_ = node;
    node->fix_height();
    current->fix_height();
    return current;
}

template<typename T>
typename AvlTree<T>::AvlNode *AvlTree<T>::rotate_left(AvlTree::AvlNode *node)
{
    AvlNode *current = node->right_;
    node->right_ = current->left_;
    current->left_ = node;
    node->fix_height();
    current->fix_height();
    return current;
}

template<typename T>
typename AvlTree<T>::AvlNode *AvlTree<T>::balance(AvlTree::AvlNode *node)
{
    node->fix_height();
    if(node->balance_factor() == 2)
    {
        if(node->right_->balance_factor() < 0)
        {
            node->right_ = rotate_right(node->right_);
        }
        return rotate_left(node);
    } else if(node->balance_factor() == -2)
    {
        if(node->left_->balance_factor() > 0)
        {
            node->left_ = rotate_left(node->left_);
        }
        return rotate_right(node);
    } else
    {
        return node;
    }
}

template<typename T>
typename AvlTree<T>::AvlNode *AvlTree<T>::add_recurse(AvlTree::AvlNode *node, const T &value)
{
    if(node == nullptr)
    {
        return new AvlNode(value);
    }
    if(node->value_ < value)
    {
        node->right_ = add_recurse(node->right_, value);
    } else
    {
        node->left_ = add_recurse(node->left_, value);
    }
    return balance(node);
}

template<typename T>
typename AvlTree<T>::AvlNode *AvlTree<T>::remove_recurse(AvlTree::AvlNode *node, const T &value)
{
    if(node == nullptr)
    {
        return nullptr;
    }
    if(value < node->value_)
    {
        node->left_ = remove_recurse(node->left_, value);
    } else if(node->value_ < value)
    {
        node->right_ = remove_recurse(node->right_, value);
    } else
    {
        AvlNode *left = node->left_;
        AvlNode *right = node->right_;
        delete node;
        this->size_--;
        if(right == nullptr)
        {
            return left;
        }
        AvlNode *min = right;
        while(min->left_)
        {
            min = min->left_;
        }
        min->right_ = remove_min(right);
        min->left_ = left;
        return balance(min);
    }
    return balance(node);
}

template<typename T>
void AvlTree<T>::add(const T &value)
{
    root_ = add_recurse(root_, value);
    this->size_++;
}

template<typename T>
void AvlTree<T>::remove(const T &value)
{
    root_ = remove_recurse(root_, value);
}

template<typename T>
typename AvlTree<T>::Iterator AvlTree<T>::find(const T &value) const
{
    if(root_)
    {
        AvlNode *current = root_;
        while(current)
        {
            if(value < current->value_)
            {
                current = current->left_;
            } else if(current->value_ < value)
            {
                current = current->right_;
            } else
            {
                return Iterator(current, Iterator::NO_TRAVEL);
            }
        }
    }
    return Iterator(nullptr);
}

template<typename T>
typename AvlTree<T>::Iterator AvlTree<T>::begin() const
{
    return Iterator(root_);
}

template<typename T>
typename AvlTree<T>::Iterator AvlTree<T>::end() const
{
    return Iterator(nullptr);
}

template<typename T>
void AvlTree<T>::clear(AvlNode *node)
{
    if(node != nullptr)
    {
        if(node->left_ != nullptr)
        {
            clear(node->left_);
        }
        if(node->right_ != nullptr)
        {
            clear(node->right_);
        }
        delete node;
    }
}

template<typename T>
long long AvlTree<T>::get_size() const
{
    return size_;
}

template<typename T>
typename AvlTree<T>::AvlNode *AvlTree<T>::remove_min(AvlTree::AvlNode *node)
{
    if(node->left_ == 0)
    {
        return node->right_;
    }
    node->left_ = remove_min(node->left_);
    return balance(node);
}
