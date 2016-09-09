
#include <CGAL/Cartesian.h>

#include <iostream.h>
#include <CGAL/Double_eps.h>
#include <CGAL/Rational.h>

// the fieldtype should come from outside
typedef FIELDTYPE fieldtype;

#include <CGAL/Segment_3.h>
#include <CGAL/IO/ostream_3.h>

typedef CGAL_Segment_3< CGAL_Cartesian<fieldtype> >   Segment;
typedef CGAL_Line_3< CGAL_Cartesian<fieldtype> >      Line;
typedef CGAL_Ray_3< CGAL_Cartesian<fieldtype> >       Ray;

typedef CGAL_Point_3< CGAL_Cartesian<fieldtype> >     Point;
typedef CGAL_Vector_3< CGAL_Cartesian<fieldtype> >    Vector;
typedef CGAL_Direction_3< CGAL_Cartesian<fieldtype> > Direction;


void Segments3()
{  
  cout << "Testing CGAL_Segment_3<R> ... " << flush;
  fieldtype x1 = -1.0,
            y1 = -1.0,
            z1 = -1.0,
            x2 = 4.0,
            y2 = 4.0,
            z2 = 4.0;

  Point p1(x1,y1,z1), p2(x2,y2,z2);
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
 
  assert( !s.is_degenerate() );

  assert( s.has_on(p1+(p2-p1)/2) );
  assert( s.has_on(p1) );
  assert( s.has_on(p2) );
  assert( s.collinear_has_on(CGAL_ORIGIN) );
  assert( !s.has_on(Point(1,2,3)) );
  assert( s.squared_length() == 75);

  cout << " done" << endl;
}

#ifdef MAIN

int main()
{
  Segments3();

  return 1;
}
#endif


