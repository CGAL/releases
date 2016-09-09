#line 379 "/u/sargas/2/prisme/fabri/Cgal/Kernel/web/test_kernel_3.fw"
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL__TEST_FCT_POINT_3_CC
#define CGAL__TEST_FCT_POINT_3_CC
#include <CGAL/_test_fct_point_3.h>

template <class R>
bool
CGAL__test_fct_point_3(const R& )
{
 cout << "Testing functions Point_3" ;

 CGAL_Point_3<R> p1( R::RT(18), R::RT(15), R::RT(-21), R::RT(3) );
 CGAL_Point_3<R> p2( R::RT(18), R::RT(15), R::RT( 12), R::RT(3) );
 CGAL_Point_3<R> p3( R::RT(18), R::RT(12), R::RT(-21), R::RT(3) );
 CGAL_Point_3<R> p4( R::RT(28), R::RT(40), R::RT( 20), R::RT(4) );
 CGAL_Point_3<R> p5( R::RT(12), R::RT(-4), R::RT(-20), R::RT(4) );

 assert( CGAL_compare_lexicographically_xyz(p1,p2) == CGAL_SMALLER );
 assert( CGAL_compare_lexicographically_xyz(p3,p2) == CGAL_SMALLER );
 assert( CGAL_compare_lexicographically_xyz(p3,p1) == CGAL_SMALLER );
 assert( CGAL_compare_lexicographically_xyz(p3,p2) == CGAL_SMALLER );
 assert( CGAL_compare_lexicographically_xyz(p2,p1) == CGAL_LARGER );
 assert( CGAL_compare_lexicographically_xyz(p2,p3) == CGAL_LARGER );
 assert( CGAL_compare_lexicographically_xyz(p4,p3) == CGAL_LARGER );
 assert( CGAL_compare_lexicographically_xyz(p4,p4) == CGAL_EQUAL );

 assert( CGAL_lexicographically_xyz_smaller_or_equal(p1,p1) );
 assert( CGAL_lexicographically_xyz_smaller_or_equal(p3,p1) );
 assert( CGAL_lexicographically_xyz_smaller_or_equal(p3,p2) );
 assert( CGAL_lexicographically_xyz_smaller_or_equal(p3,p4) );

 assert( !CGAL_lexicographically_xyz_smaller(p3,p3) );
 assert( CGAL_lexicographically_xyz_smaller(p3,p2) );
 assert( !CGAL_lexicographically_xyz_smaller(p4,p3) );

 assert( CGAL_x_equal(p1,p1) );
 assert( CGAL_x_equal(p2,p3) );
 assert( !CGAL_x_equal(p2,p4) );

 assert( CGAL_y_equal(p1,p2) );
 assert( !CGAL_y_equal(p1,p3) );

 assert( CGAL_z_equal(p1,p3) );
 assert( !CGAL_z_equal(p4,p5) );

 cout <<'.';

 CGAL_Point_3<R> p6 ( R::RT(6), R::RT(4), R::RT(7) );
 assert( CGAL_coplanar( p1, p2, p3, p6) );
 assert( CGAL_coplanar( p1, p1, p3, p4) );
 assert( CGAL_coplanar( p4, p1, p5, p5 + (p4-p1) ) );
 assert( !CGAL_coplanar( p4, p1, p2, p3 ) );
 
 assert( !CGAL_collinear( p1, p2, p3 ) );
 assert( CGAL_collinear( p1, p2, p2 + (p2-p1) ) );

 assert( CGAL_between( p1, p2 + (p2-p1), p2 ) );
 assert( !CGAL_between( p1, p2, p2 + (p2-p1)) );
 assert( !CGAL_between( p1, p2, p5 ) );

 assert( CGAL_collinear_between( p1, p2 + (p2-p1), p2 ) );
 assert( !CGAL_collinear_between( p1, p2, p2 + (p2-p1)) );

 cout << '.';

 CGAL_Point_3<R> pe0( R::RT(1), R::RT(0), R::RT(0) );
 CGAL_Point_3<R> pe1( R::RT(0), R::RT(1), R::RT(0) );
 CGAL_Point_3<R> pe2( R::RT(0), R::RT(0), R::RT(1) );

 assert( CGAL_orientation( CGAL_Point_3<R>(CGAL_ORIGIN), pe0, pe1, pe2 ) \
                           == CGAL_POSITIVE);

 assert( CGAL_orientation( p1, p2, p3, p6 ) == CGAL_ZERO );

 CGAL_Point_3<R> p7( R::RT(-8), R::RT(0), R::RT(0), R::RT(-2) );
 CGAL_Point_3<R> p8( R::RT(8), R::RT(4), R::RT(0), R::RT(2) );
 CGAL_Point_3<R> p9( R::RT(0), R::RT(12), R::RT(0), R::RT(4) );
 
 assert( CGAL_orientation( p7, p8, p9, p4) == CGAL_POSITIVE );
 assert( CGAL_orientation( p7, p9, p8, p5) == CGAL_POSITIVE );
 assert( CGAL_orientation( p7, p8, p9, p5) == CGAL_NEGATIVE );
 assert( CGAL_orientation( p8, p7, p9, p4) == CGAL_NEGATIVE );

 cout <<'.';

 CGAL_Point_3<R> p10( R::RT(0), R::RT(0), R::RT(16), R::RT(8) );

#ifdef CGAL_CARTESIAN // not yet implemented for HOMOGENEOUS

 assert( CGAL_side_of_bounded_sphere(p7,p8,p9,p10,p1) ==CGAL_ON_UNBOUNDED_SIDE);
 assert( CGAL_side_of_bounded_sphere(p7,p8,p9,p10,p1) ==CGAL_ON_UNBOUNDED_SIDE);

 CGAL_Point_3<R> p0(CGAL_ORIGIN);

 assert( CGAL_side_of_bounded_sphere(p7,p8,p9,p10,p0) ==CGAL_ON_BOUNDED_SIDE);

 CGAL_Vector_3<R> v001( R::RT(0), R::RT(0), R::RT(1) );
 CGAL_Vector_3<R> v010( R::RT(0), R::RT(1), R::RT(0) );
 CGAL_Vector_3<R> v100( R::RT(1), R::RT(0), R::RT(0) );
 
 assert( CGAL_side_of_bounded_sphere(p3 + v001, p3-v001, p3+v010, p3-v010, \
                                     p3 + v100) == CGAL_ON_BOUNDARY );

#endif // CGAL_CARTESIAN

 cout << "done" << endl;
 return true;
}
#endif // CGAL__TEST_FCT_POINT_3_CC
