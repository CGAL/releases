
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


#ifdef CGAL_REPCLASS
#include <CGAL/Segment_2.h>
#include <CGAL/IO/ostream_2.h>

#ifdef CARTESIAN
typedef C<fieldtype> reptype;
#else
typedef H<fieldtype, ringtype> reptype;
#endif // CARTESIAN

typedef CGAL_Segment_2<reptype> Segment;
typedef CGAL_Line_2<reptype> Line;
typedef CGAL_Ray_2<reptype> Ray;

typedef CGAL_Point_2<reptype> Point;
typedef CGAL_Vector_2<reptype> Vector;
typedef CGAL_Direction_2<reptype> Direction;

#else

#include <CGAL/SegmentC2.h>
#include <CGAL/IO/ostreamC2.h>
typedef CGAL_SegmentC2<fieldtype> Segment;
typedef CGAL_LineC2<fieldtype> Line;
typedef CGAL_RayC2<fieldtype> Ray;

typedef CGAL_PointC2<fieldtype> Point;
typedef CGAL_VectorC2<fieldtype> Vector;
typedef CGAL_DirectionC2<fieldtype> Direction;

#endif

#include <stream.h>


typedef CGAL_Bbox_2 Bbox;


void Segments()
{  
  cout << "Testing CGAL_Segment_2<R> ... " << flush;
  ringtype x1 = 1,
           y1 = 2,
           x2 = 3,
           y2 = 4;

  Point p1(x1,y1), p2(x2,y2);
  Segment s(p1,p2);

  Segment scoord(p1,p2), sc, scopy(s);

  {
  Segment(p1,p2) ;
  }

  
  sc = s;
  assert( s.identical(sc) );
  assert( s.identical(scopy) );


  {
    Point p(-1, -1), q(-1, 2), r(3,2);
    Segment s(p,q);
    assert( p == s.min()  && q == s.max() );

    s = Segment(p,r);
    assert( p == s.min()  && r == s.max() );
      
    s = Segment(q,r);
    assert( q == s.min()  && r == s.max() );
  }
  cout << s.min() << s.max() << endl;
  assert( s == sc );
  assert( s == scoord );
  assert( s.start() == p1 );
  assert( s.end() == p2 );
  assert( s.opposite().start() == p2 );
  assert( s.opposite().end() == p1 );
  assert( s.vertex(0) == s.start() );
  assert( s.vertex(1) == s.end() );
  assert( s.direction() == Direction(p2-p1) );
  assert( s.supporting_line() == Line(p1,p2) );
 
  Segment shor(p1, p1 + Vector(1,0)), sver(p1, p1 + Vector(0,1));

  cout << shor << endl;
  assert( shor.is_horizontal() && ! shor.is_vertical() ); 
  assert( !sver.is_horizontal() && sver.is_vertical() );
  assert( !shor.is_degenerate()  && !sver.is_degenerate() );

  assert( s.is_on(Point(2,3)) && s.is_on(p1) && s.is_on(p2) );
  assert( ! s.is_on(CGAL_ORIGIN) );
  assert( s.squared_length() == 8 );

  Bbox b = s.bbox();

#ifdef CARTESIAN
  //....... GJ

  Segment gj1(Point(0,0), Point(10.356729, 0.9826715381));
  Segment gj2(Point(1.0, 0.3782089176), Point(7.625 , 8.37361));
  //....... GJ

  Point gjp(0.745203, 0.0707067);

  if (  gj1.is_on(gjp) ) {  // FAILS with collinear_is_on() !!!
    cout << "is on" ;
  } else {
    cout << "is not on" ;
  }


  if (  gj2.is_on(gjp) ) {  // FAILS with collinear_is_on() !!!
    cout << "is on" ;
  } else {
    cout << "is not on" ;
  }

#endif // CARTESIAN


  cout << " done" << endl;
}

#ifdef MAIN

int main()
{
  Segments();

  return 1;
}
#endif // MAIN
