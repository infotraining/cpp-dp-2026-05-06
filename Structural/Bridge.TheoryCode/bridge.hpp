#ifndef BRIDGE_HPP_
#define BRIDGE_HPP_

#include <iostream>
#include <memory>
#include <vector>

namespace API_1
{
    void draw_line(int x1, int y1, int x2, int y2)
    {
        std::cout << "API_1: Drawing line from (" << x1 << ", " << y1 << ") to (" << x2 << ", " << y2 << ")\n";
    }

    void draw_ellipse(int x, int y, int rx, int ry)
    {
        std::cout << "API_1: Drawing ellipse at (" << x << ", " << y << ") with radii (" << rx << ", " << ry << ")\n";
    }
}

namespace API_2
{
    using Point = std::pair<int, int>;

    void render_line(const Point& p1, const Point& p2)
    {
        std::cout << "API_2: Drawing line from (" << p1.first << ", " << p1.second << ") to (" << p2.first << ", " << p2.second << ")\n";
    }

    void render_ellipse(int x, int y, int rx, int ry)
    {
        std::cout << "API_2: Drawing ellipse at (" << x << ", " << y << ") with radii (" << rx << ", " << ry << ")\n";
    }

    void render_polygon(const std::vector<Point>& points)
    {
        std::cout << "API_2: Drawing polygon with points: ";
        for (const auto& point : points)
            std::cout << "(" << point.first << ", " << point.second << ") ";
        std::cout << "\n";
    }
}

/////////////////////////////////////////////////////////////

class Drawing
{
public:
    virtual void draw_line(int x1, int y1, int x2, int y2) = 0;
    virtual void draw_ellipse(int x, int y, int rx, int ry) = 0;
    virtual void draw_polygon(const std::vector<std::pair<int, int>>& points) = 0;
    virtual ~Drawing() = default;
};

class DrawingAPI1 : public Drawing
{
public:
    void draw_line(int x1, int y1, int x2, int y2) override
    {
        API_1::draw_line(x1, y1, x2, y2);
    }   

    void draw_ellipse(int x, int y, int rx, int ry) override
    {
        API_1::draw_ellipse(x, y, rx, ry);
    }

    void draw_polygon(const std::vector<std::pair<int, int>>& points) override
    {
        for (size_t i = 0; i < points.size(); ++i)
        {
            const auto& p1 = points[i];
            const auto& p2 = points[(i + 1) % points.size()];
            API_1::draw_line(p1.first, p1.second, p2.first, p2.second);
        }
    }
};

class DrawingAPI2 : public Drawing
{
public:
    void draw_line(int x1, int y1, int x2, int y2) override
    {
        API_2::render_line({x1, y1}, {x2, y2});
    }

    void draw_ellipse(int x, int y, int rx, int ry) override
    {
        API_2::render_ellipse(x, y, rx, ry);
    }

    void draw_polygon(const std::vector<std::pair<int, int>>& points) override
    {
        std::vector<API_2::Point> api_points;
        for (const auto& p : points)
            api_points.emplace_back(p.first, p.second);
        API_2::render_polygon(api_points);
    }
};

class Shape
{
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
};

class ShapeBase : public Shape
{
    std::shared_ptr<Drawing> drawing_;
protected:
    std::shared_ptr<Drawing> drawing() const { return drawing_; }
public:
    ShapeBase(std::shared_ptr<Drawing> drawing) : drawing_(std::move(drawing)) {}
};

class Line : public ShapeBase
{
    int x1_, y1_, x2_, y2_;
public:
    Line(std::shared_ptr<Drawing> drawing, int x1, int y1, int x2, int y2) :
        ShapeBase(std::move(drawing)), x1_(x1), y1_(y1), x2_(x2), y2_(y2) {}

    void draw() const override
    {
        drawing()->draw_line(x1_, y1_, x2_, y2_);
    }
};

class Rectangle : public ShapeBase
{
    int x_, y_, width_, height_;
public:
    Rectangle(std::shared_ptr<Drawing> drawing, int x, int y, int width, int height) :
        ShapeBase(std::move(drawing)), x_(x), y_(y), width_(width), height_(height) {}
    
        void draw() const override
    {
        drawing()->draw_line(x_, y_, x_ + width_, y_);
        drawing()->draw_line(x_ + width_, y_, x_ + width_, y_ + height_);
        drawing()->draw_line(x_ + width_, y_ + height_, x_, y_ + height_);
        drawing()->draw_line(x_, y_ + height_, x_, y_);
    }
};

#endif // BRIDGE_HPP_