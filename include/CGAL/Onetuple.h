#line 11 "/u/sargas/2/prisme/fabri/Cgal/Kernel/spec/Onetuple.fw"
// Source: Onetuple_Rep.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL__ONETUPLE_H
#define CGAL__ONETUPLE_H

#include <LEDA/basic.h>

template < class T >
class CGAL__Onetuple : public handle_rep
{
public:
  T  e0;

  CGAL__Onetuple()
  {}

  CGAL__Onetuple(const T & a0)
    : e0(a0)
  {}

  ~CGAL__Onetuple()
  {}
};

#endif
