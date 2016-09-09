 
#include <CGAL/cartesian.h>
#include <CGAL/Bbox_2_Line_2_pair.h>
#include <CGAL/Ray_2_Bbox_2_pair.h>

 

CGAL_Bbox_2_Line_2_pair< C<double> >::CGAL_Bbox_2_Line_2_pair(
    CGAL_Bbox_2 const *bbox, CGAL_Line_2< C<double> > const *line)
{
    _bbox = bbox;
    _line = *line;
    _known = false;
}
 

 

CGAL_Ray_2_Bbox_2_pair< C<double> >::
CGAL_Ray_2_Bbox_2_pair(
            CGAL_Ray_2< C<double> > const *ray,
            CGAL_Bbox_2 const *box)
{
    _known = false;
    _box = box;
    _ref_point = ray->start();
    _dir = ray->direction().vector();
    _min = 0;
}
 

