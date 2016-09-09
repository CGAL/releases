/*  triangulation_terrain.C  */
/*---------------------------*/
#include <iostream.h>
#include <fstream.h>

#include <CGAL/Cartesian.h>
#include <CGAL/Triangulation_euclidean_traits_xy_3.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/IO/triangulation_print_OFF.h>

typedef CGAL_Cartesian<double>                          Rep;
typedef CGAL_Point_3<Rep>                               Point;

typedef CGAL_Triangulation_euclidean_traits_xy_3< Rep > Traits;
typedef CGAL_Delaunay_triangulation_2< Traits >         Delaunay;

int main(int argc, char* argv[])
{
  ifstream Points(argv[1]);
  ofstream out(argv[2]);
  Delaunay DT;

  istream_iterator<Point,ptrdiff_t> begin(Points);
  istream_iterator<Point,ptrdiff_t> end;
  DT.insert(begin, end);

  CGAL_triangulation_print_OFF(out,DT);
  return 0;
}
