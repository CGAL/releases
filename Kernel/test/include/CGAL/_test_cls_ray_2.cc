#line 1313 "/u/sargas/2/prisme/fabri/Cgal/Kernel/web/test_kernel_2.fw"
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL__TEST_CLS_RAY_2_CC
#define CGAL__TEST_CLS_RAY_2_CC
#include <CGAL/_test_cls_ray_2.h>

template <class R>
bool
CGAL__test_cls_ray_2(const R& )
{
 cout << "Testing class Ray_2";

 R::Ray_2  ir;
 CGAL_Ray_2<R> r0;

 R::RT  n0 = 0;
 R::RT  n2 = 2;
 R::RT  n3 = 3;
 R::RT  n4 = 4;
 R::RT  n5 = 5;
 R::RT  n8 = 8;
 R::RT  n9 = 9;
 R::RT n10 =10;

 CGAL_Point_2<R> p1( n2, n8, n2);
 CGAL_Point_2<R> p2( n10, n4, n2);
 CGAL_Point_2<R> p3( n9, n9, n3);
 CGAL_Point_2<R> p4( n10, n8, n2);
 CGAL_Direction_2<R> d12( p2 - p1);
 CGAL_Direction_2<R> d24( p4 - p2);

 CGAL_Ray_2<R> r1( p1, p2);
 CGAL_Ray_2<R> r2( p1, d12);
 CGAL_Ray_2<R> r3( p3, p2);
 CGAL_Ray_2<R> r4( p2, d24);
 CGAL_Ray_2<R> r5( p2, p4);
 CGAL_Ray_2<R> r6( p1, p4);
 r0 = r3;

 cout << '.';
 
 assert( r1 == r1 );
 assert( r2 == r1 );
 assert( r4 == r5 );
 assert( r0 == r3 );
 assert( r6 != r1 );
 assert( r1 != r3 );
 assert( r1 != r5 );

 assert( r2.source() == p1 );
 assert( r0.source() == p3 );
 assert( r4.source() == r4.point(0) );

 assert( r1.direction() == d12 );
 assert( r2.direction() == d12 );
 assert( r3.direction() == r1.direction() );

 assert( r3.supporting_line() == r1.supporting_line() );
 assert( r5.supporting_line() == CGAL_Line_2<R>( p2, p4 ) );

 assert( r4.opposite() == CGAL_Ray_2<R>( p2, -d24 ) );
 assert( r1.opposite() == CGAL_Ray_2<R>( p1, -d12 ) );
 assert( r2.opposite().opposite() == r2 );

 assert( r6.is_horizontal() );
 assert( ! r0.is_horizontal() );
 assert( r5.is_vertical() );
 assert( ! r5.is_horizontal() );

 assert( r1.has_on( p1 ) );
 assert( r1.has_on( p2 ) );
 assert( r1.has_on( p3 ) );
 assert( r3.opposite().has_on( p1 ) );
 assert( ! r1.has_on( p4 ) );
 assert( ! r0.has_on( CGAL_Point_2<R>( n8, n5, n8 )) );
 assert( r4.has_on( r4.point(7)) );
 assert( r3.collinear_has_on( r3.point(7)) );
 assert( r1.collinear_has_on( p3) );
 assert( ! r3.collinear_has_on( p1 ) );

 assert( CGAL_Ray_2<R>( p1, p1).is_degenerate() );
 assert( ! r0.is_degenerate() );

 cout << "done" << endl; 
 return true;
} 
#endif // CGAL__TEST_CLS_RAY_2_CC
