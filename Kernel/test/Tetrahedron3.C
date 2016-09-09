
#include <CGAL/Cartesian.h>
#include <iostream.h>
#include <CGAL/Double_eps.h>
#include <CGAL/Rational.h>

// the fieldtype should come from outside
typedef FIELDTYPE fieldtype;

#include <CGAL/Tetrahedron_3.h>
#include <CGAL/IO/ostream_3.h>

typedef CGAL_Tetrahedron_3< CGAL_Cartesian<fieldtype> > Tetrahedron;
typedef CGAL_Plane_3< CGAL_Cartesian<fieldtype> >       Plane;
typedef CGAL_Point_3< CGAL_Cartesian<fieldtype> >       Point;




void Tetrahedrons()
{
  cout << "Testing CGAL_Tetrahedron_3<R> ... " << flush;
  
  Point  p0(2, 2, 2), p1(1, 0, 0), p2(0, 1, 0), p3(0, 0, 1);

  Tetrahedron t(p0, p1, p2, p3), tcopy(t), tc,
              tunit(CGAL_ORIGIN, p1, p2, p3);


  assert( t == tcopy );
  assert( identical(t, tcopy) );

  tc = t;
  assert( t == tc );
  assert( identical(t, tc) );

  assert( t != tunit );
  assert( !identical(t, tunit) );

  for(int i=0; i<=4; i++)
    {
      assert( t.vertex(i) == t[i] );
    }

  assert( t[0] == p0 &&  t[1] == p1 &&  t[2] == p2 &&  t[3] == p3 );
  assert( t[4] == p0 );

  assert( t.has_on_bounded_side(Point(1, 1, 1)) );
  assert( t.has_on_boundary(p0) );
  assert( t.has_on_boundary(p0 + (p1-p0)/2) );
  assert( t.has_on_boundary(CGAL_ORIGIN + ((p0-CGAL_ORIGIN) 
					   + (p1-CGAL_ORIGIN)  
					   + (p2-CGAL_ORIGIN))/3 ) );

  cout << endl << "point should be CGAL_ON " << endl << "It is " ;
  switch ( t.bounded_side(CGAL_ORIGIN + ((p1-CGAL_ORIGIN) + (p2-CGAL_ORIGIN)  +(p3-CGAL_ORIGIN))/3 ) ) {
  case CGAL_ON_BOUNDED_SIDE : cout << "CGAL_ON_BOUNDED_SIDE" << endl;
                     break;
  case CGAL_ON_UNBOUNDED_SIDE : cout << "CGAL_ON_UNBOUNDED_SIDE" << endl;
                     break;
  case CGAL_ON_BOUNDARY : cout << "CGAL_ON_BOUNDARY" << endl;
                     break;
  };
  assert( t.has_on_unbounded_side(CGAL_ORIGIN) );

  cout << endl << t << endl;
  cout << "... done" << endl;
}


#ifdef MAIN

int main()
{
  Tetrahedrons();

  return 1;
}
#endif // MAIN
