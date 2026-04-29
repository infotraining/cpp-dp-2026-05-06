#include "text_reader_writer.hpp"
#include "../shape_factories.hpp"
#include "../text.hpp"

using namespace std;
using namespace Drawing;
using namespace Drawing::IO;

namespace
{
    bool is_registered = SingletonShapeRWFactory::instance()
                             .register_creator(make_type_index<Text>(), [] { return make_unique<TextReaderWriter>(); });
}

void Drawing::IO::TextReaderWriter::read(Drawing::Shape& shp, std::istream& in)
{
    Text& text_paragraph = static_cast<Text&>(shp);

    Point pt;
    std::string str;

    in >> pt >> str;

    text_paragraph.set_coord(pt);
    text_paragraph.set_text(str.c_str());
}

void TextReaderWriter::write(const Shape& shp, ostream& out)
{
    const Text& text = static_cast<const Text&>(shp);

    out << Text::id << " " << text.coord() << " " << text.text() << "\n";
}
