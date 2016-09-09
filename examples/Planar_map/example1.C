/*********************************************************************/
/*  This is an example program for the Planar_map package.           */
/*  It can be found in the manual .                                  */
/*********************************************************************/
/* By:   Eyal Flato                                                  */
/*       Iddo Hanniel <hanniel@math.tau.ac.il>                       */
/*******************************************************************/

#include <CGAL/Cartesian.h>
#include <CGAL/Pm_segment_epsilon_traits.h>
#include <CGAL/Pm_default_dcel.h>
#include <CGAL/Planar_map_2.h>


typedef double                                           number_type;
typedef CGAL_Cartesian<number_type>                      coord_t;
typedef CGAL_Pm_segment_epsilon_traits<coord_t>          pmtraits;
typedef pmtraits::Point                                  point;
typedef pmtraits::X_curve                                curve;
typedef CGAL_Pm_default_dcel<pmtraits>                   pmdcel;


int main()
{
  // creating an instance of CGAL_Planar_map_2<pmdcel,pmtraits>
  CGAL_Planar_map_2<pmdcel,pmtraits> pm;

  curve cv[5];
  int i;

  point a1(100, 0), a2(20, 50), a3(180, 50), a4(100, 100);

  // those curves are about to be inserted to pm
  cv[0] = curve(a1, a2);
  cv[1] = curve(a1, a3);
  cv[2] = curve(a2, a3);
  cv[3] = curve(a2, a4);
  cv[4] = curve(a3, a4);
  
  cout << "the curves of the map :" << endl; 
  for (i = 0; i < 5; i++)
    cout << cv[i] << endl;

  cout << endl;

  // insert the five curves to the map
  cout << "inserting the curves to the map..." << endl;
  for (i = 0; i < 5; i++)
  {
    cout << "inserting curve" << i << endl;
    pm.insert(cv[i]);
  }
  
  // check the validity of the map
  cout << "check map validity... ";
  if (pm.is_valid())
    cout << "map valid!" << endl;
  else
    cout << "map invalid!" << endl;
  cout << endl;
  
  // vertical ray shooting upward from p
  point p(95, 30);
  CGAL_Planar_map_2<pmdcel,pmtraits>::Halfedge e;  
  CGAL_Planar_map_2<pmdcel,pmtraits>::Locate_type lt;

  cout << endl << "upward vertical ray shooting from " << p << endl; 
  e=pm.vertical_ray_shoot(p, lt, true);
  cout << "returned the edge :" << e << endl;
  
  return 0;  
}








