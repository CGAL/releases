#line 744 "/u/sargas/2/prisme/fabri/Cgal/Kernel/web/test_kernel_2.fw"
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL__TEST_FCT_POINT_2_LINE_2_CC
#define CGAL__TEST_FCT_POINT_2_LINE_2_CC
#include <CGAL/_test_fct_point_line_2.h>

template <class R>
bool
CGAL__test_fct_point_line_2(const R& )
{
 cout << "Testing functions Point_2 Line_2" ;

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
 R::RT n20= 20;

 CGAL_Point_2<R>  p1( n2, n8, n2);   // ( 1, 4)
 CGAL_Point_2<R>  p2( n4, n4, n2);   // ( 2, 2)
 CGAL_Point_2<R>  p3(n12,n10, n2);   // ( 6, 5)
 CGAL_Point_2<R>  p4( n7, n3);       // ( 7, 3)
 CGAL_Point_2<R>  p5( n9, n0, n3);   // ( 3, 0)
 CGAL_Point_2<R>  p6(n12,n20, n4);   // ( 3, 5)
 CGAL_Point_2<R>  p7(n12, n3, n3);   // ( 4, 1)
 CGAL_Point_2<R>  p8( n8, n4);       // ( 8, 4)
 CGAL_Point_2<R>  p9(-n4, n8, n4);   // (-1, 2)
 CGAL_Point_2<R>  p10(n10, n4, n2);  // ( 5, 2)

 CGAL_Point_2<R>  p11( n1, -n5,-n1); // (-1, 5)
 CGAL_Point_2<R>  p0( CGAL_ORIGIN ); // ( 0, 0)
 CGAL_Point_2<R>  p13( n8, n8, n4);  // ( 4, 4)
 CGAL_Point_2<R>  p14( n5,-n1);      // ( 5,-1)
 CGAL_Point_2<R>  p16(n12, n9, n3);  // ( 4, 3)
 CGAL_Point_2<R>  p17( n0,n1);       // ( 0, 1)

 CGAL_Line_2<R>   l14( p1, p4 );
 CGAL_Line_2<R>   l23( p2, p3 );
 CGAL_Line_2<R>   l67( p6, p7 );
 CGAL_Line_2<R>   l58( p5, p8 );
 CGAL_Line_2<R>   l1617( p16, p17);
 CGAL_Line_2<R>   l1114( p11, p14);
 CGAL_Line_2<R>   l1716( p17, p16);
 CGAL_Line_2<R>   l1411( p14, p11);
 CGAL_Line_2<R>   l013( p0, p13 );
 CGAL_Line_2<R>   l910( p9, p10 ); 
 
 cout << '.';

 assert( CGAL_compare_x( p16, p14 ) == CGAL_SMALLER );

 assert( CGAL_compare_x( p9, l14, l23) == CGAL_SMALLER );
 assert( CGAL_compare_x( p8, l14, l23) == CGAL_LARGER );
 assert( CGAL_compare_x( p2, l1617, l910) == CGAL_EQUAL );
 assert( CGAL_compare_x( p2, l1716, l910) == CGAL_EQUAL );
 assert( CGAL_compare_x( p2, l1114, l013) == CGAL_EQUAL );
 
 assert( CGAL_compare_y( p6, l14, l23 ) == CGAL_LARGER ); 
 assert( CGAL_compare_y( p9, l14, l23 ) == CGAL_SMALLER ); 
 assert( CGAL_compare_x( p2, l1411, l013) == CGAL_EQUAL );
 assert( CGAL_compare_x( p2, l1716, l013) == CGAL_EQUAL );
 
 cout << '.';

 assert( CGAL_compare_x( l14, l23, l58 ) == CGAL_SMALLER);
 assert( CGAL_compare_x( l14, l58, l23 ) == CGAL_LARGER);
 assert( CGAL_compare_x( l14, l58, l58 ) == CGAL_EQUAL);
 assert( CGAL_compare_x( l1114, l013, l910 ) == CGAL_EQUAL);
 assert( CGAL_compare_x( l1617, l910, l013 ) == CGAL_EQUAL);

 assert( CGAL_compare_y( l14, l58, l23 ) == CGAL_SMALLER);
 assert( CGAL_compare_y( l14, l23, l58 ) == CGAL_LARGER);
 assert( CGAL_compare_y( l14, l58, l58 ) == CGAL_EQUAL);
 assert( CGAL_compare_y( l1114, l013, l910 ) == CGAL_EQUAL);
 assert( CGAL_compare_y( l1617, l910, l013 ) == CGAL_EQUAL);

 assert( CGAL_compare_x( l14, l23, l67, l58 ) == CGAL_SMALLER);
 assert( CGAL_compare_x( l67, l58, l23, l14 ) == CGAL_LARGER);
 assert( CGAL_compare_x( l1114, l1617, l910, l013 ) == CGAL_EQUAL);
 
 assert( CGAL_compare_y( l14, l23, l67, l58 ) == CGAL_LARGER);
 assert( CGAL_compare_y( l67, l58, l23, l14 ) == CGAL_SMALLER);
 assert( CGAL_compare_y( l1114, l1617, l910, l013 ) == CGAL_EQUAL);

 cout << '.';

 assert( CGAL_compare_y_at_x( p6, l23 ) == CGAL_LARGER );
 assert( CGAL_compare_y_at_x( p6, l23.opposite() ) == CGAL_LARGER );
 assert( CGAL_compare_y_at_x( p10, l23 ) == CGAL_SMALLER );
 assert( CGAL_compare_y_at_x( p9, l23 ) == CGAL_LARGER );
 assert( CGAL_compare_y_at_x( p17, l910 ) == CGAL_SMALLER );
 assert( CGAL_compare_y_at_x( p0, l23 ) == CGAL_SMALLER );
 assert( CGAL_compare_y_at_x( p8, l58 ) == CGAL_EQUAL );
 assert( CGAL_compare_y_at_x( p2, l1617 ) == CGAL_EQUAL );

 assert( CGAL_compare_y_at_x( l14, l23, l58 ) == CGAL_LARGER );
 assert( CGAL_compare_y_at_x( l67, l58, l23 ) == CGAL_SMALLER );
 assert( CGAL_compare_y_at_x( l910, l1716, l1114) == CGAL_EQUAL);

 assert( CGAL_compare_y_at_x( l14, l23, l58, l67 ) == CGAL_SMALLER );
 assert( CGAL_compare_y_at_x( l14, l23, l67, l58 ) == CGAL_LARGER );
 assert( CGAL_compare_y_at_x( l14, l23, l1411, l1114 ) == CGAL_EQUAL );
 assert( CGAL_compare_y_at_x( l1617, l013, l910, l67 ) == CGAL_SMALLER);
 assert( CGAL_compare_y_at_x( l1617, l013, l67, l910 ) == CGAL_LARGER);
 assert( CGAL_compare_y_at_x( l1617, l013, l1114, l910 ) == CGAL_EQUAL);
 assert( CGAL_compare_y_at_x( l1617, l013, l910, l1114 ) == CGAL_EQUAL);

 cout << "done" << endl;
 return true;
}
#endif // CGAL__TEST_FCT_POINT_2_LINE_2_CC
