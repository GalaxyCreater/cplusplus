#include <iostream>
#include <vector>
using namespace std;

struct Base
{
    int a;
    int b;
};

vector<int> Ret2()
{
    vector<int> v;
    return v;
}

Base *Ret()
{
    return new Base();
}

int main()
{
    auto p = Ret();
    p->a = 1;
    p->b = 2;
    cout << p->a << p->b << endl;

    auto *s = Ret();
    cout << s->a << s->b << endl;

    auto v = Ret2();
    cout << v.capacity() << endl;
    return 0;
}