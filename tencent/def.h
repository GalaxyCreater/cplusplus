#include <iostream>
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

struct Position
{
	int val;
	int x;
	int y;
	Position(int i, int j, int v = 1) : x(i), y(j), val(v) {}
};
