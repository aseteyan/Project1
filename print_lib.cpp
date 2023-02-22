#include "print_lib.h"
#include <iostream>

void print(int i)
{
	std::cout << i;
}

void print(const char* s)
{
	std::cout << s;
}
