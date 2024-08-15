#pragma once

#include <string>

using KeyType = std::string;
using ValueType = std::string;

/*
(Comment)
An interface to satisfy the requirements. 
Allows for different parrallel implementations (substitution) and
allows fakes to implement the interface for unit testing purposes.
Avoided templates for key and value type since datatypes were clearly defined.
*/

class HashTableInterface {
public:
    virtual void insert(KeyType key, ValueType value) = 0;
    virtual void remove(KeyType key) = 0;
    virtual ValueType get(KeyType key) = 0;
    virtual ValueType get_last() const = 0;
    virtual ValueType get_first() const = 0;
};
