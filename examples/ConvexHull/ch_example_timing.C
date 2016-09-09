#include <CGAL/basic.h>
#include <CGAL/Homogeneous.h>
#include <CGAL/Cartesian.h>

#include <CGAL/leda_integer.h>
#include <CGAL/leda_rational.h>
#include <CGAL/leda_real.h>

#include <CGAL/convex_hull_traits_2.h>

#include <fstream.h>

#include <deque.h>
#include <list.h>
#include <vector.h>

#include <CGAL/ch_akl_toussaint.h>
#include <CGAL/ch_graham_andrew.h>
#include <CGAL/ch_eddy.h>
#include <CGAL/ch_bykat.h>
#include <CGAL/ch_jarvis.h>

#ifndef CGAL_USE_LEDA
#include <stdlib.h>
extern "C" long clock();
#endif // CGAL_USE_LEDA

#include <CGAL/ch_timing_2.h>

typedef double                                            nu_type;
typedef CGAL_Cartesian< nu_type >                         RepCls;
typedef CGAL_convex_hull_traits_2<RepCls>                 TraitsCls;
typedef TraitsCls::Point_2                                Point_2;

int
main( int argc, char* argv[] )
{
  if (argc != 3)   // assertion
  {
      cerr << "Usage: ch_example_timing datafilename ";
      cerr << "number_of_iterations";
      exit(1);
  }
  vector< Point_2 > V;
  vector< Point_2 > VE;
  ifstream F(argv[1]);
  CGAL_set_ascii_mode( F );
  istream_iterator< Point_2, ptrdiff_t>  in_start( F );
  istream_iterator< Point_2, ptrdiff_t>  in_end;
  copy( in_start, in_end , back_inserter(V) );
  copy( V.begin(), V.end(), back_inserter(VE) );
  int iterations = atoi( argv[2] );
  CGAL_ch_timing(V.begin(), V.end(), VE.begin(), iterations, TraitsCls() ); 
  return 0;
}
