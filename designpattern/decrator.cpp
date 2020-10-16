#include <iostream>
using namespace std;

class CakeBase
{
public:
	virtual string name() = 0;
};

class Cake : public CakeBase
{
public:
	string name()
	{
		return "cake";
	}
};

class DecratorBase : public CakeBase
{
public:
	DecratorBase(CakeBase *c) : cake(c) {}
	virtual string name() = 0;
	CakeBase *cake;
};

// 蛋糕加牛奶
class MilkCake : public DecratorBase
{
public:
	MilkCake(CakeBase *c) : DecratorBase(c) {}
	virtual string name()
	{
		return cake->name() + ", milk";
	}
};

// 蛋糕加布丁
class PuddingCake : public DecratorBase
{
public:
	PuddingCake(CakeBase *c) : DecratorBase(c) {}
	virtual string name()
	{
		return cake->name() + ", pudding";
	}
};

int main()
{
	Cake c;
	cout << c.name() << endl;

	MilkCake *mc = new MilkCake(&c);
	cout << mc->name() << endl;

	PuddingCake *pc = new PuddingCake(&c);
	cout << pc->name() << endl;

	return 0;
}