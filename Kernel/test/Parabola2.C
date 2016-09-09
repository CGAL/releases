#include <CGAL/basic.h>
#include <math.h>
#include <iostream.h>
#include <CGAL/Double_eps.h>
#include <CGAL/Rational.h>
#include <CGAL/Integer.h>



// the following types come from outside

typedef FIELDTYPE fieldtype;
typedef RINGTYPE  ringtype;

#ifdef CARTESIAN
#include <CGAL/Cartesian.h>
#else
#include <CGAL/Homogeneous.h>
#endif // CARTESIAN

#include <CGAL/Line_2.h>
#include <CGAL/Parabola_2.h>
#include <CGAL/Parabola_arc_2.h>
#include <CGAL/Aff_transformation_2.h>
#include <CGAL/IO/ostream_2.h>
#include <CGAL/IO/Window_stream.h>

#ifdef CARTESIAN
typedef CGAL_Cartesian<fieldtype> reptype;
#else
typedef CGAL_Homogeneous<ringtype> reptype;
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

  Parabola par(Point(1,2),
	       Vector(1,1),
	       0.5);

  assert ( CGAL_ON_ORIENTED_BOUNDARY == par.oriented_side(Point(1,6)) );
  assert ( CGAL_ON_NEGATIVE_SIDE == par.oriented_side(Point(5,0)) );
  assert ( CGAL_ON_POSITIVE_SIDE == par.oriented_side(Point(0,5)) );

 
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
  CGAL_set_eps(0.00000001);
  Parabolas();

  return 1;
}


