#include <math.h>
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

#include <CGAL/Line_2.h>
#include <CGAL/Parabola_2.h>
#include <CGAL/Parabola_arc_2.h>
#include <CGAL/Aff_transformation_2.h>
#include <CGAL/IO/ostream_2.h>
#include <CGAL/IO/Window_stream.h>

#ifdef CARTESIAN
typedef C<fieldtype> reptype;
#else
typedef H<fieldtype, ringtype> reptype;
#endif // CARTESIAN

typedef CGAL_Point_2<reptype> Point;
typedef CGAL_Vector_2<reptype> Vector;
typedef CGAL_Direction_2<reptype> Direction;
typedef CGAL_Segment_2<reptype> Segment;
typedef CGAL_Line_2<reptype> Line;
typedef CGAL_Parabola_2<reptype> Parabola;
typedef CGAL_Parabola_arc_2<reptype> Parabola_arc;
typedef CGAL_Aff_transformation_2<reptype> Aff_transformation;
typedef CGAL_Bbox_2 Bbox;



void Parabolas()
{
  Point p1, p2, proj1, proj2;
  fieldtype lambda1, lambda2;
  CGAL_Window_stream W(400, 200);
  W.init(-10.0, 10.0, -5.0);
  // draw the coordinate system
  W << CGAL_red << Line(Point(0,0), Point(1,0));
  W << Line(Point(0,0), Point(0,1));
  W << CGAL_black;

  Parabola par(Point(0,0),
	       Vector(1,1),
	       -0.5);
  /*
  assert ( par.is_on(Point(1,1)) );
  assert ( par.is_on(Point(-3,-1)) );
  assert ( par.is_on(Point(-3,3)) );
  */
 
  W << par << CGAL_red << par.opposite();

  for(;;){
    W << CGAL_black;
    W >> par;
    W << CGAL_green << par.base() 
      << CGAL_blue << par.focus() << par.director();

    W << CGAL_black;
    W >> p1 >> p2;
    proj1 = par.projection(p1, lambda1);
    proj2 = par.projection(p2, lambda2);

    W << par(lambda1);
    W << CGAL_green << Parabola_arc(par, lambda1, lambda2);
    W << CGAL_red << proj1 << proj2;
    
  }

  {
    char c;
    cout << "continue?" << endl;
    cin >> c;
  }
}



int main()
{
  Parabolas();

  return 1;
}

