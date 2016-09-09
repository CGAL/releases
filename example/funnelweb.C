#line 145 "funnelweb.fw"

#line 89 "funnelweb.fw"
#include <CGAL/Cartesian.h>
#include <iostream.h>
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#line 146 "funnelweb.fw"


#line 104 "funnelweb.fw"
typedef double coord_type;
typedef CGAL_Point_2< CGAL_Cartesian<coord_type> > Point;
#line 112 "funnelweb.fw"
typedef CGAL_Segment_2< CGAL_Cartesian<coord_type> > Segment;
#line 148 "funnelweb.fw"


#line 128 "funnelweb.fw"

void alpha(){
  Point p(0.0, 10.4), q(8.9, 6.8);
  Segment r, s(p,q);
}
#line 150 "funnelweb.fw"


int main()
{
    alpha();

  cout << " done" << endl;

  return 1;
}
