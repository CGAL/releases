/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/


// Source: VectorC2.h
// Author: Andreas Fabri

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

                       CGAL_VectorC2(const CGAL_VectorC2<FT> &v);

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

  CGAL_VectorC2<FT>    operator+(const CGAL_VectorC2<FT> &w) const;
  CGAL_VectorC2<FT>    operator-(const CGAL_VectorC2<FT> &w) const;
  CGAL_VectorC2<FT>    operator-() const;
  FT                   operator*(const CGAL_VectorC2<FT> &w) const;
  CGAL_VectorC2<FT>    operator/(const FT &c) const;
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



#ifndef CGAL_NO_OSTREAM_INSERT_VECTORC2
template < class FT >
ostream &operator<<(ostream &os, const CGAL_VectorC2<FT> &v)
{
    switch(os.iword(CGAL_IO::mode)) {
    case CGAL_IO::ASCII :
        return os << v.x() << ' ' << v.y();
    case CGAL_IO::BINARY :
        CGAL_write(os, v.x());
        CGAL_write(os, v.y());
        return os;
    default:
        return os << "VectorC2(" << v.x() << ", " << v.y() << ')';
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_VECTORC2

#ifndef CGAL_NO_ISTREAM_EXTRACT_VECTORC2
template < class FT >
istream &operator>>(istream &is, CGAL_VectorC2<FT> &p)
{
    FT x, y;
    switch(is.iword(CGAL_IO::mode)) {
    case CGAL_IO::ASCII :
        is >> x >> y;
        break;
    case CGAL_IO::BINARY :
        CGAL_read(is, x);
        CGAL_read(is, y);
        break;
    default:
        cerr << "" << endl;
        cerr << "Stream must be in ascii or binary mode" << endl;
        break;
    }
    p = CGAL_VectorC2<FT>(x, y);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_VECTORC2



#endif
