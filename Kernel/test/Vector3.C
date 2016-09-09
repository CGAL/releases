
#include <CGAL/Cartesian.h>


#include <iostream.h>
#include <CGAL/Double_eps.h>
#include <CGAL/Rational.h>

// the fieldtype should come from outside
typedef FIELDTYPE fieldtype;
typedef CGAL_Cartesian<fieldtype> reptype;


#include <CGAL/Vector_3.h>
typedef CGAL_Point_3<reptype>  Point;
typedef CGAL_Vector_3<reptype> Vector;

void Vectors3()
{
  cout << "Testing CGAL_Vector_3<FT> ... " << flush;
  Point q(3, 4.5, 1.1);

  // constructors
  Vector w(2.0, 1.0, 3.0), v;
  
  // conversion and copy
  v = Vector(10, -10, -5);
  assert( v.x() == reptype::FT(10) &&
	  v.y() == reptype::FT(-10) &&
	  v.z() == reptype::FT(-5) );

  v = q - CGAL_ORIGIN;
  assert( v.dimension() == 3);
  // access functions
  assert( v.x() == q.x()  &&  v.y() == q.y() &&  v.z() == q.z() );
  assert( v[0] == q.x()  &&  v[1] == q.y()  &&  v[2] == q.z() );
  assert( v.cartesian(0) == q.x()  &&
	  v.cartesian(1) == q.y()  &&
	  v.cartesian(2) == q.z() );

  Vector u(v);
  
  // equalness and identity
  assert( w != v );
  assert( u == v  &&  v == u );
  assert( u == u );
  assert( identical(u, u) );
  assert( ! identical(w, v)  &&  ! identical(v, w));
  assert( identical(v, u)    &&  identical(u, v) );

  v = Vector(0,0,0);

  assert ( v == CGAL_NULL_VECTOR );

  v = CGAL_NULL_VECTOR;

  // vector operations
  v = Vector(10, 8, 2) ;
  assert( (v/reptype::RT(2)).x() == v.x()/reptype::RT(2)  &&
	  (v/reptype::RT(2)).y() == v.y()/reptype::RT(2)  &&
	  (v/reptype::RT(2)).z() == v.z()/reptype::RT(2));

  fieldtype scalar(2.0);
  assert( v ==  (v/scalar) * scalar );

  v * v;

  fieldtype three(3.0);

  assert( v + v + v ==   v * three);
  assert( CGAL_ORIGIN + (v - v) == CGAL_ORIGIN );

  assert( v == v.direction().vector() );

  assert(  (v.x() == -(-v.x()))  &&
	   (v.y() == -(-v.y())) &&
	   (v.z() == -(-v.z())) );

  assert( Point(-1,-2,-3) == CGAL_ORIGIN - Vector(1,2,3) );

  Point p = CGAL_ORIGIN + v + w/2 + w/2;
  assert( p.x() == (v.x() + w.x())  &&
	  p.y() == (v.y() + w.y())  &&
	  p.z() == (v.z() + w.z()));


  // point vector interaction
  v = q - CGAL_ORIGIN;
  w = CGAL_ORIGIN - q;

  assert( v == -w );
  cout << " done" << endl;
}

#ifdef MAIN

int main()
{
  Vectors3();

  return 1;
}
#endif
