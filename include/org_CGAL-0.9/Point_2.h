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


// Source: Point_2.h
// Author: Andreas Fabri

#ifndef CGAL_POINT_2_H
#define CGAL_POINT_2_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/PointH2.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/PointC2.h>
#endif // CGAL_CARTESIAN_H

#include <CGAL/Vector_2.h>

template <class _R>
class CGAL_Point_2 : public _R::Point_2
{
public:
  typedef  _R   R;
private:


#ifdef CGAL_WORKAROUND_001
friend  CGAL_Point_2<R> operator+(const CGAL_Origin &o,
                                  const CGAL_Vector_2<R> &v);
friend  CGAL_Point_2<R> operator-(const CGAL_Origin &o,
                                  const CGAL_Vector_2<R> &v);
#else
friend inline CGAL_Point_2<R> operator+(const CGAL_Origin &o,
                                        const CGAL_Vector_2<R> &v);
friend inline CGAL_Point_2<R> operator-(const CGAL_Origin &o,
                                        const CGAL_Vector_2<R> &v);
#endif // CGAL_WORKAROUND_001

public:
  CGAL_Point_2()
  {}

  CGAL_Point_2(const CGAL_Origin &o)
    : R::Point_2(o)
  {}

  CGAL_Point_2(const CGAL_Point_2<R> &p)
    : R::Point_2((R::Point_2&)p)
  {}

  CGAL_Point_2(const R::Point_2 &p)
    : R::Point_2(p)
  {}

  CGAL_Point_2(const R::RT &hx, const R::RT &hy)
    : R::Point_2(hx, hy)
  {}

  CGAL_Point_2(const R::RT &hx, const R::RT &hy, const R::RT &hw)
    : R::Point_2(hx, hy, hw)
  {}

  CGAL_Point_2<R> &operator=(const CGAL_Point_2<R> &p)
  {
    R::Point_2::operator=(p);
    return *this;
  }

  bool operator==(const CGAL_Point_2<R> &p) const
  {
    return R::Point_2::operator==(p);
  }

  bool operator!=(const CGAL_Point_2<R> &p) const
  {
    return !(*this == p);
  }

  int id() const
  {
    return (int) PTR;
  }

  R::RT hx() const
  {
    return R::Point_2::hx();
  }

  R::RT hy() const
  {
    return R::Point_2::hy();
  }

  R::RT hw() const
  {
    return R::Point_2::hw();
  }
  R::FT x() const
  {
    return R::Point_2::x();
  }

  R::FT y() const
  {
    return R::Point_2::y();
  }

  R::RT homogeneous(int i) const
  {
    return R::Point_2::homogeneous(i);
  }

  R::FT cartesian(int i) const
  {
    return R::Point_2::cartesian(i);
  }

  R::FT operator[](int i) const
  {
    return cartesian(i);
  }

  int dimension() const
  {
    return 2;
  }

  CGAL_Bbox_2       bbox() const
  {
    return R::Point_2::bbox();
  }

  CGAL_Point_2<R> transform(const CGAL_Aff_transformation_2<R> &t) const
  {
    return R::Point_2::transform(t);
  }

private:

  CGAL_Point_2(const R::Vector_2 &v)
    : R::Point_2(v)
  {}
};

#ifndef CGAL_NO_OSTREAM_INSERT_POINT_2
template < class R >
ostream &operator<<(ostream &os, const CGAL_Point_2<R> &p)
{
    return os << (const R::Point_2&)p;
}
#endif // CGAL_NO_OSTREAM_INSERT_POINT_2

#ifndef CGAL_NO_ISTREAM_EXTRACT_POINT_2
template < class R >
istream &operator>>(istream &is, CGAL_Point_2<R> &p)
{
    return is >> (R::Point_2&)p;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_POINT_2



#include <CGAL/Aff_transformation_2.h>

template < class R >
inline CGAL_Point_2<R> operator+(const CGAL_Point_2<R> &p,
                                 const CGAL_Vector_2<R> &v)
{
  return CGAL_Point_2<R>((const R::Point_2&)p + (const R::Vector_2&)v) ;
}

#ifdef CGAL_VECTOR_WRAPPER
template < class R >
inline CGAL_Point_2<R> operator+(const CGAL_Point_2<R> &p,
                                 const CGAL__Vector_2_rft_wrapper<R> &wrapper)
{
  return CGAL_Point_2<R>((const R::Point_2&)p +
                      (const R::Vector_2&)((const CGAL_Vector_2<R>&)wrapper)) ;
}

template < class R >
inline CGAL_Point_2<R> operator-(const CGAL_Point_2<R> &p,
                                 const CGAL__Vector_2_rft_wrapper<R> &wrapper)
{
  return CGAL_Point_2<R>((const R::Point_2&)p -
                      (const R::Vector_2&)((const CGAL_Vector_2<R>&)wrapper)) ;
}
#endif // CGAL_VECTOR_WRAPPER

template < class R >
inline CGAL_Point_2<R> operator-(const CGAL_Point_2<R> &p,
                                 const CGAL_Vector_2<R> &v)
{
  return CGAL_Point_2<R>((const R::Point_2&)p - (const R::Vector_2&)v) ;
}


template < class R >
#ifndef CGAL_WORKAROUND_001
inline
#endif
CGAL_Point_2<R> operator+(const CGAL_Origin &,
                          const CGAL_Vector_2<R> &v)
{
  return CGAL_Point_2<R>(v) ;
}


template < class R >
#ifndef CGAL_WORKAROUND_001
inline
#endif
CGAL_Point_2<R> operator-(const CGAL_Origin &,
                          const CGAL_Vector_2<R> &v)
{

  return CGAL_Point_2<R>(-v) ;
}

template < class R >
inline CGAL_Vector_2<R> operator-(const CGAL_Point_2<R> &p,
                                  const CGAL_Point_2<R> &q)
{
  return CGAL_Vector_2<R>((const R::Point_2&)p - (const R::Point_2&)q) ;
}

template < class R >
#ifndef CGAL_WORKAROUND_001
inline
#endif
CGAL_Vector_2<R> operator-(const CGAL_Point_2<R> &p,
                           const CGAL_Origin &)
{

  return CGAL_Vector_2<R>(p) ;
}

template < class R >
inline CGAL_Vector_2<R> operator-(const CGAL_Origin &,
                                  const CGAL_Point_2<R> &p)
{

  return CGAL_Vector_2<R>(CGAL_ORIGIN - (const R::Point_2&)p) ;
}



#endif // CGAL_POINT_2_H
