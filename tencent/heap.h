#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
#include <stack>
#include <deque>
#include <algorithm>
#include <string.h>
#include <unordered_map>
#include <list>

using namespace std;

typedef vector<int> VecInt;
typedef pair<int, int> PairInt;

class Heap
{
public:
	Heap() { data.push_back(-1); }
	void push(int val);
	bool pop(int &val);
	void InitByArry(VecInt &lst);
	int topIdx() { return data.size() == 1 ? -1 : 1; }
	VecInt topK(int n);

private:
	void downBalance(int idx);
	void upBalance(int idx);
	int leftChild(int idx)
	{
		int tmp = idx * 2;
		return tmp >= data.size() ? -1 : tmp;
	}
	int rightChild(int idx)
	{
		int tmp = idx * 2 + 1;
		return tmp >= data.size() ? -1 : tmp;
	}
	int father(int idx)
	{
		int tmp = idx / 2;
		return tmp;
	}
	void exchange(int lhs, int rhs)
	{
		int tmp = data[lhs];
		data[lhs] = data[rhs];
		data[rhs] = tmp;
	}

public:
	VecInt data; // 0位置留空,取父,左右孩子节点公式计算
};

void Heap::downBalance(int idx)
{
	int tmp = idx;
	int left = leftChild(idx);
	int right = rightChild(idx);
	while (tmp < data.size())
	{
		int maxIdx = tmp;
		if (left > 0 && data[left] > data[maxIdx])
		{
			maxIdx = left;
		}

		if (right > 0 && data[right] > data[maxIdx])
		{
			maxIdx = right;
		}

		if (maxIdx == tmp) // 已到符合规则的点
		{
			break;
		}

		exchange(tmp, maxIdx);
		tmp = maxIdx;
		left = leftChild(tmp);
		right = rightChild(tmp);
	}
}

void Heap::upBalance(int idx)
{
	int tmp = idx;
	int f = father(tmp);
	while (tmp >= 1 && f >= 1)
	{
		if (data[f] < data[tmp])
		{
			exchange(f, tmp);
		}
		else if (data[f] >= data[tmp])
		{
			break;
		}

		f = father(f);
	}
}

// 从堆中移除元素 并 从上往下调整堆
bool Heap::pop(int &val)
{
	val = 0;
	int t = topIdx();
	if (t < 0)
	{
		return false;
	}
	val = data[t];
	exchange(data.size(), t);
	data.pop_back();
	downBalance(1);
	return true;
}

void Heap::InitByArry(VecInt &lst)
{
	data.insert(++data.begin(), lst.begin(), lst.end());
	// 从n/2处,由下往上堆化
	for (size_t i = data.size() / 2; i >= 1; i--)
	{
		downBalance(i);
	}
}

VecInt Heap::topK(int n)
{
	VecInt res;
	res.reserve(n);
	for (size_t i = 0; i < n; i++)
	{
		int top = 0;
		if (pop(top))
		{
			res.push_back(top);
		}
		else
		{
			break;
		}
	}

	return res;
}