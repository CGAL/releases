// ============================================================================
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
// release       : CGAL-2.2
// release_date  : 2000, September 30
// 
// source        : web_3/advanced_3.fw
// file          : include/CGAL/Old_style_kernel/Aff_transformation_3.h
// revision      : 3.1
// revision_date : 06 Apr 2000 
// author(s)     : Stefan Schirra
//
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_OLD_STYLE_KERNEL_AFF_TRANSFORMATION_3_H
#define CGAL_OLD_STYLE_KERNEL_AFF_TRANSFORMATION_3_H

namespace CGAL {

template <class R_>
class Aff_transformation_3< R_, Old_style_tag>
  : public R_::Aff_transformation_3_base
{
 public:
  typedef  R_                           R;
  typedef typename R::RT                RT;
  typedef typename R::Vector_3_base     RVector_3;
  typedef typename R::Direction_3_base  RDirection_3;
  typedef typename R::Aff_transformation_3_base  RAff_transformation_3;

  Aff_transformation_3()
    : RAff_transformation_3() {}
  Aff_transformation_3(const RAff_transformation_3& t)
    : RAff_transformation_3(t) {}
  Aff_transformation_3(const Identity_transformation tag)
    : RAff_transformation_3(tag) {}
  Aff_transformation_3(const Translation tag,
                       const RVector_3& v)
    : RAff_transformation_3(tag, v) {}
  Aff_transformation_3(const Scaling tag,
                       const RT &s,
                       const RT &w= RT(1))
    : RAff_transformation_3(tag, s, w) {}
  Aff_transformation_3(
      const RT& m11, const RT& m12, const RT& m13, const RT& m14,
      const RT& m21, const RT& m22, const RT& m23, const RT& m24,
      const RT& m31, const RT& m32, const RT& m33, const RT& m34,
                                                   const RT& w= RT(1) )
    : RAff_transformation_3(m11, m12, m13, m14,
                            m21, m22, m23, m24,
                            m31, m32, m33, m34,
                                           w) {}
  Aff_transformation_3(
      const RT& m11, const RT& m12, const RT& m13,
      const RT& m21, const RT& m22, const RT& m23,
      const RT& m31, const RT& m32, const RT& m33,
                                                   const RT& w = RT(1) )
    : RAff_transformation_3(m11, m12, m13,
                           m21, m22, m23,
                           m31, m32, m33,
                                          w) {}

};

} // namespace CGAL
#endif // CGAL_OLD_STYLE_KERNEL_AFF_TRANSFORMATION_3_H
