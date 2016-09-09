//  Copyright CGAL 1996
//
//  cgal@cs.ruu.nl
//
//  This file is part of an internal release of the CGAL kernel.
//  The code herein may be used and/or copied only in accordance
//  with the terms and conditions stipulated in the agreement
//  under which the code has been supplied or with the written
//  permission of the CGAL Project.
//
//  Look at http://www.cs.ruu.nl/CGAL/ for more information.
//  Please send any bug reports and comments to cgal@cs.ruu.nl
//
//  The code comes WITHOUT ANY WARRANTY; without even the implied
//  warranty of FITNESS FOR A PARTICULAR PURPOSE.
//

// Source: DirectionC2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_DIRECTIONC2_H
#define CGAL_DIRECTIONC2_H

#include <CGAL/Twotuple.h>
#include <CGAL/VectorC2.h>

template < class FT >
class CGAL_DirectionC2 : public CGAL_Handle
{
public:
                       CGAL_DirectionC2();
                       CGAL_DirectionC2(const CGAL_DirectionC2<FT> &d);
                       CGAL_DirectionC2(const CGAL_VectorC2<FT> &v);
                       CGAL_DirectionC2(const FT &x,
                                        const FT &y);
                       ~CGAL_DirectionC2();

  CGAL_DirectionC2<FT> &operator=(const CGAL_DirectionC2<FT> &d);

  bool                 operator==(const CGAL_DirectionC2<FT> &d) const;
  bool                 operator!=(const CGAL_DirectionC2<FT> &d) const;
  bool                 operator>=(const CGAL_DirectionC2<FT> &d) const;
  bool                 operator<=(const CGAL_DirectionC2<FT> &d) const;
  bool                 operator>(const CGAL_DirectionC2<FT> &d) const;
  bool                 operator<(const CGAL_DirectionC2<FT> &d) const;
  bool                 counterclockwise_in_between(
                                         const CGAL_DirectionC2<FT> &d1,
                                         const CGAL_DirectionC2<FT> &d2) const;
  int                  id() const;

  CGAL_VectorC2<FT>    vector() const;

  CGAL_DirectionC2<FT> perpendicular(const CGAL_Orientation &o) const;
  CGAL_DirectionC2<FT> transform(const CGAL_Aff_transformationC2<FT> &t) const;

  CGAL_DirectionC2<FT> operator-() const;

  FT                   delta(int i) const;
  FT                   dx() const;
  FT                   dy() const;

private:
  CGAL__Twotuple<FT>*   ptr() const;
};


template < class FT >
inline CGAL__Twotuple<FT>*   CGAL_DirectionC2<FT>::ptr() const
{
  return (CGAL__Twotuple<FT>*)PTR;
}


template < class FT >
CGAL_DirectionC2<FT>::CGAL_DirectionC2()
{
  PTR = new CGAL__Twotuple<FT>();
}

template < class FT >
inline CGAL_DirectionC2<FT>::CGAL_DirectionC2(const CGAL_DirectionC2<FT> &d) :
  CGAL_Handle((CGAL_Handle&)d)
{

}

template < class FT >
inline CGAL_DirectionC2<FT>::CGAL_DirectionC2(const CGAL_VectorC2<FT> &v) :
  CGAL_Handle((CGAL_Handle&)v)
{

}

template < class FT >
CGAL_DirectionC2<FT>::CGAL_DirectionC2(const FT &x, const FT &y)
{
  PTR = new CGAL__Twotuple<FT>(x, y);
}

template < class FT >
inline CGAL_DirectionC2<FT>:: ~CGAL_DirectionC2()
{}

template < class FT >
CGAL_DirectionC2<FT> &CGAL_DirectionC2<FT>::operator=(
                                               const CGAL_DirectionC2<FT> &d)
{

  CGAL_Handle::operator=(d);
  return *this;
}
template < class FT >
bool  CGAL_DirectionC2<FT>::operator==(const CGAL_DirectionC2<FT> &d) const
{
    return (CGAL_sign(dx()) == CGAL_sign(d.dx()))
           && (CGAL_sign(dy()) == CGAL_sign(d.dy()))
           && (dy()*d.dx() == d.dy()*dx());
}

template < class FT >
inline bool  CGAL_DirectionC2<FT>::operator!=(
                                        const CGAL_DirectionC2<FT> &d) const
{
  return !( *this == d );
}

template < class FT >
int CGAL_DirectionC2<FT>::id() const
{
  return (int)PTR;
}

template < class FT >
bool  CGAL_DirectionC2<FT>::operator<(const CGAL_DirectionC2<FT> &d) const
{
  int quadrant_this = (dx() >= FT(0)) ? ((dy() >= FT(0))?1:4)
                                       : ((dy() >= FT(0))?2:3);
  int quadrant_d    = (d.dx() >= FT(0)) ? ((d.dy() >= FT(0))?1:4)
                                         : ((d.dy() >= FT(0))?2:3);

  if(quadrant_this < quadrant_d) {
    return true;
  } else if (quadrant_this > quadrant_d){
    return false;
  }else {
    return dy() * d.dx() < d.dy() * dx();
  }
}

template < class FT >
bool  CGAL_DirectionC2<FT>::operator>(const CGAL_DirectionC2<FT> &d) const
{
  return d < *this ;
}

template < class FT >
bool  CGAL_DirectionC2<FT>::operator>=(const CGAL_DirectionC2<FT> &d) const
{
  return (d < *this) || (d == *this) ;
}

template < class FT >
bool  CGAL_DirectionC2<FT>::operator<=(const CGAL_DirectionC2<FT> &d) const
{
  return (*this < d) || (d == *this) ;
}

template < class FT >
bool  CGAL_DirectionC2<FT>::counterclockwise_in_between(
                                        const CGAL_DirectionC2<FT> &d1,
                                        const CGAL_DirectionC2<FT> &d2) const
{
  return (d2 > *this) && (*this > d1) ;
}
template < class FT >
inline CGAL_VectorC2<FT> CGAL_DirectionC2<FT>::vector() const
{

  return CGAL_VectorC2<FT>(*this);
}

template < class FT >
CGAL_DirectionC2<FT> CGAL_DirectionC2<FT>::perpendicular(
                                                const CGAL_Orientation &o) const
{
  CGAL_kernel_precondition(o != CGAL_COLLINEAR);
  if(o == CGAL_COUNTERCLOCKWISE){
    return CGAL_DirectionC2<FT>(-dy(), dx());
  }else{
    return CGAL_DirectionC2<FT>(dy(), -dx());
  }
}

template < class FT >
CGAL_DirectionC2<FT> CGAL_DirectionC2<FT>::transform(
                                const CGAL_Aff_transformationC2<FT> &t) const
{
  return t.transform(*this);
}

template < class FT >
inline CGAL_DirectionC2<FT> CGAL_DirectionC2<FT>::operator-() const
{

  return CGAL_DirectionC2<FT>(-dx(), -dy());
}



template < class FT >
FT CGAL_DirectionC2<FT>::delta(int i) const
{
  CGAL_kernel_precondition( ( i == 0 ) || ( i == 1 ) );
  if(i == 0) {
    return dx();
  }
  return dy();
}


template < class FT >
FT CGAL_DirectionC2<FT>::dx() const
{

  return ptr()->e0;
}

template < class FT >
FT CGAL_DirectionC2<FT>::dy() const
{

  return ptr()->e1;
}


#endif
