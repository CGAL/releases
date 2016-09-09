
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
#include <CGAL/Triangle_2.h>

#ifdef CARTESIAN
typedef C<fieldtype> reptype;
#else
typedef H<fieldtype, ringtype> reptype;
#endif // CARTESIAN

typedef CGAL_Triangle_2<reptype>  Triangle;

typedef CGAL_Point_2<reptype>     Point;
typedef CGAL_Vector_2<reptype>    Vector;
typedef CGAL_Direction_2<reptype> Direction;

#else

#include <CGAL/TriangleC2.h>
typedef CGAL_TriangleC2<fieldtype>  Triangle;

typedef CGAL_PointC2<fieldtype>     Point;
typedef CGAL_VectorC2<fieldtype>    Vector;
typedef CGAL_DirectionC2<fieldtype> Direction;

#endif // CGAL_REPCLASS

void Triangles()
{
  cout << "Testing CGAL_Triangle_2<R> ... " << flush;
  Point p0(CGAL_ORIGIN), p1(0,1), p2(1,0);

  Triangle t, tclock(p0,p1,p2), tcycl(p1,p2,p0), tcycl2(p2,p0,p1), tanti(p1,p0,p2);
  
  t = tclock;
  assert( t.identical(tclock) );
  assert( t == t );
  assert( t == tcycl  );
  assert( t == tcycl2 );
  assert( tcycl == tcycl2 );
  assert( t != tanti );

  assert( t.vertex(0) == p0 &&  t.vertex(1) == p1 &&  t.vertex(2) == p2 );
  assert( t.vertex(3) == p0 );
  assert( t[3] == p0 );
  
  assert( t.is_on(Point(1, 1, 2)) );
  assert( t.is_on(p0) );
  assert( t.is_on(p1) );

  assert( t.is_in_bounded_region(Point(1, 1, 5)) );
  assert( !t.is_in_bounded_region(Point(-1, 1, 5)) );
  
  assert( t.is_outside(Point(1, 1, 5)) );
  assert( ! t.opposite().is_outside(Point(1, 1, 5)) );

  assert( ! t.is_inside(Point(1, 1, 5)) );
  assert( t.opposite().is_inside(Point(1, 1, 5)) );

  assert( t.is_inside(Point(-1, 1, 5)) );
  assert( !t.opposite().is_inside(Point(-1, 1, 5)) );
  
  assert( !t.is_degenerate() ); 

  cout << "... done" << endl; 
}

#ifdef MAIN

int main()
{
  Triangles();

  return 1;
}
#endif // MAIN
