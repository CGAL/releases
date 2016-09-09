#include "tutorial.h"
#include <CGAL/Point_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Bbox_2.h>

main()
{
  Triangle t1(Point(-5.2,1.7), Point(-7.1,-6.3), Point(-0.9,-2.3));
  Triangle t2(Point(-2.8,-4.5), Point(4.5,-1.1), Point(2.4,-7.6));
  Triangle t3(Point(5.5,8.8), Point(-7.7,8.3), Point(1.3,2.9));

  Bbox bb1 = t1.bbox();
  Bbox bb2 = t2.bbox();
  Bbox bb12, bb3;

  cout << "Bounding box 1: " << bb1 << "\n and bounding box 2: "<< bb2 << endl;
  if ( !CGAL::do_overlap(bb1, bb2) )
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
