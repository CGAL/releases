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

// Source: VectorC3.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_VECTORC3_H
#define CGAL_VECTORC3_H

#include <CGAL/Threetuple.h>
#include <CGAL/PointC3.h>

template < class FT >
class CGAL_VectorC3 : public CGAL_Handle
{
friend inline CGAL_VectorC3<FT> operator-(const CGAL_PointC3<FT> &p,
                                          const CGAL_Origin &o);

#ifdef CGAL_WORKAROUND_001
  // SGI has problems with the 'inline'
friend CGAL_VectorC3<FT> CGAL_DirectionC3<FT>::vector() const;

#else
#ifdef CGAL_WORKAROUND_003
  friend class CGAL_DirectionC3<FT>;
#else
  // that's what we want but the GNU g++ compiler has trouble with
  // the not yet defined class CGAL_DirectionC3<FT>
friend inline CGAL_VectorC3<FT> CGAL_DirectionC3<FT>::vector() const;
#endif // CGAL_WORKAROUND_003
#endif  // CGAL_WORKAROUND_001

public:
                       CGAL_VectorC3();

                       CGAL_VectorC3(const CGAL_VectorC3<FT> &v);

                       CGAL_VectorC3(const CGAL_Null_vector &);

                       CGAL_VectorC3(const FT &x, const FT &y, const FT &z);

                       CGAL_VectorC3(const FT &x, const FT &y, const FT &z,
                                     const FT &w);

                       ~CGAL_VectorC3();

  CGAL_VectorC3<FT>    &operator=(const CGAL_VectorC3<FT> &v);

  bool                 operator==(const CGAL_VectorC3<FT> &p) const;
  bool                 operator!=(const CGAL_VectorC3<FT> &p) const;

  bool                 operator==(const CGAL_Null_vector &) const;
  bool                 operator!=(const CGAL_Null_vector &) const;

  int                  id() const;

  FT                   x() const;
  FT                   y() const;
  FT                   z() const;
  FT                   cartesian(int i) const;
  FT                   operator[](int i) const;

  FT                   hx() const;
  FT                   hy() const;
  FT                   hz() const;
  FT                   hw() const;
  FT                   homogeneous(int i) const;

  int                  dimension() const;

  CGAL_VectorC3        operator+(const CGAL_VectorC3<FT> &w) const;
  CGAL_VectorC3        operator-(const CGAL_VectorC3<FT> &w) const;
  CGAL_VectorC3        operator-() const;
  FT                   operator*(const CGAL_VectorC3<FT> &w) const;
  CGAL_VectorC3        operator/(const FT &c) const;
  CGAL_DirectionC3<FT> direction() const;
  CGAL_VectorC3<FT> transform(const CGAL_Aff_transformationC3<FT> &) const;

protected:
                       CGAL_VectorC3(const CGAL_PointC3<FT> &p);
                       CGAL_VectorC3(const CGAL_DirectionC3<FT> &p);

private:
  CGAL__Threetuple<FT>*   ptr() const;
};

template < class FT >
inline CGAL__Threetuple<FT>*   CGAL_VectorC3<FT>::ptr() const
{
  return (CGAL__Threetuple<FT>*)PTR;
}


#include <CGAL/DirectionC3.h>

template < class FT >
CGAL_VectorC3<FT>::CGAL_VectorC3()
{
  PTR = new CGAL__Threetuple<FT>(FT(0), FT(0), FT(0));
}

template < class FT >
CGAL_VectorC3<FT>::CGAL_VectorC3(const CGAL_VectorC3<FT>  &v) :
  CGAL_Handle(v)
{}

template < class FT >
CGAL_VectorC3<FT>::CGAL_VectorC3(const CGAL_Null_vector  &)
{
  PTR = new CGAL__Threetuple<FT>(FT(0), FT(0), FT(0));
}

template < class FT >
CGAL_VectorC3<FT>::CGAL_VectorC3(const FT &x, const FT &y, const FT &z)
{
  PTR = new CGAL__Threetuple<FT>(x, y, z);
}

template < class FT >
CGAL_VectorC3<FT>::CGAL_VectorC3(const FT &x, const FT &y, const FT &z,
                                 const FT &w)
{
  if( w != FT(1)){
    PTR = new CGAL__Threetuple<FT>(x/w, y/w, z/w);
  } else {
    PTR = new CGAL__Threetuple<FT>(x, y, z);
  }
}

template < class FT >
CGAL_VectorC3<FT>::~CGAL_VectorC3()
{}


