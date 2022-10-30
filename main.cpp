#include "Calc.h"

int main() {
	Calc calc;
	try {
		calc.run();
	}
	catch (std::exception& ex)
	{
		printf("Exception: %s\n", ex.what());
	}

	return 0;
}