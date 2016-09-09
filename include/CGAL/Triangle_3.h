// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.0
// release_date  : 1999, June 03
// 
// source        : Triangle_3.fw
// file          : include/CGAL/Triangle_3.h
// package       : _3 (2.1.2)
// revision      : 2.1.2
// revision_date : 21 May 1999 
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
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

CGAL_BEGIN_NAMESPACE

template <class _R>
class Triangle_3 : public _R::Triangle_3
{
public:
  typedef          _R                       R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Triangle_3            RTriangle_3;

  Triangle_3() : RTriangle_3()
  {}
  Triangle_3(const Triangle_3<R>& t) : RTriangle_3(t)
  {}
  Triangle_3(const RTriangle_3&  t) : RTriangle_3(t)
  {}
  Triangle_3(const Point_3<R>& p,
                  const Point_3<R>& q,
                  const Point_3<R>& r)
    : R::Triangle_3(p,q,r)
  {}

  Triangle_3<R>& operator=(const Triangle_3<R>& t)
  {
    RTriangle_3::operator=(t);
    return *this;
  }
  bool                operator==(const Triangle_3<R>& t) const
                      { return RTriangle_3::operator==(t); }
  bool                operator!=(const Triangle_3<R>& t) const
                      { return !(*this == t); }
  int                 id() const   /* XXX */
                      { return (int) PTR ; }
  Plane_3<R>     supporting_plane() const
                      {
                        return
                        Plane_3<R>(
                            RTriangle_3::supporting_plane());
                      }
  Triangle_3<R>  transform(
                      const Aff_transformation_3<R>& t) const
                      {
                        return
                        Triangle_3<R>(RTriangle_3::transform( t ));
                      }
  bool                has_on(const Point_3<R>& p) const
                      { return RTriangle_3::has_on(p); }
  bool                is_degenerate() const
                      { return RTriangle_3::is_degenerate(); }
  Point_3<R>     vertex(int i) const
                      { return RTriangle_3::vertex(i); }
  Point_3<R>     operator[](int i) const
                      { return vertex(i); }
  Bbox_3         bbox() const
                      {
                        return vertex(0).bbox()
                             + vertex(1).bbox()
                             + vertex(2).bbox();
                      }
};

#ifndef NO_OSTREAM_INSERT_TRIANGLE_3
template < class R >
std::ostream&
operator<<(std::ostream& os, const Triangle_3<R>& t)
{
  typedef typename  R::Triangle_3     RTriangle_3;
  return os << (const RTriangle_3& )t;
}
#endif // NO_OSTREAM_INSERT_TRIANGLE_3

#ifndef NO_ISTREAM_EXTRACT_TRIANGLE_3
template < class R >
std::istream&
operator>>(std::istream& is, Triangle_3<R>& t)
{
  typedef typename  R::Triangle_3     RTriangle_3;
  return is >> (RTriangle_3& )t;
}
#endif // NO_ISTREAM_EXTRACT_TRIANGLE_3


CGAL_END_NAMESPACE


#endif // CGAL_TRIANGLE_3_H
