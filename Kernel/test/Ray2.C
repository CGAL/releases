
#include <CGAL/basic.h>

#include <iostream.h>
#include <CGAL/Double_eps.h>
#include <CGAL/Rational.h>
#include <CGAL/Integer.h>


typedef CGAL_Double_eps fieldtype;
typedef CGAL_Double_eps ringtype;


#ifdef CARTESIAN
#include <CGAL/Cartesian.h>
#else
#include <CGAL/Homogeneous.h>
#endif // CARTESIAN


#include <CGAL/Ray_2.h>
#include <CGAL/Aff_transformation_2.h>
#include <CGAL/IO/ostream_2.h>

#ifdef CARTESIAN
typedef CGAL_Cartesian<fieldtype> reptype;
#else
typedef CGAL_Homogeneous<ringtype> reptype;
#endif // CARTESIAN

typedef CGAL_Line_2<reptype> Line;
typedef CGAL_Ray_2<reptype> Ray;

typedef CGAL_Point_2<reptype> Point;
typedef CGAL_Vector_2<reptype> Vector;
typedef CGAL_Direction_2<reptype> Direction;


void Rays()
{  
  cout << "Testing CGAL_Ray_2<R> ... " << flush;
  ringtype x1 = 1,
           y1 = 2,
           x2 = 3,
           y2 = 4;

  Point p1(x1,y1), p2(x2,y2);
  Direction d(p2-p1);
  Ray r(p1,p2), ropp(p1, Direction(p1-p2)), rcopy(r), rp1d(p1,d);
  
  assert( r == rcopy );
  assert( identical(r, rcopy) );
  assert( !identical(r, ropp) );
  assert( ropp == r.opposite() );

  Direction dx(Vector(1,0)), dy(Vector(0,1));

  Ray rhor(p1,dx), rver(p1,dy);
  assert( !r.is_horizontal() && !r.is_vertical() );
  assert( rhor.is_horizontal()  && rver.is_vertical() );

  assert( Line(r) == r.supporting_line() );
  assert( Line(r).has_on_boundary(r.source()) );
  assert( Line(r).has_on_boundary(r.second_point()) );
  assert( Line(r).has_on_boundary(r.source() + r.direction().vector()) );
  assert( Line(r).has_on_boundary(r.source() - r.direction().vector()) );

  assert( r.has_on(r.source()) );
  assert( r.has_on(r.second_point()) );
  assert( r.has_on(r.source() + r.direction().vector()) );
  assert( r.collinear_has_on(r.source() + r.direction().vector()) );
  assert( !r.has_on(r.source() - r.direction().vector()) );


  CGAL_Aff_transformation_2<reptype> rotate(CGAL_ROTATION,
					    Direction(0, 1), 
					    1);


  cout << r << endl;
  cout << r.transform(rotate) << endl;
  assert( !r.is_degenerate() );
  cout << " done" << endl;
}

#ifdef MAIN

int main()
{
  Rays();

  return 1;
}
#endif // MAIN
