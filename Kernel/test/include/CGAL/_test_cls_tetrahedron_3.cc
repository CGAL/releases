#line 1120 "/u/sargas/2/prisme/fabri/Cgal/Kernel/web/test_kernel_3.fw"
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL__TEST_CLS_TETRAHEDRON_3_CC
#define CGAL__TEST_CLS_TETRAHEDRON_3_CC
#include <CGAL/_test_cls_tetrahedron_3.h>

template <class R>
bool
CGAL__test_cls_tetrahedron_3(const R& )
{
 cout << "Testing class Tetrahedron_3" ;

 R::Tetrahedron_3 it;
 CGAL_Tetrahedron_3<R>  t0(it);

 R::RT n0 =  0;
 R::RT n1 = 12;
 R::RT n2 = 16;
 R::RT n3 = -4;
 R::RT n4 =  2;
 R::RT n5 =  3;
 R::RT n6 = 30;
 R::RT n7 =  9;
 R::RT n8 = 24;
 R::RT n9 =  8;

 CGAL_Point_3<R> p1( n1, n2, n3, n4);
 CGAL_Point_3<R> p2( n2, n9, n3,-n3);
 CGAL_Point_3<R> p3( n5, n6, n1, n5);
 CGAL_Point_3<R> p4( n7, n7, n8, n5);

 CGAL_Point_3<R> ps3( n0, n0, n7, n5);
 CGAL_Point_3<R> ps2( n0, n7, n0, n5);
 CGAL_Point_3<R> ps1( n7, n0, n0, n5);
 CGAL_Point_3<R> ps0( CGAL_ORIGIN );

 CGAL_Tetrahedron_3<R> t1(p1,p2,p3,p4);
 CGAL_Tetrahedron_3<R> t2(p2,p1,p3,p4);
 CGAL_Tetrahedron_3<R> t3(ps0,ps1,ps2,ps3); // positive oriented
 CGAL_Tetrahedron_3<R> t4(ps0,ps1,ps3,ps2); // negative oriented
 CGAL_Tetrahedron_3<R> t5(ps0,p1,p3,ps2);
 CGAL_Tetrahedron_3<R> t6(t3);
 t0 = t4;

 assert( t4 == t4 );
 assert( t4 == t0 );
 assert( t6 == t3 );
 assert( t4 != t2 );
 assert( t4 != t3 );
 
 cout << '.';

 assert( t5.vertex(0) == ps0 );
 assert( t5.vertex(1) == p1 );
 assert( t5.vertex(2) == p3 );
 assert( t5.vertex(3) == ps2 );
 assert( t5.vertex(4) == ps0 );
 assert( t5.vertex(5) == p1 );
 assert( t1[0] == p1 );
 assert( t1[1] == p2 );
 assert( t1[2] == p3 );
 assert( t1[3] == p4 );
 assert( t1[4] == p1 );
 assert( t1[9] == p2 );

 CGAL_Tetrahedron_3<R> t7( p1,p1,p2,p3);
 CGAL_Tetrahedron_3<R> t8( p2,p2,p2,p2);
 assert( t7.is_degenerate() );
 assert( t8.is_degenerate() );

 cout << '.';

 CGAL_Point_3<R> p5(n6,n6,n6,n4);
 CGAL_Point_3<R> p6(n4,n4,n4,n9);
 CGAL_Point_3<R> p7(n7,n7,n7,n7);
 assert( t3.has_on_unbounded_side( p5 ));
 assert( t3.has_on_bounded_side( p6 ));
 assert( t3.has_on_boundary( p7 ));
 assert( t4.has_on_unbounded_side( p5 ));
 assert( t4.has_on_bounded_side( p6 ));
 assert( t4.has_on_boundary( p7 ));
 assert( t2.has_on_unbounded_side( p5 ));
 assert( t4.bounded_side( p5 ) == CGAL_ON_UNBOUNDED_SIDE );
 assert( t4.bounded_side( p6 ) == CGAL_ON_BOUNDED_SIDE );
 assert( t4.bounded_side( p7 ) == CGAL_ON_BOUNDARY );
 
 cout << '.';

 assert( t3.oriented_side( p3 ) != t4.oriented_side( p3 ) );
 assert( t4.has_on_positive_side( p5 ));
 assert( t4.has_on_negative_side( p6 ));
 assert( t3.has_on_positive_side( p6 ));
 assert( t3.has_on_negative_side( p5 ));
 assert( t4.oriented_side( p5 ) == CGAL_ON_POSITIVE_SIDE );
 assert( t4.oriented_side( p6 ) == CGAL_ON_NEGATIVE_SIDE );
 assert( t4.oriented_side( p7 ) == CGAL_ON_ORIENTED_BOUNDARY );
 assert( t3.oriented_side( p7 ) == CGAL_ON_ORIENTED_BOUNDARY );
 assert( t3.oriented_side( p6 ) == CGAL_ON_POSITIVE_SIDE );
 assert( t3.oriented_side( p5 ) == CGAL_ON_NEGATIVE_SIDE );
 assert( t2.has_on_boundary(p2) );
 assert( t2.bounded_side(p3) == CGAL_ON_BOUNDARY );
 assert( t2.oriented_side(p4) == CGAL_ON_ORIENTED_BOUNDARY );
 CGAL_Point_3<R> p8(n3, n0, n0, n3);
 CGAL_Point_3<R> p9(n0, n3, n0, n3);
 assert( t3.has_on_boundary( p8 ) );
 assert( t3.has_on_boundary( p9 ) );
 assert( t4.has_on_boundary( p8 ) );
 assert( t4.has_on_boundary( p9 ) );
 assert( t3.bounded_side(p8) == CGAL_ON_BOUNDARY );
 assert( t3.oriented_side(p8) == CGAL_ON_ORIENTED_BOUNDARY );
 assert( t4.bounded_side(p9) == CGAL_ON_BOUNDARY );
 assert( t4.oriented_side(p9) == CGAL_ON_ORIENTED_BOUNDARY );

 cout << "done" << endl;
 return true;
}
#endif // CGAL__TEST_CLS_TETRAHEDRON_3_CC
