#line 661 "/u/sargas/2/prisme/fabri/Cgal/Kernel/web/test_kernel_2.fw"
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL__TEST_FCT_DIRECTION_2_CC
#define CGAL__TEST_FCT_DIRECTION_2_CC
#include <CGAL/_test_fct_direction_2.h>

template <class R>
bool
CGAL__test_fct_direction_2(const R& )
{
 cout << "Testing functions Direction_2" ;

 R::RT n0 =  0;
 R::RT n1 =  1;
 R::RT n2 =  2;
 R::RT n3 =  3;
 R::RT n4 =  4;
 R::RT n5 =  5;
 R::RT n6 =  6;
 R::RT n8 =  8;

 CGAL_Direction_2<R> d[8];
 d[0] = CGAL_Direction_2<R>( n5, n0 );
 d[1] = CGAL_Direction_2<R>( n8, n3 );
 d[2] = CGAL_Direction_2<R>( n0, n4 );
 d[3] = CGAL_Direction_2<R>(-n4, n3 );
 d[4] = CGAL_Direction_2<R>(-n2, n0 );
 d[5] = CGAL_Direction_2<R>(-n4,-n6 );
 d[6] = CGAL_Direction_2<R>( n0,-n1 );
 d[7] = CGAL_Direction_2<R>( n4,-n5 );

 cout << '.';

 assert( d[0] >= d[0] );
 assert( d[0] <= d[0] );

 cout << '.';

 int i;
 int j;

 for ( i = 1; i <= 7; i++ )
 {
    // cout << endl;
    for ( j = 0; j+i <= 7; j++)
    {
        // cout << '('  << j << ',' << j+i << ')' ;
        assert( d[j] <= d[j+i] );
        assert( d[j] <  d[j+i] );
    }
    // cout << ' ';
    for (      ; j <= 7; j++)
    {
        // cout << '('  << j << ',' << (j+i)%8 << ')' ;
        assert( d[j] >= d[(j+i)%8] );
        assert( d[j] >  d[(j+i)%8] );
    }
    assert( d[i] >= d[i] );
    assert( d[i] <= d[i] );
 }

 cout << '.';
  
 cout << "done" << endl;
 return true;
}
#endif // CGAL__TEST_FCT_DIRECTION_2_CC
