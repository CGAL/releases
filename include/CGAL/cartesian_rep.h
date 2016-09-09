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
// file          : include/CGAL/cartesian_rep.h
// package       : Cartesian_basic (2.1)
// source        : web/Cartesian.fw
// revision      : $Revision: 1.2 $
// revision_date : $Date: 1999/02/28 09:20:04 $
// author(s)     : Andreas.Fabri
//
// coordinator   : INRIA Sophia-Antipolis
// (Herve.Bronnimann)
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_CARTESIAN_REP_H
#define CGAL_CARTESIAN_REP_H

#ifndef CGAL_REPRESENTATION_TAGS_H
#include <CGAL/representation_tags.h>
#endif // CGAL_REPRESENTATION_TAGS_H

CGAL_BEGIN_NAMESPACE

// 2D Cartesian point data accessor
template < class _FT >
class Data_accessorC2
{
public:
    typedef  _FT          FT;
    typedef  PointC2<FT>  Point;

    FT  get_x( Point const& p) const { return( p.x()); }
    FT  get_y( Point const& p) const { return( p.y()); }

    void
    get( Point const& p, FT& x, FT& y) const
    {
        x = get_x( p);
        y = get_y( p);
    }

    void
    set( Point& p, FT const& x, FT const& y) const
    {
        p = Point( x, y);
    }
};


#define CGAL_REP_CLASS_DEFINED

template <class _FT>
class Cartesian
{
public:

    typedef _FT                       FT;
    typedef _FT                       RT;

    typedef Cartesian_tag             Rep_tag;
    typedef Data_accessorC2<FT>       Data_accessor_2;

    typedef PointC2<FT>               Point_2;
    typedef VectorC2<FT>              Vector_2;
    typedef DirectionC2<FT>           Direction_2;

    typedef SegmentC2<FT>             Segment_2;
    typedef LineC2<FT>                Line_2;
    typedef RayC2<FT>                 Ray_2;
    typedef TriangleC2<FT>            Triangle_2;
    typedef CircleC2<FT>              Circle_2;
    typedef ParabolaC2<FT>            Parabola_2;
    typedef Parabola_arcC2<FT>        Parabola_arc_2;

    typedef ConicCPA2<Point_2,Data_accessor_2>  Conic_2;

    typedef Iso_rectangleC2<FT>       Iso_rectangle_2;

    typedef Aff_transformationC2<FT>  Aff_transformation_2;

    typedef PointC3<FT>               Point_3;
    typedef VectorC3<FT>              Vector_3;
    typedef DirectionC3<FT>           Direction_3;

    typedef SegmentC3<FT>             Segment_3;
    typedef LineC3<FT>                Line_3;
    typedef RayC3<FT>                 Ray_3;
    typedef TriangleC3<FT>            Triangle_3;
    typedef PlaneC3<FT>               Plane_3;
    typedef TetrahedronC3<FT>         Tetrahedron_3;

    typedef Iso_rectangleC3<FT>       Iso_rectangle_3;

    typedef Aff_transformationC3<FT>  Aff_transformation_3;

    typedef PointCd<FT>               Point_d;

#ifdef CGAL_CFG_INCOMPLETE_TYPE_BUG_1
    typedef _Vector_2_rft_wrapper< Cartesian<ft> >* dummy_W2ptr;
    typedef _Vector_3_rft_wrapper< Cartesian<ft> >* dummy_W3ptr;
#endif // CFG_INCOMPLETE_TYPE_BUG_1

static   FT make_FT(const RT & num, const RT& denom) { return num/denom;}
static   FT make_FT(const RT & num)                  { return num;}
static   RT FT_numerator(const FT &r)                { return r;}
static   RT FT_denominator(const FT &)               { return RT(1);}
};

CGAL_END_NAMESPACE

#endif  // CGAL_CARTESIAN_REP_H
