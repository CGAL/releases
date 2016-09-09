#include <stream.h>
#include <CGAL/cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/predicates_on_points_2.h>

#include <CGAL/IO/Window_stream.h>



typedef double coord_type;
typedef CGAL_Point_2< C<coord_type> > Point;

int main()
{
  
  CGAL_Window_stream W(400, 200);
  
  W.init(0.0, 40.0, 0.0);
  
  Point p,q,r,t;

  for (int i=0; i< 10; i++) {
    W << CGAL_black;
    W >> p >> q >> r >> t;

    switch(CGAL_in_circle(p,q,r, t)) {
    case CGAL_INSIDE:
      W << CGAL_red;
      W << t;
      cout << "inside" << endl;
      break;
    case CGAL_OUTSIDE:
      cout << "outside" << endl;
      break;
    default:
      cout << "??" << endl;
      break;
    }
  }
}
