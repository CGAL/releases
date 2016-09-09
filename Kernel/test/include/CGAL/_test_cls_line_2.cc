#line 878 "/u/sargas/2/prisme/fabri/Cgal/Kernel/web/test_kernel_2.fw"
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL__TEST_CLS_LINE_2_CC
#define CGAL__TEST_CLS_LINE_2_CC
#include <CGAL/_test_cls_line_2.h>

template <class R>
bool
CGAL__test_cls_line_2(const R& )
{
 cout << "Testing class Line_2";

 R::RT n0 =  0;
 R::RT n1 =  1;
 R::RT n2 =  2;
 R::RT n3 =  3;
 R::RT n4 =  4;
 R::RT n5 =  5;
 R::RT n6 =  6;
 R::RT n8 =  8;

 CGAL_Point_2<R> p1( n2, n4, n2 );   // ( 1, 2 )
 CGAL_Point_2<R> p2( n6, n8, n2 );   // ( 3, 4 )
 CGAL_Point_2<R> p3(-n6, n6, n3 );   // (-2, 2 )
 CGAL_Point_2<R> p4( n8, n4, n2 );   // ( 4, 2 )
 
 R::Line_2 il;
 CGAL_Line_2<R>  l0(il);
 CGAL_Line_2<R>  l12( p1, p2 );
 CGAL_Line_2<R>  l21( p2, p1 );
 CGAL_Line_2<R>  l34( p3, p4 );
 CGAL_Line_2<R>  l43( p4, p3 );
 CGAL_Line_2<R>  lc ( l12 );
 l0 = l12 ;

 CGAL_Segment_2<R> s12( p1, p2);
 CGAL_Line_2<R>  ls12( s12 );
 CGAL_Ray_2<R>  r21( p2, p1 );
 CGAL_Line_2<R>  lr21( r21 );
 CGAL_Direction_2<R> d12 (p2 - p1);
 CGAL_Direction_2<R> d21 (p1 - p2);
 CGAL_Line_2<R>  ld12(p1, d12);
 CGAL_Line_2<R>  ld21(p2, d21);

 cout << '.';

 assert( l12 == l12 );
 assert( l0  == l12 );
 assert( l12 == lc  );
 assert( l21 == lr21 );
 assert( l12 == ls12 );
 assert( l12 == ld12 );
 assert( l12 != l21 );
 assert( l12 != ld21 );
 assert( lr21 != ls12 );
 assert( l34 != l43 );
 assert( l12 != l43 );

 assert( l34.opposite() == l43);
 assert( l43.opposite() == l34);
 assert( l43.opposite().opposite() == l43);
 assert( ld12 == ld21.opposite() );

 CGAL_Line_2<R> labc( n2, n1, n4);
 assert( labc.a() == n2 );
 assert( labc.b() == n1 );
 assert( labc.c() == n4 );

 assert( l12.direction() == d12 );
 assert( l21.direction() == d21 );
 assert( ld21.direction() == d21 );
 assert( ld21.direction() ==  - ld12.direction() );
 assert( labc.direction() == CGAL_Direction_2<R>(labc.b(), - labc.a() ) );

 cout << '.';

 assert( l43.has_on( l43.point(0) ) );
 assert( lr21.has_on( lr21.point(1) ) );
 assert( ld21.has_on( ld21.point(-2) ) );
 assert( lr21.has_on( r21.source() ) );
 assert( labc.has_on( labc.point(0) ) );

 assert( l43.is_horizontal() );
 assert( ! l34.is_vertical() );
 assert( CGAL_Line_2<R>( n1, n0, n3 ).is_vertical() );
 assert( CGAL_Line_2<R>( n0, n2, n3 ).is_horizontal() );
 assert( ! lr21.is_horizontal() );

 assert( ld12.y_at_x( R::FT(3) ) == R::FT( 4) );
 assert( lr21.y_at_x( R::FT(3) ) == R::FT( 4) );
 assert( ld12.y_at_x( R::FT(1) ) == R::FT( 2) );
 assert( l12.y_at_x( R::FT(5) ) == R::FT( 6) );
 assert( l34.y_at_x( R::FT(8) ) == R::FT( 2) );

 assert( l12.x_at_y( R::FT(0) ) == R::FT( -1 ) );
 assert( ls12.x_at_y( R::FT(4) ) == R::FT( 3 ) );
 assert( l21.x_at_y( R::FT(6) ) == R::FT( 5 ) );
 assert( ld21.x_at_y( R::FT(2) ) == R::FT( 1 ) );

 CGAL_Direction_2<R> up( n0, n1 );
 CGAL_Aff_transformation_2<R> rot90(CGAL_ROTATION, up, n1, R::RT(100) );
 CGAL_Line_2<R> l12perp1( l12.perpendicular( p1 ) );
 CGAL_Line_2<R> l21perp1( l21.perpendicular( p1 ) );
 CGAL_Line_2<R> labcperp( labc.perpendicular( labc.point(1) ) );
 assert( l12perp1.opposite() == l21perp1 );
 assert( labcperp.direction() == CGAL_Direction_2<R>( labc.a(), labc.b()) );
 assert( l12perp1.has_on( p1 ) );
 assert( l21perp1.has_on( p1 ) );
 CGAL_Line_2<R> l12perp4( l12.perpendicular( p4 ) );
 assert( l12perp4.has_on( p4 ) );
 assert( l12.direction().transform( rot90 ) == l12perp4.direction() );

 assert( CGAL_Line_2<R>( n0, n0, n6 ).is_degenerate() );
 assert( CGAL_Line_2<R>( p1, p1 ).is_degenerate() );
 assert( ! CGAL_Line_2<R>( p1, p3 ).is_degenerate() );
 assert( ! l34.is_degenerate() );

 cout << '.';

 CGAL_Point_2<R> p5( n5, n6 );
 assert( l12.oriented_side(p3) == CGAL_ON_POSITIVE_SIDE );
 assert( l12.oriented_side(p4) == CGAL_ON_NEGATIVE_SIDE );
 assert( l12.oriented_side(p2) == CGAL_ON_BOUNDARY );
 assert( l12.oriented_side(p5) == CGAL_ON_BOUNDARY );
 assert( l21.oriented_side(p3) == CGAL_ON_NEGATIVE_SIDE );
 assert( l21.oriented_side(p5) == CGAL_ON_BOUNDARY );

 assert( l21.has_on_negative_side( p3 ) );
 assert( l12.has_on_positive_side( p3 ) );
 assert( l34.has_on_positive_side( p2 ) );
 assert( l43.has_on( CGAL_Point_2<R>( n8, n2 )) );
 assert( l43.has_on_boundary( CGAL_Point_2<R>( n8, n2 )) );
 assert( lr21.has_on( CGAL_Point_2<R>( -n1, n0 )) );

 cout << "done" << endl;
 return true;

}
#endif // CGAL__TEST_CLS_LINE_2_CC
