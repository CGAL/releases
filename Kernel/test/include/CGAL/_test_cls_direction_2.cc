#line 595 "/u/sargas/2/prisme/fabri/Cgal/Kernel/web/test_kernel_2.fw"
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL__TEST_CLS_DIRECTION_2_CC
#define CGAL__TEST_CLS_DIRECTION_2_CC
#include <CGAL/_test_cls_direction_2.h>

template <class R>
bool
CGAL__test_cls_direction_2(const R& )
{
 cout << "Testing class Direction_2" ;

 R::Direction_2  id;

 CGAL_Direction_2<R> d0;
 CGAL_Direction_2<R> d1(id);

 cout << '.';
 R::RT  n0 = 10;
 R::RT  n1 = 8;
 R::RT  n2 = 4;
 R::RT  n3 = 2;

 CGAL_Vector_2<R>  v( n1, n2);      // (8,4)
 CGAL_Direction_2<R> d2(v);
 CGAL_Direction_2<R> d3( n0, n1);   // (10,8)
 CGAL_Direction_2<R> d4( d3 );
 CGAL_Direction_2<R> d5 = d3;

 assert( d3 == d3 );
 assert( d3 == d4 );
 assert( d5 == d3 );
 assert( d2 != d3 );
 assert( d3 != d2 );

 cout << '.';
 CGAL_Vector_2<R> vv = d2.vector();
 assert( v == vv );

 d0 = -d3;
 
 assert( d0 != d3 );
 assert( d3 == -d0);
 
 cout << '.';
 assert( d3.delta(0) == n0 );
 assert( d3.delta(1) == n1 );
 assert( d3.delta(0) == d3.dx() );
 assert( d3.delta(1) == d3.dy() );

 cout << "done" << endl;
 return true;
}

#endif // CGAL__TEST_CLS_DIRECTION_2_CC
