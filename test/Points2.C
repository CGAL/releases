
#include <stream.h>
#include <CGAL/Double_eps.h>
#include <CGAL/Rational.h>
#include <CGAL/Integer.h>

// the following types come from outside

typedef FIELDTYPE fieldtype;
typedef RINGTYPE  ringtype;


#ifdef CARTESIAN
#include <CGAL/cartesian.h>
#else
#include <CGAL/homogeneous.h>
#endif // CARTESIAN

#ifdef CGAL_REPCLASS
#include <CGAL/Point_2.h>
#include <CGAL/IO/ostream_2.h>

#ifdef CARTESIAN
typedef C<fieldtype> reptype;
#else
typedef H<fieldtype, ringtype> reptype;
#endif // CARTESIAN

typedef CGAL_Point_2<reptype> Point;

#else

#include <CGAL/PointC2.h>

typedef CGAL_PointC2<fieldtype> Point;
typedef CGAL_LineC2<fieldtype> Line;

#endif  // CGAL_REPCLASS



typedef CGAL_Bbox_2 Bbox;


void Points()
{
  cout << "Testing CGAL_Point_2<R> ... " << flush;

  // constructors
  Point origin(0,0), p;


  // conversion and copy
  p = Point(10.0, -10.0);
  
  cout << p << endl;
  assert( p.x() == 10  && p.y() == -10 );
  assert( p.hx() == 10  && p.hy() == -10 && p.hw() == 1 );

  p = CGAL_ORIGIN;

  assert( p.x() == 0  && p.y() == 0 );

  assert( p.dimension() == 2 );

  // constructors
  Point q(6, 9, 2), r(p);
  // copy
  r = q;

  // access functions
  assert( q.cartesian(0) == fieldtype(3)  
	  &&  q.cartesian(1) == fieldtype(4.5) );

  assert( r.x() == q[0]  &&   r.y() == q[1] );


  // equalness and identity
  assert( p != q );
  assert( r == q  &&  q == r );
  assert( r == r );
  assert( r.identical(r) );
  assert( ! p.identical(q)  &&  ! q.identical(p));
  assert( q.identical(r)    &&  r.identical(q) );

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

