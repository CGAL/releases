#line 309 "/u/sargas/2/prisme/fabri/Cgal/Kernel/web/test_kernel_2.fw"
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL__TEST_FCT_POINT_VECTOR_2_CC
#define CGAL__TEST_FCT_POINT_VECTOR_2_CC
#include <CGAL/_test_fct_point_vector_2.h>

template <class R>
bool
CGAL__test_fct_point_vector_2(const R& )
{
 cout << "Testing functions Point_2 Vector_2" ;

 R::RT  n1( 12 );
 R::RT  n2( -4 );
 R::RT  n3(  6 );
 R::RT  n4(  2 );
 R::RT  n5(  9 );
 R::RT  n6(-18 );
 R::RT  n7( 36 );
 R::RT  n8(  3 );
 R::RT  n9( 15 );
 R::RT n10( -8 );

 CGAL_Vector_2<R>  v0(CGAL_NULL_VECTOR);
 CGAL_Vector_2<R>  v1(n1, n2, n4);
 CGAL_Vector_2<R>  v2(n5, n6, n8);
 CGAL_Vector_2<R>  v3(n5, n10);
 CGAL_Vector_2<R>  v4(n8, -n2);

 cout << '.';

 CGAL_Point_2<R> p0(CGAL_ORIGIN);
 CGAL_Point_2<R> p1 = CGAL_ORIGIN + v1;
 CGAL_Point_2<R> p2 = CGAL_ORIGIN + v2;
 CGAL_Point_2<R> p3 = CGAL_ORIGIN + v3;

 assert( CGAL_ORIGIN + v2 == CGAL_Point_2<R>( n5, n6, n8) );
 assert( CGAL_ORIGIN - v2 == CGAL_Point_2<R>( -n5, -n6, n8) );
 assert( p1 - p1 == v0 );
 assert( p1 - p0 == p1 - CGAL_ORIGIN);
 assert( p1 - p2 == v4 );
 assert( p2 + v4 == p1 );
 assert( p3 - v1 == p2 );
 assert( p3 - p1 == v2 );

 cout << "..";
 cout << "done" << endl;
 return true;
}
#endif // CGAL__TEST_FCT_POINT_VECTOR_2_CC
