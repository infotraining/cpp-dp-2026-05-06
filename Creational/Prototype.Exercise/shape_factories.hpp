#ifndef SHAPE_FACTORIES_HPP
#define SHAPE_FACTORIES_HPP

#include "generic_factory.hpp"
#include "shape.hpp"
#include "shape_readers_writers/shape_reader_writer.hpp"
#include "singleton.hpp"
#include <typeindex>

namespace Drawing
{
    using ShapeFactory = GenericFactory<Drawing::Shape>;
    using SingletonShapeFactory = SingletonHolder<ShapeFactory>;

    using ShapeRWFactory = GenericFactory<Drawing::IO::ShapeReaderWriter, std::type_index>;
    using SingletonShapeRWFactory = SingletonHolder<ShapeRWFactory>;

    template <typename T>
    std::type_index make_type_index(const T& obj)
    {
        return std::type_index(typeid(obj));
    }

    template <typename T>
    std::type_index make_type_index()
    {
        return std::type_index(typeid(T));
    }
}

#endif // SHAPE_FACTORIES_HPP
