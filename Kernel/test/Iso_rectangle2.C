
#include <CGAL/Cartesian.h>


#include <math.h>
#include <iostream.h>
#include <CGAL/Double_eps.h>
#include <CGAL/Rational.h>

// the fieldtype should come from outside
typedef FIELDTYPE fieldtype;

//#include <CGAL/Aff_transformationC2.h>
//typedef CGAL_Aff_transformationC2<fieldtype> Aff_transformation;


#include <CGAL/Iso_rectangle_2.h>
typedef CGAL_Iso_rectangle_2< CGAL_Cartesian<fieldtype> > Iso_rectangle;
typedef CGAL_Point_2< CGAL_Cartesian<fieldtype> >          Point;




void Iso_rectangles()
{
  cout << "Testing CGAL_Iso_rectangle_2<R> ... " << flush;
  const fieldtype pi = 2 * asin(1.0);
  Point p(-1,-2), q(4,5);
  Iso_rectangle is(Point(-1, -2), Point(4, 5)), ispq(p,q), isqp(q,p), is2(is), is3;

  is3 = is2;

  assert( is.vertex(0) == p );
  assert( is.vertex(0) == is[0] );
  assert( is.vertex(1) == is[1] );

  assert( is == ispq );
  assert( is == is2 );
  assert( is2 == is3 );


  //  Aff_transformation rotate(sin(pi), cos(pi));

  //  rotate(is);

  cout << " done" << endl;
}

