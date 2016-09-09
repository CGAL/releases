// Source: Threetuple.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL__THREETUPLE_H
#define CGAL__THREETUPLE_H

template < class T >
class CGAL__Threetuple : public CGAL_Handle_rep
{
public:

  T  e0;
  T  e1;
  T  e2;

  CGAL__Threetuple()
    {
    }
  CGAL__Threetuple(const T & a0, const T & a1, const T & a2)  :
    e0(a0), e1(a1), e2(a2)
    {
    }
  ~CGAL__Threetuple()
    {
    }
};
#endif
