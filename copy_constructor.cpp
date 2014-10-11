#include <iostream>
#include <vector>

class A
{
public:
    A() {  std::cout << "A constructor" << std::endl; }
    A(const A &a) {  std::cout << "A copy constructor" << std::endl; }
};
int main(void)
{
    std::vector<A> va;
    A a;
    for (int i = 0; i < 8; i++)
    {
        std::cout << i << " : ";
        std::cout << "size = " << va.size() << ", ";
        std::cout << "capacity = " << va.capacity() << std::endl;
        va.push_back(a);
    }
    std::cout << "size = " << va.size() << ", ";
    std::cout << "capacity = " << va.capacity() << std::endl;
    va.insert(va.begin(), a);  //调用九次拷贝构造函数
    std::cout << "size = " << va.size() << ", ";
    std::cout << "capacity = " << va.capacity() << std::endl;
    va.insert(va.begin(), a);  //此时会调用两次拷贝构造函数，这个和实现有关
    std::cout << "size = " << va.size() << ", ";
    std::cout << "capacity = " << va.capacity() << std::endl;
    return 0;
}
