// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.3
// release_date  : 2001, August 13
// 
// file          : include/CGAL/Tetrahedron_3.h
// package       : _3 (3.23)
// revision      : $Revision: 1.8 $
// revision_date : $Date: 2001/06/27 14:49:54 $
// author(s)     : Andreas Fabri
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_TETRAHEDRON_3_H
#define CGAL_TETRAHEDRON_3_H

#include <CGAL/Plane_3.h>

CGAL_BEGIN_NAMESPACE

template <class R_>
class Tetrahedron_3 : public R_::Tetrahedron_3_base
{
public:
  typedef          R_                       R;
  typedef typename R::RT                    RT;
  typedef typename R::FT                    FT;
  typedef typename R::Tetrahedron_3_base  RTetrahedron_3;

  Tetrahedron_3() : RTetrahedron_3()
  {}
  Tetrahedron_3(const CGAL::Tetrahedron_3<R>& t) : RTetrahedron_3(t)
  {}
  Tetrahedron_3(const RTetrahedron_3&  t) : RTetrahedron_3(t)
  {}
  Tetrahedron_3(const CGAL::Point_3<R>& p,
                     const CGAL::Point_3<R>& q,
                     const CGAL::Point_3<R>& r,
                     const CGAL::Point_3<R>& s)
    : RTetrahedron_3(p,q,r,s)
  {}

  CGAL::Point_3<R>    vertex(int i) const
                     { return RTetrahedron_3::vertex(i); }
  CGAL::Point_3<R>    operator[](int i) const
                     { return vertex(i); }
  CGAL::Tetrahedron_3<R>
                     transform(const CGAL::Aff_transformation_3<R>& t) const
                     {
                       return
                       CGAL::Tetrahedron_3<R>(RTetrahedron_3::transform(t));
                     }
};

#ifndef CGAL_NO_OSTREAM_INSERT_TETRAHEDRON_3
template < class R >
std::ostream&
operator<<(std::ostream& os, const Tetrahedron_3<R>& t)
{
  typedef typename  R::Tetrahedron_3_base  RTetrahedron_3;
  return os << static_cast<const RTetrahedron_3&>(t);
}
#endif // CGAL_NO_OSTREAM_INSERT_TETRAHEDRON_3

#ifndef CGAL_NO_ISTREAM_EXTRACT_TETRAHEDRON_3
template < class R >
std::istream&
operator>>(std::istream& is, Tetrahedron_3<R>& t)
{
  typedef typename  R::Tetrahedron_3_base  RTetrahedron_3;
  return is >> static_cast<RTetrahedron_3&>(t);
}
#endif // CGAL_NO_ISTREAM_EXTRACT_TETRAHEDRON_3

CGAL_END_NAMESPACE

#endif  // CGAL_TETRAHEDRON_3_H
