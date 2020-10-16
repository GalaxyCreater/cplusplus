/*
适配器模式
*/

#include <iostream>
using namespace std;

//////////////////////// 类适配器///////////////////////////

// 被适配者
class Adaptee
{
public:
	virtual void f1()
	{
		cout << "f1" << endl;
	}
	virtual void f2()
	{
		cout << "f2" << endl;
	}
	void New3()
	{
		cout << "New3" << endl;
	}
};

// 最终目标接口
class TargetInterface
{
public:
	virtual void New1() = 0;
	virtual void New2() = 0;
};

class Adapter : public TargetInterface, public Adaptee
{
public:
	void New1()
	{
		Adaptee::f1(); // 委托给Adaptee
	}
	// 重新实现
	void New2()
	{
		cout << "New2" << endl;
	}
	//New3不需要改变
};

//////////////////////// 对象适配器 ///////////////////////////
class ObjTargetInterface
{
public:
	virtual void New1() = 0;
	virtual void New2() = 0;
	virtual void New3() = 0;
};
class ObjAdapter : public ObjTargetInterface
{
private:
	Adaptee *adapter;

public:
	ObjAdapter(Adaptee *a) : adapter(a) {}
	virtual void New1()
	{
		adapter->f1();
	}
	virtual void New2()
	{
		cout << "obj new2" << endl;
	}
	virtual void New3()
	{
		adapter->New3();
	}
};

int main()
{
	Adapter a;
	a.New1();
	a.New2();
	a.New3();

	Adaptee *ad = new Adaptee();
	ObjAdapter o(ad);
	o.New1();
	o.New2();
	o.New3();
	return 0;
}
