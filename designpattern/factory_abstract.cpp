/*
抽象工厂
*/

#include <memory>
#include <stdio.h>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <map>
using namespace std;

//-----------------产品--------------------------
class Pad
{
public:
	virtual void Print() = 0;
};

class XiaomiPad : public Pad
{
public:
	void Print()
	{
		cout << "xiao mi pad" << endl;
	}
};
class HuaweiPad : public Pad
{
public:
	void Print()
	{
		cout << "Huawei pad" << endl;
	}
};

class Phone
{
public:
	virtual void Call() = 0;
};
class XiaomiPhone : public Phone
{
public:
	void Call()
	{
		cout << "xiaomi call" << endl;
	}
};
class HuaweiPhone : public Phone
{
public:
	void Call()
	{
		cout << "huawei call" << endl;
	}
};

//-------------------------工厂-----------------------

// 抽象工厂,用于生产不同类型集合
class AbstractFactory
{
public:
	virtual Pad *CreatePad() = 0;	 // Pad下有很多类型pad, 小米,华为,ipad
	virtual Phone *CreatePone() = 0; // Phone下有很多类型phone,小米,华为iPhone
};

class HuaweiFactory : public AbstractFactory
{
public:
	Pad *CreatePad() { return new HuaweiPad(); }
	Phone *CreatePone() { return new HuaweiPhone(); }
};

class XiaomiFactory : public AbstractFactory
{
public:
	Pad *CreatePad() { return new XiaomiPad(); }
	Phone *CreatePone() { return new XiaomiPhone(); }
};

// 超级工厂基类,用于创建工厂
class HyperFactory
{
public:
	virtual AbstractFactory *CreateFactory(int type) = 0;
};

// 1号超级工厂,可以不同号的超级工厂创建规则不一样
class HyperFactory1 : public HyperFactory
{
public:
	AbstractFactory *CreateFactory(int type)
	{
		if (1 == type)
		{
			return new XiaomiFactory();
		}
		else if (2 == type)
		{
			return new HuaweiFactory();
		}
		cout << "no type " << type << endl;

		return NULL;
	}
};

int main()
{
	HyperFactory1 hf;
	AbstractFactory *f = hf.CreateFactory(2);
	f->CreatePad()->Print();
	f->CreatePone()->Call();
	return 0;
}