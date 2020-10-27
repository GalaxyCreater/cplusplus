#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
#include <memory>
using namespace std;

typedef list<int> ListInt;
typedef unordered_map<int, int> MapInt;
typedef vector<int> VecInt;

/*

*/

struct t
{
    int a;
};

void F(shared_ptr<t> p)
{
    cout << p.use_count() << endl;
    int a[2] = {};
    cout << a[10] << endl;
}

int main()
{
    shared_ptr<t> ptr(new t());
    cout << ptr.use_count() << endl;
    F(ptr);
    cout << "---" << ptr.use_count() << endl;

    return 0;
}
