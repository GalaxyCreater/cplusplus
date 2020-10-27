/*
测试移动构造函数
编译方式:
g++ -std=c++11 rightval_test.cpp -fno-elide-constructors  -o exe && ./exe
*/

#include <iostream>
#include <vector>
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
    // 移动构造函数,转移指针所有者.这就是移动语义,减少拷贝深拷贝函数的开销
    // 注:为什么成员对象有指针要使用深拷贝构造函数?答:避免指针悬挂问题
    Base(Base &&b) : m_int(b.m_int)
    {
        b.m_int = nullptr;
        cout << "move construct" << endl;
    }
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

int main()
{
    //c++98这样的写法const Base &b = Ret();和右值引用效果一致
    Base b = Ret();

    vector<int> v(10, 10);

    vector<int> v2 = std::move(v);
    for (auto v : v2)
    {
        cout << v << endl;
    }
    cout << "--------------" << endl;
    for (auto t : v)
    {
        cout << t << endl;
    }

    return 0;
}