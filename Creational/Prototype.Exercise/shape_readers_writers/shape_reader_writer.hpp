#ifndef SHAPE_READER_WRITER_HPP
#define SHAPE_READER_WRITER_HPP

#include "../shape.hpp"

namespace Drawing
{
    namespace IO
    {
        class ShapeReaderWriter
        {
        public:
            virtual ~ShapeReaderWriter() = default;
            virtual void read(Shape& shp, std::istream& in) = 0;
            virtual void write(const Shape& shp, std::ostream& out) = 0;
        };
    }
}

#endif // SHAPE_READER_WRITER_HPP
