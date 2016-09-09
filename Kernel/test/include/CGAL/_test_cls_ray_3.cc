#line 932 "/u/sargas/2/prisme/fabri/Cgal/Kernel/web/test_kernel_3.fw"
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL__TEST_CLS_RAY_3_CC
#define CGAL__TEST_CLS_RAY_3_CC
#include <CGAL/_test_cls_ray_3.h>

template <class R>
bool
CGAL__test_cls_ray_3(const R& )
{
 cout << "Testing class Ray_3" ;
 
 R::Ray_3 ir;
 CGAL_Ray_3<R>  r1(ir);
 
 R::RT  n1 =  8;
 R::RT  n2 = 20;
 R::RT  n3 =  4;
 R::RT  n4 = 10;
 R::RT  n5 =  5;
 R::RT  n6 = 20;
 R::RT  n7 = -2;
 R::RT  n8 =  3;

 CGAL_Point_3<R> p1( n1, n2, n3, n3);
 CGAL_Point_3<R> p2( n4, n5, n6, n5);
 CGAL_Point_3<R> p3( n7, n2, n4, n7);

 CGAL_Ray_3<R> r2( p1, p2 );
 CGAL_Ray_3<R> r3( p2, p1 );
 CGAL_Ray_3<R> r4( r2 );
 r1 = r4;
 CGAL_Direction_3<R> dir( p2 - p1 );
 CGAL_Ray_3<R> r7(p1, dir);

 assert( r1 == r1 );
 assert( r4 == r2 );
 assert( r1 == r4 );
 assert( r1 == r2 );
 assert( r7 == r2 );
 assert( r2 != r3 );

 cout <<'.';

 CGAL_Ray_3<R> r5 (p3, p3 + (p1 - p3) );
 assert( r5.has_on( p1 ) );
 assert( r5.has_on( p3 ) );
 assert( r5.has_on( p3 + (p1 - p3) ) );
 assert( r3.has_on( p2 + (p1 - p2) + (p1 - p2) ) );
 assert( r2.has_on( r2.second_point() ));
 assert( r5.has_on( r5.second_point() ));
 assert( r4.has_on( r4.point(1) ));
 assert( r4.has_on( r4.point(3) ));

 cout <<'.';

 assert( r5.source() == p3 );
 assert( r2.source() != r3.source() );
 assert( r7.direction() == dir );
 assert( r2.direction() == CGAL_Direction_3<R>(r2.point(2) - r2.point(1) ));
 assert( r2.direction() == r3.opposite().direction() );
 assert( r1.supporting_line() == r2.supporting_line() );
 CGAL_Line_3<R> lin(p1,p2);
 assert( r2.supporting_line() == lin );

 cout << '.';

 CGAL_Ray_3<R> r8( p3, dir );
 CGAL_Ray_3<R> r9( p3, -dir );
 assert( r8.opposite() == r9 );
 assert( r9.opposite() == r8 );
 CGAL_Ray_3<R> sdeg(p3,p3);
 assert( sdeg.is_degenerate() );

 cout << "done" << endl;
 return true;
}

#endif // CGAL__TEST_CLS_RAY_3_CC
