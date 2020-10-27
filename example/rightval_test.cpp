/*
测试右值引用
编译方式:
g++ -std=c++11 rightval_test.cpp -fno-elide-constructors  -o exe && ./exe
*/

#include <iostream>
using namespace std;

class Base
{
    static int count;
    static int copyCount;
    static int destructCount;
    static int moveConstruct;

private:
    int *m_int;

public:
    Base(/* args */);
    // 提供移动构造函数的同时也会提供一个拷贝构造函数，以防止移动不成功的时候还能拷贝构造，使我们的代码更安全
    Base(const Base &b);
    // 移动构造函数,加上移动构造函数后,就不需要用右值引用了: Base &&b = Ret();
    // Base(Base &&b) : m_int(b.m_int)
    // {
    //     b.m_int = nullptr;
    //     cout << "move construct" << endl;
    // }
    ~Base();
};

Base::Base(const Base &b)
{
    cout << "copy count: " << ++copyCount << endl;
}

Base::Base(/* args */)
{
    m_int = new int(0);
    cout << "construct Base " << ++count << endl;
}

Base::~Base()
{
    cout << "delete Base " << ++destructCount
         << " ptr:" << m_int << endl;
}

int Base::count = 0;
int Base::copyCount = 0;
int Base::destructCount = 0;
int Base::moveConstruct = 0;

/*
Base &&b=Ret();
输出:
construct Base 1
copy count: 1
delete Base 1
delete Base 2


Base b=Ret();
输出:
construct Base 1
copy count: 1
delete Base 1
copy count: 2
delete Base 2
delete Base 3
*/
Base Ret()
{
    Base b;
    return b;
}

/*
Base b = Ret2();
输出:
construct Base 1
copy count: 1
delete Base 1
*/
Base &Ret2()
{
    Base *b = new Base();
    return *b;
}

void processValue(int &a) { cout << "lvalue" << endl; }
void processValue(int &&a) { cout << "rvalue" << endl; }
template <typename T>
void forwardValue(T &&val)
{
    processValue(std::forward<T>(val)); //照参数本来的类型进行转发。
}

void Testdelcl()
{
    int i = 0;
    forwardValue(i); //传入左值
    forwardValue(0); //传入右值
}

int main()
{
    //c++98这样的写法const Base &b = Ret();和右值引用效果一致
    Base &&b = Ret();

    Testdelcl();

    return 0;
}