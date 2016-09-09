

#include <CGAL/Cartesian.h>
#include <CGAL/Line_2.h>


typedef double fieldtype;

typedef CGAL_Cartesian<fieldtype> reptype;
typedef CGAL_Point_2<reptype> Point;
typedef CGAL_Line_2<reptype> Line;


int main()
{
  Line line2(Point(fieldtype(x1), 
		   fieldtype(y1)), 
	     Point(fieldtype(x2), 
		   fieldtype(y2)));

  Line line3 = line2;
  return 0;
}

/* 
no matching function for call to 

CGAL_Line_2<reptype>::CGAL_Line_2<reptype> (
   CGAL_Line_2<reptype> ()(CGAL_Point_2<reptype> (*)(double, double), 
                           CGAL_Point_2<reptype> (*)(double, double)))
*/
