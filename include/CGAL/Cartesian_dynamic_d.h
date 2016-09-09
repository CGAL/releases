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
// file          : include/CGAL/Cartesian_dynamic_d.h
// package       : Cartesian_kernel (6.24)
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2000/10/19 16:15:19 $
// author(s)     : Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_DYNAMIC_D_H
#define CGAL_CARTESIAN_DYNAMIC_D_H

#include <CGAL/basic.h>
#include <CGAL/basic_classes.h>
#include <CGAL/cartesian_classes.h>
#include <CGAL/user_classes.h>

#define CGAL_REP_CLASS_DEFINED
#define CGAL_CARTESIAN_CLASS_DEFINED

CGAL_BEGIN_NAMESPACE

template< class R, class FT_ >
struct Cartesian_base_dynamic_d
{
    // Number types and representation tag
    typedef FT_                                 RT;
    typedef FT_                                 FT;
    typedef Cartesian_tag                       Rep_tag;

#ifndef CGAL_CFG_NO_ADVANCED_KERNEL
    // Because of partial specialization, CGAL::Point_d<R> is selected as
    // CGAL::Point_d<Cartesian_d<FT>,Cartesian_tag>
    // CAUTION: This is not yet done, so we revert to the old class PointCd
    typedef CGAL::Point_d<R,Rep_tag>             Point_d;
#else
    typedef PointCd<FT>                          Point_d;
#endif // CGAL_CFG_NO_ADVANCED_KERNEL
};

CGAL_END_NAMESPACE

// TODO: we revert to the old class PointCd
#include <CGAL/PointCd.h>

CGAL_BEGIN_NAMESPACE

// This class is a restricted dD geometric kernel
// It is useful only if you do not need the 3D kernel
// If you need both, you should be using Cartesian<FT>

template< class FT_ >
struct Cartesian_dynamic_d
  : public Cartesian_base_dynamic_d< Cartesian_dynamic_d<FT_>, FT_ >
{
    // Number types and representation tag
    typedef FT_                                 RT;
    typedef FT_                                 FT;
    typedef Cartesian_tag                       Rep_tag;

    typedef Cartesian_dynamic_d<FT_>            Self;
    typedef Cartesian_base_dynamic_d<Self,FT_>  Kernel_base;

#ifndef CGAL_CFG_NO_ADVANCED_KERNEL
    // The lasses are inherited and because of partial specialization,
    // Cartesian_d<FT>::Point_d is exactly CGAL::Point_d< Cartesian_d<FT> >
    // We still need to inherit explicitly, see Cartesian.h for explanation

    typedef typename Kernel_base::Point_d       Point_d;

#else
    // Now CGAL::Point_d<R> is only a wrapper around CGAL::PointCd<R>
    // It is necessary to redefine here the classes to ensure that
    // Cartesian_d<FT>::Point_d is exactly CGAL::Point_d< Cartesian_d<FT> >

    // Cartesian_d<FT>::Base is needed so that CGAL::Point_d< Cartesian_d<FT> >
    // can inherit from Cartesian_d<FT>::Kernel_base::Point_d

    typedef typename Kernel_base::Point_d       Point_d_base;

    // Note: necessary to qualify Point_d by ::CGAL:: to disambiguate between
    // Point_d in the current namespace (nested within CGAL) and
    // CGAL::Point_d< Cartesian_d<FT> > (which is in the CGAL namespace)

    typedef CGAL::Point_d<Self>                 Point_d;

    // TODO: cleanup
    static   FT make_FT(const RT & num, const RT& denom) { return num/denom;}
    static   FT make_FT(const RT & num)                  { return num;}
    static   RT FT_numerator(const FT &r)                { return r;}
    static   RT FT_denominator(const FT &)               { return RT(1);}

#endif // CGAL_CFG_NO_ADVANCED_KERNEL
};

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_DYNAMIC_D_H
