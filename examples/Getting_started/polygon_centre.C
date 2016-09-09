#include "tutorial.h"
#include <CGAL/Polygon_2.h>
#include <fstream>
#include <assert.h>

typedef Polygon::Vertex_circulator Vertex_circulator;

/* centroid
   Compute the centroid of a simple polygon with formula

   centroid = sum{ (v[i]+v[i+1]) * a[i]} / (3*a)
   where v[i] are the vertices,
   a[i] = v[i].x * v[i+1].y - v[i+1].x * v[i].y,
   and a = sum{a[i]}.

   see: G. Bashein and P. Detmer, Centroid of a polygon,
        in Graphic Gems IV, Academic Press, 1994, pp 3-6.

   Precondition: polygon has at least three vertices
*/
Point centroid (Polygon &polyg)
{
  // check if the polygon has at least three vertices
  assert (polyg.size() >= 3);

  Vertex_circulator start = polyg.vertices_circulator();
  Vertex_circulator cur = start;
  Vertex_circulator next = cur;
  ++next;

  Vector centre(0,0);
  double a=0.0, atot=0.0;
  do {
    a = ((*cur).x()) * ((*next).y()) - ((*next).x()) * ((*cur).y());
    atot = atot + a;
    centre = centre + ((*cur - CGAL::ORIGIN) + (*next - CGAL::ORIGIN)) * a;
    cur = next;
    ++next;
  } while (cur != start);
  atot = 3*atot;
  centre = centre/atot;
  return CGAL::ORIGIN + centre;
}


int main()
{
  Polygon polygon;

  std::ifstream from("polygon.dat");
  CGAL::set_ascii_mode(from);
  from >> polygon;

  Point centre = centroid(polygon);
  std::cout << "The centroid " << centre << " lies ";
  if (polygon.bounded_side(centre) != CGAL::ON_BOUNDED_SIDE)
      std::cout << "not ";
  std::cout << "inside the polygon." << std::endl;
  return 0;
}
