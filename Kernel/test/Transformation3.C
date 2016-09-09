
#include <CGAL/Cartesian.h>
#include <iostream.h>
#include <math.h>


#include <CGAL/Origin.h>
#include <CGAL/Double_eps.h>
#include <CGAL/Triangle_3.h>
#include <CGAL/Plane_3.h>



#include <CGAL/Aff_transformation_3.h>

typedef CGAL_Cartesian<double> Rep;

typedef CGAL_Point_3< Rep > Point;
typedef CGAL_Vector_3< Rep > Vector;
typedef CGAL_Direction_3< Rep > Direction;

typedef CGAL_Line_3< Rep > Line;
typedef CGAL_Ray_3< Rep > Ray;

typedef CGAL_Segment_3< Rep > Segment;

typedef CGAL_Triangle_3< Rep > Triangle;
typedef CGAL_Plane_3< Rep > Plane;

typedef CGAL_Aff_transformation_3< Rep > Aff_transformation;


void Transformations3()
{
  cout << "Testing CGAL_Aff_transformation_3<R> ... " << flush;
  const double pi = 2 * asin(1.0);


  Point ppp(CGAL_ORIGIN);

  Vector v(2.0, 1.0, 0.0);

  Aff_transformation  general(-1.0, 0.0, 0.0,
			       0.0, 1.0, 0.0,
			       0.0, 0.0, 1.0);

  Aff_transformation  translate(CGAL_TRANSLATION,v), 
                      itranslate = translate.inverse();
  Aff_transformation  scale(CGAL_SCALING, 2.0),
                      iscale = scale.inverse();

  Point p(CGAL_ORIGIN), q;

  q = p.transform(translate);

  assert( q == p + v );

  assert( q == translate(p) );

  p = scale(q);

  assert( p == CGAL_ORIGIN + 2.0 * (q - CGAL_ORIGIN) );


  Direction d(v);

  assert( d == d.transform(translate) );
  assert( d == translate(d) );

  assert( d == d.transform(scale) );
  assert( d == scale(d) );

  
  Line l(Point(0,0,0), Point(1,2,1));

  assert( l == l.transform(scale));
  
  Point pp(1,2,3);

  
  Ray r(Point(1.0,2.0,0.0), Direction(1.0,1.0,1.0));
  
  Ray rr(Point(-2,1,0), Direction(-1,1,0));

  Segment s(Point(1,2,0), Point(2,3,0));

  assert ((s.transform(translate)).transform(translate.inverse()) == s );

  Point plp1(1.0, 0.0, 0.0), plp2( 0.0, 1.0, 0.0), plp3( 0.0, 0.0, 1.0);

  Aff_transformation g(1.0, 2.0, 3.0,
		       0.0, 1.0, 0.0,
		       3.0, 0.0, 1.0);
  
  Plane pl(plp1, plp2, plp3);
  Plane gpl = g(pl);



  assert( gpl.has_on(g(plp1)) );
  assert( gpl.has_on(g(plp2)) );
  assert( gpl.has_on(g(plp3)) );

  assert( g.inverse().transform(gpl) == pl );


  cout << "...  done" << endl;
}



//#ifdef MAIN

int main()
{
  Transformations3();
  double m11, m12, m13,
         m21, m22, m23,
         m31, m32, m33;

  cin >> m11 >> m12 >> m13;
  cin >> m21 >> m22 >> m23;
  cin >> m31 >> m32 >> m33;

  Aff_transformation g(m11, m12, m13,
		       m21, m22, m23,
		       m31, m32, m33);

  cout << g;
  cout << g.transpose();
  cout << g.inverse();

  return 1;
}
//#endif
