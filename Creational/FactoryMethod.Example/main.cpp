#include <cassert>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include <typeindex>

#include "rectangle.hpp"
#include "shape.hpp"
#include "shape_readers_writers/rectangle_reader_writer.hpp"
#include "shape_readers_writers/square_reader_writer.hpp"
#include "square.hpp"
#include "generic_factory.hpp"

using namespace std;
using namespace Drawing;
using namespace Drawing::IO;

// ShapeFactory shape_factory;
// ShapeRWFactory shape_rw_factory;

// using ShapeCreator = std::function<unique_ptr<Shape>()>;



// class ShapeFactory
// {
//     std::unordered_map<std::string, ShapeCreator> creators_;
// public:
//     void register_shape(const string& id, ShapeCreator creator)
//     {
//         creators_[id] = std::move(creator);
//     }

//     void unregister_shape(const string& id)
//     {
//         creators_.erase(id);
//     }

//     std::unique_ptr<Shape> create_shape(const string& id)
//     {
//         auto it = creators_.find(id);
//         if (it != creators_.end())
//         {
//             return it->second(); // call the creator function to create the shape
//         }
//         throw runtime_error("Unknown shape id: " + id);
//     }
// };

// using ShapeRWCreator = std::function<std::unique_ptr<ShapeReaderWriter>()>;

// class ShapeRWFactory
// {
//     std::unordered_map<std::type_index, ShapeRWCreator> rw_creators_;

// public:
//     void register_shape_rw(const std::type_index& shape_type, ShapeRWCreator creator)
//     {
//         rw_creators_[shape_type] = std::move(creator);
//     }

//     void unregister_shape_rw(const std::type_index& shape_type)
//     {
//         rw_creators_.erase(shape_type);
//     }

//     std::unique_ptr<ShapeReaderWriter> create_shape_rw(std::type_index shape_type)
//     {
//         auto it = rw_creators_.find(shape_type);
//         if (it != rw_creators_.end())
//         {
//             return it->second(); // call the creator function to create the shape reader/writer
//         }
//         throw runtime_error("Unknown shape type: " + string(shape_type.name()));
//     }
// };

// Static factories for Shape and ShapeReaderWriter (alternative to using separate factory classes)

// unique_ptr<Shape> create_shape(const string& id)
// {
//     if (id == Rectangle::id)
//         return make_unique<Rectangle>();
//     else if (id == Square::id)
//         return make_unique<Square>();

//     throw runtime_error("Unknown shape id");
// }

// unique_ptr<ShapeReaderWriter> create_shape_rw(Shape& shape)
// {
//     if (typeid(shape) == typeid(Rectangle))
//         return make_unique<RectangleReaderWriter>();
//     else if (typeid(shape) == typeid(Square))
//         return make_unique<SquareReaderWriter>();

//     throw runtime_error("Unknown shape id");
// }

class GraphicsDoc
{
    ShapeFactory& shape_factory_;
    ShapeRWFactory& shape_rw_factory_;
    std::vector<unique_ptr<Shape>> shapes_;

public:
    GraphicsDoc(ShapeFactory& shape_factory, ShapeRWFactory& shape_rw_factory)
        : shape_factory_(shape_factory), shape_rw_factory_(shape_rw_factory)
    {
    }

    void add(unique_ptr<Shape> shp)
    {
        shapes_.push_back(std::move(shp));
    }

    void render()
    {
        for (const auto& shp : shapes_)
            shp->draw();
    }

    void load(const string& filename)
    {
        ifstream file_in{filename};

        if (!file_in)
        {
            cout << "File not found!" << endl;
            exit(1);
        }

        while (file_in)
        {
            string shape_id;
            file_in >> shape_id;

            if (!file_in)
                return;

            cout << "Loading " << shape_id << "..." << endl;

            auto shape = shape_factory_.create(shape_id);
            auto shape_rw = shape_rw_factory_.create(make_type_index(*shape));

            shape_rw->read(*shape, file_in);

            shapes_.push_back(std::move(shape));
        }
    }

    void save(const string& filename)
    {
        ofstream file_out{filename};

        for (const auto& shp : shapes_)
        {
            auto shape_rw = shape_rw_factory_.create(make_type_index(*shp));
            shape_rw->write(*shp, file_out);
        }
    }
};

int main()
{
    cout << "Start..." << endl;

    // ShapeFactory shape_factory;
    // shape_factory.register_creator(Rectangle::id, []() { return make_unique<Rectangle>(); });
    // shape_factory.register_creator(Square::id, []() { return make_unique<Square>(); });
    // shape_factory.register_shape("Circle", []() { return make_unique<Circle>(); });

    // ShapeRWFactory shape_rw_factory;
    // shape_rw_factory.register_creator(make_type_index<Rectangle>(), []() { return make_unique<RectangleReaderWriter>(); });
    // shape_rw_factory.register_creator(make_type_index<Square>(), []() { return make_unique<SquareReaderWriter>(); });
    // shape_rw_factory.register_creator(make_type_index<Circle>(), []() { return make_unique<CircleReaderWriter>(); });

    GraphicsDoc doc(SingletonShapeFactory::instance(), SingletonShapeRWFactory::instance());

    doc.load("drawing_fm_example.txt");

    cout << "\n";

    doc.render();

    doc.save("new_drawing.txt");
}
