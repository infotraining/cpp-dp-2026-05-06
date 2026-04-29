#ifndef HRINFO_HPP_
#define HRINFO_HPP_

#include "employee.hpp"

class HRInfo
{
protected:
	const Employee* employee_;
public:
	HRInfo(const Employee* e);
    virtual ~HRInfo() = default;

	virtual void info() const = 0;
};

class StdInfo : public HRInfo
{
public:
    using HRInfo::HRInfo;

    void info() const override;
};

class TempInfo : public HRInfo
{
public:
    using HRInfo::HRInfo;

    void info() const override;
};

#endif /* HRINFO_HPP_ */
