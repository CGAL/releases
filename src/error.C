// Source: error.C
// Author: Andreas.Fabri@sophia.inria.fr

#include <stdlib.h>
#include <stream.h>
#include <CGAL/error.h>


int CGAL_breakpoint(char *msg)
{
  cerr  << msg << endl;
  return 1;
}






void CGAL_kernel_assert(int expr)

{
  if (! expr) {
    CGAL_breakpoint("stop in CGAL_breakpoint");
    exit(-1);
  }
}



