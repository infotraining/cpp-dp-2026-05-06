#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>
#include <functional>
#include <cmath>

struct StatResult
{
    std::string description;
    double value;

    StatResult(const std::string &desc, double val)
        : description(desc), value(val)
    {
    }
};

using Data = std::vector<double>;
using Results = std::vector<StatResult>;

// enum StatisticsType
// {
//     avg,
//     min_max,
//     sum
// };

using Statistics = std::function<void(const Data &, Results &)>;

void avg(const Data &data, Results &results)
{
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    double avg = sum / data.size();
    results.push_back(StatResult("Avg", avg));
}

void min(const Data &data, Results &results)
{
    double min = *(std::min_element(data.begin(), data.end()));
    results.push_back(StatResult("Min", min));
}

void max(const Data &data, Results &results)
{
    double max = *(std::max_element(data.begin(), data.end()));
    results.push_back(StatResult("Max", max));
}

// class MinMax
// {
// public:
//     void operator()(const Data &data, Results &results) const
//     {
//         double min = *(std::min_element(data.begin(), data.end()));
//         double max = *(std::max_element(data.begin(), data.end()));

//         results.push_back(StatResult("Min", min));
//         results.push_back(StatResult("Max", max));
//     }
// };

void sum(const Data &data, Results &results)
{
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    results.push_back(StatResult("Sum", sum));
}

void stddev(const Data &data, Results &results)
{
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    double avg = sum / data.size();

    double stdev = std::sqrt(std::accumulate(data.begin(), data.end(), 0.0, [avg](double acc, double d)
                                             { return acc + (d - avg) * (d - avg); }) /
                             data.size());

    results.push_back(StatResult("Standard Deviation", stdev));
}

class DataAnalyzer
{
    Statistics stat_strategy_;
    Data data_;
    Results results_;

public:
    DataAnalyzer(Statistics stat_strategy)
        : stat_strategy_{stat_strategy}
    {
    }

    void load_data(const std::string &file_name)
    {
        data_.clear();
        results_.clear();

        std::ifstream fin(file_name.c_str());
        if (!fin)
            throw std::runtime_error("File not opened");

        double d;
        while (fin >> d)
        {
            data_.push_back(d);
        }

        std::cout << "File " << file_name << " has been loaded...\n";
    }

    void set_statistics(Statistics stat_strategy)
    {
        stat_strategy_ = stat_strategy;
    }

    void calculate()
    {
        stat_strategy_(data_, results_);
    }

    const Results &results() const
    {
        return results_;
    }
};

void show_results(const Results &results)
{
    for (const auto &rslt : results)
        std::cout << rslt.description << " = " << rslt.value << std::endl;
}

class StatGroup
{
    std::vector<Statistics> stats_;

public:
    void add(Statistics stat)
    {
        stats_.push_back(stat);
    }

    void operator()(const Data &data, Results &results) const
    {
        for (const auto &strategy : stats_)
        {
            strategy(data, results);
        }
    }
};

int main()
{
    // TODO: Refactor the code above using Strategy Pattern
    // Hint#1: Define an interface for calculating Statistics
    // Hint#2: Use delegation technique to replace ifs in calculate() method

    StatGroup min_max;
    min_max.add(min);
    min_max.add(max);

    StatGroup common_stats;
    common_stats.add(avg);
    common_stats.add(min_max);
    common_stats.add(sum);

    StatGroup adv_stats;
    adv_stats.add(common_stats);
    adv_stats.add(stddev);

    DataAnalyzer da{common_stats};
    da.load_data("stats_data.dat");
    da.calculate();

    show_results(da.results());

    std::cout << "\n\n";

    da.set_statistics(adv_stats);
    da.load_data("new_stats_data.dat");
    da.calculate();

    show_results(da.results());
}
