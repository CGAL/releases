#line 494 "/u/sargas/2/prisme/fabri/Cgal/Kernel/web/test_kernel_3.fw"
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL__TEST_PVD_3_CC
#define CGAL__TEST_PVD_3_CC

#include <CGAL/_test_cls_vector_3.cc>
#include <CGAL/_test_fct_vector_3.cc>
#include <CGAL/_test_cls_point_3.cc>
#include <CGAL/_test_fct_point_vector_3.cc>
#include <CGAL/_test_fct_point_3.cc>
#include <CGAL/_test_cls_direction_3.cc>

template <class R>
bool
CGAL__test_pvd_3(const R& r)
{
 return 
    CGAL__test_cls_vector_3(r)
 && CGAL__test_fct_vector_3(r)
 && CGAL__test_cls_point_3(r)
 && CGAL__test_fct_point_vector_3(r)
 && CGAL__test_fct_point_3(r)
 && CGAL__test_cls_direction_3(r) ;
}
#endif // CGAL__TEST_PVD_3_CC
