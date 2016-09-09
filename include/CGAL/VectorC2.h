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

// Source: VectorC2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_VECTORC2_H
#define CGAL_VECTORC2_H

#include <CGAL/Twotuple.h>
#include <CGAL/PointC2.h>

template < class FT >
class CGAL_VectorC2 : public CGAL_Handle
{
friend CGAL_VectorC2<FT> operator-(const CGAL_PointC2<FT> &p,
                                   const CGAL_Origin &o);

#ifdef CGAL_WORKAROUND_001
  // SGI has problems with the 'inline'
friend CGAL_VectorC2<FT> CGAL_DirectionC2<FT>::vector() const;

#else


#ifdef CGAL_WORKAROUND_003
  friend class CGAL_DirectionC2<FT>;
#else
  // that's what we want but the GNU g++ compiler has trouble with
  // the not yet defined class CGAL_DirectionC2<FT>
  friend inline CGAL_VectorC2<FT> CGAL_DirectionC2<FT>::vector() const;
#endif // CGAL_WORKAROUND_003

#endif  // CGAL_WORKAROUND_001

public:
                       CGAL_VectorC2();

                       CGAL_VectorC2(const CGAL_VectorC2 &v);

                       CGAL_VectorC2(const CGAL_Null_vector &);

                       CGAL_VectorC2(const FT &hx, const FT &hy, const FT &hw);

                       CGAL_VectorC2(const FT &x, const FT &y);

                       ~CGAL_VectorC2();


  CGAL_VectorC2<FT>    &operator=(const CGAL_VectorC2<FT> &v);

  bool                 operator==(const CGAL_VectorC2<FT> &v) const;
  bool                 operator!=(const CGAL_VectorC2<FT> &v) const;

  bool                 operator==(const CGAL_Null_vector &) const;
  bool                 operator!=(const CGAL_Null_vector &p) const;

  int                  id() const;

  FT                   hx() const;
  FT                   hy() const;
  FT                   hw() const;

  FT                   x() const;
  FT                   y() const;
  FT                   cartesian(int i) const;
  FT                   operator[](int i) const;

  FT                   homogeneous(int i) const;

  int                  dimension() const;

  CGAL_VectorC2        operator+(const CGAL_VectorC2<FT> &w) const;
  CGAL_VectorC2        operator-(const CGAL_VectorC2<FT> &w) const;
  CGAL_VectorC2        operator-() const;
  FT                   operator*(const CGAL_VectorC2<FT> &w) const;
  CGAL_VectorC2        operator/(const FT &c) const;
  CGAL_DirectionC2<FT> direction() const;

  CGAL_VectorC2<FT>    perpendicular(const CGAL_Orientation &o) const;
  CGAL_VectorC2<FT>    transform(const CGAL_Aff_transformationC2<FT> &) const;

protected:
                       CGAL_VectorC2(const CGAL_PointC2<FT> &p);
                       CGAL_VectorC2(const CGAL_DirectionC2<FT> &d);
private:
  CGAL__Twotuple<FT>*   ptr() const;
};

template < class FT >
inline CGAL__Twotuple<FT>*   CGAL_VectorC2<FT>::ptr() const
{
  return (CGAL__Twotuple<FT>*)PTR;
}


#include <CGAL/DirectionC2.h>


template < class FT >
CGAL_VectorC2<FT>::CGAL_VectorC2()
{
  PTR = new CGAL__Twotuple<FT>();
}

template < class FT >
inline CGAL_VectorC2<FT>::CGAL_VectorC2(const CGAL_VectorC2<FT>  &v) :
  CGAL_Handle((CGAL_Handle&)v)
{}

template < class FT >
CGAL_VectorC2<FT>::CGAL_VectorC2(const CGAL_Null_vector &)
{
PTR = new CGAL__Twotuple<FT>(FT(0), FT(0));
}


template < class FT >
CGAL_VectorC2<FT>::CGAL_VectorC2(const FT &hx, const FT &hy, const FT &hw)
{
  if( hw == FT(1)){
    PTR = new CGAL__Twotuple<FT>(hx, hy);
  } else {
    PTR = new CGAL__Twotuple<FT>(hx/hw, hy/hw);
  }
}

template < class FT >
CGAL_VectorC2<FT>::CGAL_VectorC2(const FT &x, const FT &y)
{
  PTR = new CGAL__Twotuple<FT>(x, y);
}

template < class FT >
inline CGAL_VectorC2<FT>::~CGAL_VectorC2()
{}

