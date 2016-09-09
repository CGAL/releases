#include <CGAL/basic.h>

#include <iostream.h>
#include <CGAL/Double_eps.h>
#include <CGAL/Rational.h>
#include <CGAL/Integer.h>
#include <CGAL/Object.h>


// the fieldtype should come from outside
typedef FIELDTYPE fieldtype;
typedef RINGTYPE  ringtype;

#ifdef CARTESIAN
#include <CGAL/Cartesian.h>
typedef CGAL_Cartesian<double> Rcart;
#else
#include <CGAL/Homogeneous.h>
#endif // CARTESIAN


#include <CGAL/Segment_2.h>
#include <CGAL/Line_2.h>



#include <CGAL/intersection_2_1.h>
#include <CGAL/IO/ostream_2.h>

#ifdef CARTESIAN
typedef CGAL_Cartesian<fieldtype> reptype;
#else
typedef CGAL_Homogeneous<ringtype> reptype;
#endif // CARTESIAN

typedef CGAL_Point_2<reptype>   Point;
typedef CGAL_Segment_2<reptype> Segment;
typedef CGAL_Line_2<reptype>    Line;
typedef CGAL_Bbox_2             Bbox;



void SegmentSegment(const Segment &s1, const Segment &s2)
{
  Point p;
  Segment s;

  cout << "intersection(" << s1 <<  "," << endl;
  cout << "            (" << s2 << " )" << endl;

  CGAL_Object o = CGAL_intersection(s1, s2);

  if (CGAL_assign(p, o)){
    cout << " point intersection " ;
    assert( s1.has_on(p) && s2.has_on(p) );
    cout << p;
  } else if (CGAL_assign(s, o)){
    cout << " segment intersection " ;
    assert( s1.has_on(s.source()) && s1.has_on(s.target()) );
    assert( s2.has_on(s.source()) && s2.has_on(s.target()) );
    cout << s;
  } else {
    cout << " no intersection " ;
  } 
  cout << endl << endl;
}


void LineLine(const Line &l1, const Line &l2)
{
  Point p;
  Segment l;

  cout << "intersection(" << l1 <<  "," << endl;
  cout << "            (" << l2 << " )" << endl;

  CGAL_Object o = CGAL_intersection(l1, l2);

  if (CGAL_assign(p, o)){
    cout << " point intersection " ;
    assert( l1.has_on(p) && l2.has_on(p) );
    cout << p;
  } else if (CGAL_assign(l, o)){
    cout << " line intersection " ;
    assert( ( l1 == l2) || ( l1.opposite() == l2) );
    cout << l;
  } else {
    cout << " no intersection " ;
  } 
  cout << endl << endl;
}


void LineSegment(const Line &l1, const Segment &s2)
{
  //  cout << l1 << s2 << endl;

  Point p;
  Segment s;

  cout << "intersection(" << l1 <<  "," << endl;
  cout << "            (" << s2 << " )" << endl;

  CGAL_Object o = CGAL_intersection(l1, s2);

  if (CGAL_assign(p, o)){
    cout << " point intersection " ;
    assert( l1.has_on(p) && s2.has_on(p) );
    cout << p;
  } else if (CGAL_assign(s, o)){
    cout << " segment intersection " ;    
    assert( l1.has_on(s.source()) && l1.has_on(s.target()) );
    assert( s2.has_on(s.source()) && s2.has_on(s.target()) );
    cout << s;
  } else {
    cout << " no intersection " ;
  } 

  cout << endl << endl;

}

void Intersections()
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
      SegmentSegment(segments[i], segments[j]);
      LineSegment(segments[i].supporting_line(), segments[j].opposite());
      LineLine(segments[i].supporting_line(), segments[j].supporting_line());
    }
  }
  cout << " done" << endl;
}

#ifdef MAIN

int main()
{
  Intersections();

  return 1;
}
#endif // MAIN
