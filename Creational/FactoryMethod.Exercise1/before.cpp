#include <memory>
#include <vector>

#include "employee.hpp"
#include "hrinfo.hpp"

HRInfo* gen_info(const Employee& e)
{
    if (const Salary* s = dynamic_cast<const Salary*>(&e))
        return new StdInfo(s);
    if (const Hourly* h = dynamic_cast<const Hourly*>(&e))
        return new StdInfo(h);
    if (const Temp* t = dynamic_cast<const Temp*>(&e))
        return new TempInfo(t);

    throw std::runtime_error("Wrong employee type");
}

int main()
{
    using namespace std;

    vector<std::unique_ptr<Employee>> emps;
    emps.push_back(make_unique<Salary>("Jan Kowalski"));
    emps.push_back(make_unique<Hourly>("Adam Nowak"));
    emps.push_back(make_unique<Temp>("Anna Nowakowska"));

    cout << "HR Report:\n---------------\n";

    // TODO: refactor this code
    // Hint: remove dynamic casts in gen_info() - use the Factory Method pattern to connect Employee hierarchy with HRInfo hierarchy
    for (const auto& emp : emps)
    {
        HRInfo* hri = gen_info(*emp);
        hri->info();
        cout << endl;
    } // Beware! Memory leak!
}
