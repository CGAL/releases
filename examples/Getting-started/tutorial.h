#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/Vector_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Circle_2.h>
#include <CGAL/Euclidean_2.h>
#include <CGAL/Triangulation_2.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL_Cartesian<double> TutorialR;
typedef CGAL_Point_2<TutorialR> Point_2;
typedef CGAL_Vector_2<TutorialR> Vector_2;
typedef CGAL_Segment_2<TutorialR> Segment_2;
typedef CGAL_Circle_2<TutorialR> Circle_2;
typedef CGAL_Triangulation_2< CGAL_Euclidean_2<TutorialR> > Triangulation_2;
typedef CGAL_Delaunay_triangulation_2< CGAL_Euclidean_2<TutorialR> > Delaunay_triangulation_2;
