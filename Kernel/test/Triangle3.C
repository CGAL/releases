
#include <CGAL/Cartesian.h>

#include <iostream.h>
#include <CGAL/Double_eps.h>
#include <CGAL/Rational.h>

// the fieldtype should come from outside
typedef FIELDTYPE fieldtype;

#include <CGAL/Triangle_3.h>
#include <CGAL/IO/ostream_3.h>
typedef CGAL_Triangle_3< CGAL_Cartesian<fieldtype> >   Triangle;

typedef CGAL_Point_3< CGAL_Cartesian<fieldtype> >      Point;
typedef CGAL_Vector_3< CGAL_Cartesian<fieldtype> >     Vector;
typedef CGAL_Direction_3< CGAL_Cartesian<fieldtype> >  Direction;

void Triangles3()
{
  cout << "Testing CGAL_Triangle_3<R> ... " << flush;
  Point p0(1,0,0), p1(0,1,0), p2(0,0,1);

  Triangle t, tclock(p0,p1,p2), tcycl(p1,p2,p0), tcycl2(p2,p0,p1), tanti(p1,p0,p2);
  
  t = tclock;

  cout << endl << t << endl;
  assert( identical(t, tclock) );
  assert( t == t );
  assert( t == tcycl  );
  assert( t == tcycl2 );
  assert( tcycl == tcycl2 );
  assert( t != tanti );

  assert( t.vertex(0) == p0 &&  t.vertex(1) == p1 &&  t.vertex(2) == p2 );
  assert( t.vertex(3) == p0 );
  assert( t[3] == p0 );
  
  assert( t.has_on(CGAL_ORIGIN + ((p0-CGAL_ORIGIN) + (p1-CGAL_ORIGIN) +(p2-CGAL_ORIGIN) )/3) );
  assert( t.has_on(p0 + (p1-p0)/2) );
  assert( t.has_on(p0) );
  assert( t.has_on(p1) );

  assert( !t.is_degenerate() ); 

  cout << "... done" << endl;
}

#ifdef MAIN

int main()
{
  Triangles3();

  return 1;
}
#endif
