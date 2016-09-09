#line 837 "/u/sargas/2/prisme/fabri/Cgal/Kernel/web/test_kernel_3.fw"
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL__TEST_CLS_SEGMENT_3_CC
#define CGAL__TEST_CLS_SEGMENT_3_CC
#include <CGAL/_test_cls_segment_3.h>

template <class R>
bool
CGAL__test_cls_segment_3(const R& )
{
 cout << "Testing class Segment_3" ;
 
 R::Segment_3 is;
 CGAL_Segment_3<R>  s1(is);
 
 R::RT  n1 =  7;
 R::RT  n2 = 21;
 R::RT  n3 = 14;
 R::RT  n4 =-10;
 R::RT  n5 =  5;
 R::RT  n6 = 20;
 R::RT  n7 = -1;
 R::RT  n8 =  3;

 CGAL_Point_3<R> p1( n1, n2, n3, n1);
 CGAL_Point_3<R> p2( n4, n5, n6, n5);
 CGAL_Point_3<R> p3( n2, n8, n2, n8);

 CGAL_Segment_3<R> s2( p1, p2 );
 CGAL_Segment_3<R> s3( p2, p1 );
 CGAL_Segment_3<R> s4( s2 );
 s1 = s4;

 assert( s1 == s1 );
 assert( s4 == s2 );
 assert( s1 == s4 );
 assert( s1 == s2 );
 assert( s2 != s3 );

 CGAL_Segment_3<R> s5 (p3, p3 + (p1 - p3) + (p1 - p3) );
 assert( s5.has_on( p1 ) );
 assert( s5.has_on( p3 ) );
 assert( s2.has_on( p2 ) );

 cout <<'.';

 assert( s5.source() == p3 );
 assert( s5.target() == p1 + (p1 - p3) );
 assert( s2.source() != s3.source() );
 assert( s2.target() != s3.target() );

 cout <<'.';

 assert( s2.min() == p2 );
 assert( s2.max() == p1 );
 assert( s2.min() == s3.min() );
 assert( s2.max() == s3.max() );
 assert( s5.max() != s5.min() );
 assert( s5.max() == s5.opposite().max() );
 assert( s5.vertex(0) == s5.source() );
 assert( s2.vertex(1) == s2.target() );
 assert( s2.vertex(1) == s2.min() );
 assert( s2[1] == s1[1] );
 assert( s2[1] == s3[0] );
 
 cout << '.';

 assert( s2.squared_length() == R::FT( R::RT(17) ) );
 assert( s2.direction() == CGAL_Direction_3<R>(s2.target() - s2.source() ));
 assert( s2.direction() == s3.opposite().direction() );
 
 assert( s1.supporting_line() == s2.supporting_line() );
 CGAL_Line_3<R> lin(p1,p2);
 assert( s2.supporting_line() == lin );

 CGAL_Segment_3<R> sdeg(p3,p3);
 assert( sdeg.is_degenerate() );

 cout << "done" << endl;
 return true;
}
#endif // CGAL__TEST_CLS_SEGMENT_3_CC
