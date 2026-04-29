#include "report_builder.hpp"

using namespace std;

ReportBuilder& HtmlReportBuilder::add_header(const std::string& header_text)
{
    doc_.clear();
    doc_.append("<h1>" + header_text + "</h1>\n");

    return *this;
}

ReportBuilder& HtmlReportBuilder::begin_data()
{
    doc_.append("<table>\n");

    return *this;
}

ReportBuilder& HtmlReportBuilder::add_row(const DataRow& data_row)
{
    doc_.append("  <tr>\n");
    for (const auto& item : data_row)
    {
        doc_.append("    <td>" + item + "</td>\n");
    }
    doc_.append("  </tr>\n");

    return *this;
}

ReportBuilder& HtmlReportBuilder::end_data()
{
    doc_.append("</table>\n");

    return *this;
}

ReportBuilder& HtmlReportBuilder::add_footer(const std::string& footer)
{
    doc_.append("<div class='footer'>" + footer + "</div>\n");

    return *this;
}

HtmlDocument HtmlReportBuilder::get_report()
{
    return std::move(doc_);
}

ReportBuilder& CsvReportBuilder::add_header(const std::string& header_text)
{
    doc_.clear();
    doc_.push_back("# " + header_text);

    return *this;
}

ReportBuilder& CsvReportBuilder::begin_data()
{
    doc_.push_back("\n");

    return *this;
}

ReportBuilder& CsvReportBuilder::add_row(const DataRow& data_row)
{

    string csv_row;

    for (const auto& item : data_row)
    {
        csv_row.append(item + ";");
    }
    doc_.push_back(csv_row);

    return *this;
}

ReportBuilder& CsvReportBuilder::end_data()
{
    doc_.push_back("\n");

    return *this;
}

ReportBuilder& CsvReportBuilder::add_footer(const std::string& footer)
{
    doc_.push_back("# Summary: " + footer);

    return *this;
}

CsvDocument CsvReportBuilder::get_report()
{
    return std::move(doc_);
}
