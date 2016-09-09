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
// file          : include/CGAL/Cartesian/Aff_transformation_rep_2.C
// package       : C2 (3.3.11)
// revision      : $Revision: 1.11 $
// revision_date : $Date: 1999/11/05 22:29:38 $
// author(s)     : Andreas Fabri, Lutz Kettner
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_CARTESIAN_AFF_TRANSFORMATION_REP_2_C
#define CGAL_CARTESIAN_AFF_TRANSFORMATION_REP_2_C

#ifdef CGAL_CFG_TYPENAME_BUG
#define typename
#endif

CGAL_BEGIN_NAMESPACE

template < class R >
CGAL_KERNEL_LARGE_INLINE
Aff_transformation_repC2<R>::Aff_transformation_2
Aff_transformation_repC2<R>::
inverse() const
{
  FT det = FT(1) / (t11 * t22 - t12 * t21);
  return Aff_transformation_2(
    det * t22,    det * (-t12), det * (t12*t23-t13*t22),
    det * (-t21), det * t11 ,   det * (t13*t21-t11*t23));
}

template < class R >
CGAL_KERNEL_INLINE
typename Aff_transformation_repC2<R>::Aff_transformation_2
Aff_transformation_repC2<R>::
operator*(const Aff_transformation_rep_baseC2<R> &t) const
{
  return t.compose(*this);
}
 
template < class R >
CGAL_KERNEL_LARGE_INLINE
typename Aff_transformation_repC2<R>::Aff_transformation_2
Aff_transformation_repC2<R>::
compose(const Aff_transformation_repC2<R> &t) const
{
  return Aff_transformation_2(t.t11*t11 + t.t12*t21,
                              t.t11*t12 + t.t12*t22,
                              t.t11*t13 + t.t12*t23 + t.t13,
                              t.t21*t11 + t.t22*t21,
                              t.t21*t12 + t.t22*t22,
                              t.t21*t13 + t.t22*t23 + t.t23 );
}

template < class R >
CGAL_KERNEL_LARGE_INLINE
typename Aff_transformation_repC2<R>::Aff_transformation_2
Aff_transformation_repC2<R>::
compose(const Translation_repC2<R> &t) const
{
  return Aff_transformation_2(t11,
                              t12,
                              t13 + t._translationvector.x(),
                              t21,
                              t22,
                              t23 + t._translationvector.y());
}

template < class R >
CGAL_KERNEL_LARGE_INLINE
typename Aff_transformation_repC2<R>::Aff_transformation_2
Aff_transformation_repC2<R>::
compose(const Rotation_repC2<R> &t) const
{
  return Aff_transformation_2(t._cosinus*t11 - t._sinus*t21,
                              t._cosinus*t12 - t._sinus*t22,
                              t._cosinus*t13 - t._sinus*t23,
                              t._sinus*t11 + t._cosinus*t21,
                              t._sinus*t12 + t._cosinus*t22,
                              t._sinus*t13 + t._cosinus*t23);
}

template < class R >
CGAL_KERNEL_LARGE_INLINE
typename Aff_transformation_repC2<R>::Aff_transformation_2
Aff_transformation_repC2<R>::
compose(const Scaling_repC2<R> &t) const
{
   return Aff_transformation_2(t._scalefactor * t11,
                               t._scalefactor * t12,
                               t._scalefactor * t13,
                               t._scalefactor * t21,
                               t._scalefactor * t22,
                               t._scalefactor * t23);
}

CGAL_END_NAMESPACE

#ifdef CGAL_CFG_TYPENAME_BUG
#undef typename
#endif

#endif // CGAL_CARTESIAN_AFF_TRANSFORMATION_REP_2_C
