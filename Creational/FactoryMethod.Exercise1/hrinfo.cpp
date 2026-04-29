#include "hrinfo.hpp"

HRInfo::HRInfo(const Employee* e) : employee_{e}
{
}

void StdInfo::info() const
{
	std::cout << "Standard information for:" << std::endl;
	employee_->description();
}

void TempInfo::info() const
{
	std::cout << "Information for temporary employee:" << std::endl;
	employee_->description();
}
