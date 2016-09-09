
#include <CGAL/basic.h>

#include <iostream.h>
#include <CGAL/Double_eps.h>
#include <CGAL/Rational.h>
#include <CGAL/Integer.h>

// the following types come from outside

typedef CGAL_Double_eps fieldtype;
typedef CGAL_Double_eps  ringtype;


#ifdef CARTESIAN
#include <CGAL/Cartesian.h>
#else
#include <CGAL/Homogeneous.h>
#endif // CARTESIAN


#include <CGAL/Point_2.h>
#include <CGAL/IO/ostream_2.h>

#ifdef CARTESIAN
typedef CGAL_Cartesian<fieldtype> reptype;
#else
typedef CGAL_Homogeneous<ringtype> reptype;
#endif // CARTESIAN

typedef CGAL_Point_2<reptype> Point;
typedef CGAL_Bbox_2 Bbox;


void call_by_value(Point p)
{
  Point q = p;
}


void Points()
{
  cout << "Testing CGAL_Point_2<R> ... " << flush;

  // constructors
  Point origin(0,0), p;


  // conversion and copy
  p = Point(10.0, -10.0);
  
  call_by_value(p);

  cout << p << endl;
  assert( p.x() == reptype::FT(10)  && p.y() == reptype::FT(-10) );
  assert( p.hx() == reptype::FT(10)  && p.hy() == reptype::FT(-10) && p.hw() == reptype::FT(1) );


  p = CGAL_ORIGIN;

  assert( p.x() == reptype::FT(0)  && p.y() == reptype::FT(0) );

  assert( p.dimension() == 2 );

  // constructors
  Point q(6, 9, 2), r(p);
  // copy
  r = q;

  // access functions
  assert( q.cartesian(0) == reptype::FT(3)  
	  &&  q.cartesian(1) == reptype::FT(4.5) );

  assert( r.x() == q[0]  &&   r.y() == q[1] );


  // equalness and identity
  assert( p != q );
  assert( r == q  &&  q == r );
  assert( r == r );
  assert( identical(r, r) );
  assert( ! identical(p, q)  &&  ! identical(q, p));
  assert( identical(q, r)    &&  identical(r, q) );

  Bbox b = p.bbox();
  cout << " done" << endl;
}


#ifdef MAIN

int main()
{
  Points();

  return 1;
}
#endif

