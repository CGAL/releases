
#include <CGAL/Cartesian.h>

#include <iostream.h>

#include <CGAL/Double_eps.h>
#include <CGAL/Rational.h>

// the fieldtype should come from outside
typedef CGAL_Double_eps fieldtype;

#include <CGAL/Direction_3.h>
#include <CGAL/Line_3.h>
#include <CGAL/IO/ostream_3.h>

typedef CGAL_Segment_3< CGAL_Cartesian<fieldtype> >   Segment;
typedef CGAL_Line_3< CGAL_Cartesian<fieldtype> >      Line;
typedef CGAL_Ray_3< CGAL_Cartesian<fieldtype> >       Ray;

typedef CGAL_Point_3< CGAL_Cartesian<fieldtype> >     Point;
typedef CGAL_Vector_3< CGAL_Cartesian<fieldtype> >    Vector;
typedef CGAL_Direction_3< CGAL_Cartesian<fieldtype> > Direction;

void Lines3()
{
  CGAL_set_eps(0.00001);
  cout << "Testing CGAL_Line_3<R> ... " << flush;
  fieldtype x1 = -1.0,
            y1 = -1.0,
            z1 = -1.0,
            x2 = 4.0,
            y2 = 4.0,
            z2 = 4.0;
  fieldtype scalar(3.0);
  
  Point p1(x1,y1,z1), p2(x2,y2,z2);
  Vector v((p2-p1) * scalar);

  Line l, lp(p1,p2), lprev(p2,p1), lpcopy(lp);
  Segment s(p1,p2); 
  Line ls(p1,p2);
  Ray r(p1,p2);
  Line lr(r);
  
  CGAL_Direction_3< CGAL_Cartesian<fieldtype> > d(v);
  Line lp1d(p1,d);
  l = lp;


  assert( lp == lpcopy );
  assert( identical(lp, lpcopy) );

  assert( ls == lp1d );
  assert( ls == lp );
  assert( ls == lr );

  assert( !identical(lp, lprev) );
  assert( lp == lprev.opposite() );
  

  Direction dx(Vector(1,0,0)), dy(Vector(0,1,0));

  assert(  !lp.is_degenerate() );

  Line lhor(p1,dx), lver(p1,dy);


  assert( lhor.has_on(Point(p2.x(), p1.y(), p1.z())) );
  assert( lhor.projection(p2) == Point(p2.x(), p1.y(), p1.z()) );
  assert( lver.projection(p2) == Point(p1.x(), p2.y(), p1.z()) );

  Point p = Point(1,-1,-1),
        proj = lp.projection(p);
  
  //  assert( (((proj-p) * lp.direction().vector()) == 0.0) );

  assert( lp.has_on(proj) );
  p = Point(34.5, 234.6878, -4567.67);
  proj = lp.projection(p);
  assert( (((proj-p) * lp.direction().vector()) == fieldtype(0)) &&
	  lp.has_on(proj) );
 
  assert( Point(CGAL_ORIGIN) == lp.projection(CGAL_ORIGIN) );
  assert( lp.has_on(Point(0.5, 0.5, 0.5)) );
  assert( lp.projection(p1) == p1 );
  assert( !lp.has_on(Point(1,0,1) ) );
  assert( lp.perpendicular_plane(p1).perpendicular_line(p1) == lp );

  Point pp(-100,-100,-100);
  assert( lp.perpendicular_plane(pp).perpendicular_line(Point(0.1, 0.1, 0.1)) == lp );

  cout << endl << lp << endl;
  cout << "...  done" << endl;
}

#ifdef MAIN

int main()
{
  Lines3();

  return 1;
}
#endif

