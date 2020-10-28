/*
友元测试
*/
#include <iostream>
using namespace std;

class Base;
class Other
{
	friend class Base;
	int v;

public:
	Other()
	{
		v = 10;
	}
};

class Base
{

private:
	int m_v;
	Other o;
	void Add() { ++m_v; }

public:
	Base(/* args */) { m_v = 0; }
	~Base() {}

	void Print(Base &b)
	{
		b.Add();
		cout << b.m_v << endl
			 << o.v << endl;
	}
};

int main()
{
	Base b;
	Base b1;
	b.Print(b1);

	return 0;
}