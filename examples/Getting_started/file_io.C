#include "tutorial.h"
#include <fstream>

struct MySegment {int i;};

std::istream& operator>>(std::istream& is,  MySegment &seg)
{ return is >> seg.i; }

std::ostream& operator<<(std::ostream& os, const MySegment &seg)
{ return os << seg.i; }

int main()
{
    MySegment seg;
    std::ifstream fin("segin");
    std::ofstream fout("segout");
    fin >> seg;
    if (fin.good())
    fout << seg << '\n';
    return 0;
}
