#include "Calc.h"

typedef IKlass* (__cdecl* iklass_factory)();

void Calc::run() {
	readDll();
	PrintOp();
	std::string expression = getExpression();
	while (expression != "x") {
		expression = makeGoodExpression(expression);
		std::string result = OPZ(expression);
		double calc = solve(result);
		std::cout << "Answer: " << calc << std::endl;
		expression = getExpression();
	}
}

Calc::~Calc() {
	for (auto& operat : oper) {
		delete operat;
	}

	for (auto& dll : dlls) {
		FreeLibrary(dll);
	}
}

Calc::Calc() {
	oper.push_back(new Add);
	oper.push_back(new Divide);
	oper.push_back(new Multiply);
	oper.push_back(new Subtract);
	oper.push_back(new Unar_Subtract);
};

std::string Calc::makeGoodExpression(std::string exp) {
	std::string newExp;
	std::string symb = "";
	for (int i = 0; i < exp.size(); ++i) {
		symb.push_back(exp[i]);
		if (is_operation(symb) || exp[i] == '(' || exp[i] == ')') {
			newExp += ' ' + symb + ' ';
		}
		else {
			newExp.push_back(exp[i]);
		}
		symb = "";
	}
	return newExp;
}

void Calc::PrintOp() {
	std::cout << "List of operations: " << std::endl;
	for (auto& operat : oper) {
		std::cout << operat->getName() << "  ";
	}
	std::cout << std::endl;
}

void Calc::readDll() {
	const std::string pluginsDir = "plugins";
	const std::filesystem::path plugins{ pluginsDir };
	std::cout << "Loaded operations:" << std::endl;
	if (std::filesystem::is_directory(plugins))
	{
		for (auto const& file : std::filesystem::directory_iterator{ plugins })
		{
			HINSTANCE dll_handle = ::LoadLibraryA(file.path().generic_string().c_str());
			if (!dll_handle) {
				std::cerr << "Unable to load DLL!\n";
				return;
			}
			iklass_factory factory_func = reinterpret_cast<iklass_factory>(::GetProcAddress(dll_handle, "create_klass"));
			if (!factory_func) {
				std::cerr << "Unable to load create_klass from DLL!\n";
				::FreeLibrary(dll_handle);
				return;
			}

			IKlass* instance = factory_func();

			oper.push_back(instance);
			dlls.push_back(dll_handle);
			std::cout << instance->getName() << std::endl;
		}
	}
}
std::string Calc::getExpression() {
	std::string expression;
	std::cout << "Input expression: ";
	std::getline(std::cin, expression);
	return expression;
}

int Calc::getPriority(std::string& operation) {
	if (operation == "(") return 1;
	for (auto& operat : oper) {
		if (operat->getName() == operation) {
			return operat->getPriority();
		}
	}
}

bool Calc::is_operation(std::string& operation) {
	for (auto& operat : oper) {
		if (operat->getName() == operation) {
			return true;
		}
	}
	return false;
}

std::string Calc::OPZ(std::string& exp) {
	std::stack <std::string> stack;
	std::string result = "";
	std::stringstream s(exp);
	std::string symb;
	while (s >> symb) {
		if (is_operation(symb)) {
			int priority = getPriority(symb);
			if (stack.empty()) {
				stack.push(symb);
			}
			else {
				while (!stack.empty() && getPriority(stack.top()) >= priority) {
					result += ' ' + stack.top();
					stack.pop();
				}
				stack.push(symb);
			}
		}
		else if (symb == "(") {
			stack.push(symb);
		}
		else if (symb == ")") {
			while (stack.top() != "(") {
				result += ' ' + stack.top();
				stack.pop();
			}
			stack.pop();
		}
		else {
			if (result == "") {
				result += symb;
			}
			else {
				result += ' ' + symb;
			}
		}
	}
	while (!stack.empty()) {
		result += ' ' + stack.top();
		stack.pop();
	}
	return result;
}

double Calc::makeCalculation(double a, double b, std::string& operation) {
	for (auto& operat : oper) {
		if (operat->getName() == operation) {
			return operat->func(a, b);
		}
	}
	/*if (operation == "sqrt") {
		if (a <= 0.0) {
			throw std::exception("err: a <= 0, sqrt(a)");
		}
		return sqrt(a);
	}*/
}

bool Calc::is_binary(std::string& operation) {
	for (auto& operat : oper) {
		if (operat->getName() == operation) {
			return operat->is_binary();
		}
	}
	return false;
}

bool Calc::is_unary(std::string& operation) {
	for (auto& operat : oper) {
		if (operat->getName() == operation) {
			return !operat->is_binary();
		}
	}
	return false;
}

double Calc::solve(std::string& exp) {
	std::stack <std::string> stack;
	std::stringstream s(exp);
	std::string symb;
	while (s >> symb) {
		if (is_binary(symb)) {
			if (stack.empty()) {
				throw std::exception("error: Input Error");
			}
			double a = stod(stack.top());
			stack.pop();
			if (stack.empty()) {
				throw std::exception("error: Input Error");
			}
			double b = stod(stack.top());
			stack.pop();
			stack.push(std::to_string(makeCalculation(a, b, symb)));
		}
		else if (is_unary(symb)) {
			if (stack.empty()) {
				throw std::exception("error: Input Error");
			}
			double a = stod(stack.top());
			stack.pop();
			stack.push(std::to_string(makeCalculation(a, 0, symb)));
		}
		else {
			stack.push(symb);
		}
	}
	return stod(stack.top());
}
