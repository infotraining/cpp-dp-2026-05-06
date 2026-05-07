#include "text.hpp"
#include "shape_factories.hpp"

using namespace Drawing;

namespace
{
    // TODO - register creator for a Text class
    bool is_registered = SingletonShapeFactory::instance()
                             .register_creator(Text::id, []
                                               { return std::make_unique<Text>(); });
}

Text::Text(int x, int y, const std::string& txt)
    : ShapeBase{x, y}, LegacyCode::Paragraph{txt.c_str()}
{
}

std::string Text::text() const
{
    return get_paragraph();
}

void Text::set_text(const std::string& txt)
{
    set_paragraph(txt.c_str());
}

void Text::draw() const
{
    render_at(coord().x, coord().y);
}