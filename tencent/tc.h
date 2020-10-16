
#ifndef _H_TX_H
#define _H_TX_H

#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <set>
#include <algorithm>
#include <string.h>
#include "def.h"

using namespace std;

// 合并两个有序数组
void Combine()
{
	int a[] = {2, 4, 5};
	int b[] = {1, 4, 6, 10, 21};

	int max = 0;
	int lenA = sizeof(a) / sizeof(a[0]);
	int lenB = sizeof(b) / sizeof(b[0]);

	int aIdx, bIdx = 0;
	vector<int> res;
	res.reserve(lenA + lenB);

	while (1)
	{
		if (a[aIdx] > b[bIdx])
		{
			max = b[bIdx];
			bIdx++;
		}
		else
		{
			max = a[aIdx];
			aIdx++;
		}
		res.push_back(max);

		//a是否已经结束了
		if (aIdx >= lenA)
		{
			// 把b剩下的给a
			res.insert(res.end(), b + bIdx, b + lenB);
			break;
		}

		if (bIdx >= lenB)
		{
			res.insert(res.end(), a + aIdx, a + lenA);
			break;
		}
	}

	for (size_t i = 0; i < res.size(); i++)
	{
		printf("%d ", res[i]);
	}
	printf("\n");
}

// 腐烂相邻的橘子
int orangesRotting(vector<VecInt> &grid)
{
	static int dir_x[4] = {0, 0, -1, 1}; // 上下左右
	static int dir_y[4] = {1, -1, 0, 0}; // 上下左右

	int maxX = grid.size();
	int maxY = grid[0].size();
	int total = 0; // 记录总橘子数,防止有一个独立的橘子,不会腐烂
	deque<Position> dq;
	// 找出所有有问题的橘子
	for (size_t x = 0; x < grid.size(); x++)
	{
		for (size_t y = 0; y < grid[x].size(); y++)
		{
			if (grid[x][y] == 2)
			{
				dq.push_back(Position(x, y));
			}
			else if (grid[x][y] == 1)
			{
				total++;
			}
		}
	}

	if (dq.empty())
	{
		return -1;
	}

	vector<VecInt> tVec(grid.size(), VecInt());
	for (size_t i = 0; i < grid.size(); i++)
	{
		tVec[i].resize(grid[0].size(), 0); // -1表示没被访问过
	}

	int res = 0;
	while (1)
	{
		Position p = dq.front();
		dq.pop_front();
		// 腐烂周边4个方向
		for (size_t i = 0; i < 4; i++)
		{
			int x = p.x + dir_x[i];
			int y = p.y + dir_y[i];

			if (x < 0 || x >= maxX || y < 0 || y >= maxY ||
				grid[x][y] == 2 || // 已腐烂
				grid[x][y] == 0)   // 这个位置没橘子
			{
				continue;
			}

			if (grid[x][y] == 1)
			{
				dq.push_back(Position(x, y));
				tVec[x][y] = tVec[p.x][p.y] + 1;
				res = tVec[x][y];
				total--;
				grid[x][y] = 2; // 腐烂橘子,这样就不会重复放到队列里了
				if (total == 0) // 结束:所有都腐烂完
				{
					break;
				}
			}
		}

		if (dq.empty()) // 结束:已经没相邻的橘子
		{
			break;
		}
	}

	if (total > 0)
	{
		return -1;
	}

	return res;
}

void TestorangesRotting()
{
	int a[3][3] = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};
	vector<VecInt> v;

	for (size_t i = 0; i < 3; i++)
	{
		VecInt tmp(a[0], a[0] + 3);
		v.push_back(tmp);
	}

	orangesRotting(v);
}

void TestTecnt()
{
	TestorangesRotting();
}

#endif //_H_TX_H