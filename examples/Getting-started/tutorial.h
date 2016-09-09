
#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/Vector_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Circle_2.h>
#include <CGAL/Polygon_2.h>

#include <CGAL/Triangulation_euclidean_traits_2.h>
#include <CGAL/Triangulation_2.h>
#include <CGAL/Delaunay_triangulation_2.h>

#include <list.h>

typedef CGAL_Cartesian<double> TutorialR;
typedef CGAL_Point_2<TutorialR> Point_2;
typedef CGAL_Vector_2<TutorialR> Vector_2;
typedef CGAL_Segment_2<TutorialR> Segment_2;
typedef CGAL_Triangle_2<TutorialR> Triangle_2;
typedef CGAL_Circle_2<TutorialR> Circle_2;
typedef CGAL_Bbox_2 Bbox_2;
typedef CGAL_Polygon_traits_2<TutorialR> Polygon_traits_2;
typedef list< Point_2 > Polygon_Container_2;
typedef CGAL_Polygon_2< Polygon_traits_2, Polygon_Container_2 > Polygon_2;
typedef CGAL_Aff_transformation_2<TutorialR> Transformation_2;

typedef CGAL_Triangulation_2
    < CGAL_Triangulation_euclidean_traits_2<TutorialR> >
    Triangulation_2;
typedef CGAL_Delaunay_triangulation_2
    < CGAL_Triangulation_euclidean_traits_2<TutorialR> >
    Delaunay_triangulation_2;


