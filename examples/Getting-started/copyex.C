// ---------------------------------------
// Example program from Getting Started with CGAL
// Chapter: Appendix (A short introduction to C++)
// Author: Geert-Jan Giezeman
// June 1997
// ---------------------------------------

#include "tutorial.h
#include <list.h>
#include <vector.h>
#include <algobase.h>
#include <iterator.h>
#include <iostream.h>


main()
{
    double d_array[2] = { 1.3, 1.2};
    vector<double> d_vec(3, 0.5);
    d_vec[2] = 1.4;
    list<double> d_list;
    copy(d_vec.begin(), d_vec.end(), back_inserter(d_list));
// d_list: 0.5, 0.5, 1.4 ;
    copy(d_array, d_array+2, back_inserter(d_list));
// d_list: 0.5, 0.5, 1.4, 1.3, 1.2 ;
// The following is not yet available in all STL implementations,
//    d_vec.clear();
// so it is replaced by the more cumbersome:
    d_vec.erase(d_vec.begin(), d_vec.end());
// d_vec:  ;
    copy(d_list.begin(), d_list.end(), back_inserter(d_vec));
// d_vec: 0.5, 0.5, 1.4, 1.3, 1.2 ;
    copy(d_vec.begin(), d_vec.end(), ostream_iterator<double>(cout, " "));
    cout<<endl;
}
