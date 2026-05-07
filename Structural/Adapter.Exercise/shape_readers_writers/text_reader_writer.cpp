#include "text_reader_writer.hpp"
#include "../shape_factories.hpp"
#include "../text.hpp"

using namespace std;
using namespace Drawing;
using namespace IO;

// TODO: Register creator for a TextReaderWriter class
namespace 
{
    bool is_registered = SingletonShapeRWFactory::instance()
        .register_creator(make_type_index<Text>(), [] { return make_unique<TextReaderWriter>(); });
}

void TextReaderWriter::read(Shape& shp, istream& in)
{
    // TODO: Implement reading Text from stream
    Point pt;
    string txt;

    in >> pt >> txt;

    Text& text = static_cast<Text&>(shp);
    text.set_coord(pt);
    text.set_text(txt.c_str());
}

void TextReaderWriter::write(const Shape& shp, ostream& out)
{
    // TODO: Implement writing Text to stream
    const Text& text = static_cast<const Text&>(shp);

    out << Text::id << " " << text.coord() << " " << text.text() << "\n";
}
