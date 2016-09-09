
#include <CGAL/Cartesian.h>
#include <iostream.h>

#include <CGAL/Point_2.h>
#include <CGAL/Ray_2.h>
#include <CGAL/Line_2.h>
#include <CGAL/Iso_rectangle_2.h>

typedef CGAL_Segment_2< CGAL_Cartesian<double> > Segment;
typedef CGAL_Line_2< CGAL_Cartesian<double> > Line;
typedef CGAL_Ray_2< CGAL_Cartesian<double> > Ray;
typedef CGAL_Iso_rectangle_2< CGAL_Cartesian<double> > Iso_rectangle;


typedef CGAL_Vector_2< CGAL_Cartesian<double> > Vector;
typedef CGAL_Direction_2< CGAL_Cartesian<double> > Direction;

typedef CGAL_Bbox_2 Bbox;


typedef CGAL_Point_2< CGAL_Cartesian<double> > Point;

int main()
{  
  cout << "Testing CGAL_Segment_2<R> ... " << flush;
  double x1 = 1.0,
         y1 = 2.0,
         x2 = 3.0,
         y2 = 4.0;




  Point p1(x1,y1), p2(x2,y2), p3(20.0, 40.0);

  Segment s(p1,p2);
  
  Segment scoord(p1,p2), sc, scopy(s);
  
  sc = s;
  assert( identical(s, sc) );
  assert( identical(s, scopy) );

  assert( s == sc );
  assert( s == scoord );
  assert( s.source() == p1 );
  assert( s.target() == p2 );
  assert( s.opposite().source() == p2 );
  assert( s.opposite().target() == p1 );
  assert( s.vertex(0) == s.source() );
  assert( s.vertex(1) == s.target() );
  assert( s.direction() == Direction(p2-p1) );
  assert( s.supporting_line() == Line(p1,p2) );
 
  Segment shor(p1, p1 + Vector(1,0)), sver(p1, p1 + Vector(0,1));

  assert( shor.is_horizontal() && ! shor.is_vertical() ); 
  assert( !sver.is_horizontal() && sver.is_vertical() );
  assert( !shor.is_degenerate()  && !sver.is_degenerate() );

  assert( s.has_on(Point(2,3)) && s.has_on(p1) && s.has_on(p2) );
  assert( ! s.has_on(CGAL_ORIGIN) );
  assert( s.squared_length() == 8 );

  Bbox b = s.bbox();

  cout << " done" << endl;

  return 1;
}


