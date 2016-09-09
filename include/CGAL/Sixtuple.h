// Source: Sixtuple.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL__SIXTUPLE_H
#define CGAL__SIXTUPLE_H

#include <LEDA/basic.h>

template < class T >
class CGAL__Sixtuple : public handle_rep
{
public:

  T  e0;
  T  e1;
  T  e2;
  T  e3;
  T  e4;
  T  e5;

  CGAL__Sixtuple()
   {
   }
  CGAL__Sixtuple(const T & a0, const T & a1, const T & a2,
                 const T & a3, const T & a4, const T & a5) :
    e0(a0), e1(a1), e2(a2), e3(a3), e4(a4), e5(a5)
    {
    }
  ~CGAL__Sixtuple()
    {
    }
};
#endif
