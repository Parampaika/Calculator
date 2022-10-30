#include<iostream>
#include<stack>
#include<string>
#include<sstream>
#include<istream>
#include <cmath>
#include "generic_interface.h"
#include <vector>
#include <windows.h>
#include <filesystem>
#include "Simple_operation.h";
#include <conio.h>

typedef IKlass* (__cdecl* iklass_factory)();

class Calc {
public:
	void run();
	Calc();
	~Calc();


private:
	std::string makeGoodExpression(std::string exp);

	void PrintOp();

	void readDll();
	std::string getExpression();

	int getPriority(std::string& operation);

	bool is_operation(std::string& operation);

	std::string OPZ(std::string& exp);

	double makeCalculation(double a, double b, std::string& operation);

	bool is_binary(std::string& operation);

	bool is_unary(std::string& operation);

	double solve(std::string& exp);
	std::vector<HINSTANCE> dlls;
	std::vector<IKlass*> oper;
};
