#include <vector.h>

void remove_2(vector<int> &l)
{
    vector<int>::iterator x, cur(l.end());
    while (cur != l.begin()) {
        --cur;
        if (*cur == 2) {
            x = cur;
            --cur;
            l.erase(x);
            ++cur;
        }
    }
}

void insert_7(vector<int> &l)
{
    vector<int>::iterator cur(l.begin()), x;
    while (cur != l.end()) {
        x = cur;
        l.insert(++x, 7);
        ++(++cur);
    }
}

int count_7(const vector<int> & l)
{
    vector<int>::const_iterator cur;
    int n = 0;
    for (cur = l.begin(); cur != l.end(); ++cur) {
        if (*cur == 7)
            ++n;
    }
    return n;
}

int main()
{
    vector<int> l;
    for (int i=-1; i<4; i++)
        l.push_back(i);
    // l contains -1 0 1 2 3
    remove_2(l);
    //  l contains -1 0 1 3
    insert_7(l);
    //  l contains -1 7 0 7 1 7 3 7
    l.erase(l.begin());
    //  l contains 7 0 7 1 7 3 7
    return count_7(l)-4;
}