template < class FT >
CGAL_VectorC2<FT> &CGAL_VectorC2<FT>::operator=(const CGAL_VectorC2<FT> &v)
{

  CGAL_Handle::operator=(v);
  return *this;
}
template < class FT >
inline CGAL_VectorC2<FT>::CGAL_VectorC2(const CGAL_PointC2<FT> &p) :
  CGAL_Handle((CGAL_Handle&)p)
{

}

template < class FT >
inline CGAL_VectorC2<FT>::CGAL_VectorC2(const CGAL_DirectionC2<FT> &d) :
  CGAL_Handle((CGAL_Handle&)d)
{

}
template < class FT >
bool CGAL_VectorC2<FT>::operator==(const CGAL_VectorC2<FT> &v) const
{
  return  ((x() == v.x()) && (y() == v.y())) ;
}

template < class FT >
inline bool CGAL_VectorC2<FT>::operator!=(const CGAL_VectorC2<FT> &v) const
{
  return !(*this == v);
}

template < class FT >
bool CGAL_VectorC2<FT>::operator==(const CGAL_Null_vector &) const
{
  return  ((x() == FT(0)) && (y() == FT(0))) ;
}

template < class FT >
inline bool CGAL_VectorC2<FT>::operator!=(const CGAL_Null_vector &v) const
{
  return !(*this == v);
}

template < class FT >
int CGAL_VectorC2<FT>::id() const
{
  return (int) PTR ;
}
template < class FT >
FT CGAL_VectorC2<FT>::x()  const
{

  return ptr()->e0;
}

template < class FT >
FT CGAL_VectorC2<FT>::y()  const
{

  return  ptr()->e1 ;
}

template < class FT >
inline FT  CGAL_VectorC2<FT>::cartesian(int i) const
{
  CGAL_kernel_precondition( (i == 0) || (i == 1) );
  if(i == 0) {
    return x();
  }
  return y();
}

template < class FT >
inline FT  CGAL_VectorC2<FT>::operator[](int i) const
{
  return cartesian(i);
}

template < class FT >
inline int CGAL_VectorC2<FT>::dimension() const
{

  return 2;
}

template < class FT >
FT CGAL_VectorC2<FT>::hx()  const
{

  return ptr()->e0;
}

template < class FT >
FT CGAL_VectorC2<FT>::hy()  const
{

  return ptr()->e1;
}

template < class FT >
FT CGAL_VectorC2<FT>::hw()  const
{

  return FT(1);
}

template < class FT >
FT  CGAL_VectorC2<FT>::homogeneous(int i) const
{
  if (i == 2) {
    return FT(1);
  }
  return cartesian(i);
}
template < class FT >
inline CGAL_VectorC2<FT> CGAL_VectorC2<FT>::operator+(
                                             const CGAL_VectorC2<FT> &w) const
{
  return CGAL_VectorC2<FT>(x() + w.x(), y() + w.y()) ;
}

template < class FT >
inline CGAL_VectorC2<FT> CGAL_VectorC2<FT>::operator-(
                                             const CGAL_VectorC2<FT> &w) const
{
  return CGAL_VectorC2<FT>(x() - w.x(), y() - w.y()) ;
}

template < class FT >
inline CGAL_VectorC2<FT> CGAL_VectorC2<FT>::operator-() const
{

  return CGAL_VectorC2<FT>(-x(), -y()) ;
}

template < class FT >
inline FT CGAL_VectorC2<FT>::operator*(const CGAL_VectorC2<FT> &w) const
{
  return x() * w.x() + y() * w.y() ;
}

template < class FT >
CGAL_VectorC2<FT> operator*(const FT &c, const CGAL_VectorC2<FT> &w)
{
   return CGAL_VectorC2<FT>( c* w.x(), c * w.y()) ;
}


template < class FT >
inline CGAL_VectorC2<FT> CGAL_VectorC2<FT>::operator/(const FT &c) const
{
  return CGAL_VectorC2<FT>( x()/c, y()/c) ;
}

template < class FT >
inline CGAL_DirectionC2<FT>   CGAL_VectorC2<FT>::direction() const
{
  return CGAL_DirectionC2<FT>(*this) ;
}

template < class FT >
CGAL_VectorC2<FT> CGAL_VectorC2<FT>::perpendicular(
                                                const CGAL_Orientation &o) const
{
  CGAL_kernel_precondition( o != CGAL_COLLINEAR );
  if(o == CGAL_COUNTERCLOCKWISE){
    return CGAL_VectorC2<FT>(-y(), x());
  }else{
    return CGAL_VectorC2<FT>(y(), -x());
  }
}

template < class FT >
CGAL_VectorC2<FT> CGAL_VectorC2<FT>::transform(
                                 const CGAL_Aff_transformationC2<FT> &t) const
{
  return t.transform(*this);
}



#endif
