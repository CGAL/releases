

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

#include <CGAL/Ray_2.h>
#include <CGAL/Aff_transformation_2.h>
#include <CGAL/IO/ostream_2.h>

#ifdef CARTESIAN
typedef C<fieldtype> reptype;
#else
typedef H<fieldtype, ringtype> reptype;
#endif // CARTESIAN

typedef CGAL_Line_2<reptype> Line;
typedef CGAL_Ray_2<reptype> Ray;

typedef CGAL_Point_2<reptype> Point;
typedef CGAL_Vector_2<reptype> Vector;
typedef CGAL_Direction_2<reptype> Direction;

#else

#include <CGAL/RayC2.h>
#include <CGAL/IO/ostreamC2.h>
typedef CGAL_LineC2<fieldtype> Line;
typedef CGAL_RayC2<fieldtype> Ray;

typedef CGAL_PointC2<fieldtype> Point;
typedef CGAL_VectorC2<fieldtype> Vector;
typedef CGAL_DirectionC2<fieldtype> Direction;

#endif


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
  assert( r.identical(rcopy) );
  assert( !r.identical(ropp) );
  assert( ropp == r.opposite() );

  Direction dx(Vector(1,0)), dy(Vector(0,1));

  Ray rhor(p1,dx), rver(p1,dy);
  assert( !r.is_horizontal() && !r.is_vertical() );
  assert( rhor.is_horizontal()  && rver.is_vertical() );

  assert( Line(r) == r.supporting_line() );
  assert( Line(r).is_on(r.start()) );
  assert( Line(r).is_on(r.second_point()) );
  assert( Line(r).is_on(r.start() + r.direction().vector()) );
  assert( Line(r).is_on(r.start() - r.direction().vector()) );

  assert( r.is_on(r.start()) );
  assert( r.is_on(r.second_point()) );
  assert( r.is_on(r.start() + r.direction().vector()) );
  assert( r.collinear_is_on(r.start() + r.direction().vector()) );
  assert( !r.is_on(r.start() - r.direction().vector()) );


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
