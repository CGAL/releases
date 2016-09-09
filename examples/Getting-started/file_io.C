// ---------------------------------------
// Example program from Getting Started with CGAL
// Chapter: Appendix (A short introduction to C++)
// Author: Geert-Jan Giezeman
// June 1997
// ---------------------------------------

#include "tutorial.h"
#include <fstream.h>

struct Segment {int i;};

istream& operator>>(istream& is,  Segment &seg)
{ return is >> seg.i; }

ostream& operator<<(ostream& os, const Segment &seg)
{ return os << seg.i; }

main()
{
    Segment seg;
    ifstream fin("segin");
    ofstream fout("segout");
    fin >> seg;
    if (fin.good())
    fout << seg << '\n';
}
