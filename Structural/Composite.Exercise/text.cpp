#include "text.hpp"
#include "shape_factories.hpp"

using namespace std;
using namespace Drawing;

namespace
{
    bool is_registered = SingletonShapeFactory::instance().register_creator(
        Text::id, [] { return make_unique<Text>(); });
}

Text::Text(int x, int y, const string& text)
    : ShapeBase{x, y}, LegacyCode::Paragraph{text.c_str()}
{
}

string Text::text() const
{
    return get_paragraph();
}

void Text::set_text(const string& text)
{
    set_paragraph(text.c_str());
}

void Text::draw() const
{
    render_at(coord().x, coord().y);
}
