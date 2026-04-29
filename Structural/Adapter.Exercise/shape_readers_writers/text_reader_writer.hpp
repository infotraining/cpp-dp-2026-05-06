#ifndef TEXT_READER_WRITER_HPP
#define TEXT_READER_WRITER_HPP

#include "../text.hpp"
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
#endif // TEXT_READER_WRITER_HPP
