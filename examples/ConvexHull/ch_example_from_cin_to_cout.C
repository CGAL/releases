#include <CGAL/basic.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/ch_graham_andrew.h>

typedef   CGAL_Point_2<CGAL_Cartesian<double> >        Point_2;

int
main()
{
  CGAL_set_ascii_mode(cin); 
  CGAL_set_ascii_mode(cout); 
  istream_iterator< Point_2, ptrdiff_t >  in_start( cin );
  istream_iterator< Point_2, ptrdiff_t >  in_end;
  ostream_iterator< Point_2 >             out( cout, "\n" );
  CGAL_ch_graham_andrew( in_start, in_end, out );
  return 0;
}

