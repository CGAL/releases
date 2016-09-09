#line 1412 "/u/sargas/2/prisme/fabri/Cgal/Kernel/web/test_kernel_2.fw"
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL__TEST_CLS_TRIANGLE_2_CC
#define CGAL__TEST_CLS_TRIANGLE_2_CC
#include <CGAL/_test_cls_triangle_2.h>

template <class R>
bool
CGAL__test_cls_triangle_2(const R& )
{
 cout << "Testing class Triangle_2";

 R::Triangle_2 it;
 CGAL_Triangle_2<R> t0(it);

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
 R::RT n21= 21;

 CGAL_Point_2<R> p1( n6, n6, n6);    // ( 1, 1)
 CGAL_Point_2<R> p2( n6, n9, n3);    // ( 2, 3)
 CGAL_Point_2<R> p3( n6, n10, n2);   // ( 3, 5)
 CGAL_Point_2<R> p4( n5, n4, n1);    // ( 5, 4)
 CGAL_Point_2<R> p5( n21, n9, n3);   // ( 7, 3)
 CGAL_Point_2<R> p6( n8, n4, n2);    // ( 4, 2)
 CGAL_Point_2<R> p7( n4, n0);        // ( 4, 0)
 CGAL_Point_2<R> p8(-n12,-n8,-n2);   // ( 6, 4)
 CGAL_Point_2<R> p9( n9, n9, n3);    // ( 3, 3)

 CGAL_Triangle_2<R> t1( p1, p3, p5);
 CGAL_Triangle_2<R> t2( p3, p1, p5);
 CGAL_Triangle_2<R> t3( p7, p8, p9);
 CGAL_Triangle_2<R> t4( p3, p5, p1);
 CGAL_Triangle_2<R> t5( p5, p1, p3);
 t0 = t3;

 cout << '.';

 assert( t1 == t1 );
 assert( t4 == t1 );
 assert( t1 == t5 );
 assert( t0 == t3 );
 assert( t1 != t2 );
 assert( t3 != t2 );

 assert( t3.vertex(0) == p7 );
 assert( t3.vertex(1) == p8 );
 assert( t3.vertex(2) == p9 );
 assert( t3.vertex(3) == p7 );
 assert( t3.vertex(4) == p8 );
 assert( t3.vertex(5) == p9 );
 assert( t2[5] == t2.vertex(5) );
 assert( t2[6] == t2.vertex(6) );

 assert( t1.orientation() == CGAL_NEGATIVE );
 assert( t2.orientation() == CGAL_POSITIVE );
 assert( t0.orientation() == CGAL_POSITIVE );

 cout << '.';

 assert( t1.oriented_side( p9 ) == CGAL_ON_NEGATIVE_SIDE );
 assert( t1.oriented_side( p7 ) == CGAL_ON_POSITIVE_SIDE );
 assert( t1.oriented_side( p8 ) == CGAL_ON_POSITIVE_SIDE );
 assert( t1.oriented_side( p6 ) == CGAL_ON_ORIENTED_BOUNDARY );
 assert( t2.oriented_side( p8 ) == CGAL_ON_NEGATIVE_SIDE );
 assert( t2.oriented_side( p9 ) == CGAL_ON_POSITIVE_SIDE );
 assert( t2.oriented_side( p6 ) == CGAL_ON_ORIENTED_BOUNDARY );
 assert( t2.oriented_side( p3 ) == CGAL_ON_ORIENTED_BOUNDARY );

 assert( t1.bounded_side( p9 ) == CGAL_ON_BOUNDED_SIDE );
 assert( t1.bounded_side( p7 ) == CGAL_ON_UNBOUNDED_SIDE );
 assert( t1.bounded_side( p2 ) == CGAL_ON_BOUNDARY );
 assert( t2.bounded_side( p9 ) == CGAL_ON_BOUNDED_SIDE );
 assert( t2.bounded_side( p7 ) == CGAL_ON_UNBOUNDED_SIDE );
 assert( t2.bounded_side( p2 ) == CGAL_ON_BOUNDARY );
 assert( t2.bounded_side( p1 ) == CGAL_ON_BOUNDARY );
 assert( t2.bounded_side( p5 ) == CGAL_ON_BOUNDARY );

 assert( t1.opposite().has_on_positive_side( p9 ) );
 assert( t1.has_on_positive_side( p8 ) );
 assert( t3.has_on_negative_side( p2 ) );
 assert( t2.has_on_boundary( p1 ) );
 assert( t2.has_on_boundary( p2 ) );
 assert( t2.has_on_boundary( p3 ) );
 assert( t2.has_on_boundary( p4 ) );
 assert( t2.has_on_boundary( p5 ) );
 assert( t2.has_on_boundary( p6 ) );
 assert( t1.has_on_bounded_side( CGAL_Point_2<R>( n6, n8, n2)) );
 assert( t1.has_on_unbounded_side( CGAL_Point_2<R>( -n4, n8, n6)) );

 cout << '.';

 assert( t1.opposite() == t2 );
 assert( t3 == t3.opposite().opposite() );

 CGAL_Triangle_2<R> tdeg1( p1, p7, p7);
 CGAL_Triangle_2<R> tdeg2( p6, p6, p6);
 assert( tdeg1.orientation() == CGAL_ZERO );
 assert( tdeg2.orientation() == CGAL_ZERO );
 assert( tdeg1.is_degenerate() );
 assert( tdeg2.is_degenerate() );

 cout << "done" << endl;
 return true;
}
#endif // CGAL__TEST_CLS_TRIANGLE_2_CC
