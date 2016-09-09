#include "tutorial.h"
#include <CGAL/Point_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Bbox_2.h>
#include <CGAL/intersections.h>

void main()
{
  Triangle_2 t1(Point_2(-5.2,1.7), Point_2(-7.1,-6.3), Point_2(-0.9,-2.3));
  Triangle_2 t2(Point_2(-4.8,-4.5), Point_2(4.5,-1.1), Point_2(2.4,-7.6));

  Bbox_2 bbox1 = t1.bbox();
  Bbox_2 bbox2 = t2.bbox();

  cout << "Triangle 1:\n" << t1 << "\nand triangle 2:\n" << t2 << endl;
  if ( ! CGAL_do_overlap(bbox1, bbox2) )
    cout << "do not intersect" << endl;
  else if ( ! CGAL_do_intersect(t1,t2))
    cout << "do not intersect" << endl;
  else
    cout << "do intersect" << endl;
}
