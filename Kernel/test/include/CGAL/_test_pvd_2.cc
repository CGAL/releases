#line 553 "/u/sargas/2/prisme/fabri/Cgal/Kernel/web/test_kernel_2.fw"
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL__TEST_PVD_2_CC
#define CGAL__TEST_PVD_2_CC

#include <CGAL/_test_cls_vector_2.cc>
#include <CGAL/_test_fct_vector_2.cc>
#include <CGAL/_test_cls_point_2.cc>
#include <CGAL/_test_fct_point_vector_2.cc>
#include <CGAL/_test_fct_point_2.cc>
#include <CGAL/_test_cls_direction_2.cc>

template <class R>
bool
CGAL__test_pvd_2(const R& r)
{
 return 
    CGAL__test_cls_vector_2(r)
 && CGAL__test_fct_vector_2(r)
 && CGAL__test_cls_point_2(r)
 && CGAL__test_fct_point_vector_2(r)
 && CGAL__test_fct_point_2(r)
 && CGAL__test_cls_direction_2(r)
 && CGAL__test_fct_direction_2(r)
 ;
}
#endif // CGAL__TEST_PVD_2_CC
