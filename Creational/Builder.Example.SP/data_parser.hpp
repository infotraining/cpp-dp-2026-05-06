#ifndef DATA_PARSER_HPP
#define DATA_PARSER_HPP

#include "report_builder.hpp"
//#include <boost/algorithm/string.hpp>
#include <fstream>
#include <string>
#include <sstream>

std::vector<std::string> split(const std::string& s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}

template <typename ReportBuilder>
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

            DataRow data = split(row, ' ');

            report_builder_.add_row(data);
        }

        report_builder_.end_data();

        report_builder_.add_footer("Copyright RaportBuilder 2013");
    }

    DataParser(const DataParser&) = default;
    DataParser& operator=(const DataParser&) = default;
    DataParser(DataParser&&) = default;
    DataParser& operator=(DataParser&&) = default;

    virtual ~DataParser() = default;

public:
    ReportBuilder& report_builder_;
};

template <typename ReportBuilder>
DataParser(ReportBuilder) -> DataParser<ReportBuilder>;

#endif