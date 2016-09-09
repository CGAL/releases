// ---------------------------------------
// Example program from Getting Started with CGAL
// Chapter: Appendix (A short introduction to C++)
// Author: Geert-Jan Giezeman
// June 1997
// ---------------------------------------

#include "tutorial.h
#include <vector.h>
#include <iostream.h>

main()
{
    vector<float> fvec;
    fvec.push_back(3.14159265358979323846);
    fvec.push_back(2.7182818284590452354);
    vector<int> ivec(fvec.size());
    int i;
    for (i=0; i<ivec.size(); i++)
	ivec[i] = (int) fvec[i];
    cout << ivec[0] <<' '<< ivec[1] <<'\n';
}
