// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-1.1
// release_date  : 1998, July 24
// 
// source        : Homogeneous.fw
// file          : include/CGAL/homogeneous_rep.h
// package       : Kernel_basic (1.2)
// revision      : 1.2
// revision_date : 12 Jun 1998 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_HOMOGENEOUS_REP_H
#define CGAL_HOMOGENEOUS_REP_H

#define CGAL_REP_CLASS_DEFINED

#ifndef CGAL_QUOTIENT_H
#include <CGAL/Quotient.h>
#endif // CGAL_QUOTIENT_H
#ifndef CGAL_REPRESENTATION_TAGS_H
#include <CGAL/representation_tags.h>
#endif // CGAL_REPRESENTATION_TAGS_H

// 2D homogeneous point data accessor
template < class _FT, class _RT >
class CGAL_Data_accessorH2
{
public:
    typedef  _FT                  FT;
    typedef  _RT                  RT;
    typedef  CGAL_PointH2<FT,RT>  Point;

    RT  get_hx( Point const& p) const { return( p.hx()); }
    RT  get_hy( Point const& p) const { return( p.hy()); }
    RT  get_hw( Point const& p) const { return( p.hw()); }

    void
    get( Point const& p, RT& hx, RT& hy, RT& hw) const
    {
        hx = get_hx( p);
        hy = get_hy( p);
        hw = get_hw( p);
    }

    void
    set( Point& p, RT const& hx, RT const& hy, RT const& hw) const
    {
        p = Point( hx, hy, hw);
    }
};

template<class nt>
class CGAL_Homogeneous
{
public:
  // number-type
    typedef nt                                RT;
    typedef CGAL_Quotient<nt>                 FT;
  
  // representation type tag
    typedef CGAL_Homogeneous_tag              Rep_tag;
  
  // data accessor
    typedef CGAL_Data_accessorH2<FT,RT>       Data_accessor_2;
  
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
  
    typedef CGAL_ConicHPA2<Point_2,Data_accessor_2>
                                              Conic_2;
  
  
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
  
  #ifdef CGAL_CFG_INCOMPLETE_TYPE_BUG_1
    typedef CGAL__Vector_2_rft_wrapper< CGAL_Homogeneous<RT> >* W2ptr;
    typedef CGAL__Vector_3_rft_wrapper< CGAL_Homogeneous<RT> >* W3ptr;
  #endif // CGAL_CFG_INCOMPLETE_TYPE_BUG_1
  
  
  // D-dimensional
    typedef CGAL_PointHd<FT,RT>               Point_d;
  
  
    static
    FT
    make_FT(const RT & num, const RT& denom)
    { return FT(num, denom); }
  
    static
    FT
    make_FT(const RT & num)
    { return FT(num); }
  
    static
    RT
    FT_numerator(const FT &r)
    { return r.numerator(); }
  
    static
    RT
    FT_denominator(const FT &r)
    { return r.denominator(); }
  
  
};


#endif // CGAL_HOMOGENEOUS_REP_H
