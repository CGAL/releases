#include <CGAL/basic.h>

#include <iostream.h>
#include <CGAL/Double_eps.h>
#include <CGAL/Rational.h>


typedef CGAL_Double_eps fieldtype;

#include <CGAL/Cartesian.h>
typedef CGAL_Cartesian<fieldtype> reptype;

#include <CGAL/Point_3.h>
typedef CGAL_Point_3<reptype> Point;



void call_by_value(Point p)
{
  Point q;

  q = p;
}

void Points3()
{
  cout << "Testing CGAL_Point_3<FT> ... " << flush;
  // constructors
  Point origin(0,0,0), p;


  p = Point(10, -10, -5);
  assert( p.x() == reptype::FT(10)  && 
	  p.y() == reptype::FT(-10) && 
	  p.z() == reptype::FT(-5) );


  call_by_value(p);

  p = CGAL_ORIGIN;
  assert( p.x() == reptype::FT(0) &&
	  p.y() == reptype::FT(0) &&
	  p.z() == reptype::FT(0) );

  assert( p.dimension() == 3 );

  // constructors
  Point q(3, 4.5, 1.1), r(p);
  // copy
  r = q;
  // access functions
  assert( q.cartesian(0) == reptype::FT(3)  &&
	  q.cartesian(1) == reptype::FT(4.5) &&
	  q.cartesian(2) == reptype::FT(1.1) );
  assert( r.x() == q[0]  &&   r.y() == q[1]  &&   r.z() == q[2]);

  // equalness and identity
  assert( p != q );
  assert( r == q  &&  q == r );
  assert( r == r );
  assert( identical(r, r) );
  assert( ! identical(p, q)  &&  ! identical(q, p));
  assert( identical(q, r)    &&  identical(r, q) );
  cout << " done" << endl;
}

#ifdef MAIN

int main()
{
  Points3();

  return 1;
}
#endif


