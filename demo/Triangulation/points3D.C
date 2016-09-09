extern "C" long clock();

#include <assert.h>
#include <iostream.h>
#include <fstream.h>
#include <string.h>
#include <CGAL/Cartesian.h>

#include <CGAL/Point_3.h>
#include <CGAL/predicates_on_points_3.h>
#include <CGAL/Triangle_3.h>
// #include <CGAL/IO/istream_3.h>
// #include <CGAL/IO/ostream_3.h>

#include <CGAL/Triangulation_vertex.h>
#include <CGAL/Triangulation_face.h>
#include <CGAL/Triangulation_face_circulator.h>
#include <CGAL/Triangulation_vertex_circulator.h>

#include <CGAL/Triangulation_euclidean_traits_xy_3.h>
#include <CGAL/Delaunay_triangulation_2.h>

#include <CGAL/IO/triangulation_print_OFF.h>
// #include <CGAL/IO/Geomview_stream.h>

typedef CGAL_Cartesian<double> Rep;
typedef CGAL_Point_3<Rep> Point;

typedef CGAL_Triangulation_euclidean_traits_xy_3< Rep > Traits;

typedef CGAL_Triangulation_2< Traits >          Triangulation;
typedef CGAL_Delaunay_triangulation_2< Traits > Delaunay;



int main(int argc, char* argv[])
{
  ifstream Points(argv[1]);
  ofstream out(argv[2]);
  Delaunay DT;

  istream_iterator<Point,ptrdiff_t> begin(Points);
  istream_iterator<Point,ptrdiff_t> end;

  long t1=clock();
  DT.insert(begin, end);
  long t2=clock();
  cout << "Triangulation takes time " << (t2-t1)/1000000.0 << endl;

  // CGAL_Geomview_stream Geomview;
  CGAL_triangulation_print_OFF(out,DT);

  return 0;
}
