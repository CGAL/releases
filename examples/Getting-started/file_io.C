#include "tutorial.h"
#include <fstream.h>

struct Segment {int i;};

istream& operator>>(istream& is,  Segment &seg)
{ return is >> seg.i; }

ostream& operator<<(ostream& os, const Segment &seg)
{ return os << seg.i; }

void main()
{
    Segment seg;
    ifstream fin("segin");
    ofstream fout("segout");
    fin >> seg;
    if (fin.good())
    fout << seg << '\n';
}
