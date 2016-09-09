#line 1023 "/u/sargas/2/prisme/fabri/Cgal/Kernel/web/test_kernel_3.fw"
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL__TEST_CLS_TRIANGLE_3_CC
#define CGAL__TEST_CLS_TRIANGLE_3_CC
#include <CGAL/_test_cls_triangle_3.h>

template <class R>
bool
CGAL__test_cls_triangle_3(const R& )
{
 cout << "Testing class Triangle_3" ;

 R::Triangle_3 it; 
 CGAL_Triangle_3<R> t0(it);

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

 CGAL_Triangle_3<R> t1(p1,p2,p3);
 CGAL_Triangle_3<R> t2(p4,p2,p3);
 CGAL_Triangle_3<R> t3(ps1,ps2,ps3);
 CGAL_Triangle_3<R> t4(ps2,ps1,ps3);
 CGAL_Triangle_3<R> t5( t1 );
 t0 = t1;
 
 assert( t0 == t0 );
 assert( t0 == t1 );
 assert( t5 == t1 );
 assert( t2 != t4 );
 assert( t3 != t4 );

 cout <<'.';

 CGAL_Plane_3<R> pl1( p1,p2,p3);
 CGAL_Plane_3<R> pl2( p4,p2,p3);
 assert( t1.supporting_plane() == pl1 );
 assert( t2.supporting_plane() == pl2 );
 assert( t3.supporting_plane() == t4.supporting_plane().opposite() );
 
 cout <<'.';

 assert( t1.has_on(p3) );
 assert( t1.has_on(p2) );
 assert( t2.has_on(p4) );
 assert( ! t1.has_on(p4) );
 CGAL_Point_3<R> pt( n7, n7, n7, n7);
 assert( t3.has_on( pt ) );
 assert( t4.has_on( pt ) );

 assert( t1.vertex(0) == p1 );
 assert( t1.vertex(1) == p2 );
 assert( t1.vertex(2) == p3 );
 assert( t4[0] == ps2 );
 assert( t4[1] == ps1 );
 assert( t4[2] == ps3 );

 cout <<'.';

 CGAL_Triangle_3<R> tdeg1( p3,p3,p1);
 CGAL_Triangle_3<R> tdeg2( p3,p3,p3);
 assert( tdeg1.is_degenerate() );
 assert( tdeg2.is_degenerate() );

 cout << "done" << endl;
 return true;
}

#endif // CGAL__TEST_CLS_TRIANGLE_3_CC
