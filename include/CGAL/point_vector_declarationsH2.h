
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
// release       : CGAL-2.2
// release_date  : 2000, September 30
// 
// source        : PV_decl_2.fw
// file          : include/CGAL/point_vector_declarationsH2.h
// package       : H2 (2.12)
// revision      : 2.12
// revision_date : 03 Aug 2000 
// author(s)     : Stefan Schirra
//
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_POINT_VECTOR_DECLARATIONSH2_H
#define CGAL_POINT_VECTOR_DECLARATIONSH2_H

#ifndef CGAL_HOMOGENEOUS_CLASSES_H
#include <CGAL/homogeneous_classes.h>
#endif // #ifndef CGAL_HOMOGENEOUS_CLASSES_H


CGAL_BEGIN_NAMESPACE

template <class FT, class RT>
inline
PointH2<FT,RT>
origin_plus_vector(const VectorH2<FT,RT>& v);

template <class FT, class RT>
inline
PointH2<FT,RT>
origin_minus_vector(const VectorH2<FT,RT>& v);

template <class FT, class RT>
inline
VectorH2<FT,RT>
point_minus_origin(const PointH2<FT,RT>& p);

template <class FT, class RT>
inline
VectorH2<FT,RT>
origin_minus_point(const PointH2<FT,RT>& p);

template <class FT, class RT>
CGAL_KERNEL_INLINE
PointH2<FT,RT>
operator-(const PointH2<FT,RT>& p, const VectorH2<FT,RT>& v);

template <class FT, class RT>
CGAL_KERNEL_INLINE
VectorH2<FT,RT>
operator-(const PointH2<FT,RT>& p, const PointH2<FT,RT>& q);


template <class FT, class RT>
CGAL_KERNEL_INLINE
VectorH2<FT,RT>
operator+(const VectorH2<FT,RT>& u, const VectorH2<FT,RT>& v);

template <class FT, class RT>
CGAL_KERNEL_INLINE
VectorH2<FT,RT>
operator-(const VectorH2<FT,RT>& u, const VectorH2<FT,RT>& v);

template <class FT, class RT>
CGAL_KERNEL_INLINE
FT
operator*(const VectorH2<FT,RT>& u, const VectorH2<FT,RT>& v);

template <class FT, class RT>
CGAL_KERNEL_INLINE
VectorH2<FT,RT>
operator/(const VectorH2<FT,RT>& v, const RT& f);

template <class FT, class RT>
CGAL_KERNEL_INLINE
VectorH2<FT,RT>
operator*(const VectorH2<FT,RT>& v, const RT& f);

template <class FT, class RT>
CGAL_KERNEL_INLINE
VectorH2<FT,RT>
operator*(const RT& f, const VectorH2<FT,RT>& v);



CGAL_END_NAMESPACE


#endif // CGAL_POINT_VECTOR_DECLARATIONS_2_H
