#include "square_reader_writer.hpp"
#include "../square.hpp"

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
