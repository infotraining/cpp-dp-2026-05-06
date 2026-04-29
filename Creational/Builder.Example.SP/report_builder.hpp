#ifndef RAPORT_BUILDER_HPP
#define RAPORT_BUILDER_HPP

#include <memory>
#include <string>
#include <vector>

using DataRow = std::vector<std::string>;
using HtmlDocument = std::string;
using CsvDocument = std::vector<std::string>;

class HtmlReportBuilder
{
public:
    HtmlReportBuilder& add_header(const std::string& header_text);
    HtmlReportBuilder& begin_data();
    HtmlReportBuilder& add_row(const DataRow& data_row);
    HtmlReportBuilder& end_data();
    HtmlReportBuilder& add_footer(const std::string& footer);

    HtmlDocument get_report();

private:
    HtmlDocument doc_;
};

class CsvReportBuilder 
{
public:
    CsvReportBuilder& add_header(const std::string& header_text);
    CsvReportBuilder& begin_data();
    CsvReportBuilder& add_row(const DataRow& data_row);
    CsvReportBuilder& end_data();
    CsvReportBuilder& add_footer(const std::string& footer);

    CsvDocument get_report();

private:
    CsvDocument doc_;
};

#endif // RAPORT_BUILDER_HPP
