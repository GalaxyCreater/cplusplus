class CxString // 使用关键字explicit的类声明, 显示转换
{
public:
	char *_pstr;
	int _size;
	explicit CxString(int size)
	{
		_size = size;
		// 代码同上, 省略...
	}
	CxString(const char *p)
	{
		// 代码同上, 省略...
	}
};

int main()
{
	CxString string1(24);	  // 这样是OK的
	CxString string2 = 10;	  // 这样是不行的, 因为explicit关键字取消了隐式转换
	CxString string3;		  // 这样是不行的, 因为没有默认构造函数
	CxString string4("aaaa"); // 这样是OK的
	CxString string5 = "bbb"; // 这样也是OK的, 调用的是CxString(const char *p)
	CxString string6 = 'c';	  // 这样是不行的, 其实调用的是CxString(int size), 且size等于'c'的ascii码, 但explicit关键字取消了隐式转换
	string1 = 2;			  // 这样也是不行的, 因为取消了隐式转换
	string2 = 3;			  // 这样也是不行的, 因为取消了隐式转换
	string3 = string1;		  // 这样也是不行的, 因为取消了隐式转换, 除非类实现操作符"="的重载
	return 0;
}
