/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/

// Source: cartesian_rep.h
// Author: Andreas Fabri

#ifndef CGAL_CARTESIAN_REP_H
#define CGAL_CARTESIAN_REP_H

#define CGAL_REP_CLASS_DEFINED

template<class ft>
class CGAL_Cartesian
{
public:
    typedef ft           FT;
    typedef ft           RT;
    typedef CGAL_PointC2<FT>  Point_2;
    typedef CGAL_VectorC2<FT> Vector_2;
    typedef CGAL_DirectionC2<FT>  Direction_2;

    typedef CGAL_SegmentC2<FT>  Segment_2;
    typedef CGAL_LineC2<FT>  Line_2;
    typedef CGAL_RayC2<FT>  Ray_2;
    typedef CGAL_TriangleC2<FT>  Triangle_2;
    typedef CGAL_CircleC2<FT>  Circle_2;
    typedef CGAL_ParabolaC2<FT>  Parabola_2;
    typedef CGAL_Parabola_arcC2<FT>  Parabola_arc_2;

    typedef CGAL_Iso_rectangleC2<FT>  Iso_rectangle_2;

    typedef CGAL_Aff_transformationC2<FT>  Aff_transformation_2;

    typedef CGAL_PointC3<FT>  Point_3;
    typedef CGAL_VectorC3<FT> Vector_3;
    typedef CGAL_DirectionC3<FT>  Direction_3;

    typedef CGAL_SegmentC3<FT>  Segment_3;
    typedef CGAL_LineC3<FT>  Line_3;
    typedef CGAL_RayC3<FT>  Ray_3;
    typedef CGAL_TriangleC3<FT>  Triangle_3;

    typedef CGAL_Iso_rectangleC3<FT>  Iso_rectangle_3;

    typedef CGAL_Aff_transformationC3<FT>  Aff_transformation_3;

    typedef CGAL_PlaneC3<FT> Plane_3;
    typedef CGAL_TetrahedronC3<FT> Tetrahedron_3;

#ifdef CGAL_WORKAROUND_013
    typedef CGAL__Vector_2_rft_wrapper< CGAL_Cartesian<ft> >* dummy_W2ptr;
    typedef CGAL__Vector_3_rft_wrapper< CGAL_Cartesian<ft> >* dummy_W3ptr;
#endif // CGAL_WORKAROUND_013

static    FT make_FT(const RT & num, const RT& denom)
        { return num/denom;}
static   FT make_FT(const RT & num)
        { return num;}
static   RT FT_numerator(const FT &r)
        { return r;}
static   RT FT_denominator(const FT &)
        { return RT(1);}
};

#endif  // CGAL_CARTESIAN_REP_H
