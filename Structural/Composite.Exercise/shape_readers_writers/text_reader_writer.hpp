#ifndef TEXTREADERWRITER_HPP
#define TEXTREADERWRITER_HPP

#include "shape_reader_writer.hpp"

namespace Drawing
{
    namespace IO
    {
        class TextReaderWriter : public ShapeReaderWriter
        {
        public:
            void read(Shape& shp, std::istream& in) override;
            void write(const Shape& shp, std::ostream& out) override;
        };
    }
}

#endif // TEXTREADERWRITER_HPP
