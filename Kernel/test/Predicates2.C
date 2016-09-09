#include <iostream.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/Line_2.h>
#include <CGAL/predicates_on_points_2.h>
#include <CGAL/predicates_on_lines_2.h>

#include <CGAL/IO/Window_stream.h>



typedef double coord_type;
typedef CGAL_Point_2< CGAL_Cartesian<coord_type> > Point;
typedef CGAL_Line_2< CGAL_Cartesian<coord_type> > Line;

int main()
{
  
  CGAL_Window_stream W(400, 200);
  
  W.init(0.0, 40.0, 0.0);
  
  Line l1, l2, l3, l4;
  for(int j=0; j < 1; j++){
  W << CGAL_black;
  W  >> l1 >> l2 ;

  W << CGAL_red;
  W >> l3;
  W << CGAL_green;
  W >> l4;

  W << CGAL_blue;  

  const coord_type &l1a = l1.a();
  const coord_type &l2a = l2.a();

  const coord_type &l1b = l1.b();
  const coord_type &l2b = l2.b();

  const coord_type &l1c = l1.c();
  const coord_type &l2c = l2.c();

  coord_type x = CGAL_det2x2_by_formula(-l1c, l1b, -l2c, l2b)
          / CGAL_det2x2_by_formula(l1a, l1b, l2a, l2b);

  cout << "x = " << x << endl;
  cout << "l3.y_at_x(x) = " << l3.y_at_x(x) << endl;
  W << Point(x, l3.y_at_x(x));
  W << CGAL_green;
  W << Point(x, l3.y_at_x(x));
  CGAL_Comparison_result res = CGAL_compare_y_at_x(l1,l2,l3,l4);

  cout << ((res == CGAL_SMALLER) ? "smaller" : "larger") << endl; 
  }
  Point p,q,r,t;

  for (int i=0; i< 10; i++) {
    W << CGAL_black;
    W >> p >> q >> r >> t;

    switch(CGAL_side_of_bounded_circle(p,q,r, t)) {
    case CGAL_ON_BOUNDED_SIDE:
      W << CGAL_red;
      W << t;
      cout << "inside" << endl;
      break;
    case CGAL_ON_UNBOUNDED_SIDE:
      cout << "outside" << endl;
      break;
    default:
      cout << "??" << endl;
      break;
    }
  }
}

