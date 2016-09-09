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


// Source: homogeneous_rep.h
// Author: Stefan Schirra

#ifndef CGAL_HOMOGENEOUS_REP_H
#define CGAL_HOMOGENEOUS_REP_H

#define CGAL_REP_CLASS_DEFINED

#include <CGAL/Quotient.h>

template<class nt>
class CGAL_Homogeneous
{
public:
// number-type

    typedef     nt                            RT;
    typedef     CGAL_Quotient<nt>             FT;

// two-dimensional

    typedef CGAL_PointH2<FT,RT>               Point_2;
    typedef CGAL_VectorH2<FT,RT>              Vector_2;
    typedef CGAL_DirectionH2<FT,RT>           Direction_2;

    typedef CGAL_Aff_transformationH2<FT,RT>  Aff_transformation_2;

    typedef CGAL_SegmentH2<FT,RT>             Segment_2;
    typedef CGAL_LineH2<FT,RT>                Line_2;
    typedef CGAL_RayH2<FT,RT>                 Ray_2;

    typedef CGAL_TriangleH2<FT,RT>            Triangle_2;
    typedef CGAL_CircleH2<FT,RT>              Circle_2;

    typedef CGAL_Iso_rectangleH2<FT,RT>       Iso_rectangle_2;


// three-dimensional

    typedef CGAL_PointH3<FT,RT>               Point_3;
    typedef CGAL_VectorH3<FT,RT>              Vector_3;
    typedef CGAL_DirectionH3<FT,RT>           Direction_3;

    typedef CGAL_Aff_transformationH3<FT,RT>  Aff_transformation_3;

    typedef CGAL_PlaneH3<FT,RT>               Plane_3;

    typedef CGAL_SegmentH3<FT,RT>             Segment_3;
    typedef CGAL_LineH3<FT,RT>                Line_3;
    typedef CGAL_RayH3<FT,RT>                 Ray_3;
    typedef CGAL_TriangleH3<FT,RT>            Triangle_3;

    typedef CGAL_Iso_rectangleH3<FT,RT>       Iso_rectangle_3;

    typedef CGAL_TetrahedronH3<FT,RT>         Tetrahedron_3;

#ifdef CGAL_WORKAROUND_013
    typedef CGAL__Vector_2_rft_wrapper< CGAL_Homogeneous<RT> >* W2ptr;
    typedef CGAL__Vector_3_rft_wrapper< CGAL_Homogeneous<RT> >* W3ptr;
#endif // CGAL_WORKAROUND_013

// Geert-Jan's additional features

  static
  FT
  make_FT(const RT & num, const RT& denom)
  {
   return FT(num, denom);
  }

  static
  FT
  make_FT(const RT & num)
  {
   return FT(num);
  }

  static
  RT
  FT_numerator(const FT &r)
  {
   return r.numerator();
  }

  static
  RT
  FT_denominator(const FT &r)
  {
   return r.denominator();
  }

};

#endif // CGAL_HOMOGENEOUS_REP_H
