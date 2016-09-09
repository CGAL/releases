
#include <CGAL/basic.h>

#include <iostream.h>
#include <CGAL/Double_eps.h>
#include <CGAL/Rational.h>
#include <CGAL/Integer.h>


typedef CGAL_Double_eps fieldtype;
typedef CGAL_Double_eps  ringtype;


#ifdef CARTESIAN
#include <CGAL/Cartesian.h>
#else
#include <CGAL/Homogeneous.h>
#endif // CARTESIAN



#include <CGAL/Triangle_2.h>

#ifdef CARTESIAN
typedef CGAL_Cartesian<fieldtype> reptype;
#else
typedef CGAL_Homogeneous<ringtype> reptype;
#endif // CARTESIAN

typedef CGAL_Triangle_2<reptype>  Triangle;

typedef CGAL_Point_2<reptype>     Point;
typedef CGAL_Vector_2<reptype>    Vector;
typedef CGAL_Direction_2<reptype> Direction;

void Triangles()
{
  cout << "Testing CGAL_Triangle_2<R> ... " << flush;
  Point p0(CGAL_ORIGIN), p1(0,1), p2(1,0);

  Triangle t, tclock(p0,p1,p2), tcycl(p1,p2,p0), tcycl2(p2,p0,p1), tanti(p1,p0,p2);
  
  t = tclock;
  assert( identical(t, tclock) );
  assert( t == t );
  assert( t == tcycl  );
  assert( t == tcycl2 );
  assert( tcycl == tcycl2 );
  assert( t != tanti );

  assert( t.vertex(0) == p0 &&  t.vertex(1) == p1 &&  t.vertex(2) == p2 );
  assert( t.vertex(3) == p0 );
  assert( t[3] == p0 );
  
  assert( t.has_on_boundary(Point(1, 1, 2)) );
  assert( t.has_on_boundary(p0) );
  assert( t.has_on_boundary(p1) );

  assert( t.has_on_bounded_side(Point(1, 1, 5)) );
  assert( !t.has_on_bounded_side(Point(-1, 1, 5)) );
  
  assert( t.opposite().has_on_bounded_side(Point(1, 1, 5)) );
  assert( ! t.opposite().has_on_bounded_side(Point(-1, 1, 5)) );

  assert( t.has_on_negative_side(Point(1, 1, 5)) );
  assert( ! t.opposite().has_on_negative_side(Point(1, 1, 5)) );

  assert( t.has_on_positive_side(Point(-1, 1, 5)) );
  assert( !t.opposite().has_on_positive_side(Point(-1, 1, 5)) );
  
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
