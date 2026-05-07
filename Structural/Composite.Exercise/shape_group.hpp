#ifndef SHAPE_GROUP_HPP
#define SHAPE_GROUP_HPP

#include <memory>
#include <vector>

#include "shape.hpp"

namespace Drawing
{
    // TODO: implement a composite for shapes
    // TODO: implement Iterator pattern for ShapeGroup composite that allows iterating over aggregated shapes
    class ShapeGroup : public CloneableShape<ShapeGroup>
    {
        std::vector<std::unique_ptr<Shape>> shapes_;
    public:
        static constexpr auto id = "ShapeGroup";

        using iterator = typename std::vector<std::unique_ptr<Shape>>::iterator;
        using const_iterator = typename std::vector<std::unique_ptr<Shape>>::const_iterator;

        ShapeGroup() = default;

        ShapeGroup(const ShapeGroup& source)
        {
            for(const auto& shp : source.shapes_)
            {
                shapes_.push_back(shp->clone());
            }
        }

        ShapeGroup& operator=(const ShapeGroup& source)
        {
            ShapeGroup temp{source}; // cc
            swap(temp);

            return *this;
        }

        ShapeGroup(ShapeGroup&&) = default;
        ShapeGroup& operator=(ShapeGroup&&) = default;

        void swap(ShapeGroup& other)
        {
            shapes_.swap(other.shapes_);
        }

        void add_shape(std::unique_ptr<Shape> shp)
        {
            shapes_.push_back(std::move(shp));
        }

        void draw() const override
        {
            for(const auto& shp : shapes_)
                shp->draw();
        }

        void move(int dx, int dy) override
        {
            for(auto& shp : shapes_)
            {
                shp->move(dx, dy);
            }
        }

        size_t size() const
        {
            return shapes_.size();
        }

        iterator begin()
        {
            return shapes_.begin();
        }

        iterator end()
        {
            return shapes_.end();
        }

        const_iterator begin() const
        {
            return shapes_.begin();
        }

        const_iterator end() const
        {
            return shapes_.end();
        }
    };
}

#endif // SHAPE_GROUP_HPP
