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


// Source: Point_3.h
// Author: Andreas Fabri 

#ifndef CGAL_POINT_3_H
#define CGAL_POINT_3_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/PointH3.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/PointC3.h>
#endif // CGAL_CARTESIAN_H

#include <CGAL/Vector_3.h>

template <class _R>
class CGAL_Point_3 : public _R::Point_3
{
public:
  typedef  _R   R;
private:


#ifdef CGAL_WORKAROUND_001
friend  CGAL_Point_3<R> operator+(const CGAL_Origin &o,
                                  const CGAL_Vector_3<R> &v);
friend  CGAL_Point_3<R> operator-(const CGAL_Origin &o,
                                  const CGAL_Vector_3<R> &v);
#else
friend inline CGAL_Point_3<R> operator+(const CGAL_Origin &o,
                                        const CGAL_Vector_3<R> &v);
friend inline CGAL_Point_3<R> operator-(const CGAL_Origin &o,
                                        const CGAL_Vector_3<R> &v);
#endif // CGAL_WORKAROUND_001

public:
  CGAL_Point_3()
  {}

  CGAL_Point_3(const CGAL_Origin &o)
    : R::Point_3(o)
  {}

  CGAL_Point_3(const CGAL_Point_3<R> &p)
    : R::Point_3((R::Point_3&)p)
  {}

  CGAL_Point_3(const R::Point_3 &p)
    : R::Point_3(p)
  {}

  CGAL_Point_3(const R::RT &hx, const R::RT &hy,  const R::RT &hz)
    : R::Point_3(hx, hy, hz)
  {}

  CGAL_Point_3(const R::RT &hx, const R::RT &hy,  const R::RT &hz,
               const R::RT &hw)
    : R::Point_3(hx, hy, hz, hw)
  {}


  CGAL_Point_3<R> &operator=(const CGAL_Point_3<R> &p)
  {
    R::Point_3::operator=(p);
    return *this;
  }

  bool operator==(const CGAL_Point_3<R> &p) const
  {
    return R::Point_3::operator==(p);
  }

  bool operator!=(const CGAL_Point_3<R> &p) const
  {
    return !(*this == p);
  }

  int id() const
  {
    return (int) PTR ;
  }

  R::RT hx() const
  {
    return R::Point_3::hx();
  }

  R::RT hy() const
  {
    return R::Point_3::hy();
  }

  R::RT hz() const
  {
    return R::Point_3::hz();
  }

  R::RT hw() const
  {
    return R::Point_3::hw();
  }
  R::FT x() const
  {
    return R::Point_3::x();
  }

  R::FT y() const
  {
    return R::Point_3::y();
  }

  R::FT z() const
  {
    return R::Point_3::z();
  }

  R::RT homogeneous(int i) const
  {
    return R::Point_3::homogeneous(i);
  }

  R::FT cartesian(int i) const
  {
    return R::Point_3::cartesian(i);
  }

  R::FT operator[](int i) const
  {
    return cartesian(i);
  }

  int dimension() const
  {
    return 3;
  }

  CGAL_Bbox_3       bbox() const
  {
    return R::Point_3::bbox();
  }


  CGAL_Point_3<R> transform(const CGAL_Aff_transformation_3<R> &t) const
  {
    return R::Point_3::transform(t);
  }


private:

  CGAL_Point_3(const R::Vector_3 &v)
    : R::Point_3(v)
  {}
};


#include <CGAL/Aff_transformation_3.h>

template < class R >
inline CGAL_Point_3<R> operator+(const CGAL_Point_3<R> &p,
                                 const CGAL_Vector_3<R> &v)
{
  return CGAL_Point_3<R>((R::Point_3&)p + (R::Vector_3&)v) ;
}


#ifdef CGAL_VECTOR_WRAPPER
template < class R >
inline CGAL_Point_3<R> operator+(const CGAL_Point_3<R> &p,
                                 const CGAL__Vector_3_rft_wrapper<R> &wrapper)
{
  return CGAL_Point_3<R>((const R::Point_3&)p +
                      (const R::Vector_3&)((const CGAL_Vector_3<R>&)wrapper)) ;
}


template < class R >
inline CGAL_Point_3<R> operator-(const CGAL_Point_3<R> &p,
                                 const CGAL__Vector_3_rft_wrapper<R> &wrapper)
{
  return CGAL_Point_3<R>((const R::Point_3&)p -
                      (const R::Vector_3&)((const CGAL_Vector_3<R>&)wrapper)) ;
}
#endif // CGAL_VECTOR_WRAPPER

template < class R >
inline CGAL_Point_3<R> operator-(const CGAL_Point_3<R> &p,
                                  const CGAL_Vector_3<R> &v)
{
  return CGAL_Point_3<R>((R::Point_3&)p - (R::Vector_3&)v) ;
}



template < class R >
inline CGAL_Point_3<R> operator+(const CGAL_Origin &,
                                  const CGAL_Vector_3<R> &v)
{

  return CGAL_Point_3<R>(v) ;
}


template < class R >
inline CGAL_Point_3<R> operator-(const CGAL_Origin &,
                                  const CGAL_Vector_3<R> &v)
{

  return CGAL_Point_3<R>(-v) ;
}

template < class R >
inline CGAL_Vector_3<R> operator-(const CGAL_Point_3<R> &p,
                                   const CGAL_Point_3<R> &q)
{
  return CGAL_Vector_3<R>((R::Point_3&)p - (R::Point_3&)q) ;
}

template < class R >
inline CGAL_Vector_3<R> operator-(const CGAL_Point_3<R> &p,
                                   const CGAL_Origin &)
{

  return CGAL_Vector_3<R>(p) ;
}

template < class R >
inline CGAL_Vector_3<R> operator-(const CGAL_Origin &,
                                   const CGAL_Point_3<R> &p)
{

  return CGAL_Vector_3<R>(CGAL_ORIGIN - (R::Point_3&)p) ;
}



#ifndef CGAL_NO_OSTREAM_INSERT_POINT_3

template < class R >
ostream &operator<<(ostream &os, const CGAL_Point_3<R> &p)
{
    return os << (const R::Point_3&)p;
}
#endif // CGAL_NO_OSTREAM_INSERT_POINT_3

#ifndef CGAL_NO_ISTREAM_EXTRACT_POINT_3
template < class R >
istream &operator>>(istream &is, CGAL_Point_3<R> &p)
{
    return is >> (R::Point_3&)p;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_POINT_3


#endif // CGAL_POINT_3_H
