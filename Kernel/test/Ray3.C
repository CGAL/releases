
#include <CGAL/Cartesian.h>

#include <iostream.h>
#include <CGAL/Double_eps.h>
#include <CGAL/Rational.h>

// the fieldtype should come from outside
typedef FIELDTYPE fieldtype;

#include <CGAL/Ray_3.h>
typedef CGAL_Segment_3< CGAL_Cartesian<fieldtype> > Segment;
typedef CGAL_Line_3< CGAL_Cartesian<fieldtype> > Line;
typedef CGAL_Ray_3< CGAL_Cartesian<fieldtype> > Ray;

typedef CGAL_Point_3< CGAL_Cartesian<fieldtype> > Point;
typedef CGAL_Vector_3< CGAL_Cartesian<fieldtype> > Vector;
typedef CGAL_Direction_3< CGAL_Cartesian<fieldtype> > Direction;


void Rays3()
{  
  cout << "Testing CGAL_Ray_3<R> ... " << flush;
  fieldtype x1 = -1,
            y1 = -1,
            z1 = -1,
            x2 = 4,
            y2 = 4,
            z2 = 4;

  Point p1(x1,y1,z1), p2(x2,y2,z2);
  Direction d((p2-p1) * 3);
  Ray r(p1,p2), ropp(p1, Direction(p1-p2)), rcopy(r), rp1d(p1,d);
  
  assert( r == rcopy );
  assert( identical(r, rcopy) );
  assert( !identical(r, ropp) );
  assert( ropp == r.opposite() );

  Direction dx(Vector(1,0,0)), dy(Vector(0,1,0));

  assert( Line(r) == r.supporting_line() );
  assert( Line(r).has_on(r.source()) );
  assert( Line(r).has_on(r.second_point()) );
  assert( Line(r).has_on(r.source() + r.direction().vector()) );
  assert( Line(r).has_on(r.source() - r.direction().vector()) );

  assert( r.has_on(r.source()) );
  assert( r.has_on(r.second_point()) );
  assert( r.has_on(r.source() + r.direction().vector()) );
  assert( r.collinear_has_on(r.source() + r.direction().vector()) );
  assert( !r.has_on(r.source() - r.direction().vector()) );
  
  assert( !r.is_degenerate() );
  cout << " done" << endl;
}

#ifdef MAIN

int main()
{
  Rays3();

  return 1;
}
#endif
