#line 113 "/u/sargas/2/prisme/fabri/Cgal/Kernel/web/test_kernel_2.fw"
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL__TEST_FCT_VECTOR_2_CC
#define CGAL__TEST_FCT_VECTOR_2_CC
#include <CGAL/_test_fct_vector_2.h>

template <class R>
bool
CGAL__test_fct_vector_2(const R& )
{
 cout << "Testing functions Vector_2" ;

 R::RT  n1( 12 );
 R::RT  n2( -4 );
 R::RT  n3(  6 );
 R::RT  n4(  2 );
 R::RT  n5(  9 );
 R::RT  n6(-18 );
 R::RT  n7( 36 );
 R::RT  n8(  3 );
 R::RT  n9( 15 );
 R::RT n10( -8 );

 CGAL_Vector_2<R>  v0(CGAL_NULL_VECTOR);   // ( 0, 0)
 CGAL_Vector_2<R>  v1(n1, n2, n4);         // ( 6,-2)
 CGAL_Vector_2<R>  v2(n5, n6, n8);         // ( 3,-6)
 CGAL_Vector_2<R>  v3(n5, n10);            // ( 9,-8)
 CGAL_Vector_2<R>  v4(n8, -n2 );           // ( 3, 4)
 CGAL_Vector_2<R> mv4(-n8, n2 );           // (-3,-4)

 R::RT  n15( -5 );
 CGAL_Vector_2<R>  v8( n1,  n3, -n4);      // (-6,-3)
 CGAL_Vector_2<R>  v9( R::RT(0), n15);     // ( 0,-5)

 assert( v1 + v2 == v3 );
 assert( v1 - v2 == v4 );
 assert( v3 - v1 == v2 );
 assert( v3 - v2 == v1 );
 assert( v4 + v2 == v1 );
 assert( v4 + v2 == v3 - v2);
 assert( v9 == v1 + v8 );

 cout << '.';

 assert( (-(- v1)) == v1 ); 
 assert( -v4 == mv4);
 assert( mv4 == v2 - v1);
 assert( -( v1 - v2) == mv4);
 assert( v1 + v0 == v1 );
 assert( v0 - v4 == mv4 );
 assert( v0 + v4 == v4 );
 assert( v2 - v0 == v2 );
 
 cout << '.';

#ifdef CGAL_VECTOR_WRAPPER
 assert( R::FT(v1 * v2) == R::FT(30) );
 assert( R::FT(v1 * v0) == R::FT(0) );
 assert( CGAL_Vector_2<R>( n1, n2) == R::RT(2) * v1 );
 assert( (CGAL_Vector_2<R>&)(R::RT(2) * v1) == CGAL_Vector_2<R>( n1, n2) );
 assert( CGAL_Vector_2<R>( n5, n6) == R::RT(3) * v2 );
 assert( v2 / R::RT(3) == CGAL_Vector_2<R>( R::RT(1), -n4) );
 assert( (CGAL_Vector_2<R>&)(R::RT(3) * (v2 / R::RT(3))) == v2 );
 assert( (CGAL_Vector_2<R>&)(R::RT(3) * v2 ) / R::RT(3) == v2 );
 // assert( (R::RT(3) * v2 ) / R::RT(3) == v2 );
 // ->: no match for
 //  `operator ==(class CGAL_Quotient<integer>, 
 //               class CGAL_Vector_2<CGAL_Homogeneous<integer> >)'
#else // no multiplication scalar * vector ( only from the right side )
 assert( v1 * v2 == R::FT(30) );
 assert( v1 * v2 == R::FT(30) );
 assert( v1 * v0 == R::FT(0) );
 assert( CGAL_Vector_2<R>( n1, n2) == v1 * R::RT(2));
 assert( CGAL_Vector_2<R>( n5, n6) == v2 * R::RT(3));
 assert( v2 / R::RT(3) == CGAL_Vector_2<R>( R::RT(1), -n4) );
 assert( (v2 * R::RT(3)) / R::RT(3) == v2 );
 assert( (v2 / R::RT(3)) * R::RT(3) == v2 );
#endif // CGAL_VECTOR_WRAPPER
 
 cout << '.';

 assert( v2.cartesian(0) == v2[0] ); 
 assert( v2.cartesian(1) == v2[1] );
 
 CGAL_Point_2<R> p0(CGAL_ORIGIN);
 CGAL_Point_2<R> p1 = CGAL_ORIGIN + v1;
 CGAL_Point_2<R> p2 = CGAL_ORIGIN + v2;
 CGAL_Point_2<R> p3 = CGAL_ORIGIN + v3;

 assert( CGAL_ORIGIN + v2 == CGAL_Point_2<R>( n5, n6, n8) );
 assert( CGAL_ORIGIN - v2 == CGAL_Point_2<R>( -n5, -n6, n8) );
 assert( p1 - p1 == v0 );
 assert( p1 - p0 == p1 - CGAL_ORIGIN);
 assert( p1 - p2 == v4 );
 assert( p2 + v4 == p1 );
 assert( p3 - v1 == p2 );
 assert( p3 - p1 == v2 );

 cout << "done" << endl;
 return true;
}
#endif // CGAL__TEST_FCT_VECTOR_2_CC
