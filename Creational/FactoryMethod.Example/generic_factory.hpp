#pragma once

#include <unordered_map>
#include <functional>
#include <stdexcept>
#include <string>
#include <memory>
#include <typeindex>

#include "shape.hpp"
#include "shape_readers_writers/shape_reader_writer.hpp"


template <typename TProduct, typename TId = std::string, typename TCreator = std::function<std::unique_ptr<TProduct>()>>
class GenericFactory
{
    std::unordered_map<TId, TCreator> creators_;
public:
    bool register_creator(const TId& id, TCreator creator)
    {
        return creators_.emplace(id, std::move(creator)).second;
    }

    void unregister_creator(const TId& id)
    {
        creators_.erase(id);
    }

    std::unique_ptr<TProduct> create(const TId& id)
    {
        auto it = creators_.find(id);
        if (it != creators_.end())
        {
            return it->second(); // call the creator function to create the product
        }
        throw std::runtime_error("Unknown id!");
    }
};

template <typename T>
std::type_index make_type_index()
{
    return std::type_index(typeid(T));
}

template <typename T>
std::type_index make_type_index(const T& obj)
{
    return std::type_index(typeid(obj));
}

using ShapeFactory = GenericFactory<Drawing::Shape>;
using ShapeRWFactory = GenericFactory<Drawing::IO::ShapeReaderWriter, std::type_index>;

template <typename T>
class SingletonHolder
{
    SingletonHolder() = default;
public:
    SingletonHolder(const SingletonHolder&) = delete;
    SingletonHolder& operator=(const SingletonHolder&) = delete;

    static T& instance()
    {
        static T unique_instance;

        return unique_instance;
    }
};

using SingletonShapeFactory = SingletonHolder<ShapeFactory>;
using SingletonShapeRWFactory = SingletonHolder<ShapeRWFactory>;