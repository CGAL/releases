#include <stream.h>
#include <CGAL/Ray_2.h>

typedef CGAL_Segment_2< C<double> > Segment;
typedef CGAL_Line_2< C<double> > Line;
typedef CGAL_Ray_2< C<double> > Ray;

typedef CGAL_Point_2< C<double> > Point;
typedef CGAL_Vector_2< C<double> > Vector;
typedef CGAL_Direction_2< C<double> > Direction;

typedef CGAL_Bbox_2 Bbox;


int main()
{  
  cout << "Testing CGAL_Segment_2<R> ... " << flush;
  double x1 = 1.0,
         y1 = 2.0,
         x2 = 3.0,
         y2 = 4.0;

  Point p1(x1,y1), p2(x2,y2);
  Segment s(p1,p2);

  Segment scoord(p1,p2), sc, scopy(s);

  {
  Segment(p1,p2) ;
  }

  
  sc = s;
  assert( s.identical(sc) );
  assert( s.identical(scopy) );


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

  assert( shor.is_horizontal() && ! shor.is_vertical() ); 
  assert( !sver.is_horizontal() && sver.is_vertical() );
  assert( !shor.is_degenerate()  && !sver.is_degenerate() );

  assert( s.is_on(Point(2,3)) && s.is_on(p1) && s.is_on(p2) );
  assert( ! s.is_on(CGAL_ORIGIN) );
  assert( s.squared_length() == 8 );

  Bbox b = s.bbox();

  cout << " done" << endl;

  return 1;
}


