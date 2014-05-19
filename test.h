#include <algorithm>
#include <iostream>
#include <cstring>
//测试__STL_STATIC_TEMPLATE_MEMBER_BUG
template <typename T>
class testClass
{
	public:
		static int _data;
};
//测试__STL_CLASS_PARTIAL_SPECIALIZATION
template <class I, class O>
class testClass2
{
	public:
	testClass2(){std::cout << "I, O" << std::endl;}
};
//特殊化
template <class T>
class testClass2<T*, T*>
{
	public:
	testClass2(){std::cout << "T*, T*" << std::endl;}
};
template <class T>
class testClass2<const T*, T*>
{
	public:
	testClass2(){std::cout << "const T*, T*" << std::endl;}
};

//__STL_FUNCTION_TMPL_PARTIAL_ORDER
class MyAlloc
{
};
template <class T, class Alloc = MyAlloc>
class MyVector
{
	public:
		void swap(MyVector<T, Alloc>&){std::cout << "swap()" << std::endl;}
		//__STL_EXPLICIT_FUNCTION_TMPL_ARGS
		typedef T value_type;
		typedef value_type* iterator;

		template <class I>
		void insert(iterator position, I first, I last)
		{
			std::cout << "insert()" << std::endl;
		}
};

namespace std
{
//#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER
template <class T, class Alloc>
void swap(MyVector<T, Alloc>& x, MyVector<T,	Alloc>& y){
	x.swap(y);
}
//#endif
}
