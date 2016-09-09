#line 1202 "/u/sargas/2/prisme/fabri/Cgal/Kernel/web/test_kernel_2.fw"
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL__TEST_CLS_SEGMENT_2_CC
#define CGAL__TEST_CLS_SEGMENT_2_CC
#include <CGAL/_test_cls_segment_2.h>

template <class R>
bool
CGAL__test_cls_segment_2(const R& )
{
 cout << "Testing class Segment_2";

 R::Segment_2  is;
 CGAL_Segment_2<R> s0;

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

 CGAL_Segment_2<R> s1 ( p1, p2 );
 CGAL_Segment_2<R> s2 ( p2, p1 );
 CGAL_Segment_2<R> s3 ( p2, p3 );
 CGAL_Segment_2<R> s4 ( p2, p4 );
 CGAL_Segment_2<R> s5 ( p4, p1 );
 CGAL_Segment_2<R> s6 ( s3 );
 s0 = s2;

 assert( s5 == s5 );
 assert( s6 == s3 );
 assert( s2 == s0 );
 assert( s0 == s2 );
 assert( s1 != s5 );
 assert( s1 != s2 );
 assert( s3 != s2 );

 cout << '.';
 
 assert( s1.source() == p1 );
 assert( s2.source() == p2 );
 assert( s6.source() == p2 );
 assert( s4.target() == p4 );
 assert( s5.target() == p1 );

 assert( s1.min() == p1 );
 assert( s3.min() == p3 );
 assert( s4.min() == p2 );
 assert( s4.max() == p4 );
 assert( s5.max() == p4 );

 assert( s3.vertex(0) == p2 );
 assert( s3.vertex(1) == p3 );
 assert( s3.vertex(2) == p2 );
 assert( s4.point(8) == s4.vertex(8) );
 assert( s1.point(3) == s1.vertex(3) );
 assert( s5[0] == s5.vertex(0) );
 assert( s6[1] == s6.vertex(1) );

 cout << '.';

 assert( s1.squared_length() == R::FT( 20 ) );
 assert( s5.squared_length() == R::FT( 16 ) );
 assert( s4.direction() == CGAL_Direction_2<R>( p4 - p2 ) );
 assert( s2.opposite() == s1 );
 assert( s1.opposite() == s2 );
 assert( s1.supporting_line() == CGAL_Line_2<R>( p1, p2 ) );
 assert( s3.supporting_line() == CGAL_Line_2<R>( p2, p3 ) );
 assert( ! s1.is_horizontal() );
 assert( ! s1.is_vertical() );
 assert( s5.is_horizontal() );
 assert( s4.is_vertical() );

 cout << '.';

 assert( s1.has_on( p1 ) );
 assert( s1.has_on( p2 ) );
 assert( s1.has_on( p3 ) );
 assert( s2.has_on( p3 ) );
 assert( ! s4.has_on( p3 ) );
 assert( s1.collinear_has_on( p3 ) );
 assert( s2.collinear_has_on( p1 ) );
 assert( ! s3.collinear_has_on( p1 ) );
 assert( s3.collinear_has_on( CGAL_Point_2<R>( n8, n5, n2)) );

 assert( CGAL_Segment_2<R>( p3, p3).is_degenerate() );

 cout << "done" << endl;
 return true;
}
#endif // CGAL__TEST_CLS_SEGMENT_2_CC
