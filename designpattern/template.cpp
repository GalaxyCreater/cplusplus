/*
模板方法:
	模板方法模式在一个方法中定义一个算法骨架，并将某些步骤推迟到子类中实现。
模板方法模式可以让子类在不改变算法整体结构的情况下，重新定义算法中的某些步骤。
*/

#include <iostream>
using namespace std;

class Interface
{
public:
	virtual void templateFunc() = 0;
	virtual void method1() = 0;
	virtual void method2() = 0;
};

class Template1 : public Interface
{
public:
	virtual void templateFunc()
	{
		method2();
		method1();
	}

	virtual void method1()
	{
		cout << "Template1 method1" << endl;
	}
	virtual void method2()
	{
		cout << "Template1 method2" << endl;
	}
};

class Template2 : public Interface
{
public:
	virtual void templateFunc()
	{
		method1();
		method2();
	}

	virtual void method1()
	{
		cout << "Template2 method1" << endl;
	}
	virtual void method2()
	{
		cout << "Template2 method2" << endl;
	}
};

int main()
{
	Template1 t1;
	t1.templateFunc();
	Template2 t2;
	t2.templateFunc();
}
