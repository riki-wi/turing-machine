#pragma once
#ifndef SIMPLEMAP_H
#define SIMPLEMAP_H

#include "AvlTree.h"

template<typename T, typename L>
class Simple_Map
{
private:
    class Pair
    {
    private:
        T key_;

        L value_;
    public:
        Pair();

        explicit Pair(const T &key);

        Pair(const T &key, const L &value);

        T get_key() const;

        L get_value() const;

        void set_key(const T &new_key);

        void set_value(const L &new_value);

        bool operator==(const Pair &right) const;

        bool operator<(const Pair &right) const;
    };

    AvlTree<Pair> tree;

public:
    Simple_Map();

    void add(const T &key, const L &value);

    void remove(const T &key);

    bool find_by_key(const T &key) const;

    L get_by_key(const T &key) const;

    void change_by_key(const T &key, const L &new_value);

    long long size();
};

template<typename T, typename L>
Simple_Map<T, L>::Pair::Pair() = default;

template<typename T, typename L>
Simple_Map<T, L>::Pair::Pair(const T &key) : key_(key)
{
}

template<typename T, typename L>
Simple_Map<T, L>::Pair::Pair(const T &key, const L &value) : key_(key), value_(value)
{
}

template<typename T, typename L>
T Simple_Map<T, L>::Pair::get_key() const
{
    return key_;
}

template<typename T, typename L>
L Simple_Map<T, L>::Pair::get_value() const
{
    return value_;
}

template<typename T, typename L>
void Simple_Map<T, L>::Pair::set_key(const T &new_key)
{
    key_ = new_key;
}

template<typename T, typename L>
void Simple_Map<T, L>::Pair::set_value(const L &new_value)
{
    value_ = new_value;
}

template<typename T, typename L>
bool Simple_Map<T, L>::Pair::operator==(const Simple_Map::Pair &right) const
{
    return this->key_ == right.key_;
}

template<typename T, typename L>
bool Simple_Map<T, L>::Pair::operator<(const Simple_Map::Pair &right) const
{
    return this->key_ < right.key_;
}

template<typename T, typename L>
Simple_Map<T, L>::Simple_Map() = default;

template<typename T, typename L>
void Simple_Map<T, L>::add(const T &key, const L &value)
{
    Pair pair(key, value);
    tree.add(pair);
}

template<typename T, typename L>
void Simple_Map<T, L>::remove(const T &key)
{
    for(auto iter = tree.begin(); iter != tree.end; ++iter)
    {
        if(iter.operator*().get_key() == key)
        {
            tree.remove(iter.operator*().get_key(), iter.operator*().get_value());
        }
    }
}

template<typename T, typename L>
bool Simple_Map<T, L>::find_by_key(const T &key) const
{
    auto iter = tree.find(Pair(key));
    if(iter != tree.end())
    {
        return true;
    } else
    {
        return false;
    }
}

template<typename T, typename L>
void Simple_Map<T, L>::change_by_key(const T &key, const L &new_value)
{
    auto iter = tree.find(Pair(key));
    if(iter != tree.end())
    {
        iter.operator*().set_value(new_value);
    }
}

template<typename T, typename L>
long long Simple_Map<T, L>::size()
{
    return tree.get_size();
}

template<typename T, typename L>
L Simple_Map<T, L>::get_by_key(const T &key) const
{
    if(find_by_key(key))
    {
        auto iter = tree.find(Pair(key));
        return iter.operator*().get_value();
    }
}

#endif


