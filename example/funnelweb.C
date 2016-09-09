#line 144 "funnelweb.fw"

#line 89 "funnelweb.fw"
#include <stream.h>
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#line 145 "funnelweb.fw"


#line 103 "funnelweb.fw"
typedef double coord_type;
typedef CGAL_Point_2< C<coord_type> > Point;
#line 111 "funnelweb.fw"
typedef CGAL_Segment_2< C<coord_type> > Segment;
#line 147 "funnelweb.fw"


#line 127 "funnelweb.fw"

void alpha(){
  Point p(0.0, 10.4), q(8.9, 6.8);
  Segment r, s(p,q);
}
#line 149 "funnelweb.fw"


int main()
{
    alpha();

  cout << " done" << endl;

  return 1;
}
