#include <iostream>
#include <tuple>
#include <vector>
//#include <boost/flyweight.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;

class Taxpayer
{
    int id_;
    std::string first_name_;
    std::string last_name_;

public:
    Taxpayer(int id, std::string fname, std::string lname)
        : id_(id)
        , first_name_(std::move(fname))
        , last_name_(std::move(lname))
    {
    }

    int id() const
    {
        return id_;
    }

    string first_name() const
    {
        return first_name_;
    }

    void set_first_name(const string& fname)
    {
        first_name_ = fname;
    }

    void to_upper()
    {
        boost::to_upper(first_name_);
        boost::to_upper(last_name_);
    }

    string last_name() const
    {
        return last_name_;
    }

    void set_last_name(const string& lname)
    {
        last_name_ = lname;
    }

    bool operator==(const Taxpayer& p)
    {
        return std::tie(id_, first_name_, last_name_) == std::tie(p.id_, p.first_name_, p.last_name_);
    }
};

int main()
{
    vector<Taxpayer> payers{Taxpayer{1, "Jan", "Kowalski"}, Taxpayer{2, "Jan", "Nowak"}};

    payers.emplace_back(3, "Anna", "Kowalska");
    payers.emplace_back(1, "Anna", "Nowakowska");
    payers.insert(payers.end(), {Taxpayer{6, "Jan", "Nijaki"}, Taxpayer{10, "Anna", "Anonim"}});

    payers[0].to_upper();
    payers[1].to_upper();

    for (const auto& p : payers)
    {
        cout << p.first_name() << " " << p.last_name() << endl;
    }
}
