#include "shape_group_reader_writer.hpp"

using namespace std;
using namespace Drawing;
using namespace Drawing::IO;

namespace
{
    bool is_registered = SingletonShapeRWFactory::instance()
                             .register_creator(
                                 make_type_index<ShapeGroup>(),
                                 [] { return make_unique<ShapeGroupReaderWriter>(SingletonShapeFactory::instance(), SingletonShapeRWFactory::instance()); });
}

void ShapeGroupReaderWriter::read(Shape& shp, istream& in)
{
    ShapeGroup& shape_group = static_cast<ShapeGroup&>(shp);

    int size;

    in >> size;

    for (int i = 0; i < size; ++i)
    {
        string shape_id;
        in >> shape_id;
        cout << "Loading in ShapeGroup: " << shape_id << "..." << endl;

        auto shape = shape_factory_.create(shape_id);
        auto shape_rw = shape_rw_factory_.create(make_type_index(*shape));

        shape_rw->read(*shape, in);

        shape_group.add_shape(std::move(shape));
    }
}

void ShapeGroupReaderWriter::write(const Shape& shp, ostream& out)
{
    const ShapeGroup& shape_group = static_cast<const ShapeGroup&>(shp);

    out << ShapeGroup::id << " " << shape_group.size() << "\n";

    for (const auto& s : shape_group)
    {
        auto shape_rw = shape_rw_factory_.create(make_type_index(*s));
        shape_rw->write(*s, out);
    }
}