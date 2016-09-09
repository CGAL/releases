
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

#include <CGAL/Vector_2.h>

#ifdef CARTESIAN
typedef C<fieldtype> reptype;
#else
typedef H<fieldtype, ringtype> reptype;
#endif // CARTESIAN

typedef CGAL_Point_2<reptype>  Point;
typedef CGAL_Vector_2<reptype> Vector;

#else

#include <CGAL/VectorC2.h>
typedef CGAL_PointC2<fieldtype> Point;
typedef CGAL_VectorC2<fieldtype> Vector;

#endif // CGAL_REPCLASS


void Vectors()
{
  cout << "Testing CGAL_Vector_2<R> ... " << flush;

  Point q(6, 9, 2);

  // constructors
  Vector w(2.0, 1.0), v;

  
  // conversion and copy
  v = Vector(10.0, -10.0);
  assert( v.x() == 10  && v.y() == -10 );


  v = q - CGAL_ORIGIN;
  assert( v.dimension() == 2);
  // access functions
  assert( v.x() == q.x()  &&  v.y() == q.y() );
  assert( v[0] == q.x()  &&  v[1] == q.y() );
  assert( v.cartesian(0) == q.x()  &&  v.cartesian(1) == q.y() );

  Vector u(v);
  
  // equalness and identity
  assert( w != v );
  assert( u == v  &&  v == u );
  assert( u == u );
  assert( u.identical(u) );
  assert( ! w.identical(v)  &&  ! v.identical(w));
  assert( v.identical(u)    &&  u.identical(v) );

  // vector operations
  v = Vector(10,8) ;
  assert( (v/2).x() == v.x()/2  && (v/2).y() == v.y()/2 );

  ringtype scalar(2);

  assert( scalar * (v/2) == v );

  assert( v + v + v == 3.0 * v);

  assert( CGAL_ORIGIN + (v - v) == CGAL_ORIGIN );

  assert( v == v.direction().vector() );

  assert( Point(-2,-2) == CGAL_ORIGIN - Vector(2,2) );
  assert(  (v.x() == -(-v.x()))  && (v.y() == -(-v.y())) );

  Point p = CGAL_ORIGIN + v + w/2 + w/2;
  assert( p.x() == (v.x() + w.x())  && p.y() == (v.y() + w.y()) );

  fieldtype f = v * v;

  // point vector interaction
  v = q - CGAL_ORIGIN;
  w = CGAL_ORIGIN - q;

  assert( v == -w );

  w = Point(0,0) - q;

  assert( v == -w );

  p = Point(0,0) + Vector(1,0);
  assert ( p == Point(1,0) );
  
  cout << " done" << endl;
}

#ifdef MAIN

int main()
{
  Vectors();

  return 1;
}
#endif
