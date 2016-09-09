#include <stream.h>
#include <CGAL/Double_eps.h>
#include <CGAL/Rational.h>
#include <CGAL/Integer.h>

// the fieldtype should come from outside
typedef FIELDTYPE fieldtype;
typedef RINGTYPE  ringtype;

#ifdef CARTESIAN
#include <CGAL/cartesian.h>
#else
#include <CGAL/homogeneous.h>
#endif // CARTESIAN


#include <CGAL/Segment_2.h>
#include <CGAL/Line_2.h>
#include <CGAL/IO/ostream_2.h>
#include <CGAL/intersection_2_1.h>

#ifdef CARTESIAN
typedef C<fieldtype> reptype;
#else
typedef H<fieldtype, ringtype> reptype;
#endif // CARTESIAN

typedef CGAL_Point_2<reptype>   Point;
typedef CGAL_Segment_2<reptype> Segment;
typedef CGAL_Line_2<reptype>    Line;
typedef CGAL_Bbox_2                    Bbox;
typedef CGAL_Line_2_Segment_2_pair<reptype> Line_Segment_pair;
typedef CGAL_Segment_2_Segment_2_pair<reptype> Segment_Segment_pair;



void fct(const Segment &s1, const Segment &s2)
{
  Point p;
  Segment s;
  Segment_Segment_pair pair(&s1, &s2);

  cout << "intersection(" << s1 <<  "," << endl;
  cout << "            (" << s2 << " )" << endl;


  switch (pair.intersection_type()){
  case Segment_Segment_pair::NO : 
    cout << " no intersection " ;
    break;
    case Segment_Segment_pair::POINT :
    cout << " point intersection " ;
    pair.intersection(p);
    cout << p;
    break;
  case Segment_Segment_pair::SEGMENT :
    cout << " segment intersection " ;
    pair.intersection(s);
    cout << s;
    break;
  }
  cout << endl << endl;
}

void LineSegment(const Line &l1, const Segment &s2)
{
  Point p;
  Segment s;
  Line_Segment_pair pair(&l1, &s2);

  cout << "intersection(" << l1 <<  "," << endl;
  cout << "            (" << s2 << " )" << endl;

  switch (pair.intersection_type()){
  case Line_Segment_pair::NO : 
    cout << " no intersection " ;
    break;
    case Line_Segment_pair::POINT :
    cout << " point intersection " ;
    pair.intersection(p);
    cout << p;
    break;
  case Line_Segment_pair::SEGMENT :
    cout << " segment intersection " ;
    pair.intersection(s);
    cout << s;
    break;
  }
  cout << endl << endl;
}

void intersections()
{  
  cout << "Testing intersections ... " << endl;
  
  Point p, 
  p1(1, 1), 
  p2(4, 1),  
  p3(1, 4), 
  p4(2, 2), 
  p5(2, 0), 
  p6(2, -1), 
  p7(2, 3);

  Segment segments[4];

  segments[1] = Segment(p1,p2);
  segments[2] = Segment(p2,p3);
  segments[3] = Segment(p4, p5);

  for(int i = 1; i <=3; i++){
    for(int j=1; j<=3; j++){
      fct(segments[i], segments[j]);
      LineSegment(segments[i].supporting_line(), segments[j].opposite());
    }
  }
  cout << " done" << endl;
}

#ifdef MAIN

int main()
{
  intersections();

  return 1;
}
#endif // MAIN
