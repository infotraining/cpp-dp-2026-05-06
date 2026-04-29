#ifndef PROXY_HPP_
#define PROXY_HPP_

#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

// "Subject"
class Image
{
public:
    virtual void draw() = 0;
    virtual ~Image() = default;
};

// "RealSubject"
class Bitmap : public Image
{
    using Pixel = char;
    std::vector<std::vector<Pixel>> bmp_;

public:
    Bitmap(const std::string& filename)
    {
        std::cout << "Loading a bitmap..." << std::endl;
        // creating an object is time-consuming operation
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(2s);

        std::ifstream fin(filename);
        if (!fin)
        {
            std::cerr << "Failed to open file!" << std::endl;
            throw std::runtime_error("File not opened");
        }

        while (fin)
        {
            std::string line;
            std::getline(fin, line);
            bmp_.push_back(std::vector<Pixel>{line.begin(), line.end()});
        }
    }

    Bitmap(const Bitmap&) = default;
    Bitmap& operator=(const Bitmap&) = default;
    Bitmap(Bitmap&&) = default;
    Bitmap& operator=(Bitmap&&) = default;

    ~Bitmap()
    {
        std::cout << "Bitmap's clean-up" << std::endl;
    }

    void draw() override
    {
        for (const auto& line : bmp_)
        {
            for (const auto& pixel : line)
                std::cout << pixel;
            std::cout << "\n";
        }
    }
};

// "Proxy"
class LazyBitmap : public Image
{
    std::string path_;
    std::unique_ptr<Bitmap> bitmap_;

public:
    LazyBitmap(std::string path)
        : path_{std::move(path)}
        , bitmap_{nullptr}
    {
        std::cout << "Proxy's creation" << std::endl;
    }

    void draw() override
    {
        // lazy initialization
        if (!bitmap_)
        {
            bitmap_ = std::make_unique<Bitmap>(path_);
        }

        bitmap_->draw();
    }
};

#endif /*PROXY_HPP_*/
