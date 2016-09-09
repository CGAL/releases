/*********************************************************************/
/*  This is an example program for the Planar_map package.           */
/*  It can be found in the manual .                                  */
/*********************************************************************/
/* By:   Eyal Flato                                                  */
/*       Iddo Hanniel <hanniel@math.tau.ac.il>                       */
/*********************************************************************/

//#include <CGAL/name_defs.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Pm_segment_epsilon_traits.h>
#include <CGAL/Pm_default_dcel.h>
#include <CGAL/Planar_map_2.h>

typedef double                                           number_type;
typedef CGAL::Cartesian<number_type>                      coord_t;
typedef CGAL::Pm_segment_epsilon_traits<coord_t>          pmtraits;
typedef pmtraits::Point                                  point;
typedef pmtraits::X_curve                                curve;
typedef CGAL::Pm_default_dcel<pmtraits>                   pmdcel;

int main()
{
  // creating an instance of CGAL::Planar_map_2<pmdcel,pmtraits>
  //CGAL::Pm_naive_point_location_strategy<pmdcel,pmtraits> pl_strategy;  
  //CGAL::Planar_map_2<pmdcel,pmtraits> pm(&pl_strategy);
    CGAL::Planar_map_2<pmdcel,pmtraits> pm;

  curve cv[5];
  int i;

  point a1(100, 0), a2(20, 50), a3(180, 50), a4(100, 100);

  // those curves are about to be inserted to pm
  cv[0] = curve(a1, a2);
  cv[1] = curve(a1, a3);
  cv[2] = curve(a2, a3);
  cv[3] = curve(a2, a4);
  cv[4] = curve(a3, a4);
  
  std::cout << "the curves of the map :" << std::endl; 
  for (i = 0; i < 5; i++)
    std::cout << cv[i] << std::endl;

  std::cout << std::endl;

  // insert the five curves to the map
  std::cout << "inserting the curves to the map..." << std::endl;
  for (i = 0; i < 5; i++)
  {
    std::cout << "inserting curve" << i << std::endl;
    pm.insert(cv[i]);
  }
  
  // check the validity of the map
  std::cout << "check map validity... ";
  if (pm.is_valid())
    std::cout << "map valid!" << std::endl;
  else
    std::cout << "map invalid!" << std::endl;
  std::cout << std::endl;
  
  // vertical ray shooting upward from p
  point p(95, 30);
  CGAL::Planar_map_2<pmdcel,pmtraits>::Halfedge_handle e;  
  CGAL::Planar_map_2<pmdcel,pmtraits>::Locate_type lt;

  std::cout << std::endl << "upward vertical ray shooting from " << p << std::endl; 
  e=pm.vertical_ray_shoot(p, lt, true);
  std::cout << "returned the curve :" << e->curve() << std::endl;
  
  return 0;  
}













