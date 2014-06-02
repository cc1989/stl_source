#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstddef>
//测试__STL_STATIC_TEMPLATE_MEMBER_BUG
template <typename T>
class testClass
{
	public:
		static int _data;
		//静态常量整数成员在class内部直接初始化,也可以在类外部初始化
		static const int _datai;
		static const long _datal = 3L;
		static const char _datac = 'c';
		//const非静态成员变量只能用初始化列表初始化
		const int cdata;
		testClass()
			:cdata(1)
		{}
};
/*
//只有类的静态成员可以这样用
template <typename T>
const int testClass<T>::cdata = 1;
*/
template <typename T>
const int testClass<T>::_datai = 1;

//测试__STL_CLASS_PARTIAL_SPECIALIZATION
template <class I>
class testClass2
{
	public:
	testClass2(){std::cout << "I, O" << std::endl;}
};
//特殊化
template <class T>
class testClass2<T*>
{
	public:
	testClass2(){std::cout << "T*, T*" << std::endl;}
};
template <class T>
class testClass2<const T*>
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

//__STL_NON_TYPE_TMPL_PARAM_BUG
//测试类模板是否可拥有non-type tempalte参数
inline size_t __deque_buf_size(size_t n, size_t sz)
{
	return n != 0 ? n : (sz < 512 ? size_t(512 / sz) : size_t(1));
}
template <class T, class Ref, class Ptr, size_t BufSiz>
struct __deque_iterator
{
	typedef __deque_iterator<T, T&, T*, BufSiz> iterator;
	typedef __deque_iterator<T, const T&, const T*, BufSiz> const_iterator;
	static size_t buffer_size() {return __deque_buf_size(BufSiz, sizeof(T));}
};
//测试template参数可否根据前一个template参数而设定默认值
template <class T, class Alloc = MyAlloc, size_t BufSiz = 0>
class deque
{
public:
	//测试类模板是否可拥有non-type tempalte参数
	typedef __deque_iterator<T, T&, T*, BufSiz> iterator;
	deque() { std::cout << "deque" << std::endl; }
};

//__STL_LIMITED_DEFAULT_TEMPLATES
//根据前一个参数T，设定下一个参数Sequence的默认值为deque<T>
template <class T, class Sequence = deque<T> >
class stack
{
public:
	stack() { std::cout << "stack" << std::endl; }
private:
	Sequence c;
};

//产生临时对象
template <class T>
class print
{
public:
	void operator() (const T& elem)
	{
		std::cout << elem << " ";	
	}
};

//实现operator*,operator++,operator--
class INT
{
	friend std::ostream& operator<< (std::ostream& os, const INT& i);
public:
	INT(int i) : m_i(i) {}

	//++前置
	INT& operator++()
	{
		++(this->m_i);
		return *this;
	}
	//++后置
	const INT operator++(int)
	{
		INT temp = *this;
		++(this->m_i);
		return temp;
	}
	//--前置
	INT& operator--()
	{
		--(this->m_i);
		return *this;
	}
	//--后置
	const INT operator--(int)
	{
		INT temp = *this;
		--(this->m_i);
		return temp;
	}
	//*	
	int& operator*() const
	{
		return (int&)m_i;
	}
private:
	int m_i;
};

/*//利用函数模板推导迭代器所指之物的类型
template <class I, class T>
void func_impl(I iter, T t)
{
	T tmp;  //这里就解决了问题，T就是迭代器所指之物的类型
	std::cout << "类型获取成功" << std::endl;
}

template <class I>
inline void func(I iter)
{
	func_impl(iter, *iter);
}*/
//traits模板部分特化
template <class I>
struct iterator_cc_traits
{
	typedef typename I::value_type value_type;
};
//针对指针类型
template <class I>
struct iterator_cc_traits<I*>
{
	typedef I value_type;
};
//声明内嵌类型
template <class  T>
struct MyIter
{
	typedef T value_type;
	T * ptr;
	MyIter(T* p = 0): ptr(p) {}
	T& operator*() const {return *ptr;} 
};
template <class I>
typename iterator_cc_traits<I>::value_type  
func(I ite)
{
	return *ite;
}

