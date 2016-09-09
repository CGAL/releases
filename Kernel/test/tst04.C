

#include <CGAL/Cartesian.h>
#include <CGAL/Line_2.h>
#include <CGAL/Double_eps.h>


typedef double fieldtype;

typedef CGAL_Cartesian<fieldtype> reptype;
typedef CGAL_Point_2< reptype > Point;
typedef CGAL_Line_2< reptype > Line;


int main()
{
  fieldtype f = 0;
	Line line2(Point(fieldtype(x1), 
			 fieldtype(y1)), 
		   Point(fieldtype(x2), 
			 fieldtype(y2)));

	Line line3 = line2;
 return 0;
}

/*
cannot convert type `

CGAL_Line_2<CGAL_Cartesian<double> > (*)
    (CGAL_Point_2<CGAL_Cartesian<double> > (*)(double, double), 
     CGAL_Point_2<CGAL_Cartesian<double> > (*)(double, double))'

 to type `const CGAL_Line_2<CGAL_Cartesian<double> > &'
 */
