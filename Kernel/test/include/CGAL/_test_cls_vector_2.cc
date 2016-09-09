#line 32 "/u/sargas/2/prisme/fabri/Cgal/Kernel/web/test_kernel_2.fw"
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL__TEST_CLS_VECTOR_2_CC
#define CGAL__TEST_CLS_VECTOR_2_CC
#include <CGAL/_test_cls_vector_2.h>

template <class R>
bool
CGAL__test_cls_vector_2(const R& )
{
 cout << "Testing class Vector_2" ;

 R::Vector_2       iv;

 CGAL_Vector_2<R>  v1;
 CGAL_Vector_2<R>  v2(iv);
 CGAL_Vector_2<R>  v0(CGAL_NULL_VECTOR);

 R::RT  n1( 12 );
 R::RT  n2( -4 );
 R::RT  n3(  6 );
 R::RT  n4(  2 );

 CGAL_Vector_2<R>  v3(n1, n2 );       // ( 12, -4)
 CGAL_Vector_2<R>  v4(n1, n2, n4);    // (  6, -2)
 CGAL_Vector_2<R>  v5(n1, n2, n4);    // (  6, -2)
 CGAL_Vector_2<R>  v6( v5 );
                   v1 = v4;
 CGAL_Vector_2<R>  v7(-n1, -n2, -n4); // (  6, -2)

 
 cout << '.';

 assert( v4 == v5 );
 assert( v5 == v6 );
 assert( v4 == v6 );
 assert( v1 == v6 );
 assert( v0 == CGAL_NULL_VECTOR);
 assert( v5 == v7 );

 assert( v3 != v4 );
 assert( v0 != v1 );
 assert( v1 != CGAL_NULL_VECTOR);

 assert( v3.hx() == n1 );   // don't replace v3 
 assert( v3.hy() == n2 );

 assert( R::FT( v5.hx()) / R::FT(v5.hw()) == R::FT( n1) / R::FT( n4) );
 assert( R::FT( v5.hy()) / R::FT(v5.hw()) == R::FT( n2) / R::FT( n4) );
 
 assert( v5.x() == R::FT( n1) / R::FT( n4) );
 assert( v5.y() == R::FT( n2) / R::FT( n4) );
 
 cout << '.';

 assert( v3.homogeneous(0) == v3.hx() );  // don't replace v3 
 assert( v3.homogeneous(1) == v3.hy() );
 assert( v3.homogeneous(2) == v3.hw() );
 assert( v6.cartesian(0) == v6.x() ); 
 assert( v6.cartesian(1) == v6.y() );

 cout << '.';

 assert( v0.dimension() == 2 );
 assert( v4.homogeneous( v4.dimension() ) == v4.hw() );

 cout << "done" << endl;
 return true;
}
#endif // CGAL__TEST_CLS_VECTOR_2_CC
