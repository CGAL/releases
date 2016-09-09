// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

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
// file          : include/CGAL/Cartesian/Aff_transformation_d.C
// package       : Cd (1.14)
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2000/11/17 14:52:05 $
// author(s)     : Herve Brönnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_AFF_TRANSFORMATION_D_C
#define CGAL_CARTESIAN_AFF_TRANSFORMATION_D_C

#include <CGAL/Cartesian/Aff_transformation_rep_d.C>
#include <iostream>

#ifndef CGAL_CTAG
#define CGAL_CTAG
#endif

#ifdef CGAL_CFG_TYPENAME_BUG
#define typename
#endif

CGAL_BEGIN_NAMESPACE

#ifndef CGAL_NO_OSTREAM_INSERT_AFF_TRANSFORMATIONCD
template < class R >
std::ostream &
operator<<(std::ostream &os,
           const Aff_transformationCd<R CGAL_CTAG> &t)
{
  t.print(os);
  return os;
}
#endif // CGAL_NO_OSTREAM_INSERT_AFF_TRANSFORMATIONCD

#ifndef CGAL_NO_ISTREAM_EXTRACT_AFF_TRANSFORMATIONCD
template < class R >
std::istream &
operator>>(std::istream &is,
           Aff_transformationCd<R CGAL_CTAG> &t)
{
  // FIXME : TODO
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_AFF_TRANSFORMATIONCD

CGAL_END_NAMESPACE

#ifdef CGAL_CFG_TYPENAME_BUG
#undef typename
#endif

#endif // CGAL_CARTESIAN_AFF_TRANSFORMATION_D_C
