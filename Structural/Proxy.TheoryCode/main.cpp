#include "proxy.hpp"
#include <functional>

using ImageFactory = std::function<std::unique_ptr<Image>(std::string)>;

class ClientApplication
{
    std::vector<std::unique_ptr<Image>> images_;

public:
    ClientApplication(std::initializer_list<std::string> filenames, ImageFactory image_factory)
    {
        std::cout << "Loading images..." << std::endl;
        for (const auto& filename : filenames)
            images_.push_back(image_factory(filename));
        std::cout << "Images loaded images..." << std::endl;
    }

    void render(size_t index)
    {
        images_.at(index)->draw();
    }
};

int main()
{
    using namespace std::literals;
    auto image_filenames = {"drawing1.drw"s, "drawing2.drw"s, "drawing3.drw"s};

    ClientApplication c{image_filenames, &std::make_unique<LazyBitmap, std::string>};

    c.render(0);
    c.render(1);
    c.render(2);
}
