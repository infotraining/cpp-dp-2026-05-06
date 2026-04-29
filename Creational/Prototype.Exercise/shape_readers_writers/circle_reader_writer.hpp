#ifndef CIRCLEREADERWRITER_HPP
#define CIRCLEREADERWRITER_HPP

#include "shape_reader_writer.hpp"

namespace Drawing
{
    namespace IO
    {
        class CircleReaderWriter : public ShapeReaderWriter
        {
        public:
            void read(Shape& shp, std::istream& in) override;
            void write(const Shape& shp, std::ostream& out) override;
        };
    }
}

#endif // CIRCLEREADERWRITER_HPP
