#include "square_reader_writer.hpp"
#include "../shape_factories.hpp"
#include "../square.hpp"

using namespace std;
using namespace Drawing;
using namespace IO;

namespace
{
    bool is_registered = SingletonShapeRWFactory::instance()
                             .register_creator(make_type_index<Square>(), [] { return make_unique<SquareReaderWriter>(); });
}

void SquareReaderWriter::read(Shape& shp, istream& in)
{
    Square& sqr = static_cast<Square&>(shp);

    Point pt;
    int size;

    in >> pt >> size;

    sqr.set_size(size);
    sqr.set_coord(pt);
}

void SquareReaderWriter::write(const Shape& shp, ostream& out)
{
    const Square& square = static_cast<const Square&>(shp);

    out << Square::id << " " << square.coord() << " " << square.size() << endl;
}
