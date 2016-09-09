// Source: cartesian_classes.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_CLASSES_H
#define CGAL_CLASSES_H

#include <CGAL/enum.h>
#include <assert.h>
#include <CGAL/utils.h>
#include <CGAL/number_utils.h>
#include <CGAL/doublefield.h>

class CGAL_Origin;

class CGAL_Bbox_2;

class CGAL_Bbox_3;

template < class FT >
class CGAL_PointC2;

template < class R >
class CGAL_Point_2;

template < class FT >
class CGAL_VectorC2;

template < class R >
class CGAL_Vector_2;

template < class FT >
class CGAL_DirectionC2;

template < class FT >
class CGAL_LineC2;

template < class R >
class CGAL_Line_2;

template < class FT >
class CGAL_RayC2;

template < class R >
class CGAL_Ray_2;

template < class FT >
class CGAL_SegmentC2;

template < class R >
class CGAL_Segment_2;

template < class FT >
class CGAL_TriangleC2;

template < class R >
class CGAL_Triangle_2;

template < class FT >
class CGAL_PolygonC2;

template < class R >
class CGAL_Polygon_2;

template < class FT >
class CGAL_Iso_rectangleC2;

template < class FT >
class CGAL_Iso_rectangleC3;

template < class R >
class CGAL_Iso_rectangle_2;

template < class R >
class CGAL_Iso_rectangle_3;

template < class FT >
class CGAL_Aff_transformation_baseC2;

template < class R >
class CGAL_Aff_transformation_base_2;

template < class FT >
class CGAL_Aff_transformationC2;

template < class R >
class CGAL_Aff_transformation_2;

template < class FT >
class CGAL_PlaneC3;

template < class R >
class CGAL_Plane_3;

template < class FT >
class CGAL_PointC3;

template < class FT >
class CGAL_VectorC3;

template < class FT >
class CGAL_DirectionC3;

template < class FT >
class CGAL_LineC3;

template < class R >
class CGAL_Line_3;

template < class FT >
class CGAL_RayC3;

template < class FT >
class CGAL_Ray_3;

template < class FT >
class CGAL_SegmentC3;

template < class FT >
class CGAL_Segment_3;

template < class FT >
class CGAL_TriangleC3;

template < class FT >
class CGAL_Triangle_3;

template < class FT >
class CGAL_TetrahedronC3;

template < class FT >
class CGAL_Tetrahedron_3;

template < class FT >
class CGAL_Aff_transformationC3;

class dint;  // integers in the range of [..] stored in a double


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

#endif