template < class FT >
CGAL_VectorC3<FT> &CGAL_VectorC3<FT>::operator=(const CGAL_VectorC3<FT> &v)
{

  CGAL_Handle::operator=(v);
  return *this;
}
template < class FT >
inline CGAL_VectorC3<FT>::CGAL_VectorC3(const CGAL_PointC3<FT> &p) :
  CGAL_Handle((CGAL_Handle&)p)
{

}

template < class FT >
inline CGAL_VectorC3<FT>::CGAL_VectorC3(const CGAL_DirectionC3<FT> &d) :
  CGAL_Handle((CGAL_Handle&)d)
{

}
template < class FT >
bool CGAL_VectorC3<FT>::operator==(const CGAL_VectorC3<FT> &v) const
{
  return (x() == v.x()) && (y() == v.y()) && (z() == v.z()) ;
}

template < class FT >
inline bool CGAL_VectorC3<FT>::operator!=(const CGAL_VectorC3<FT> &v) const
{
  return !(*this == v);
}


template < class FT >
bool CGAL_VectorC3<FT>::operator==(const CGAL_Null_vector &) const
{
  return (x() == FT(0)) && (y() == FT(0)) && (z() == FT(0)) ;
}

template < class FT >
inline bool CGAL_VectorC3<FT>::operator!=(const CGAL_Null_vector &v) const
{
  return !(*this == v);
}


template < class FT >
int CGAL_VectorC3<FT>::id() const
{
  return (int) PTR ;
}
template < class FT >
FT CGAL_VectorC3<FT>::x()  const
{

  return ptr()->e0;
}

template < class FT >
FT CGAL_VectorC3<FT>::y()  const
{

  return  ptr()->e1 ;
}

template < class FT >
FT CGAL_VectorC3<FT>::z()  const
{
  return  ptr()->e2 ;
}

template < class FT >
inline FT  CGAL_VectorC3<FT>::cartesian(int i) const
{
  CGAL_kernel_precondition(i == 0 || i == 1 || i == 2 );
  switch (i)
    {
    case 0: return x();
    case 1: return y();
    case 2: return z();
    default: assert(0);
    };
  return 0;
}

template < class FT >
inline FT  CGAL_VectorC3<FT>::operator[](int i) const
{
  return cartesian(i);
}

template < class FT >
inline int CGAL_VectorC3<FT>::dimension() const
{
  return 3;
}

template < class FT >
FT CGAL_VectorC3<FT>::hx()  const
{
  return ptr()->e0;
}

template < class FT >
FT CGAL_VectorC3<FT>::hy()  const
{
  return ptr()->e1;
}

template < class FT >
FT CGAL_VectorC3<FT>::hz()  const
{
  return ptr()->e2;
}

template < class FT >
FT CGAL_VectorC3<FT>::hw()  const
{
  return FT(1);
}

template < class FT >
FT  CGAL_VectorC3<FT>::homogeneous(int i) const
{
  if( i == 3 ) {
    return FT(1);
  }
  return cartesian(i);
}
template < class FT >
inline CGAL_VectorC3<FT> CGAL_VectorC3<FT>::operator+(
                                            const CGAL_VectorC3<FT> &w) const
{
  return CGAL_VectorC3<FT>(x() + w.x(), y() + w.y(), z() + w.z()) ;
}

template < class FT >
inline CGAL_VectorC3<FT> CGAL_VectorC3<FT>::operator-(
                                            const CGAL_VectorC3<FT> &w) const
{
  return CGAL_VectorC3<FT>(x() - w.x(), y() - w.y(), z() - w.z()) ;
}

template < class FT >
inline CGAL_VectorC3<FT> CGAL_VectorC3<FT>::operator-() const
{

  return CGAL_VectorC3<FT>(-x(), -y(), -z()) ;
}

template < class FT >
inline FT CGAL_VectorC3<FT>::operator*(const CGAL_VectorC3<FT> &w) const
{
  return x() * w.x() + y() * w.y() + z() * w.z() ;
}

template < class FT >
inline CGAL_VectorC3<FT> operator*(const FT &c, const CGAL_VectorC3<FT> &w)
{
  return CGAL_VectorC3<FT>( c* w.x(), c * w.y(), c * w.z()) ;
}

template < class FT >
inline CGAL_VectorC3<FT> CGAL_VectorC3<FT>::operator/(const FT &c) const
{

  return CGAL_VectorC3<FT>( x()/c, y()/c, z()/c) ;
}

template < class FT >
inline CGAL_DirectionC3<FT> CGAL_VectorC3<FT>::direction() const
{

  return CGAL_DirectionC3<FT>(*this) ;
}


template < class FT >
CGAL_VectorC3<FT> CGAL_VectorC3<FT>::transform(
                                 const CGAL_Aff_transformationC3<FT> &t) const
{
  return t.transform(*this);
}


#endif
