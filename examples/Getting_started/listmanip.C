#include "tutorial.h"
#include <list>

using std::list;

void remove_2(list<int> &l)
{
    list<int>::iterator x, cur(l.begin());
    while (cur != l.end()) {
        if (*cur == 2) {
            x = cur;
            ++cur;
            l.erase(x);
        } else {
            ++cur;
        }
    }
}

void insert_7(list<int> &l)
{
    list<int>::iterator cur(l.begin());
    while (cur != l.end())
        l.insert(++cur, 7);
}

int count_7(const list<int> & l)
{
    list<int>::const_iterator cur;
    int n = 0;
    for (cur = l.begin(); cur != l.end(); ++cur) {
        if (*cur == 7)
            ++n;
    }
    return n;
}

int main()
{
    list<int> l;
    for (int i=-1; i<4; i++)
        l.push_back(i);
    // l contains -1 0 1 2 3
    remove_2(l);
    //  l contains -1 0 1 3
    insert_7(l);
    //  l contains -1 7 0 7 1 7 3 7
    l.pop_front();
    //  l contains 7 0 7 1 7 3 7
    return count_7(l) - 4;  // should return 0 (succes).
}
