// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : include/CGAL/Cartesian/global_operators_d.h
// package       : Cd (1.1.1)
// revision      : $Revision: 1.2 $
// revision_date : $Date: 1999/12/07 18:53:29 $
// author(s)     : Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_CARTESIAN_GLOBAL_OPERATORS_D_C
#define CGAL_CARTESIAN_GLOBAL_OPERATORS_D_C

#include <CGAL/Cartesian/redefine_names_d.h>

CGAL_BEGIN_NAMESPACE

template < class R >
inline
PointCd<R CGAL_CTAG>
operator+(const PointCd<R CGAL_CTAG> &p, const VectorCd<R CGAL_CTAG> &v)
{
  PointCd<R CGAL_CTAG> result(v.dimension());
  // Note: to be able to access the non-const result.begin(),
  // this function must be a friend of PointCd
  std::transform(p.begin(), p.end(), v.begin(), result.begin(),
                 std::plus<typename R::FT>());
  return result;
}

template < class R >
inline
PointCd<R CGAL_CTAG>
operator-(const PointCd<R CGAL_CTAG> &p, const VectorCd<R CGAL_CTAG> &v)
{
  PointCd<R CGAL_CTAG> result(v.dimension());
  // Note: to be able to access the non-const result.begin(),
  // this function must be a friend of PointCd
  std::transform(p.begin(), p.end(), v.begin(), result.begin(),
                 std::minus<typename R::FT>());
  return result;
}

template < class R >
inline
PointCd<R CGAL_CTAG>
operator+(const Origin &, const VectorCd<R CGAL_CTAG> &v)
{
  return PointCd<R CGAL_CTAG>(v);
}

template < class R >
inline
PointCd<R CGAL_CTAG>
operator-(const Origin &, const VectorCd<R CGAL_CTAG> &v)
{
  return PointCd<R CGAL_CTAG>(-v);
}

template < class R >
inline
VectorCd<R CGAL_CTAG>
operator-(const PointCd<R CGAL_CTAG> &p, const PointCd<R CGAL_CTAG> &q)
{
  VectorCd<R CGAL_CTAG> result(p.dimension());
  // Note: to be able to access the non-const result.begin(),
  // this function must be a friend of VectorCd
  std::transform(p.begin(), p.end(), q.begin(), result.begin(),
                 std::minus<typename R::FT>());
  return result;
}

template < class R >
inline
VectorCd<R CGAL_CTAG>
operator-(const PointCd<R CGAL_CTAG> &p, const Origin &)
{
  return VectorCd<R CGAL_CTAG>(p) ;
}

template < class R >
inline
VectorCd<R CGAL_CTAG>
operator-(const Origin &, const PointCd<R CGAL_CTAG> &p)
{
  return - VectorCd<R CGAL_CTAG>(p) ;
}

template < class R >
CGAL_KERNEL_INLINE
VectorCd<R CGAL_CTAG>
operator*(const typename R::FT &c, const VectorCd<R CGAL_CTAG> &w)
{
  return w * c;
}

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_GLOBAL_OPERATORS_D_C
