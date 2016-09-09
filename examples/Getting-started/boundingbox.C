#include "tutorial.h"
#include <CGAL/Point_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Bbox_2.h>

void main()
{
  Triangle_2 t1(Point_2(-5.2,1.7), Point_2(-7.1,-6.3), Point_2(-0.9,-2.3));
  Triangle_2 t2(Point_2(-2.8,-4.5), Point_2(4.5,-1.1), Point_2(2.4,-7.6));
  Triangle_2 t3(Point_2(5.5,8.8), Point_2(-7.7,8.3), Point_2(1.3,2.9));

  Bbox_2 bb1 = t1.bbox();
  Bbox_2 bb2 = t2.bbox();
  Bbox_2 bb12, bb3;

  cout << "Bounding box 1: " << bb1 << "\n and bounding box 2: "<< bb2 << endl;
  if ( !CGAL_do_overlap(bb1, bb2) )
     cout << "do not ";
  cout << "overlap." << endl;

  bb12 = bb1 + bb2;
  bb3 = t3.bbox();

  if (bb12.ymax()<bb3.ymin()) {
     cout << "Triangle 3:\n" << t3 << endl;
     cout << "lies above triangle 1:\n" << t1 << endl;
     cout << "and triangle 2:\n" << t2 << endl;
  }
}
