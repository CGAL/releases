//  Copyright CGAL 1996
//
//  cgal@cs.ruu.nl
//
//  This file is part of an internal release of the CGAL kernel.
//  The code herein may be used and/or copied only in accordance
//  with the terms and conditions stipulated in the agreement
//  under which the code has been supplied or with the written
//  permission of the CGAL Project.
//
//  Look at http://www.cs.ruu.nl/CGAL/ for more information.
//  Please send any bug reports and comments to cgal@cs.ruu.nl
//
//  The code comes WITHOUT ANY WARRANTY; without even the implied
//  warranty of FITNESS FOR A PARTICULAR PURPOSE.
//

// Source: homogeneous_rep.h
// Author: Stefan.Schirra@mpi-sb.mpg.de
#ifndef CGAL_HOMOGENEOUS_REP_H
#define CGAL_HOMOGENEOUS_REP_H

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

//    typedef CGAL_PolygonH2<FT,RT>             Polygon_2;

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
