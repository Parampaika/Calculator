#pragma once
#include <iostream>

class IKlass {
public:
	virtual void destroy() = 0;
	virtual double func(double a, double b) = 0;
	virtual std::string getName() = 0;
	virtual bool is_binary() = 0;
	virtual int getPriority() = 0;
};