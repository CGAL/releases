#include <CGAL/basic.h>
#include <stdio.h>
#include <string.h>
#include <iostream.h>
#include <fstream.h>
#include <strstream.h>


#include <CGAL/Fixed_precision_nt.h>
#include <CGAL/Timer.h>

#include <CGAL/Cartesian.h>
#include <CGAL/squared_distance_2.h>   // to avoid a g++ problem
#include <CGAL/Point_2.h>

#include <CGAL/Triangulation_euclidean_traits_2.h>

#include <CGAL/Delaunay_triangulation_2.h>

#include <CGAL/point_generators_2.h>

typedef CGAL_Fixed_precision_nt coord_type;
static bool Fixed_precision_nt_init_result
             = CGAL_Fixed_precision_nt::init(2000.0);

typedef CGAL_Cartesian<coord_type>  Rep;

typedef CGAL_Point_2<Rep>  Point_;

typedef CGAL_Triangulation_euclidean_traits_2<Rep> Traits_;
typedef CGAL_Triangulation_vertex_base_2<Traits_> Vb;
typedef CGAL_Triangulation_face_base_2<Traits_>  Fb;
typedef CGAL_Triangulation_default_data_structure_2<Traits_,Vb,Fb> Tds;
typedef CGAL_Delaunay_triangulation_2<Traits_,Tds>  Delaunay_;


int main(int argc, char* argv[])
{
    CGAL_Timer t;
    Delaunay_ D;

    CGAL_Random_points_in_square_2<Point_,
      CGAL_Creator_uniform_2<double,Point_> > Input ( 1.0 );

    int N; if (argc==2) sscanf(argv[1], "%d", &N); 
    else {N=100; cerr<<"usage : "<<argv[0]<<" nb-of-points"<<endl<<endl;}
    cout << "Delaunay of "<<N<<" random points"<<endl;
    t.start();
    while(N--) D.insert( *++Input);
    t.stop();
    cout << " in "<<t.time()<<" seconds"<<endl;
    return 0;
}

