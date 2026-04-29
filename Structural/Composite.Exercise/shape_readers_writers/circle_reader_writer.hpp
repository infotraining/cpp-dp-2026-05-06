#ifndef CIRCLEREADERWRITER_H
#define CIRCLEREADERWRITER_H

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

#endif // CIRCLEREADERWRITER_H
