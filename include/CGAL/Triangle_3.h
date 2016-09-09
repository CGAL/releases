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
// source        : Triangle_3.fw
// file          : include/CGAL/Triangle_3.h
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
 

#ifndef CGAL_TRIANGLE_3_H
#define CGAL_TRIANGLE_3_H

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif  // CGAL_REP_CLASS_DEFINED


#ifdef CGAL_HOMOGENEOUS_H
#ifndef CGAL_TRIANGLEH3_H
#include <CGAL/TriangleH3.h>
#endif // CGAL_TRIANGLEH3_H
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#ifndef CGAL_TRIANGLEC3_H
#include <CGAL/TriangleC3.h>
#endif // CGAL_TRIANGLEC3_H
#endif // CGAL_CARTESIAN_H

#ifndef CGAL_PLANE_3_H
#include <CGAL/Plane_3.h>
#endif // CGAL_PLANE_3_H

template <class _R>
class CGAL_Triangle_3 : public _R::Triangle_3
{
public:
  typedef          _R                       R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Triangle_3            Triangle_3;

  CGAL_Triangle_3() : Triangle_3()
  {}
  CGAL_Triangle_3(const CGAL_Triangle_3<R>& t) : Triangle_3(t)
  {}
  CGAL_Triangle_3(const Triangle_3& t) : Triangle_3(t)
  {}
  CGAL_Triangle_3(const CGAL_Point_3<R>& p,
                  const CGAL_Point_3<R>& q,
                  const CGAL_Point_3<R>& r)
    : R::Triangle_3(p,q,r)
  {}

  CGAL_Triangle_3<R>& operator=(const CGAL_Triangle_3<R>& t)
  {
    Triangle_3::operator=(t);
    return *this;
  }
  bool                operator==(const CGAL_Triangle_3<R>& t) const
                      { return Triangle_3::operator==(t); }
  bool                operator!=(const CGAL_Triangle_3<R>& t) const
                      { return !(*this == t); }
  int                 id() const   /* XXX */
                      { return (int) PTR ; }
  CGAL_Plane_3<R>     supporting_plane() const
                      {
                        return
                        CGAL_Plane_3<R>(
                            Triangle_3::supporting_plane());
                      }
  CGAL_Triangle_3<R>  transform(
                      const CGAL_Aff_transformation_3<R>& t) const
                      {
                        return
                        CGAL_Triangle_3<R>(Triangle_3::transform( t ));
                      }
  bool                has_on(const CGAL_Point_3<R>& p) const
                      { return Triangle_3::has_on(p); }
  bool                is_degenerate() const
                      { return Triangle_3::is_degenerate(); }
  CGAL_Point_3<R>     vertex(int i) const
                      { return Triangle_3::vertex(i); }
  CGAL_Point_3<R>     operator[](int i) const
                      { return vertex(i); }
  CGAL_Bbox_3         bbox() const
                      {
                        return vertex(0).bbox()
                             + vertex(1).bbox()
                             + vertex(2).bbox();
                      }
};

#ifndef CGAL_NO_OSTREAM_INSERT_TRIANGLE_3
template < class R >
ostream&
operator<<(ostream& os, const CGAL_Triangle_3<R>& t)
{
  typedef typename  R::Triangle_3     Triangle_3;
  return os << (const Triangle_3&)t;
}
#endif // CGAL_NO_OSTREAM_INSERT_TRIANGLE_3

#ifndef CGAL_NO_ISTREAM_EXTRACT_TRIANGLE_3
template < class R >
istream&
operator>>(istream& is, CGAL_Triangle_3<R>& t)
{
  typedef typename  R::Triangle_3     Triangle_3;
  return is >> (Triangle_3&)t;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_TRIANGLE_3



#endif
