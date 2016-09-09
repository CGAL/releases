
#include <CGAL/basic.h>
#include <iostream.h>

#include <CGAL/Double_eps.h>
#include <CGAL/Rational.h>
#include <CGAL/Integer.h>
#include <CGAL/Quotient.h>

// the following types come from outside
typedef CGAL_Double_eps fieldtype;
typedef CGAL_Double_eps ringtype;


#ifdef CARTESIAN
#include <CGAL/Cartesian.h>
#else
#include <CGAL/Homogeneous.h>
#endif // CARTESIAN


#include <CGAL/Vector_2.h>

#ifdef CARTESIAN
typedef CGAL_Cartesian<fieldtype> reptype;
#else
typedef CGAL_Homogeneous<ringtype> reptype;
#endif // CARTESIAN

typedef CGAL_Point_2<reptype>  Point;
typedef CGAL_Vector_2<reptype> Vector;



void Vectors()
{
  cout << "Testing CGAL_Vector_2<R> ... " << flush;

  Point q(6, 9, 2);

  // constructors
  Vector w(2.0, 1.0), v;

  
  // conversion and copy
  v = Vector(10.0, -10.0);
  assert( v.x() == reptype::FT(10)  && v.y() == reptype::FT(-10) );


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
  assert( identical(u, u) );
  assert( ! identical(w, v)  &&  ! identical(v, w));
  assert( identical(v, u)    &&  identical(u, v) );

  v = Vector(0,0);

  assert ( v == CGAL_NULL_VECTOR );

  v = CGAL_NULL_VECTOR;

  // vector operations
  v = Vector(10,8) ;
  assert( (v/reptype::RT(2)).x() == v.x()/reptype::RT(2)  
	  && (v/reptype::RT(2)).y() == v.y()/reptype::RT(2) );

  reptype::RT scalar(2);

  assert( v ==  (v/2) * scalar );

  assert( v + v + v ==  v * reptype::RT(3.0));

  assert( CGAL_ORIGIN + (v - v) == CGAL_ORIGIN );

  assert( v == v.direction().vector() );

  assert( Point(-2,-2) == CGAL_ORIGIN - Vector(2,2) );
  assert(  (v.x() == -(-v.x()))  && (v.y() == -(-v.y())) );

  Point p = CGAL_ORIGIN + v + w/2 + w/2;
  assert( p.x() == (v.x() + w.x())  && p.y() == (v.y() + w.y()) );

  fieldtype f = v * v;


  CGAL_Quotient<reptype::RT> quot(2);
  v =  v * quot;


  // point vector interaction
  v = q - CGAL_ORIGIN;
  w = CGAL_ORIGIN - q;

  assert( v == -w );

  w = Point(0,0) - q;

  assert( v == -w );


  p = Point(0,0) +  Vector(1,0) * fieldtype(1);
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
