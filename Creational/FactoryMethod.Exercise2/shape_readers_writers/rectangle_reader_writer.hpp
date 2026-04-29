#ifndef RECTANGLE_READER_WRITER_HPP
#define RECTANGLE_READER_WRITER_HPP

#include "shape_reader_writer.hpp"

namespace Drawing
{
    namespace IO
    {
        class RectangleReaderWriter : public ShapeReaderWriter
        {
            // ShapeReaderWriter interface
        public:
            void read(Shape& shp, std::istream& in) override;
            void write(const Shape& shp, std::ostream& out) override;
        };
    }
}

#endif // RECTANGLE_READER_WRITER_HPP
