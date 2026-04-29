#include "bridge.hpp"

using namespace std;

#define API_1

#ifdef API_1
auto drawing_api = make_shared<DrawingAPI1>();
#else   
auto drawing_api = make_shared<DrawingAPI2>();
#endif

class IShapeFactory
{
public:
    virtual ~IShapeFactory() = default;
    virtual unique_ptr<Shape> create_line(int x1, int y1, int x2, int y2) const = 0;
    virtual unique_ptr<Shape> create_rectangle(int x, int y, int width, int height) const = 0;
};

class ShapeFactory : public IShapeFactory
{
    shared_ptr<Drawing> drawing_;

public:
    ShapeFactory(std::shared_ptr<Drawing> drawing)
        : drawing_(drawing)
    { }

    unique_ptr<Shape> create_line(int x1, int y1, int x2, int y2) const override
    {
        return make_unique<Line>(drawing_, x1, y1, x2, y2);
    }

    unique_ptr<Shape> create_rectangle(int x, int y, int width, int height) const override  
    {
        return make_unique<Rectangle>(drawing_, x, y, width, height);
    }
};

int main()
{
    // explicit shape creation without factory
    Line line(drawing_api, 0, 0, 100, 100);
    line.draw();

    Rectangle rect(drawing_api, 50, 50, 200, 100);
    rect.draw();

    cout << "----" << endl;

    // shape creation via factory
    ShapeFactory factory(drawing_api);

    auto line2 = factory.create_line(10, 10, 110, 110);
    line2->draw();

    auto rect2 = factory.create_rectangle(60, 60, 210, 110);
    rect2->draw();  
}