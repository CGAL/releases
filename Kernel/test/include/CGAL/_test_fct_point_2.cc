#line 373 "/u/sargas/2/prisme/fabri/Cgal/Kernel/web/test_kernel_2.fw"
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL__TEST_FCT_POINT_2_CC
#define CGAL__TEST_FCT_POINT_2_CC
#include <CGAL/_test_fct_point_2.h>

template <class R>
bool
CGAL__test_fct_point_2(const R& )
{
 cout << "Testing functions Point_2" ;

 CGAL_Point_2<R> p1( R::RT(18), R::RT(12), R::RT(3) );  // ( 6, 4)
 CGAL_Point_2<R> p2( R::RT(18), R::RT(15), R::RT(3) );  // ( 6, 5)
 CGAL_Point_2<R> p3( R::RT(18), R::RT( 9), R::RT(3) );  // ( 6, 3)
 CGAL_Point_2<R> p4( R::RT(28), R::RT(40), R::RT(4) );  // ( 7,10)
 CGAL_Point_2<R> p5( R::RT(12), R::RT(-4), R::RT(4) );  // ( 3,-1)
 CGAL_Point_2<R> p6( R::RT(28), R::RT(12), R::RT(4) );  // ( 7, 3)
 CGAL_Point_2<R> p7( R::RT(18), R::RT( 6), R::RT(3) );  // ( 6, 2)

 assert( CGAL_compare_lexicographically_xy(p1,p2) == CGAL_SMALLER );
 assert( CGAL_compare_lexicographically_xy(p3,p2) == CGAL_SMALLER );
 assert( CGAL_compare_lexicographically_xy(p3,p1) == CGAL_SMALLER );
 assert( CGAL_compare_lexicographically_xy(p3,p2) == CGAL_SMALLER );
 assert( CGAL_compare_lexicographically_xy(p2,p1) == CGAL_LARGER );
 assert( CGAL_compare_lexicographically_xy(p2,p3) == CGAL_LARGER );
 assert( CGAL_compare_lexicographically_xy(p4,p3) == CGAL_LARGER );
 assert( CGAL_compare_lexicographically_xy(p4,p4) == CGAL_EQUAL );

 assert( CGAL_lexicographically_xy_smaller_or_equal(p1,p1) );
 assert( CGAL_lexicographically_xy_smaller_or_equal(p3,p1) );
 assert( CGAL_lexicographically_xy_smaller_or_equal(p3,p2) );
 assert( CGAL_lexicographically_xy_smaller_or_equal(p3,p4) );

 assert( !CGAL_lexicographically_xy_smaller(p3,p3) );
 assert(  CGAL_lexicographically_xy_smaller(p3,p2) );
 assert( !CGAL_lexicographically_xy_smaller(p4,p3) );

 assert( CGAL_lexicographically_xy_larger(p2,p1) );
 assert( CGAL_lexicographically_xy_larger(p1,p3) );
 assert( CGAL_lexicographically_xy_larger(p2,p3) );
 assert( CGAL_lexicographically_xy_larger(p4,p3) );
 
 assert( CGAL_lexicographically_xy_larger_or_equal(p3,p3) );
 assert( CGAL_lexicographically_xy_larger_or_equal(p2,p3) );
 assert( CGAL_lexicographically_xy_larger_or_equal(p4,p3) );

 cout <<'.';

 assert( CGAL_x_equal(p1,p1) );
 assert( CGAL_x_equal(p2,p3) );
 assert( !CGAL_x_equal(p2,p4) );

 assert( CGAL_y_equal(p3,p6) );
 assert( !CGAL_y_equal(p1,p3) );

 assert( CGAL_compare_x( p1, p2 ) == CGAL_EQUAL );
 assert( CGAL_compare_x( p1, p4 ) == CGAL_SMALLER );
 assert( CGAL_compare_x( p4, p1 ) == CGAL_LARGER );
 assert( CGAL_compare_x( p6, p5 ) == CGAL_LARGER );

 assert( CGAL_compare_y( p3, p6 ) == CGAL_EQUAL );
 assert( CGAL_compare_y( p5, p7 ) == CGAL_SMALLER );
 assert( CGAL_compare_y( p3, p4 ) == CGAL_SMALLER );
 assert( CGAL_compare_y( p2, p1 ) == CGAL_LARGER );

 cout <<'.';

 CGAL_Point_2<R> pe0( R::RT(1), R::RT(0) );
 CGAL_Point_2<R> pe1( R::RT(0), R::RT(1) );

 assert( CGAL_orientation( CGAL_Point_2<R>(CGAL_ORIGIN), pe0, pe1 ) \
                           == CGAL_POSITIVE);
 
 assert( CGAL_orientation( p1, p2, p3) == CGAL_COLLINEAR );
 assert( CGAL_orientation( p1, p2, p4) == CGAL_RIGHTTURN );
 assert( CGAL_orientation( p2, p1, p4) == CGAL_LEFTTURN );
 assert( CGAL_orientation( p5, p4, p3) == CGAL_RIGHTTURN );
 assert( CGAL_orientation( p2, p4, p6) == CGAL_RIGHTTURN );
 assert( CGAL_orientation( p6, p4, p2) == CGAL_LEFTTURN );
 assert( CGAL_orientation( p4, p6, p2) == CGAL_RIGHTTURN );
 assert( CGAL_orientation( p5, p6, p7) == CGAL_COLLINEAR );
 assert( CGAL_orientation( p6, p5, p7) == CGAL_COLLINEAR );

 assert( CGAL_collinear( p1, p2, p3 ) );
 assert( CGAL_collinear( p1, p2, p7 ) );
 assert( CGAL_collinear( p6, p5, p7 ) );
 assert( CGAL_collinear( p1, p2, p3 ) );
 assert( !CGAL_collinear( p1, p2, p4 ) );
 assert( CGAL_collinear( p6, p6, p3 ) );

 assert( CGAL_leftturn( p1, p4, p2 ) );
 assert( CGAL_leftturn( p6, p4, p2 ) );

 assert( CGAL_rightturn( p4, p6, p2 ) );
 assert( CGAL_rightturn( p1, p2, p4 ) );

 cout << '.';

 assert( CGAL_between( p5, p7, p6 ) );   // p7 between p6 and p5
 assert( CGAL_between( p6, p7, p5 ) );   
 assert( CGAL_between( p2, p1, p3 ) );
 assert( !CGAL_between( p7, p6, p5 ) );  
 assert( !CGAL_between( p7, p5, p6 ) );  
 assert( !CGAL_between( p7, p4, p6 ) );  
 assert( !CGAL_between( p2, p4, p6 ) );  
 assert( CGAL_collinear_between( p5, p7, p6 ) );   
 assert( CGAL_collinear_between( p6, p7, p5 ) );   
 assert( CGAL_collinear_between( p2, p1, p3 ) );
 assert( !CGAL_collinear_between( p7, p6, p5 ) );  

 cout << '.';

 CGAL_Vector_2<R>     v( R::RT(10), R::RT(20), R::RT(-5) );
 CGAL_Direction_2<R>  dir1(R::RT(-11),R::RT( 13)),
                      dir2(R::RT( 14),R::RT(-22)),
                      dir3(R::RT(-12),R::RT( 47)),
                      dir4(R::RT(- 7),R::RT(- 8)),
                      dir5(R::RT( -3), R::RT( 4));

 CGAL_Aff_transformation_2<R> rotate1(CGAL_ROTATION,dir1, R::RT(1), R::RT(100)),
                              rotate2(CGAL_ROTATION,dir2, R::RT(1), R::RT(100)),
                              rotate3(CGAL_ROTATION,dir3, R::RT(1), R::RT(100)),
                              rotate4(CGAL_ROTATION,dir4, R::RT(1), R::RT(100)),
                              rotate5(CGAL_ROTATION,dir5, R::RT(1), R::RT(100));



 CGAL_Point_2<R>   p0 = pe1;
 p1 = p0.transform(rotate1);
 p2 = p0.transform(rotate2);
 p3 = p0.transform(rotate3);
 p4 = p0.transform(rotate4);
 p5 = p0.transform(rotate5);

 // assert( (p5 - CGAL_ORIGIN).direction() == dir5 );

 assert( CGAL_side_of_bounded_circle(p1, p2, p3, CGAL_Point_2<R>(CGAL_ORIGIN))\
                                      == CGAL_ON_BOUNDED_SIDE );
 assert( CGAL_side_of_bounded_circle(p1+v, p2+v, p3+v, CGAL_ORIGIN + v) \
                                      == CGAL_ON_BOUNDED_SIDE );
 assert( CGAL_side_of_bounded_circle(p1+v, p2+v, p3+v, CGAL_ORIGIN - v) \
                                      == CGAL_ON_UNBOUNDED_SIDE );
 assert( CGAL_side_of_bounded_circle(p1, p2, p3, p4) \
                                      == CGAL_ON_BOUNDARY );
 assert( CGAL_side_of_bounded_circle(p1+v, p2+v, p3+v, p4+v) \
                                      == CGAL_ON_BOUNDARY );
 assert( CGAL_side_of_bounded_circle(p1+v, p3+v, p4+v, p2+v) \
                                      == CGAL_ON_BOUNDARY );
 assert( CGAL_side_of_bounded_circle(p2+v, p4+v, p1+v, p3+v) \
                                      == CGAL_ON_BOUNDARY );

 assert( CGAL_orientation( p1, p2, p3 ) == CGAL_POSITIVE );

 assert( CGAL_side_of_oriented_circle(p1,p2,p3,CGAL_Point_2<R>(CGAL_ORIGIN))\
                                      == CGAL_ON_POSITIVE_SIDE );
 assert( CGAL_side_of_oriented_circle(p1+v, p2+v, p3+v, CGAL_ORIGIN + v) \
                                      == CGAL_ON_POSITIVE_SIDE );
 assert( CGAL_side_of_oriented_circle(p1+v, p3+v, p2+v, CGAL_ORIGIN + v) \
                                      == CGAL_ON_NEGATIVE_SIDE );
 assert( CGAL_side_of_oriented_circle(p1+v, p2+v, p3+v, CGAL_ORIGIN - v) \
                                      == CGAL_ON_NEGATIVE_SIDE );
 assert( CGAL_side_of_oriented_circle(p2+v, p1+v, p3+v, CGAL_ORIGIN - v) \
                                      == CGAL_ON_POSITIVE_SIDE );
 assert( CGAL_side_of_oriented_circle(p1, p2, p3, p4) \
                                      == CGAL_ON_ORIENTED_BOUNDARY );
 assert( CGAL_side_of_oriented_circle(p1+v, p2+v, p3+v, p4+v) \
                                      == CGAL_ON_ORIENTED_BOUNDARY );
 assert( CGAL_side_of_oriented_circle(p1+v, p3+v, p4+v, p2+v) \
                                      == CGAL_ON_ORIENTED_BOUNDARY );

 cout << "done" << endl;
 return true;
}
#endif // CGAL__TEST_FCT_POINT_2_CC
