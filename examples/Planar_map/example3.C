/*******************************************************************/
/* This is an example program for the Planar Map package           */
/* Tests the point location in various possibilities               */
/* It also demonstrates the usage of const iterators and const     */
/* circulators when passing a const referance to a planar map      */
/*******************************************************************/
/* By:   Doron Jacoby                                              */
/*       Iddo Hanniel < hanniel@math.tau.ac.il>                    */
/*******************************************************************/


#include <CGAL/Cartesian.h>
#include <CGAL/Pm_segment_epsilon_traits.h>
#include <CGAL/Pm_default_dcel.h>
#include <CGAL/Planar_map_2.h>


typedef CGAL::Cartesian<double>                        coord_t;
typedef CGAL::Pm_segment_epsilon_traits<coord_t>       pmtraits;
//typedef CGAL::Pm_segment_epsilon_traits<coord_t,1,4>       pmtraits;
typedef pmtraits::Point                               point;
typedef pmtraits::X_curve                             curve;
typedef CGAL::Pm_default_dcel<pmtraits>                pmdcel;

typedef CGAL::Planar_map_2<pmdcel,pmtraits>   planar_map;
typedef planar_map::Halfedge_handle	Halfedge_handle;
typedef planar_map::Halfedge_const_handle	Halfedge_const_handle;
typedef planar_map::Locate_type Locate_type;
typedef planar_map::Ccb_halfedge_circulator Ccb_halfedge_circulator;
typedef planar_map::Ccb_halfedge_const_circulator Ccb_halfedge_const_circulator;

// use only for this program
void draw_point_locate(const point &, const planar_map&);
// end part of use only for this program

int main()
{
	// creating an instance of CGAL::Planar_map_2<pmdcel,pmtraits>
	planar_map pm;

	curve cv[18];
	int i;

	CGAL::set_ascii_mode(std::cout);

	point a1(6, 1), a2(1, 3), a3(4, 3), a4(8, 3), a5(11,3) ;
	point a6(3, 5), a7(9, 5), a8(1, 7), a9(4, 7), a10(8,7) ;
	point a11(11, 7), a12(6, 9);

	// those curves are about to enter to pm
	cv[0] = curve(a1, a3);
	cv[1] = curve(a1, a4);
	cv[2] = curve(a2, a3);
	cv[3] = curve(a2, a6);
	cv[4] = curve(a3, a6);
	cv[5] = curve(a3, a4);
	cv[6] = curve(a4, a5);
	cv[7] = curve(a4, a7);
	cv[8] = curve(a5, a7);
	cv[9] = curve(a6, a8);
	cv[10] = curve(a6, a9);
	cv[11] = curve(a7, a10);
	cv[12] = curve(a7, a11);
	cv[13] = curve(a8, a9);
	cv[14] = curve(a9, a10);
	cv[15] = curve(a9, a12);
	cv[16] = curve(a10, a11);
	cv[17] = curve(a10, a12);
   
	  std::cout << "the curves of the map :" << std::endl; 
	  for (i = 0; i < 18; i++)
		std::cout << cv[i] << std::endl;

	  std::cout << std::endl;

  // insert the curves to the map
	std::cout << "inserting the curves to the map..." << std::endl;
	for (i = 0; i < 18; i++)
          pm.insert(cv[i]);

  // check the validity of the map
	std::cout << "check map validity... ";
	if (pm.is_valid())
		std::cout << "map valid!" << std::endl;
	else{
		std::cout << "map invalid!" << std::endl;
		return 1;
	}
	std::cout << std::endl;
  
  // draw the map 
	std::cout << "    1  3 4  6  8 9 11		 " << std::endl;
	std::cout << "								 " << std::endl;
	std::cout << "           a12            9             "<< "a1(" << a1 << ")  a2(" << a2 << ")  a3(" << a3 << ")" << std::endl;        
	std::cout << "           *  *           8             "<< "a4(" << a4 << ")  a5(" << a5 << ")  a6(" << a6 << ")" << std::endl;
	std::cout << "    a8===a9===a10==a11    7             "<< "a7(" << a7 << ")  a8(" << a8 << ")  a9(" << a9 << ")" << std::endl;
	std::cout << "     *  *       *  *      6             "<< "a10(" << a10 << ")  a11(" << a11 << ")  a12(" << a12 << ")" << std::endl;
	std::cout << "      a6         a7       5" << std::endl;
	std::cout << "     *  *       *  *      4" << std::endl;
	std::cout << "    a2===a3===a4==a5      3" << std::endl;
	std::cout << "          *   *           2" << std::endl;
	std::cout << "           a1             1" << std::endl;

  // try to find some point locations
	draw_point_locate( point(6,1) , pm );
	draw_point_locate( point(2,3) , pm );
	draw_point_locate( point(6,8) , pm );
        std::cout << std::endl ;

        std::cout << "Enter x coordinate for point location:" << std::endl;
        double x;
        std::cin >> x;
        std::cout << "Enter y coordinate for point location:" << std::endl;
        double y;
        std::cin >> y;
        
        draw_point_locate( point(x,y) ,pm );

        //        std::cout << std::endl << pm;

	return 0;

}

void draw_point_locate(const point & p, const planar_map & pm){
	Locate_type lt;	
        Halfedge_const_handle edge  = pm.locate( p,  lt);
	Ccb_halfedge_const_circulator curr,first;
        std::cout << "The location of point " << p << " is of type " ;
	switch ( lt ) {
	case CGAL::Planar_map_2<pmdcel,pmtraits>::VERTEX	:	
          std::cout << "VERTEX" << std::endl;
          std::cout << "The vertex is : (" << edge->target()->point() << ")" << std::endl;
          break;
	case CGAL::Planar_map_2<pmdcel,pmtraits>::EDGE	:
          std::cout << "EDGE" << std::endl;
 		 std::cout << "The edge is : {(" << edge->source()->point() ;
                 std::cout<< ")->(" << edge->target()->point() << ")}" << std::endl;
		 break;
	case CGAL::Planar_map_2<pmdcel,pmtraits>::FACE	:
                 first = Ccb_halfedge_const_circulator(edge);
                 curr=first;
                std::cout << "FACE" << std::endl;
		std::cout << "The face is : " ;
                std::cout << "[" ;
                do {
                  std::cout << "(" << curr->target()->point() << ")-" ;
                  ++curr;
                }while (curr!=first) ;
                  std::cout << "(" << curr->target()->point() << ")]" << std::endl;
		break;
	case CGAL::Planar_map_2<pmdcel,pmtraits>::UNBOUNDED_FACE	:
          std::cout << "UNBOUNDED_FACE" << std::endl;
		break;
	}


}






