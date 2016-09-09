// ======================================================================
//
// Copyright (c) 2001 The CGAL Consortium

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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/Filtered_kernel.h
// package       : Interval_arithmetic (4.141)
// revision      : $Revision: 1.19 $
// revision_date : $Date: 2001/12/19 14:10:52 $
// author(s)     : Sylvain Pion
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_FILTERED_KERNEL_H
#define CGAL_FILTERED_KERNEL_H

// This file contains the definition of a generic kernel filter.
//
// TODO:
// - at the moment, it's restricted to IA filtering, but this should be
//   generalized to allow filters (static...).
// - at the moment, only the predicates are filtered.
//   Constructions will come later.
// - the kernel only works with traits only and as a pure traits only.

#include <CGAL/basic.h>
#include <CGAL/Filtered_predicate.h>
#include <CGAL/Cartesian_converter.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/MP_Float.h>

CGAL_BEGIN_NAMESPACE

// CK = construction kernel.
// EK = exact kernel called when needed by the filter.
// FK = filtering kernel
template <class CK,
          class EK = Simple_cartesian<MP_Float>,
          class FK = Simple_cartesian<Interval_nt_advanced>,
	  class C2E = Cartesian_converter<CK, EK>,
	  class C2F = Cartesian_converter<CK, FK,
	              Interval_converter<
#ifndef __SUNPRO_CC
		      CGAL_TYPENAME_MSVC_NULL
#endif
		      CK::RT> > >
class Filtered_kernel
{
public:
    // What to do with the tag ?
    // Probably this should not exist, should it ?
    // struct filter_tag{};
    // typedef filter_tag                                     Kernel_tag;
    // typedef typename CK::Kernel_tag                       Kernel_tag;
    typedef typename CK::Rep_tag                          Rep_tag;
    typedef typename CK::RT                               RT;
    typedef typename CK::FT                               FT;

    // Macros to define the types, predicates and constructions.

    // If we adopt this solution, then we can simply derive ?
#define CGAL_Filter_type(X) \
    typedef typename CK::X X##_base; \
    typedef typename CK::X X;

#define CGAL_Filter_pred(P, Pf) \
    typedef Filtered_predicate<typename EK::P, typename FK::P, \
	                     C2E, C2F> P; \
    P Pf() const { return P(); }

    // The following could be used instead for some Cartesian predicates
    // that are exact : compare* and exact*.
#define CGAL_Filter_already_exact_pred(P, Pf) \
    typedef typename CK::P P; \
    P Pf() const { return P(); }

#define CGAL_Filter_cons(C, Cf) \
    typedef typename CK::C C; \
    C Cf() const { return C(); }

    // Types :

    // CGAL_Filter_type(RT) // ?
    // CGAL_Filter_type(FT) // ?

    CGAL_Filter_type(Object_2)
    CGAL_Filter_type(Point_2)
    CGAL_Filter_type(Vector_2)
    CGAL_Filter_type(Direction_2)
    CGAL_Filter_type(Segment_2)
    CGAL_Filter_type(Line_2)
    CGAL_Filter_type(Ray_2)
    CGAL_Filter_type(Triangle_2)
    CGAL_Filter_type(Circle_2)
    CGAL_Filter_type(Iso_rectangle_2)
    CGAL_Filter_type(Conic_2)
    // CGAL_Filter_type(Aff_transformation_2)
    // CGAL_Filter_type(Data_accessor_2) // ?

    CGAL_Filter_type(Object_3)
    CGAL_Filter_type(Point_3)
    CGAL_Filter_type(Vector_3)
    CGAL_Filter_type(Direction_3)
    CGAL_Filter_type(Segment_3)
    CGAL_Filter_type(Line_3)
    CGAL_Filter_type(Plane_3)
    CGAL_Filter_type(Ray_3)
    CGAL_Filter_type(Triangle_3)
    CGAL_Filter_type(Tetrahedron_3)
    CGAL_Filter_type(Sphere_3)
    CGAL_Filter_type(Iso_cuboid_3)
    // CGAL_Filter_type(Aff_transformation_3)

#define CGAL_Kernel_pred(X,Y,Z) CGAL_Filter_pred(Y,Z)
#define CGAL_Kernel_cons(X,Y,Z) CGAL_Filter_cons(Y,Z)
#define CGAL_Kernel_pred2(W,X,Y,Z) CGAL_Filter_pred(Y,Z)
#define CGAL_Kernel_cons2(W,X,Y,Z) CGAL_Filter_cons(Y,Z)

#include <CGAL/Kernel/interface_macros.h>

};

CGAL_END_NAMESPACE

#endif // CGAL_FILTERED_KERNEL_H
