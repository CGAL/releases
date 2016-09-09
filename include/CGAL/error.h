// Source: error.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_ERROR_H
#define CGAL_ERROR_H


int CGAL_breakpoint(char *msg);




#ifdef CGAL_CHECK_PRECONDITIONS

extern void CGAL_kernel_assert(int expr);

#define CGAL_kernel_precondition(expr) CGAL_kernel_assert(expr)

#else

#define CGAL_kernel_precondition(expr) 1

#endif


#endif

