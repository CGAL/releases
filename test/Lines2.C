
#include <stream.h>
#include <CGAL/Double_eps.h>
#include <CGAL/Rational.h>
#include <CGAL/Integer.h>

typedef FIELDTYPE fieldtype;
typedef RINGTYPE  ringtype;


#ifdef CARTESIAN
#include <CGAL/cartesian.h>
#else
#include <CGAL/homogeneous.h>
#endif // CARTESIAN


#ifdef CGAL_REPCLASS

#include <CGAL/Line_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Ray_2.h>
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

#include <CGAL/LineC2.h>
#include <CGAL/IO/ostreamC2.h>
typedef CGAL_LineC2<fieldtype> Line;
typedef CGAL_RayC2<fieldtype> Ray;
typedef CGAL_SegmentC2<fieldtype> Segment;

typedef CGAL_PointC2<fieldtype> Point;
typedef CGAL_VectorC2<fieldtype> Vector;
typedef CGAL_DirectionC2<fieldtype> Direction;

#endif


void Lines()
{


  cout << "Testing Line_2<R> ... " << flush;
  ringtype x1 = 1,
           y1 = 2,
           x2 = 3,
           y2 = 4;

  Point p1(x1,y1), p2(x2,y2);
  Line l, lp(p1,p2), lprev(p2,p1), lpcopy(lp);
  Segment s(p1,p2); 

  Line ls(s);
  Ray r(p1,p2);
  Line lr(r);
  Direction d(p2-p1);
  Line lp1d(p1,d);
  l = lp;

  cout << endl <<  lp1d << endl;
  assert( lp == lpcopy );
  assert( lp.identical(lpcopy) );
  assert( lp != lprev );

  assert( !lp.identical(lprev) );
  assert( lp == lprev.opposite() );
  assert( lp == lp.opposite().opposite() );
  assert( lp.direction() == - lp.opposite().direction() );
  assert( ls == lp );
  assert( ls == lr );
  assert( ls == lp1d );

  assert( lp == Line(lp.a(), lp.b(), lp.c()) );
  assert( lp == Line(lp.point(), lp.direction()) );
  assert( y1 == lp.y_at_x(x1) && y2 == lp.y_at_x(x2) );
  assert( x1 == lp.x_at_y(y1) && x2 == lp.x_at_y(y2) );

  Direction dx(Vector(1,0)), dy(Vector(0,1));

  assert( !lp.is_horizontal() );

  assert(  !lp.is_vertical() );
  assert(  !lp.is_degenerate() );

  Line lhor(p1,dx), lver(p1,dy);
  assert( lhor.is_horizontal()  && lver.is_vertical() );

  assert( lhor.projection(p2) == Point(p2.hx() * p1.hw(), 
				       p1.hy() * p2.hw(),
				       p1.hw() * p2.hw()) );
  assert( lver.projection(p2) == Point(p1.hx() * p2.hw(),
				       p2.hy() * p1.hw(),
				       p1.hw() * p2.hw()) );

  assert( Point(0,1) == lp.projection(Point(1,0)) );
  assert( lp.is_on(Point(-1,0)) );
  assert( lp.projection(Point(-1,0)) == Point(-1,0) );
  assert( !lp.is_on(Point(1,0)) );
  assert( lp.perpendicular(Point(3,1)).perpendicular(Point(0,1)) == lp.opposite() );
  assert( lp.perpendicular(Point(-1,0)).perpendicular(Point(-1,0)) == lp.opposite() );

  cout << "... done" << endl;
}


#ifdef MAIN

int main()
{
  Lines();

  return 1;
}
#endif
