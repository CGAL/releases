
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
typedef CGAL_Cartesian<double> Rcart;
#else
#include <CGAL/Homogeneous.h>
#endif // CARTESIAN


#include <CGAL/Circle_2.h>
#include <CGAL/IO/ostream_2.h>
#include <CGAL/IO/Window_stream.h>

#ifdef CARTESIAN
typedef CGAL_Cartesian<fieldtype> reptype;
#else
typedef CGAL_Homogeneous<ringtype> reptype;
#endif // CARTESIAN

typedef CGAL_Point_2<reptype> Point;
typedef CGAL_Circle_2<reptype> Circle;


typedef CGAL_Bbox_2 Bbox;


void Circles()
{
  CGAL_set_eps(0.00001);
  cout << "Testing CGAL_Circle_2<R> ... " << flush;


  CGAL_Window_stream W(400, 200);
  
  W.init(-20.0, 20.0, -10.0);
  
  // constructors
  Point origin(0,0), p(10.0, -10.0);
  
  fieldtype radius = fieldtype(3);

  Circle c1(p, radius*radius), c2(c1), c3;

  c3 = c1;

  assert( identical(c1, c2) );
  assert( identical(c1, c3) );
  assert( c1 == c3 );
  
  assert( c1.center() == p );
  assert( c1.squared_radius() == fieldtype(3*3) );

  cout << "Enter the center and a point that will be on the circle" << endl;

  W << CGAL_BLACK;
  W >> c1;

  cout << c1 << endl;
  W << CGAL_RED << c1.bbox() << CGAL_BLACK;

  for(int k = 0; k< 5; k++){
    cout << "Enter 3 Points" << endl;

    Point p1, p2, p3;
    W >> p1 >> p2 >> p3;
    Circle circle(p1,p2,p3);

    W << circle;
    cout << "Orientation " << ((circle.orientation() == CGAL_CLOCKWISE) ?
      " clockwise " : " counterclockwise" ) << endl;

    
    W >> p1;
    if (circle.has_on_bounded_side(p1)){
      cout << " on bounded side " << endl;
    } else {
      cout << " on unbounded side " << endl;
    }

    if (circle.has_on_positive_side(p1)){
      cout << " on positive side " << endl;
    } else {
      cout << " on negative side " << endl;
    }
  }
  char c;
  cin >> c;

  cout << " done" << endl;
}




int main()
{
  Circles();

  return 1;
}


