// Source: Fourtuple.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL__FOURTUPLE_H
#define CGAL__FOURTUPLE_H

template < class T >
class CGAL__Fourtuple : public CGAL_Handle_rep
{
public:
  T  e0;
  T  e1;
  T  e2;
  T  e3;

  CGAL__Fourtuple()
    {
    }
  CGAL__Fourtuple(const T & a0, const T & a1, const T & a2, const T & a3) :
    e0(a0), e1(a1), e2(a2), e3(a3)
    {
    }
  ~CGAL__Fourtuple()
    {
    }
};
#endif
