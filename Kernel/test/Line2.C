
#include <CGAL/basic.h>

#include <iostream.h>
#include <CGAL/Double_eps.h>
#include <CGAL/Rational.h>
#include <CGAL/Integer.h>


typedef CGAL_Double_eps  fieldtype;
typedef CGAL_Double_eps  ringtype;


#ifdef CARTESIAN
#include <CGAL/Cartesian.h>
#else
#include <CGAL/Homogeneous.h>
#endif // CARTESIAN


#include <CGAL/Line_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Ray_2.h>
#include <CGAL/IO/ostream_2.h>

#ifdef CARTESIAN
typedef CGAL_Cartesian<fieldtype> reptype;
#else
typedef CGAL_Homogeneous<ringtype> reptype;
#endif // CARTESIAN

typedef CGAL_Segment_2<reptype> Segment;
typedef CGAL_Line_2<reptype> Line;
typedef CGAL_Ray_2<reptype> Ray;

typedef CGAL_Point_2<reptype> Point;
typedef CGAL_Vector_2<reptype> Vector;
typedef CGAL_Direction_2<reptype> Direction;


void Lines()
{

  cout << "Testing Line_2<R> ... " << flush;
  ringtype x1 = 1,
           y1 = 2,
           x2 = 3,
           y2 = 4;

  Point p1(x1,y1), p2(x2,y2);

  Line l, lp(p1,p2), lprev(p2,p1), lpcopy(lp);
  Line l2p (Point(ringtype(1),ringtype(2)), Point(y1,x1));

  Line l3p = l2p;

  Segment s(p1,p2); 

  Line ls(s);
  Ray r(p1,p2);
  Line lr(r);
  Direction d(p2-p1);
  Line lp1d(p1,d);
  l = lp;

  cout << endl <<  lp1d << endl;
  assert( lp == lpcopy );
  assert( identical(lp, lpcopy) );
  assert( lp != lprev );

  assert( !identical(lp, lprev) );
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
  assert( lp.has_on_boundary(Point(-1,0)) );
  assert( lp.projection(Point(-1,0)) == Point(-1,0) );
  assert( !lp.has_on_boundary(Point(1,0)) );
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
