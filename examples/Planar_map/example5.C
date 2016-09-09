/********************************************************************/
/* This is an example program for the Planar Map package            */
/* It tests the direct insertion functions (insert_from_vertex etc.)*/
/* and uses the naive point location strategy instead of the        */
/* default strategy provided.                                       */
/*******************************************************************/
/* By:   Iddo Hanniel < hanniel@math.tau.ac.il>                    */
/*******************************************************************/

#include <CGAL/Homogeneous.h>
#include <CGAL/Pm_segment_exact_traits.h>

#include <CGAL/Pm_default_dcel.h>
#include <CGAL/Planar_map_2.h>

#include <CGAL/Pm_naive_point_location.h>

typedef CGAL::Homogeneous<long>                     coord_t;
typedef CGAL::Pm_segment_exact_traits<coord_t>         pmtraits;
typedef pmtraits::Point                               point;
typedef pmtraits::X_curve                             curve;
typedef CGAL::Pm_default_dcel<pmtraits>                pmdcel;
typedef CGAL::Planar_map_2<pmdcel,pmtraits>            pmap;
int main()
{
  // creating an instance of CGAL::Planar_map_2<pmdcel,pmtraits>
  //with a naive point location strategy
  CGAL::Pm_naive_point_location<pmap> naive_pl;
  pmap pm(&naive_pl);

  curve cv[4];
  int i;

  CGAL::set_ascii_mode(std::cout);

  point a1(1, 1), a2(1, 0), a3(0, 0), a4(0, 1);

  cv[0] = curve(a1, a2);
  cv[1] = curve(a2, a3);
  cv[2] = curve(a3, a4);
  cv[3] = curve(a4, a1);


  // inserting the curves to the map
  CGAL::Planar_map_2<pmdcel,pmtraits>::Halfedge_handle e[4];  

  e[0]=pm.insert_in_face_interior(cv[0],pm.unbounded_face());

  for (i = 1; i < 3; i++)
  {
    e[i]=pm.insert_from_vertex(cv[i],e[i-1]->target(), true);
  }

  e[3]=pm.insert_at_vertices(cv[3],e[0]->source(),e[2]->target() );

  // check the validity of the map
  CGAL_assertion(pm.is_valid());

  return 0;  
}














