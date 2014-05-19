#include "test.h"
#include <iostream>
#include <vector>
#include <string.h>
#include <exception>
#include <stdexcept>
#include <typeinfo>

template<>
int testClass<int>::_data = 1;
template<>
int testClass<char>::_data = 2;

int main(int argc, char **argv)
{

//窥探编译器对标准c++的支持
#if defined(__sgi)
	std::cout << "__sgi" << std::endl;
#endif
#if defined(__GNUC__)
	std::cout << "__GNUC__" << std::endl;
	std::cout << __GNUC__ << " " << __GNUC_MINOR__ << std::endl;
#endif
	std::cout << testClass<int>::_data << std::endl;
	std::cout << testClass<char>::_data << std::endl;
	testClass<int> obji1, obji2;
	testClass<char> objc1, objc2;
	std::cout << obji1._data << std::endl;
	std::cout << obji2._data << std::endl;
	std::cout << objc1._data << std::endl;
	std::cout << objc2._data << std::endl;

	testClass2<int, char> obj1;
	testClass2<int*, char*> obj2;
	testClass2<const int*, char*> obj3;

	MyVector<int> x, y;
	std::swap(x, y);
	
	std::cout << "program endl" << std::endl;
	return 0;
}