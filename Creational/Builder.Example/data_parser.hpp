#ifndef DATA_PARSER_HPP
#define DATA_PARSER_HPP

#include "report_builder.hpp"
// #include <boost/algorithm/string.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>

class DataParser
{
public:
    explicit DataParser(ReportBuilder& report_builder)
        : report_builder_(report_builder)
    {
    }

    virtual void Parse(const std::string& file_name)
    {
        report_builder_.add_header(std::string("Raport from file: ") + file_name);

        report_builder_.begin_data();

        std::ifstream fin(file_name.c_str());

        while (!fin.eof())
        {
            std::string row;
            std::getline(fin, row);

            std::istringstream iss(row);
            DataRow data(std::istream_iterator<std::string>{iss},
                std::istream_iterator<std::string>());

            report_builder_.add_row(data);
        }

        report_builder_.end_data();

        report_builder_.add_footer("Copyright RaportBuilder 2013");
    }

    virtual ~DataParser() = default;

public:
    ReportBuilder& report_builder_;
};

#endif