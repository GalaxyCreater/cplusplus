/*
爬楼梯
假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？
注意：给定 n 是一个正整数。
*/
#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
using namespace std;

typedef list<int> ListInt;
typedef unordered_map<int, int> MapInt;
typedef vector<int> VecInt;

int cnt = 0;
void _climbStairs(int n)
{
    if (n <= 0)
    {
        if (n == 0)
        {
            cnt++;
        }

        return;
    }
    _climbStairs(n - 1);
    _climbStairs(n - 2);
}

// 方法1
int climbStairs(int n)
{
    _climbStairs(n);
    return cnt;
}

/*
方法2:动态规划
f(x)=f(x-1)+f(x-2)
*/
class Solution
{
public:
    // 时间复杂度O(n),空间复杂度O(n)
    int climbStairs(int n)
    {
        VecInt v;
        if (n <= 2)
        {
            return n;
        }

        v.resize(n + 1);

        v[0] = 0;
        v[1] = 1;
        v[2] = 2;

        for (int i = 3; i <= n; i++)
        {
            v[i] = v[i - 1] + v[i - 2];
        }

        return v[n];
    }

    // 优化空间复杂度版,时间复杂度O(n),空间复杂度O(1)
    int climbStairs2(int n)
    {
        if (n <= 2)
        {
            return n;
        }

        int f0 = 0;
        int f1 = 1;
        int f = 2;

        for (int i = 3; i <= n; i++)
        {
            f0 = f1;
            f1 = f;
            f = f1 + f0;
        }

        return f;
    }
};

int main()
{
    Solution s;
    cout << s.climbStairs2(3) << endl;
    return 0;
}
