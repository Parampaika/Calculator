#pragma once
#include "Simple_operation.h";

Add::Add(): name("+") {}
Add::~Add()
{
	std::cerr << "MyKlass destructor\n";
}
void Add::destroy() {};
double Add::func(double a, double b) {
	return a + b;
}
std::string Add::getName() {
	return name;
}
bool Add::is_binary() {
	return true;
}
int Add::getPriority() {
	return 2;
}


Divide::Divide() : name("/") {}
Divide::~Divide(){
	std::cerr << "MyKlass destructor\n";
}
void Divide::destroy() {};
double Divide::func(double a, double b) {
	if (a == 0.0) {
		throw std::exception("err: n / 0");
	}
	return b / a;
}
std::string Divide::getName() {
	return name;
}
bool Divide::is_binary() {
	return true;
}
int Divide::getPriority() {
	return 3;
}


Multiply::Multiply() : name("*") {};
Multiply::~Multiply(){
	std::cerr << "MyKlass destructor\n";
}
void Multiply::destroy() {};
double Multiply::func(double a, double b) {
	return a * b;
}
std::string Multiply::getName() {
	return name;
}
bool Multiply::is_binary() {
	return true;
}
int Multiply::getPriority() {
	return 3;
}



std::string name;
Subtract::Subtract() : name("-") {};
Subtract::~Subtract()
{
	std::cerr << "MyKlass destructor\n";
}
double Subtract::func(double a, double b) {
	return b - a;
}
void Subtract::destroy() {};
std::string Subtract::getName() {
	return name;
}
bool Subtract::is_binary() {
	return true;
}
int Subtract::getPriority() {
	return 2;
}


Unar_Subtract::Unar_Subtract() : name("~") {}
Unar_Subtract::~Unar_Subtract(){
	std::cerr << "MyKlass destructor\n";
}
void Unar_Subtract::destroy() {};
double Unar_Subtract::func(double a, double b) {
	return b - a;
}
std::string Unar_Subtract::getName() {
	return name;
}
bool Unar_Subtract::is_binary() {
	return false;
}
int Unar_Subtract::getPriority() {
	return 2;
}
