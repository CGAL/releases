/*******************************************************************/
/* This is a test program for the Planar Map package           */
/*******************************************************************/
/* By:   Eyal Flato, flato@math.tau.ac.il                          */
/*******************************************************************/

#include <CGAL/Homogeneous.h>

#include <CGAL/Pm_segment_exact_traits.h>

#include <CGAL/Pm_default_dcel.h>
#include <CGAL/Planar_map_2.h>


typedef CGAL_Homogeneous<long>                     coord_t;
typedef CGAL_Pm_segment_exact_traits<coord_t>   pmtraits;

typedef pmtraits::Point                         point;
typedef pmtraits::X_curve                       curve;

typedef CGAL_Pm_default_dcel<pmtraits>                    pmdcel;

int main()
{
  // creating an instance of CGAL_Planar_map_2<pmdcel,pmtraits>
  CGAL_Planar_map_2<pmdcel,pmtraits> pm;

  curve cv[5];
  int i;

  CGAL_set_ascii_mode(cout);

  point a1(100, 0), a2(20, 50), a3(180, 50), a4(100, 100);

  // those curves are about to enter to pm
  cv[0] = curve(a1, a2);
  cv[1] = curve(a1, a3);
  cv[2] = curve(a2, a3);
  cv[3] = curve(a2, a4);
  cv[4] = curve(a3, a4);
  
  CGAL_Planar_map_2<pmdcel,pmtraits>::Halfedge e[5];  
  // insert the five curves to the map and return e[i]
  for (i = 0; i < 5; i++)
  {
    e[i]=pm.insert(cv[i]);
  }
  
  //map before splitting the edge and adding curve
  cout << "Map before:" << endl;
  cout << pm << endl;
  

  //splitting e[2] of the map at the middle and inserting an edge between the 
  // new vertex and the vertex at a1
  point p(100, 50);
  curve c1(a2,p);
  curve c2(p,a3);

  CGAL_Planar_map_2<pmdcel,pmtraits>::Halfedge se = pm.split_edge(e[2],c1,c2); 

  pm.insert_at_vertices( curve(p,a1), se.target(),e[0].source() );

  cout << "Map after:" << endl;
  cout << pm;

  return 0;  
}














