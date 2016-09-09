 
// Source: homogeneous_rep.h
// Author: Stefan.Schirra@mpi-sb.mpg.de
#ifndef CGAL_HOMOGENEOUS_REP_H
#define CGAL_HOMOGENEOUS_REP_H

 
template<class ft, class rt>
class H
{
public:
// number-type

    typedef ft                                FT;
    typedef rt                                RT;

// two-dimensional

    typedef CGAL_PointH2<FT,RT>               Point_2;
    typedef CGAL_VectorH2<FT,RT>              Vector_2;
    typedef CGAL_DirectionH2<FT,RT>           Direction_2;

    typedef CGAL_Aff_transformationH2<FT,RT>  Aff_transformation_2;

    typedef CGAL_SegmentH2<FT,RT>             Segment_2;
    typedef CGAL_LineH2<FT,RT>                Line_2;
    typedef CGAL_RayH2<FT,RT>                 Ray_2;

    typedef CGAL_TriangleH2<FT,RT>            Triangle_2;

    typedef CGAL_Iso_rectangleH2<FT,RT>       Iso_rectangle_2;

    typedef CGAL_PolygonH2<FT,RT>             Polygon_2;

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
};
 

#endif // CGAL_HOMOGENEOUS_REP_H
