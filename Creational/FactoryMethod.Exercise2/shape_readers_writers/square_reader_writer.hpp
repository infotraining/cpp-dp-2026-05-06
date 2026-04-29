#ifndef SQUARE_READER_WRITER_HPP
#define SQUARE_READER_WRITER_HPP

#include "shape_reader_writer.hpp"

namespace Drawing
{
    namespace IO
    {
        class SquareReaderWriter : public ShapeReaderWriter
        {
            // ShapeReaderWriter interface
        public:
            void read(Shape& shp, std::istream& in) override;
            void write(const Shape& shp, std::ostream& out) override;
        };
    }
}
#endif // SQUARE_READER_WRITER_HPP
