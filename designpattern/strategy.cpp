/*
策略模式
*/

#include <iostream>
using std::cout;
using std::endl;

class Strategy
{
public:
	virtual void doSomething() = 0;
};

class Strategy1 : public Strategy
{
public:
	virtual void doSomething()
	{
		cout << "Strategy1" << endl;
	}
};

class Strategy2 : public Strategy
{
public:
	virtual void doSomething()
	{
		cout << "Strategy2" << endl;
	}
};

class StrategyFactory
{
public:
	static Strategy *CreateStrategy(int type)
	{
		switch (type)
		{
		case 1:
			return new Strategy1();
		case 2:
			return new Strategy2();

		default:
			break;
		}
		return NULL;
	}
};

int main()
{
	int type = 1;
	Strategy *s = StrategyFactory::CreateStrategy(type);
	s->doSomething();
	return 0;
}