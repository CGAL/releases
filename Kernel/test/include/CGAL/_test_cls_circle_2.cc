#line 1032 "/u/sargas/2/prisme/fabri/Cgal/Kernel/web/test_kernel_2.fw"
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL__TEST_CLS_CIRCLE_2_CC
#define CGAL__TEST_CLS_CIRCLE_2_CC
#include <CGAL/_test_cls_circle_2.h>

template <class R>
bool
CGAL__test_cls_circle_2(const R&)
{
 cout << "Testing class Circle_2";

 R::Circle_2  ic;
 CGAL_Circle_2<R> c0;

 R::RT n0 =  0;
 R::RT n1 = 16;
 R::RT n2 = -4;
 R::RT n3 =  2;
 R::RT n4 =  5;
 R::RT n5 = 10;
 R::RT n6 =  6;
 R::RT n8 =  9;
 R::RT n9 = 36;
 R::RT n10=  3;
 R::RT n11=-11;
 R::RT n12=200;
 R::RT n13= 13;

 CGAL_Point_2<R> p0( n1, n2, -n2);  // ( 4, -1)
 CGAL_Point_2<R> p1( n6, n8, n10);  // ( 2,  3)
 CGAL_Point_2<R> p2( n2, n0,  n2);  // ( 1,  0)
 CGAL_Point_2<R> p3( n5, n5,  n4);  // ( 2,  2)
 CGAL_Point_2<R> p4( n0, n2,  n2);  // ( 0,  1)

 CGAL_Vector_2<R> vx = p2 - CGAL_ORIGIN;
 CGAL_Vector_2<R> vy = p4 - CGAL_ORIGIN;
 CGAL_Vector_2<R> v1 = p1 - CGAL_ORIGIN;

 CGAL_Circle_2<R> c1( p0, p1, p2); 
 CGAL_Circle_2<R> c2( p0, p1, p3); 
 CGAL_Circle_2<R> c3( p1, p0, p2); 
 CGAL_Circle_2<R> c4( p3, R::FT( n9 ));      // n9 = (n6)^2
 CGAL_Vector_2<R> vx6 = vx * n6;
 CGAL_Vector_2<R> vy6 = vy * n6;
 CGAL_Circle_2<R> c5( p3 - vx6, p3 + vx6, p3 + vy6);
 CGAL_Circle_2<R> c6( c3 );
 CGAL_Circle_2<R> c7( p3, n9, CGAL_POSITIVE);
 CGAL_Circle_2<R> c8( p3, n9, CGAL_NEGATIVE);
 CGAL_Circle_2<R> cc( p3, p3 + vx6);
 CGAL_Circle_2<R> cp( p3, p3 + vx6, CGAL_POSITIVE);
 CGAL_Circle_2<R> cn( p3, p3 + vx6, CGAL_NEGATIVE);
 c0 = c3;

 assert( c1 == c1 );
 assert( c1 != c2 );
 assert( c3 == c0 );
 assert( c0 == c3 );
 assert( c3 == c6 );
 assert( c7 != c8 );
 assert( c4 == c7 );
 assert( cc == cp );
 assert( cn != cp );
 assert( cc == c7 );

 assert( c5.center() == p3 );
 assert( cc.center() == p3 );
 assert( c5.squared_radius() == R::FT( n9 ) );
 assert( c4.squared_radius() == cc.squared_radius() );
 assert( c4 == c5 );
 assert( c4 == c7 );
 assert( c4 != c8 );
 assert( cn == cp.opposite() );
 assert( c7.opposite() == c8 );
 assert( c8.opposite() == c7 );
 assert( c1.opposite() == c3 );
 assert( c3.opposite() == c1 );
 assert( c7.orientation() == CGAL_POSITIVE );
 assert( c8.orientation() == CGAL_NEGATIVE );
 assert( c5.orientation() == CGAL_POSITIVE );
 assert( cc.orientation() == CGAL_POSITIVE );
 assert( cp.orientation() == CGAL_POSITIVE );
 assert( cn.orientation() == CGAL_NEGATIVE );

 cout << '.';

 assert( c4.center() == p3 );
 assert( c5.center() == p3 );
 assert( c4.squared_radius() == R::FT( n9 ) );
 assert( c5.squared_radius() == R::FT( n9 ) );
 assert( c8.squared_radius() == R::FT( n9 ) );
 
 assert( c7.bounded_side( p3 + vx*n2 ) == CGAL_ON_BOUNDED_SIDE );
 assert( c7.bounded_side( p3 + vy*n11 ) == CGAL_ON_UNBOUNDED_SIDE );
 assert( c7.bounded_side( p3 - vy6 ) == CGAL_ON_BOUNDARY );
 assert( c8.bounded_side( p3 + vx*n2 ) == CGAL_ON_BOUNDED_SIDE );
 assert( c8.bounded_side( p3 + vy*n11 ) == CGAL_ON_UNBOUNDED_SIDE );
 assert( c8.bounded_side( p3 - vy6 ) == CGAL_ON_BOUNDARY );
 assert( cc.has_on_boundary( p3 + vy6) );
 assert( cc.has_on_boundary( p3 - vx6) );

 cout << '.';

 CGAL_Aff_transformation_2<R> 
          rotate1(CGAL_ROTATION,CGAL_Direction_2<R>(n11,n13),-n2,n12), 
          rotate2(CGAL_ROTATION,CGAL_Direction_2<R>(-n8, n9),-n2,n12), 
          rotate3(CGAL_ROTATION,CGAL_Direction_2<R>( n5,-n1),-n2,n12), 
          rotate4(CGAL_ROTATION,CGAL_Direction_2<R>(-n5,-n11),-n2,n12);
 CGAL_Point_2<R> p6 = p2.transform( rotate1 );
 CGAL_Point_2<R> p7 = p2.transform( rotate2 );
 CGAL_Point_2<R> p8 = p2.transform( rotate3 );
 CGAL_Point_2<R> p9 = p2.transform( rotate4 );
 p6 = p6 + v1;  // v1 = ( 2, 3 )
 p7 = p7 + v1;
 p8 = p8 + v1;
 p9 = p9 + v1;
 
 cout << p6 << p8 << p7 << endl;
 CGAL_Circle_2<R> c10 (p6, p8, p7);
 cout << c10 << endl;
 cout <<  p9 << endl;
 
 assert( c10.orientation() == CGAL_POSITIVE );
 assert( c10.opposite().orientation() == CGAL_NEGATIVE );

 assert( c10.oriented_side(c10.center() ) == CGAL_POSITIVE );
 assert( c10.oriented_side(CGAL_ORIGIN + v1 + vx/n2 ) == CGAL_POSITIVE );
 assert( c10.oriented_side(CGAL_ORIGIN + v1 + vx*n2 ) == CGAL_NEGATIVE );

 assert( c10.oriented_side(p9 ) == CGAL_ON_ORIENTED_BOUNDARY );
 assert( c10.has_on_boundary(p9) );
 assert( c10.has_on_boundary(p4 + v1) );
 CGAL_Point_2<R> p11( n4, n4, n3) ; // (2.5, 2.5)
 CGAL_Point_2<R> p12( n5, n5, n3) ; // ( 5 ,  5 )
 assert( c10.has_on_bounded_side( p11 ) );
 assert( ! c10.has_on_bounded_side( p12 ) );
 assert( c10.has_on_unbounded_side( p12 ) );
 assert( c10.has_on_positive_side( p11 ) );
 assert( c10.has_on_negative_side( p12 ) );
 assert( c10.opposite().has_on_negative_side( p11 ) );
 assert( c10.opposite().has_on_positive_side( p12 ) );
 assert( c10.has_on_boundary( p6 ) );
 assert( c10.has_on_boundary( p8 ) );

 cout << '.';

 CGAL_Circle_2<R> c11( p0, p0, p1) ;
 CGAL_Circle_2<R> c12( p1, p1 + v1, p1 + v1 * R::RT(2)) ;
 assert( c11.orientation() == CGAL_ZERO );
 assert( c12.orientation() == CGAL_ZERO );
 assert( c11.is_degenerate() );
 assert( c12.is_degenerate() );

 cout << "done" << endl;
 return true;
}

#endif // CGAL__TEST_CLS_CIRCLE_2_CC
