#include "tutorial.h"
#include <fstream.h>

struct MySegment {int i;};

istream& operator>>(istream& is,  MySegment &seg)
{ return is >> seg.i; }

ostream& operator<<(ostream& os, const MySegment &seg)
{ return os << seg.i; }

main()
{
    MySegment seg;
    ifstream fin("segin");
    ofstream fout("segout");
    fin >> seg;
    if (fin.good())
    fout << seg << '\n';
}
