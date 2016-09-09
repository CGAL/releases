#line 534 "/u/sargas/2/prisme/fabri/Cgal/Kernel/web/test_kernel_3.fw"
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL__TEST_CLS_DIRECTION_3_CC
#define CGAL__TEST_CLS_DIRECTION_3_CC
#include <CGAL/_test_cls_direction_3.h>

template <class R>
bool
CGAL__test_cls_direction_3(const R& )
{
 cout << "Testing class Direction_3" ;

 R::Direction_3  id;

 CGAL_Direction_3<R> d0;
 CGAL_Direction_3<R> d1(id);

 cout << '.';
 R::RT   n0 = 10;
 R::RT  n1 = 8;
 R::RT  n2 = 4;
 R::RT  n3 = 2;

 CGAL_Vector_3<R>  v( n1, n2, n3); 
 CGAL_Direction_3<R> d2(v);
 CGAL_Direction_3<R> d3( n0, n1, n2);
 CGAL_Direction_3<R> d4( d3 );
 CGAL_Direction_3<R> d5 = d3;

 assert( d3 == d3 );
 assert( d3 == d4 );
 assert( d5 == d3 );
 assert( d2 != d3 );
 assert( d3 != d2 );

 cout << '.';
 CGAL_Vector_3<R> vv = d2.vector();
 assert( v == vv );

 d0 = -d3;
 
 assert( d0 != d3 );
 assert( d3 == -d0);
 
 cout << '.';
 assert( d3.delta(0) == n0 );
 assert( d3.delta(1) == n1 );
 assert( d3.delta(2) == n2 );
 assert( d3.delta(0) == d3.dx() );
 assert( d3.delta(1) == d3.dy() );
 assert( d3.delta(2) == d3.dz() );

 cout << "done" << endl;
 return true;
}

#endif // CGAL__TEST_CLS_DIRECTION_3_CC
