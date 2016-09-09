
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

#include <list>

typedef CGAL::Cartesian<double> TutorialR;
typedef CGAL::Point_2<TutorialR> Point;
typedef CGAL::Vector_2<TutorialR> Vector;
typedef CGAL::Segment_2<TutorialR> Segment;
typedef CGAL::Triangle_2<TutorialR> Triangle;
typedef CGAL::Circle_2<TutorialR> Circle;
typedef CGAL::Bbox_2 Bbox;
typedef CGAL::Polygon_traits_2<TutorialR> Polygon_traits;
typedef std::list< Point > Polygon_Container;
typedef CGAL::Polygon_2< Polygon_traits, Polygon_Container > Polygon;
typedef CGAL::Aff_transformation_2<TutorialR> Transformation;

typedef CGAL::Triangulation_euclidean_traits_2<TutorialR> EucliTraits;
typedef CGAL::Triangulation_vertex_base_2<EucliTraits> TrianVbase;
typedef CGAL::Triangulation_face_base_2<EucliTraits> TrianFbase;
typedef CGAL::Triangulation_default_data_structure_2<EucliTraits,
    TrianVbase, TrianFbase> TrianDs;
typedef CGAL::Triangulation_2
    <EucliTraits, TrianDs>
    Triangulation;
typedef CGAL::Delaunay_triangulation_2
    < EucliTraits, TrianDs >
    Delaunay_triangulation;


