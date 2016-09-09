/*******************************************************************/
/* This is an example program for the Planar Map package           */
/* It tests the use of exact traits with homogeneous coordinates , */
/* and the direct insertion functions (insert_from_vertex etc.).   */
/*******************************************************************/
/* By:   Iddo Hanniel < hanniel@math.tau.ac.il>                    */
/*******************************************************************/

#include <CGAL/Homogeneous.h>
#include <CGAL/Pm_segment_exact_traits.h>

#include <CGAL/Pm_default_dcel.h>
#include <CGAL/Planar_map_2.h>


typedef CGAL_Homogeneous<long>                     coord_t;
typedef CGAL_Pm_segment_exact_traits<coord_t>         pmtraits;
typedef pmtraits::Point                               point;
typedef pmtraits::X_curve                             curve;
typedef CGAL_Pm_default_dcel<pmtraits>                pmdcel;

int main()
{
  // creating an instance of CGAL_Planar_map_2<pmdcel,pmtraits>
  CGAL_Planar_map_2<pmdcel,pmtraits> pm;

  curve cv[6];
  int i;

  CGAL_set_ascii_mode(cout);

  point a1(1, 1), a2(1, 0), a3(0, 0), a4(0, 1), a5(1,4,2) ;

  //              a5 
  //            /\  
  //           /  \
  //       a4  ----  a1
  //          |    | 
  //          |    | 
  //          |    |
  //       a3  ----  a2
          
       

  // those curves are about to enter to pm
  cv[0] = curve(a1, a2);
  cv[1] = curve(a2, a3);
  cv[2] = curve(a3, a4);
  cv[3] = curve(a4, a5);
  cv[4] = curve(a5, a1);
  cv[5] = curve(a1, a4);
   
  cout << "the curves of the map :" << endl; 
  for (i = 0; i < 6; i++)
    cout << cv[i] << endl;

  cout << endl;


  // insert the five curves to the map
  cout << "inserting the curves to the map..." << endl;
  CGAL_Planar_map_2<pmdcel,pmtraits>::Halfedge e[6];  
  e[0]=pm.insert(cv[0]);
  for (i = 1; i < 4; i++)
  {
    e[i]=pm.insert_from_vertex(cv[i],e[i-1].target(), true);
  }

  e[4]=pm.insert_at_vertices(cv[4],e[0].source(),e[3].target() );

  e[5]=pm.insert_at_vertices(cv[5],e[0].source(),e[2].target() );
  
               
  //        e3  /\  e4
  //           /  \
  //           ----
  //          | e5 | 
  //       e2 |    | e0
  //          |    |
  //           ----
  //            e1 



  // check the validity of the map
  cout << "check map validity... ";
  if (pm.is_valid())
    cout << "map valid!" << endl;
  else
    cout << "map invalid!" << endl;
  cout << endl << "Printing map: " << endl;
  
  cout << pm ;

  return 0;  
}














