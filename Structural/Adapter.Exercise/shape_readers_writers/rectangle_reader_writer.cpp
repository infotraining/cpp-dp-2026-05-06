#include "rectangle_reader_writer.hpp"
#include "../rectangle.hpp"
#include "../shape_factories.hpp"

using namespace std;
using namespace Drawing;
using namespace IO;

namespace
{
    bool is_registered = SingletonShapeRWFactory::instance()
                             .register_creator(make_type_index<Rectangle>(), [] { return make_unique<RectangleReaderWriter>(); });
}

void RectangleReaderWriter::read(Shape& shp, std::istream& in)
{
    Rectangle& rect = static_cast<Rectangle&>(shp);

    Point pt;
    int w, h;

    in >> pt >> w >> h;

    rect.set_coord(pt);
    rect.set_height(h);
    rect.set_width(w);
}

void RectangleReaderWriter::write(const Shape& shp, std::ostream& out)
{
    const Rectangle& rect = static_cast<const Rectangle&>(shp);

    out << Rectangle::id << " " << rect.coord() << " " << rect.width() << " " << rect.height() << std::endl;
}
