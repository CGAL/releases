 
// Source: double-specializationsC2.C
// Author: Andreas.Fabri@sophia.inria.fr

 
#include <CGAL/cartesian.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Iso_rectangle_2.h>

CGAL_Triangle_2< C<double> >;
CGAL_Iso_rectangle_2< C<double> >;



static void dummy()
{
  CGAL_Triangle_2< C<double> > t;
  CGAL_Iso_rectangle_2< C<double> > r;

  t.vertex(0);
  r.vertex(0);

}
 

