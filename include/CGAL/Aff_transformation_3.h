// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-1.2
// release_date  : 1999, January 18
// 
// source        : Aff_transformation_3.fw
// file          : include/CGAL/Aff_transformation_3.h
// package       : _3 (1.4)
// revision      : 1.4
// revision_date : 15 Dec 1998 
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
//
// email         : cgal@cs.uu.nl
//
// ======================================================================
 

#ifndef CGAL_AFF_TRANSFORMATION_3_H
#define CGAL_AFF_TRANSFORMATION_3_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED

#if defined(CGAL_CFG_INCOMPLETE_TYPE_BUG_1) && \
   !defined(CGAL_NO_PLANE_TRANSFORM_IN_AT)
#define CGAL_NO_PLANE_TRANSFORM_IN_AT
#endif // CGAL_CFG_INCOMPLETE_TYPE_BUG_1

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/Aff_transformationH3.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/Aff_transformationC3.h>
#endif // CGAL_CARTESIAN_H

#include <CGAL/Point_3.h>
#include <CGAL/Vector_3.h>
#include <CGAL/Direction_3.h>
#include <CGAL/Plane_3.h>

template <class _R>
class CGAL_Aff_transformation_3 : public _R::Aff_transformation_3
{
public:
  typedef _R                                R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Plane_3               Plane_3;
  typedef typename R::Aff_transformation_3  Aff_transformation_3;

  // default constructor
  CGAL_Aff_transformation_3() : Aff_transformation_3()
  {}
  // copy constructor
  CGAL_Aff_transformation_3(const CGAL_Aff_transformation_3<R>& t)
    : Aff_transformation_3(t)
  {}
  // up cast constructor
  CGAL_Aff_transformation_3(const Aff_transformation_3& t)
    : Aff_transformation_3(t)
  {}
  // translation:
  CGAL_Aff_transformation_3(const CGAL_Translation tag,
                            const CGAL_Vector_3<R>& v)
    : Aff_transformation_3(tag, v)
  {}
  // scaling:
  CGAL_Aff_transformation_3(const CGAL_Scaling tag,
                            const RT& s,
                            const RT& w= RT(1) )
    : Aff_transformation_3(tag, s, w)
  {}
  // the general case:
  CGAL_Aff_transformation_3(
      const RT& m11, const RT& m12, const RT& m13, const RT& m14,
      const RT& m21, const RT& m22, const RT& m23, const RT& m24,
      const RT& m31, const RT& m32, const RT& m33, const RT& m34,
                                                   const RT& w= RT(1) )
    : Aff_transformation_3(m11, m12, m13, m14,
                           m21, m22, m23, m24,
                           m31, m32, m33, m34,
                                          w)
  {}
  CGAL_Aff_transformation_3(
      const RT& m11, const RT& m12, const RT& m13,
      const RT& m21, const RT& m22, const RT& m23,
      const RT& m31, const RT& m32, const RT& m33,
                                                   const RT& w = RT(1) )
    : Aff_transformation_3(m11, m12, m13,
                           m21, m22, m23,
                           m31, m32, m33,
                                          w)
  {}
  // dtor
  ~CGAL_Aff_transformation_3()
  {}
  // transformations
  CGAL_Point_3<R>       transform(const CGAL_Point_3<R>& p) const
                        { return Aff_transformation_3::transform(p); }
  CGAL_Point_3<R>       operator()(const CGAL_Point_3<R>& p) const
                        { return Aff_transformation_3::transform(p); }
  CGAL_Vector_3<R>      transform(const CGAL_Vector_3<R>& v) const
                        { return Aff_transformation_3::transform(v); }
  CGAL_Vector_3<R>      operator()(const CGAL_Vector_3<R>& v) const
                        { return Aff_transformation_3::transform(v); }
  CGAL_Direction_3<R>   transform(const CGAL_Direction_3<R>& d) const
                        { return Aff_transformation_3::transform(d); }
  CGAL_Direction_3<R>   operator()(const CGAL_Direction_3<R>& d) const
                        { return Aff_transformation_3::transform(d); }
#ifndef CGAL_NO_PLANE_TRANSFORM_IN_AT
  CGAL_Plane_3<R>       transform(const CGAL_Plane_3<R>& pl) const
                        { return Aff_transformation_3::transform(pl); }
#else
  CGAL_Plane_3<R>
    transform(const CGAL_Plane_3<R>& pl) const
    {
      return
      (( const Plane_3& )pl).transform( (const Aff_transformation_3&)(*this) );
    }
#endif // CGAL_NO_PLANE_TRANSFORM_IN_AT
  CGAL_Plane_3<R>       operator()(const CGAL_Plane_3<R>& pl) const
                        { return transform(pl); }
  // further members
  CGAL_Aff_transformation_3<R>
                        inverse() const
                        { return Aff_transformation_3::inverse(); }
  bool                  is_even() const
                        { return Aff_transformation_3::is_even(); }
  bool                  is_odd() const
                        { return !is_even(); }
  // access
  FT                    cartesian(int i, int j) const
                        { return Aff_transformation_3::cartesian(i,j); }
  RT                    homogeneous(int i, int j) const
                        { return Aff_transformation_3::homogeneous(i,j); }
  FT                    m(int i, int j) const
                        { return Aff_transformation_3::m(i,j); }
  RT                    hm(int i, int j) const
                        { return Aff_transformation_3::hm(i,j); }
  // composition
  CGAL_Aff_transformation_3<R>
                        operator*(const CGAL_Aff_transformation_3<R>& t) const
                        {
                          return
                          CGAL_static_cast(const Aff_transformation_3&,*this) *
                          CGAL_static_cast(const Aff_transformation_3&,t ) ;
                        }
};

// I/O operators
#ifndef CGAL_NO_OSTREAM_INSERT_AFF_TRANSFORMATION_3
template < class R >
ostream&
operator<<(ostream& os, const CGAL_Aff_transformation_3<R>& t)
{
  typedef typename   R::Aff_transformation_3  Aff_transformation_3;
  return os << CGAL_static_cast(const Aff_transformation_3&,t);
}
#endif // CGAL_NO_OSTREAM_INSERT_AFF_TRANSFORMATION_3

#ifndef CGAL_NO_ISTREAM_EXTRACT_AFF_TRANSFORMATION_3
template < class R >
istream&
operator>>(istream& is, CGAL_Aff_transformation_3<R>& t)
{
  typedef typename   R::Aff_transformation_3  Aff_transformation_3;
  return is >> CGAL_static_cast(const Aff_transformation_3&,t);
}
#endif // CGAL_NO_ISTREAM_EXTRACT_AFF_TRANSFORMATION_3


#endif // CGAL_AFF_TRANSFORMATION_3_H
