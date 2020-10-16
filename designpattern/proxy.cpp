/*
代理模式
*/

#include <memory>
#include <stdio.h>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <map>
using namespace std;

class UserControllerInterface
{
public:
	virtual void login() = 0; // 登录
};

class UserController : public UserControllerInterface
{
public:
	// 不用代理模式,如果要记录login时间,入侵了代码
	// void login()
	// {
	//     int begin = time(NULL);
	//     cout << "login" << endl;
	//     int end = time(NULL);
	//     cout << "login cost time:" << end - begin << endl;
	// }

	void login()
	{
		cout << "login" << endl;
	}
};

// 组合方式实现
class UserControllerProxyCB : public UserControllerInterface
{
public:
	UserControllerProxyCB(UserControllerInterface *c) : control(c) {}
	void login()
	{
		int begin = time(NULL);
		control->login();
		int end = time(NULL);
		cout << "combiner login cost time:" << end - begin << endl;
	}

private:
	UserControllerInterface *control;
};

// 继承方式实现
class UserControllerProxyInherit : public UserController
{
public:
	void login()
	{
		int begin = time(NULL);
		UserController::login();
		int end = time(NULL);
		cout << "inherit login cost time:" << end - begin << endl;
	}
};

int main()
{
	// 组合方式实现
	UserController *user = new UserController();
	UserControllerProxyCB *combine = new UserControllerProxyCB(user);
	combine->login();

	// 继承方式实现
	UserControllerProxyInherit *pxInherit = new UserControllerProxyInherit();
	pxInherit->login();

	return 0;
}