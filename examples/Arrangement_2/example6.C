//the following example creates an arrangement with a walk point location
//with the cached info traits class. You can see the difference between
//the regular exact traits and the cached traits by replacing the relevant 
//lines with the commented lines.
//NOTE: if you want to run this example with different numbers
//(even slightly larger numbers), use a
//multiple precision integer (e.g., gmpz or leda_integer). Otherwise there
//will be an overflow and the program will go into an infinite loop.

//example6.C

// Define shorter names to please linker (g++/egcs)
#define Arrangement_2 Ar
#define _In_place_list_iterator IPLI
#define Homogeneous Ho
#define Arr_segment_exact_cached_traits ASECT
#define Arr_segment_exact_traits ASET

#include <CGAL/Homogeneous.h>
#include <CGAL/Arr_2_bases.h>
#include <CGAL/Arr_2_default_dcel.h>
#include <CGAL/Arr_segment_exact_cached_traits.h>
//#include <CGAL/Arr_segment_exact_traits.h>
#include <CGAL/Arrangement_2.h>
#include <CGAL/Pm_walk_along_line_point_location.h>

//#include <CGAL/leda_integer.h>
//typedef leda_integer                              NT;
typedef long                                        NT;

typedef CGAL::Homogeneous<NT>                            R;

typedef CGAL::Arr_segment_exact_cached_traits<R>      Traits;
//typedef CGAL::Arr_segment_exact_traits<R>      Traits;

typedef Traits::Point                                 Point;
typedef Traits::X_curve                               X_curve;
typedef Traits::Curve                                 Curve;

typedef CGAL::Arr_base_node<Curve>                     Base_node;
typedef CGAL::Arr_2_default_dcel<Traits>               Dcel;
typedef CGAL::Arrangement_2<Dcel,Traits,Base_node >    Arr_2;

using namespace std;

int main() {
  CGAL::Pm_walk_along_line_point_location<Arr_2::Planar_map> pl;

  Arr_2 arr(&pl);

  //insertion of the curves
  Arr_2::Curve_iterator cit=arr.insert(Curve(Point(0,0),Point(3,3)));
  cit=arr.insert(Curve(Point(0,3),Point(3,0))); 
  cit=arr.insert(Curve(Point(0,1),Point(3,1)));

  CGAL_assertion(arr.number_of_halfedges()==18);
  

  //traversal of the curves
  Arr_2::Edge_iterator eit;
  for (cit=arr.curve_node_begin(); cit!=arr.curve_node_end(); ++cit) {
    cout << "\nCurve level:\n" << cit->curve() << endl ;
    cout << "Edge level:\n";
    for (eit=cit->edges_begin(); eit!=cit->edges_end(); ++eit) {
      cout << eit->curve() << endl ;
    }
  }
  return 0;
}

















