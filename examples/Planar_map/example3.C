/*******************************************************************/
/* This is an example program for the Planar Map package           */
/* Tests the point location in various possibilities               */
/*******************************************************************/
/* By:   Doron Jacoby                                              */
/*       Iddo Hanniel < hanniel@math.tau.ac.il>                    */
/*******************************************************************/
#include <CGAL/Cartesian.h>
#include <CGAL/Pm_segment_epsilon_traits.h>
#include <CGAL/Pm_default_dcel.h>
#include <CGAL/Planar_map_2.h>


typedef CGAL_Cartesian<double>                        coord_t;
typedef CGAL_Pm_segment_epsilon_traits<coord_t>       pmtraits;
typedef pmtraits::Point                               point;
typedef pmtraits::X_curve                             curve;
typedef CGAL_Pm_default_dcel<pmtraits>                pmdcel;

typedef CGAL_Planar_map_2<pmdcel,pmtraits>   planar_map;
typedef planar_map::Halfedge	Halfedge;
typedef planar_map::Locate_type Locate_type;
typedef planar_map::Ccb_halfedge_circulator Ccb_halfedge_circulator;

// use only for this program
void draw_point_locate(point &, planar_map&);
// end part of use only for this program

int main()
{
	// creating an instance of CGAL_Planar_map_2<pmdcel,pmtraits>
	planar_map pm;

	curve cv[18];
	int i;

	CGAL_set_ascii_mode(cout);

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
   
	  cout << "the curves of the map :" << endl; 
	  for (i = 0; i < 18; i++)
		cout << cv[i] << endl;

	  cout << endl;

  // insert the curves to the map
	cout << "inserting the curves to the map..." << endl;
	for (i = 0; i < 18; i++)
	{
		  pm.insert(cv[i]);
	}


  // check the validity of the map
	cout << "check map validity... ";
	if (pm.is_valid())
		cout << "map valid!" << endl;
	else{
		cout << "map invalid!" << endl;
		return 1;
	}
	cout << endl;
  
  // draw the map 
	cout << "    1  3 4  6  8 9 11		 " << endl;
	cout << "								 " << endl;
	cout << "           a12            9             "<< "a1(" << a1 << ")  a2(" << a2 << ")  a3(" << a3 << ")" << endl;        
	cout << "           *  *           8             "<< "a4(" << a4 << ")  a5(" << a5 << ")  a6(" << a6 << ")" << endl;
	cout << "    a8===a9===a10==a11    7             "<< "a7(" << a7 << ")  a8(" << a8 << ")  a9(" << a9 << ")" << endl;
	cout << "     *  *       *  *      6             "<< "a10(" << a10 << ")  a11(" << a11 << ")  a12(" << a12 << ")" << endl;
	cout << "      a6         a7       5" << endl;
	cout << "     *  *       *  *      4" << endl;
	cout << "    a2===a3===a4==a5      3" << endl;
	cout << "          *   *           2" << endl;
	cout << "           a1             1" << endl;

  // try to find some point locations
	draw_point_locate( point(6,1) , pm );
	draw_point_locate( point(2,3) , pm );
	draw_point_locate( point(6,8) , pm );

        cout << endl ;

        cout << "Enter x coordinate for point location:" << endl;
        double x;
        cin >> x;
        cout << "Enter y coordinate for point location:" << endl;
        double y;
        cin >> y;
        
        draw_point_locate( point(x,y) ,pm );

        //        cout << endl << pm;
        

	return 0;

}

void draw_point_locate(point & p, planar_map & pm){
	Locate_type lt;	
	Halfedge edge  = pm.locate( p,  lt);
	Ccb_halfedge_circulator ccb;
	cout << "The location of point " << p << " is of type " << lt << endl;
	switch ( lt ) {
	case CGAL_Planar_map_2<pmdcel,pmtraits>::VERTEX	:	
		 cout << "The vertex is : " << edge.source() << endl;
		 break;
	case CGAL_Planar_map_2<pmdcel,pmtraits>::EDGE	:
 		 cout << "The edge is : " << edge << endl;
		 break;
	case CGAL_Planar_map_2<pmdcel,pmtraits>::FACE	:
		ccb = Ccb_halfedge_circulator(edge);
		cout << "The face is : " << ccb << endl;
		break;
	case CGAL_Planar_map_2<pmdcel,pmtraits>::UNBOUNDED_FACE	:
		break;
	}


}






