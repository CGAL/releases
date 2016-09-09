
#include <CGAL/basic.h>
#include <CGAL/Integer.h>
#include <CGAL/Real.h>

#ifdef CARTESIAN
#include <CGAL/Double_eps.h>
#include <CGAL/Cartesian.h>
#else
#include <CGAL/Homogeneous.h>
#endif // CARTESIAN

#include <CGAL/Point_2.h>
#include <CGAL/Circle_2.h>

#include <CGAL/Aff_transformation_2.h>
#include <CGAL/IO/ostream_2.h>
#include <CGAL/IO/Window_stream.h>

#include <CGAL/_test_pvd_2.cc>
#include <CGAL/_test_fct_point_line_2.cc>
#include <CGAL/_test_fct_direction_2.cc>

#include <CGAL/_test_cls_circle_2.cc>




#ifdef __GNUG__
#ifndef CARTESIAN
template 
  integer 
  operator*(CGAL_VectorH2<CGAL_Quotient<integer>,integer> const &, 
            integer const &);
/*
template class CGAL_Quotient<integer>;
template double CGAL_to_double(CGAL_Quotient<integer> const &);
template bool CGAL_is_finite(CGAL_Quotient<integer> const &);
template 
  real 
  operator*(CGAL_VectorH3<CGAL_Quotient<real>,real> const &, real const &);
*/
#endif // CARTESIAN
#endif // __GNUG__


  
main()
{
  
#ifdef CARTESIAN
 typedef  CGAL_Cartesian<CGAL_Double_eps>  Rep_Cls;
 CGAL_set_eps(0.0000001);

#else
 typedef  CGAL_Homogeneous<integer>  Rep_Cls;
#endif // CARTESIAN
 return  
     CGAL__test_pvd_2( Rep_Cls() )
     && CGAL__test_fct_point_line_2( Rep_Cls() )
     && CGAL__test_cls_circle_2( Rep_Cls() )
 ;
}

