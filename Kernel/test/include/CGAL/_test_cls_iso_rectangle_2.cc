#line 1540 "/u/sargas/2/prisme/fabri/Cgal/Kernel/web/test_kernel_2.fw"
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL__TEST_CLS_ISO_RECTANGLE_2_CC
#define CGAL__TEST_CLS_ISO_RECTANGLE_2_CC
#include <CGAL/_test_cls_iso_rectangle_2.h>

template <class R>
bool
CGAL__test_cls_iso_rectangle_2(const R& )
{
 cout << "Testing class Iso_rectangle_2";
 
 R::Iso_rectangle_2 ir;
 CGAL_Iso_rectangle_2<R>  r0(ir);

 R::RT n0 =  0;
 R::RT n1 =  1;
 R::RT n2 =  2;
 R::RT n3 =  3;
 R::RT n4 =  4;
 R::RT n5 =  5;
 R::RT n6 =  6;
 R::RT n7 =  7;
 R::RT n8 =  8;
 R::RT n9 =  9;
 R::RT n10= 10;
 R::RT n12= 12;

 CGAL_Point_2<R> p1( n5, n5, n5);    // ( 1, 1)
 CGAL_Point_2<R> p2( n2, n8, n2);    // ( 1, 4)
 CGAL_Point_2<R> p3( n12, n12, n3);  // ( 4, 4)
 CGAL_Point_2<R> p4( n5, n4, n1);    // ( 5, 4)
 CGAL_Point_2<R> p5( n4, n1);        // ( 4, 1)
 CGAL_Point_2<R> p6( n8, n4, n2);    // ( 4, 2)
 CGAL_Point_2<R> p7( n6, n3, n2);    // ( 3, 1.5)
 CGAL_Point_2<R> p8( n4, n6, n2);    // ( 2, 3)
 CGAL_Point_2<R> p9(-n3, n7);        // (-3, 7) 

 CGAL_Iso_rectangle_2<R> r1( p1, p3);
 CGAL_Iso_rectangle_2<R> r2( p3, p1);
 CGAL_Iso_rectangle_2<R> r3( p2, p5);
 CGAL_Iso_rectangle_2<R> r4( p5, p2);
 CGAL_Iso_rectangle_2<R> r5( p9, p2);
 CGAL_Iso_rectangle_2<R> r6( r2 );
 r0 = r1;

 assert( r1 == r1 );
 assert( r0 == r1 );
 assert( r1 == r2 );
 assert( r1 == r3 );
 assert( r1 == r4 );
 assert( r2 == r6 );
 assert( r2 != r5 );

 cout << '.';

 assert( r1.vertex(0) == p1 );
 assert( r1.vertex(1) == p5 );
 assert( r1.vertex(2) == p3 );
 assert( r1.vertex(3) == p2 );
 assert( r1.vertex(4) == p1 );
 assert( r3.vertex(0) == p1 );
 assert( r3.vertex(1) == p5 );
 assert( r3.vertex(2) == p3 );
 assert( r3.vertex(3) == p2 );
 assert( r3.vertex(4) == p1 );
 assert( r2[0] == r2.vertex(0) );
 assert( r2[1] == r2.vertex(1) );
 assert( r2[3] == r2.vertex(3) );
 assert( r2[4] == r2.vertex(0) );

 cout << '.';

 assert( r4.min() == p1 );
 assert( r1.min() == p1 );
 assert( r5.min() != p9 );
 assert( r2.max() == p3 ); 

 assert( r1.bounded_side( p8 ) == CGAL_ON_BOUNDED_SIDE );
 assert( r2.bounded_side( p7 ) == CGAL_ON_BOUNDED_SIDE );
 assert( r3.bounded_side( p9 ) == CGAL_ON_UNBOUNDED_SIDE );
 assert( r1.bounded_side( p4 ) == CGAL_ON_UNBOUNDED_SIDE );
 assert( r4.bounded_side( p6 ) == CGAL_ON_BOUNDARY );
 assert( r4.bounded_side( p1 ) == CGAL_ON_BOUNDARY );

 assert( r5.has_on_boundary( p2 ) );
 assert( r4.has_on_boundary( p2 ) );
 assert( r2.has_on_bounded_side( p7 ) );
 assert( r4.has_on_unbounded_side( p9 ) );

 cout << '.';

 assert( CGAL_Iso_rectangle_2<R>( p1, p1 ).is_degenerate() );
 assert( CGAL_Iso_rectangle_2<R>( p1, p2 ).is_degenerate() );
 assert( CGAL_Iso_rectangle_2<R>( p3, p4 ).is_degenerate() );

 cout << "done" << endl;
 return true;
}
#endif // CGAL__TEST_CLS_ISO_RECTANGLE_2_CC
