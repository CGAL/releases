 
// Source: cartesian_rep.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_CARTESIAN_REP_H
#define CGAL_CARTESIAN_REP_H

template<class ft>
class C
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
    typedef CGAL_ParabolaC2<FT>  Parabola_2;
    typedef CGAL_Parabola_arcC2<FT>  Parabola_arc_2;

    typedef CGAL_Iso_rectangleC2<FT>  Iso_rectangle_2;

    typedef CGAL_PolygonC2<FT> Polygon_2;
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
};

#endif  // CGAL_CARTESIAN_REP_H
