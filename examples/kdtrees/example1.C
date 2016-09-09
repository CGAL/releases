/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
 * example1.C -
 *    Simple example the CGAL KD-tree module.
 *
 * Written by Sariel Har-Peled 
 *            Iddo Hanniel
\*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
 
//might be needed when compiling with g++-2.7.2
//#ifdef  __GNUG__ 
//#include  <typeinfo>
//#endif  /* __GNUG__ */ 

#include  <iostream.h>
#include  <time.h>
#include  <assert.h>

#include  <CGAL/Cartesian.h>
#include  <CGAL/Point_2.h>

#include  <list.h>

#include  <CGAL/kdtree_d.h>

typedef CGAL_Point_2<CGAL_Cartesian<double> >  point;
typedef CGAL_Kdtree_interface_2d<point>  kd_interface;
typedef CGAL_Kdtree_d<kd_interface>  kd_tree;
typedef kd_tree::Box  box;
typedef list<point>  points_list; 

int   main()
{

    CGAL_Kdtree_d<kd_interface>  tree(2);
    points_list  l , res;

    srand( (unsigned)time(NULL) );

    cout << "Insering evenly 81 points  in the square (0,0)-(10,10) ...\n\n" ;
    for (int i=1; i<10; i++)
      for (int j=1; j<10; j++)
        {
          point p(i,j);
          l.push_front(p);
        }

    // building the tree for the random points
    tree.build( l );
       
    //checking validity
    if  ( ! tree.is_valid() )
        tree.dump();
    assert( tree.is_valid() );

    
    //defining and searching the box r
    double lx,ly,rx,ry;
    cout << "Define your query square.\nEnter left x coordinate: " ;
    cin >> lx ;
    cout << "Enter left y coordinate: ";
    cin >> ly;
    cout << "Enter right x coordinate: " ;
    cin >> rx ;
    cout << "Enter right y coordinate: ";
    cin >> ry;
    cout << endl; 

    box r(point(lx,ly), point(rx,ry) ,2);

    tree.search( back_inserter( res ), r );
    
    cout << "Listing of the points in the square: \n" ;
    copy (res.begin(),res.end(),ostream_iterator<point>(cout," \n") );
    cout << endl;

    tree.delete_all();

    

    return  0;
}

