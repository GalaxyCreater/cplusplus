//实现求链表的中间结点

#include <iostream>
#include <list>
using namespace std;

typedef list<int> ListInt;

void GetMinNode(ListInt &l)
{
    ListInt::iterator slow = l.begin();
    ListInt::iterator quick = l.begin();
    while (quick != l.end())
    {
        slow++;
        quick++;
        if (quick == l.end())
        {
            break;
        }

        quick++;
    }
    cout << *slow << endl;
}

int main()
{
    int a[] = {1, 2, 3, 4, 5, 6};
    int len = sizeof(a) / sizeof(a[0]);
    ListInt l;
    for (int i = 0; i < len; i++)
    {
        l.push_back(i);
    }

    GetMinNode(l);

    return 0;
}
