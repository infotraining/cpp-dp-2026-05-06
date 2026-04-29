#include "circle_reader_writer.hpp"
#include "../circle.hpp"
#include "../shape_factories.hpp"

using namespace std;
using namespace Drawing;
using namespace Drawing::IO;

namespace
{
    bool is_registered = SingletonShapeRWFactory::instance()
                             .register_creator(make_type_index<Circle>(), [] { return make_unique<CircleReaderWriter>(); });
}

void CircleReaderWriter::read(Shape& shp, std::istream& in)
{
    Point pt;
    int r;

    in >> pt >> r;

    Circle& c = static_cast<Circle&>(shp);
    c.set_coord(pt);
    c.set_radius(r);
}

void CircleReaderWriter::write(const Shape& shp, ostream& out)
{
    const Circle& c = static_cast<const Circle&>(shp);

    out << Circle::id << " " << c.coord() << " " << c.radius() << "\n";
}
