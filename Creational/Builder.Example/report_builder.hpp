#ifndef RAPORT_BUILDER_HPP
#define RAPORT_BUILDER_HPP

#include <memory>
#include <string>
#include <vector>

using DataRow = std::vector<std::string>;
using HtmlDocument = std::string;
using CsvDocument = std::vector<std::string>;

class ReportBuilder
{
public:
    virtual ~ReportBuilder() = default;
    virtual ReportBuilder& add_header(const std::string& header_text) = 0;
    virtual ReportBuilder& begin_data() = 0;
    virtual ReportBuilder& add_row(const DataRow& data_row) = 0;
    virtual ReportBuilder& end_data() = 0;
    virtual ReportBuilder& add_footer(const std::string& footer) = 0;
};

class HtmlReportBuilder : public ReportBuilder
{
public:
    ReportBuilder& add_header(const std::string& header_text) override;
    ReportBuilder& begin_data() override;
    ReportBuilder& add_row(const DataRow& data_row) override;
    ReportBuilder& end_data() override;
    ReportBuilder& add_footer(const std::string& footer) override;

    HtmlDocument get_report();

private:
    HtmlDocument doc_;
};

class CsvReportBuilder : public ReportBuilder
{
public:
    ReportBuilder& add_header(const std::string& header_text) override;
    ReportBuilder& begin_data() override;
    ReportBuilder& add_row(const DataRow& data_row) override;
    ReportBuilder& end_data() override;
    ReportBuilder& add_footer(const std::string& footer) override;

    CsvDocument get_report();

private:
    CsvDocument doc_;
};

#endif // RAPORT_BUILDER_HPP
