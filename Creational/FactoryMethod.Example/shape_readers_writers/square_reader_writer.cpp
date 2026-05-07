#include "square_reader_writer.hpp"
#include "../square.hpp"
#include "../generic_factory.hpp"

static bool is_registered = 
    SingletonShapeRWFactory::instance()
        .register_creator(make_type_index<Drawing::Square>(), []() { return std::make_unique<Drawing::IO::SquareReaderWriter>(); });

void Drawing::IO::SquareReaderWriter::read(Drawing::Shape& shp, std::istream& in)
{
    Square& sqr = static_cast<Square&>(shp);

    Point pt;
    int size;

    in >> pt >> size;

    sqr.set_size(size);
    sqr.set_coord(pt);
}

void Drawing::IO::SquareReaderWriter::write(const Drawing::Shape& shp, std::ostream& out)
{
    const Square& square = static_cast<const Drawing::Square&>(shp);

    out << Square::id << " " << square.coord() << " " << square.size() << std::endl;
}
