#pragma once

#include <string>
#include <optional>

using KeyType = std::string;
using ValueType = int;

/*
(Comment)
An interface to satisfy the requirements. 
Allows for different parrallel implementations (substitution) and
allows fakes to implement the interface for unit testing purposes.
Avoided templates for key and value type since datatypes were clearly defined.
*/

class HashTableInterface {
public:
    virtual bool insert(const KeyType& key, ValueType value) = 0;
    virtual void remove(const KeyType& key) = 0;
    virtual std::optional<ValueType> get(const KeyType& key) = 0;
    virtual std::optional<ValueType> get_last() const = 0;
    virtual std::optional<ValueType> get_first() const = 0;
};
