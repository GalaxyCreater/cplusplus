#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
using namespace std;

typedef vector<int> VecInt;
typedef list<int> ListInt;
typedef unordered_map<int, int> MapInt;

/*

*/
int firstMissingPositive(vector<int> &nums)
{
    sort(nums.begin(), nums.end());

    int last = *nums.rbegin();
    if (last <= 0)
    {
        return 1;
    }

    return last + 1;
}

int main()
{
    int a[] = {3, 4, -1, 1};
    VecInt v(a, a + sizeof(a) / sizeof(a[0]));
    cout << firstMissingPositive(v) << endl;
    ;
    return 0;
}
