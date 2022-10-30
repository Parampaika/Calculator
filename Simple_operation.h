#pragma once
#include <iostream>
#include "generic_interface.h"

class Add : public IKlass {
public:
	std::string name;
	Add();
	~Add();
	void destroy();
	double func(double a, double b);
	std::string getName();
	bool is_binary();
	int getPriority();
}; 

class Divide : public IKlass {
public:
	std::string name;
	Divide();
	~Divide();
	void destroy();
	double func(double a, double b);
	std::string getName();
	bool is_binary();
	int getPriority();
};

class Multiply : public IKlass {
public:
	std::string name;
	Multiply();
	~Multiply();
	void destroy();
	double func(double a, double b);
	std::string getName();
	bool is_binary();
	int getPriority();
};

class Subtract : public IKlass {
public:
	std::string name;
	Subtract();
	~Subtract();
	double func(double a, double b);
	void destroy();
	std::string getName();
	bool is_binary();
	int getPriority();
};

class Unar_Subtract : public IKlass {
public:
	std::string name;
	Unar_Subtract();
	~Unar_Subtract();
	void destroy();
	double func(double a, double b);
	std::string getName();
	bool is_binary();
	int getPriority();

};