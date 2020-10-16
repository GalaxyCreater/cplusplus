
#include <cstdlib>
#include <iostream>
#include <vector>
#include <set>
#include <string.h>
using namespace std;

/*
O(n)时间复杂度,O(1)空间复杂度删除字符串中所有空格
*/
void DelSpace(char *a, int len)
{
	char *spIdx = NULL;
	char *p = a;

	int idx = 0;
	while (1)
	{
		if (*a == ' ')
		{
			if (spIdx == NULL)
			{
				spIdx = a;
			}
		}
		else
		{
			// spIdx 正在指向空格
			if (spIdx != NULL)
			{
				// 和空格交换后,空格指针往后挪一位
				*spIdx = *a;
				*a = ' ';
				spIdx++;
				if (*spIdx != ' ') // 挪一位后发现不是空格,置空
				{
					spIdx = NULL;
				}
			}
		}
		a++;
		idx++;
		if (a == NULL || idx >= len)
		{
			break;
		}
	}
}

void DelSpace2(char *a, int len)
{
	int idx = 0;
	char *pre = a;
	char *quick = a;

	while (1)
	{
		*pre = *quick;
		pre++;
		quick++;
		idx++;
		if (idx >= len || quick == NULL)
		{
			return;
		}

		while (*quick == ' ')
		{
			quick++;
			idx++;
			if (idx >= len || quick == NULL)
			{
				return;
			}
		}
	}
}

int main()
{
	char a[] = "ab  cd ef g ";
	//DelSpace(a, sizeof(a) / sizeof(a[0]));
	DelSpace2(a, sizeof(a) / sizeof(a[0]));
	cout << a << endl;
	return 0;
}