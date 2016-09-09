
// A test example
#include <CGAL/basic.h>
#include <CGAL/Integer.h>
// #include <CGAL/Real.h>

#ifdef CARTESIAN
#include <CGAL/Double_eps.h>
#include <CGAL/Cartesian.h>
#else
#include <CGAL/Homogeneous.h>
#endif // CARTESIAN


// includes of the definitions of the testfunctions
#include <CGAL/_test_pvd_3.cc>
#include <CGAL/_test_cls_plane_3.cc>
#include <CGAL/_test_cls_line_3.cc>
#include <CGAL/_test_cls_segment_3.cc>
#include <CGAL/_test_cls_ray_3.cc>
#include <CGAL/_test_cls_triangle_3.cc>
#include <CGAL/_test_cls_tetrahedron_3.cc>

#ifdef __GNUG__
// some explicit instantiantions that g++ doesn't create otherwise, e.g.
template double CGAL_to_double(CGAL_Quotient<integer> const &);
template bool CGAL_is_finite(CGAL_Quotient<integer> const &);
#endif // __GNUG__


#ifdef CARTESIAN


#include <strstream.h>
#include <CGAL/Point_3.h>
#include <CGAL/Line_3.h>
#include <CGAL/Plane_3.h>
#include <CGAL/IO/ostream_3.h>

char *db_pretty_print(const CGAL_Double_eps *p,
                      int ,
                      char *)
{


  ostrstream os;

  os << p->d() << ends ;

  return os.str();
}
#endif // CARTESIAN


main()
{
#ifdef CARTESIAN
 typedef  CGAL_Cartesian<CGAL_Double_eps>  Rep_Cls;
 CGAL_set_eps(0.0000001);

#else
 typedef  CGAL_Homogeneous<integer>  Rep_Cls;
#endif // CARTESIAN
 return 
    CGAL__test_pvd_3( Rep_Cls() )
 && CGAL__test_cls_plane_3( Rep_Cls() )
 && CGAL__test_cls_line_3( Rep_Cls() )
 && CGAL__test_cls_segment_3( Rep_Cls() )
 && CGAL__test_cls_ray_3( Rep_Cls() )
 && CGAL__test_cls_triangle_3( Rep_Cls() )
 && CGAL__test_cls_tetrahedron_3( Rep_Cls() )
 ;
}


