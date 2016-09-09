#line 1989 "/u/sargas/2/prisme/fabri/Cgal/Kernel/web/test_kernel_2.fw"
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL__TEST_2_CC
#define CGAL__TEST_2_CC

#include <CGAL/_test_cls_vector_2.cc>
#include <CGAL/_test_fct_vector_2.cc>
#include <CGAL/_test_cls_point_2.cc>
#include <CGAL/_test_fct_point_vector_2.cc>
#include <CGAL/_test_fct_point_3.cc>
#include <CGAL/_test_cls_direction_2.cc>
#include <CGAL/_test_fct_direction_2.cc>
#include <CGAL/_test_fct_point_line_2.cc>
#include <CGAL/_test_cls_line_2.cc>
#include <CGAL/_test_cls_segment_2.cc>
#include <CGAL/_test_cls_ray_2.cc>
#include <CGAL/_test_cls_triangle_2.cc>
#include <CGAL/_test_cls_circle_2.cc>
#include <CGAL/_test_cls_iso_rectangle_2.cc>
#include <CGAL/_test_cls_aff_transformation_2.cc>

template <class R>
bool
CGAL__test_3(const R& r)
{
 return 
    CGAL__test_cls_vector_2(r)
 && CGAL__test_fct_vector_2(r)
 && CGAL__test_cls_point_2(r)
 && CGAL__test_fct_point_vector_2(r)
 && CGAL__test_fct_point_2(r)
 && CGAL__test_fct_direction_2( r )
 && CGAL__test_fct_direction_2(r)
 && CGAL__test_fct_point_line_2( r )
 && CGAL__test_cls_line_2( r )
 && CGAL__test_cls_segment_2( r )
 && CGAL__test_cls_ray_2( r )
 && CGAL__test_cls_triangle_2( r )
 && CGAL__test_cls_circle_2( r )
 && CGAL__test_cls_iso_rectangle_2( r )
 && CGAL__test_cls_aff_transformation_2( r )
 ;
}
#endif // CGAL_TEST_2_CC
