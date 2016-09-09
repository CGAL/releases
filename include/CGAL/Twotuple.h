// Source: Twotuple_Rep.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL__TWOTUPLE_H
#define CGAL__TWOTUPLE_H


template < class T >
class CGAL__Twotuple : public CGAL_Handle_rep
{
public:
  T  e0;
  T  e1;

  CGAL__Twotuple()
    {
    }
  CGAL__Twotuple(const T & a0, const T &a1) :
    e0(a0), e1(a1)
    {
    }
  ~CGAL__Twotuple()
    {
    }
};

#endif
