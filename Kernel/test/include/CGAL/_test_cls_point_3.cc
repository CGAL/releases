#line 232 "/u/sargas/2/prisme/fabri/Cgal/Kernel/web/test_kernel_3.fw"
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL__TEST_CLS_POINT_3_CC
#define CGAL__TEST_CLS_POINT_3_CC
#include <CGAL/_test_cls_point_3.h>

template <class R>
bool
CGAL__test_cls_point_3(const R& )
{
 cout << "Testing class Point_3" ;

 R::Point_3       ip;

 CGAL_Point_3<R>  p1;
 CGAL_Point_3<R>  p2(ip);
 CGAL_Point_3<R>  p0(CGAL_ORIGIN);

 R::RT  n1(-35 );
 R::RT  n2( 50 );
 R::RT  n3(-20 );
 R::RT  n4(  5 );

 CGAL_Point_3<R>  p3(n1, n2, n3);
 CGAL_Point_3<R>  p4(n1, n2, n3, n4);
 CGAL_Point_3<R>  p5(n1, n2, n3, n4);
 CGAL_Point_3<R>  p6( p5 );
                  p1 = p4;
 
 cout << '.';

 assert( p4 == p5 );
 assert( p5 == p6 );
 assert( p4 == p6 );
 assert( p1 == p6 );
 assert( p0 == CGAL_ORIGIN);

 assert( p3 != p4 );
 assert( p0 != p1 );
 assert( p1 != CGAL_ORIGIN);

 assert( p3.hx() == n1 );   // don't replace p3 
 assert( p3.hy() == n2 );
 assert( p3.hz() == n3 );

 assert( R::FT(p5.hx()) / R::FT(p5.hw()) == R::FT( n1) / R::FT( n4) );
 assert( R::FT(p5.hy()) / R::FT(p5.hw()) == R::FT( n2) / R::FT( n4) );
 assert( R::FT(p5.hz()) / R::FT(p5.hw()) == R::FT( n3) / R::FT( n4) );
 
 assert( p5.x() == R::FT( n1) / R::FT( n4 ) );
 assert( p5.y() == R::FT( n2) / R::FT( n4 ) );
 assert( p5.z() == R::FT( n3) / R::FT( n4 ) );
 
 cout << '.';

 assert( p3.homogeneous(0) == p3.hx() );  // don't replace p3 
 assert( p3.homogeneous(1) == p3.hy() );
 assert( p3.homogeneous(2) == p3.hz() );
 assert( p3.homogeneous(3) == p3.hw() );
 assert( p6.cartesian(0) == p6.x() ); 
 assert( p6.cartesian(1) == p6.y() );
 assert( p6.cartesian(2) == p6.z() );

 cout << '.';

 assert( p0.dimension() == 3 );

 cout << "done" << endl;
 return true;
}
#endif // CGAL__TEST_CLS_POINT_3_CC
