
#include <cstdlib>
#include <iostream>
#include <vector>
#include <set>
#include <string.h>
using namespace std;

bool CheckValid(string &s)
{
	int val = atoi(s.c_str());
	if (val < 0 || val > 255)
	{
		return false;
	}

	// 首位不能是0
	if (s[0] == '0' && s.length() >= 2)
	{
		return false;
	}

	return true;
}

/*
打印所有合法ip
调用:PrintIp("1921681199")
*/
void PrintIp(string &s)
{
	if (s.length() > 12 || s.length() < 4)
	{
		cout << "invalid length" << s.length() << endl;
		return;
	}

	vector<string> vec;
	bool valid = true;
	// 第一位数
	for (int i = 1; i <= 3; i++)
	{
		int left = s.length() - i;
		if (left < 3 || left > 9)
		{
			continue;
		}

		// 第二位数
		for (int j = 1; j <= 3; j++)
		{
			left = s.length() - i - j;
			if (left < 2 || left > 6)
			{
				continue;
			}

			// 第三位
			for (int m = 1; m <= 3; m++)
			{
				left = s.length() - i - j - m;
				if (left <= 0 || left > 3)
				{
					continue;
				}

				string p1 = s.substr(0, i);
				string p2 = s.substr(i, j);
				string p3 = s.substr(i + j, m);
				string p4 = s.substr(i + j + m, left);
				if (!CheckValid(p1) || !CheckValid(p2) || !CheckValid(p3) || !CheckValid(p4))
				{
					continue;
				}
				char tmp[100] = "";
				sprintf(tmp, "%s.%s.%s.%s", p1.c_str(), p2.c_str(), p3.c_str(), p4.c_str());
				vec.push_back(tmp);
			}
		}
	}

	if (vec.empty())
	{
		cout << "no ip" << endl;
		return;
	}

	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << endl;
	}
}

int main()
{
	string s;

	// cout << "input ip:";
	// cin >> s;
	//s = "1921681199";
	PrintIp(s);

	return 0;
}