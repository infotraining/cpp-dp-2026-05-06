#ifndef PARAGRAPH_HPP_
#define PARAGRAPH_HPP_

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>

namespace LegacyCode
{
    class Paragraph
    {
        char* buffer_;

    protected:
        void swap(Paragraph& p)
        {
            std::swap(buffer_, p.buffer_);
        }

    public:
        Paragraph()
            : buffer_(new char[1024])
        {
            std::strcpy(buffer_, "Default text!");
        }

        Paragraph(const Paragraph& p)
            : buffer_(new char[1024])
        {
            std::strcpy(buffer_, p.buffer_);
        }

        Paragraph(const char* txt)
            : buffer_(new char[1024])
        {
            assert(txt != nullptr && "Null pointer is not allowed");
            assert(std::strlen(txt) < 1024 && "Input text is too long");
            std::strcpy(buffer_, txt);
        }

        Paragraph& operator=(Paragraph p)
        {
            swap(p);

            return *this;
        }

        void set_paragraph(const char* txt)
        {
            assert(txt != nullptr && "Null pointer is not allowed");
            assert(std::strlen(txt) < 1024 && "Input text is too long");
            std::strcpy(buffer_, txt);
        }

        const char* get_paragraph() const
        {
            return buffer_;
        }

        void render_at(int posx, int posy) const
        {
            std::cout << "Rendering text '" << buffer_ << "' at: [" << posx << ", " << posy << "]" << std::endl;
        }

        ~Paragraph()
        {
            delete[] buffer_;
        }
    };
} // namespace LegacyCode

#endif /*PARAGRAPH_HPP_*/
