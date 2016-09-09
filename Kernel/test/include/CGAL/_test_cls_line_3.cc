#line 730 "/u/sargas/2/prisme/fabri/Cgal/Kernel/web/test_kernel_3.fw"
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL__TEST_CLS_LINE_3_CC
#define CGAL__TEST_CLS_LINE_3_CC
#include <CGAL/_test_cls_line_3.h>

template <class R>
bool
CGAL__test_cls_line_3(const R& )
{
 cout << "Testing class Line_3" ;

 R::Line_3 il;
 CGAL_Line_3<R> l0( il );
 CGAL_Line_3<R> l1;
 
 R::RT n1 =  3;
 R::RT n2 = 53;
 R::RT n3 =-14;
 R::RT n4 = 28;
 R::RT n5 = 16;
 R::RT n6 = -6;
 R::RT n7 = 11;
 R::RT n8 =-17;
 R::RT n9 = 30;

 CGAL_Point_3<R> p1( n1, n2, n3);
 CGAL_Point_3<R> p2( n4, n5, n6);
 CGAL_Point_3<R> p3( n7, n8, n9);

 CGAL_Line_3<R> l2(p1,p2);
 CGAL_Line_3<R> l3(l2);
 
 assert( l2 == l2);
 assert( l2 == l3);

 CGAL_Direction_3<R> dir( n9, n3, n1);
 CGAL_Line_3<R> l4(p3, dir);
 assert( l2 != l4);

 CGAL_Segment_3<R> seg(p1,p2);
 CGAL_Ray_3<R>     ray(p2,p1);
 CGAL_Line_3<R>    l5(seg);
 CGAL_Line_3<R>    l6(ray);
 assert( l2 == l5);
 
 cout <<'.';

 assert( l2 == l5 );
 assert( l2.direction() == l5.direction() );
 assert( l5.direction() ==  - l6.direction() );
 assert( l5.has_on( p1 ) );
 assert( l5.has_on( p2 ) );
 assert( l5.has_on( l5.point() ));
 assert( l6.has_on( p1 ) );
 assert( l6.has_on( p2 ) );
 assert( l6.has_on( l5.point() ));
 assert( l5.opposite() == l6 );
 assert( l2.opposite() == l6 );
 assert( l5 != l6 );
 
 CGAL_Plane_3<R> pl = l6.perpendicular_plane( l6.point() );
 CGAL_Plane_3<R> plstrich(l6.point(), l6.direction() );
 assert( pl == plstrich );
 assert( pl.orthogonal_direction() == l6.direction() );
 CGAL_Plane_3<R> plzweistrich(l6.point(), l5.direction() );
 assert( plzweistrich.opposite() == pl );

 cout << '.';

 assert( l4.point(2) - l4.point(1) == l4.point(1) - l4.point(0) );
 CGAL_Point_3<R> p1l4proj = l4.projection(p1);
 assert( l4.has_on( p1l4proj ) );
 assert( l4.perpendicular_plane( p1l4proj ).has_on( p1l4proj ) );
 assert( l4.perpendicular_plane( p1l4proj ).has_on( p1 ) );
 CGAL_Point_3<R> p4 = l4.projection(p2);
 CGAL_Point_3<R> p5 = l4.projection(p3);
 assert(  ( l4.direction() == ( p5 - p4 ).direction() )\
        ||( l4.direction() == ( p4 - p5 ).direction() )  );        
 assert( l5.direction() == - l6.direction() );

 cout <<'.';

 assert( l2.has_on(p1) );
 assert( l2.has_on(p2) );
 assert( l4.has_on(p4) );
 assert( l4.has_on(p5) );
 assert( CGAL_Line_3<R>(p1,p1).is_degenerate() );

 cout << "done" << endl;
 return true;
}

#endif // CGAL__TEST_CLS_LINE_3_CC
