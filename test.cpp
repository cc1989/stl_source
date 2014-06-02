#include "test.h"
#include <iostream>
#include <vector>
#include <string.h>
#include <exception>
#include <stdexcept>
#include <typeinfo>

std::ostream& operator<<(std::ostream& os, const INT& i)
{
	os << '[' << i.m_i << ']';
	return os;
}
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

	int ia[5] = {0, 1, 2, 3, 4};
	MyVector<int>::iterator ite;
	x.insert(ite, ia, ia + 5);

	stack<int> sx;

	std::cout << deque<int>::iterator::buffer_size() << std::endl;
	std::cout << deque<int, MyAlloc, 64>::iterator::buffer_size() << std::endl;

	//产生临时对象
	std::vector<int> iv(ia, ia + 5);
	std::for_each(iv.begin(), iv.end(), print<int>());

	std::cout << testClass<int>::_datai << std::endl;
	std::cout << testClass<int>::_datal << std::endl;
	std::cout << testClass<int>::_datac << std::endl;

	INT I(5);
	std::cout << I++ << std::endl;
	std::cout << ++I << std::endl;
	std::cout << I-- << std::endl;
	std::cout << --I << std::endl;
	std::cout << *I << std::endl;

	INT *p = (INT *)::operator new(sizeof(INT));
	new(p) INT(I);
	std::cout << **p << std::endl;

	/*int i;
	func(&i);*/
	MyIter<int> iter(new int(8));
	std::cout << func(iter) << std::endl;
	std::cout << "program endl" << std::endl;
	return 0;
}
