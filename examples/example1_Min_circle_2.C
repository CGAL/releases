// ============================================================================
// The CGAL Project
// Example Program: 2D Smallest Enclosing Circle (1)
// ----------------------------------------------------------------------------
// file  : example/example1_Min_circle_2.C
// author: Sven Schönherr 
// ----------------------------------------------------------------------------
// $Revision: 3.1 $
// $Date: 1997/06/23 13:23:20 $
// ============================================================================
 
#include <CGAL/Gmpz.h>
#include <CGAL/Homogeneous.h>
#include <CGAL/Point_2.h>
#include <CGAL/Optimisation_traits_2.h>
#include <CGAL/Min_circle_2.h>
#include <iostream.h>

typedef  CGAL_Gmpz                      NT;
typedef  CGAL_Homogeneous<NT>           R;
typedef  CGAL_Point_2<R>                Point;
typedef  CGAL_Optimisation_traits_2<R>  Traits;
typedef  CGAL_Min_circle_2<Traits>      Min_circle;

int
main( int, char**)
{
    int     n = 100;
    Point*  P = new Point[ n];

    for ( int i = 0; i < n; ++i)
	P[ i] = Point( (i%2 == 0 ? i : -i), 0);
    /* (0,0), (-1,0), (2,0), (-3,0), ... */

    /* very slow */
    cout << "without randomization..." << flush;
    Min_circle  mc1( P, P+n);
    cout << "done" << endl;

    /* fast */
    cout << "with randomization..." << flush;
    Min_circle  mc2( P, P+n, true);
    cout << "done" << endl;

    delete[] P;
}

// ===== EOF ==================================================================
