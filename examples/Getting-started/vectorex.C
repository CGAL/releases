// ---------------------------------------
// Example program from Getting Started with CGAL
// Chapter: Appendix (A short introduction to C++)
// Author: Geert-Jan Giezeman
// June 1997
// ---------------------------------------

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
    return count_7(l);
}

/*
void sort_mapping(vector<int> &mapping, const vector<int> &data)
{
    mapping.clear();
    if (data.size() == 0)
	return;
    mapping.reserve(data.size());
    int i;
    int candidate, cand_val, last_found;
    candidate = 0;
    cand_val = data[0];
    for (i=1; i<data.size(); i++) {
	if (data[i] < cand_val) {
	    cand_val = data[i];
	    candidate = i;
	}
    }
    mapping.push_back(candidate);
    last_found = candidate;
    for (i=1; i<data.size(); i++) {
	for (j=last_found+1; j<data.size(); j++) {
	    if (data[j]>= last_val && data[j] < candidate must be inited)
	}
    }
}
*/
