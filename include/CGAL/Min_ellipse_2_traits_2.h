// ======================================================================
//
// Copyright (c) 1997-2001 The CGAL Consortium

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
// file          : include/CGAL/Min_ellipse_2_traits_2.h
// package       : Min_ellipse_2 (3.14)
// chapter       : Geometric Optimisation
//
// source        : web/Min_ellipse_2.aw
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2001/07/17 12:51:08 $
//
// author(s)     : Sven Schönherr, Bernd Gärtner
// coordinator   : ETH Zürich (Bernd Gärtner)
//
// implementation: default traits class for 2D Smallest Enclosing Ellipse
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_MIN_ELLIPSE_2_TRAITS_2_H
#define CGAL_MIN_ELLIPSE_2_TRAITS_2_H

// includes
#ifndef CGAL_POINT_2_H
#  include <CGAL/Point_2.h>
#endif
#ifndef CGAL_OPTIMISATION_ELLIPSE_2_H
#  include <CGAL/Optimisation_ellipse_2.h>
#endif

CGAL_BEGIN_NAMESPACE

// Class declarations
// ==================
template < class Traits_ >
class Min_ellipse_2;

template < class K_ >
class Min_ellipse_2_traits_2;

// Class interface and implementation
// ==================================
template < class K_ >
class Min_ellipse_2_traits_2 {
  public:
    // types
    typedef  K_                               K;
    typedef  CGAL::Point_2<K>                 Point;
    typedef  CGAL::Optimisation_ellipse_2<K>  Ellipse;

private:
    // data members
    Ellipse  ellipse;                                // current ellipse

    // friends
    friend  class CGAL::Min_ellipse_2< CGAL::Min_ellipse_2_traits_2<K> >;

  public:
    // creation (use default implementations)
    // Min_ellipse_2_traits_2( );
    // Min_ellipse_2_traits_2( Min_ellipse_2_traits_2<K> const&);
};

CGAL_END_NAMESPACE

#endif // CGAL_MIN_ELLIPSE_2_TRAITS_2_H

// ===== EOF ==================================================================
