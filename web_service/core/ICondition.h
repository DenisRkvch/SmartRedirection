#ifndef ICONDITION_H_INCLUDED
#define ICONDITION_H_INCLUDED


class ICondition
{
public:
	virtual ~ICondition() = default;
	virtual bool check() = 0;
};
#endif