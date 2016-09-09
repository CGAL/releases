/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/


#ifndef CGAL_UTILS_H
#define CGAL_UTILS_H

#include <assert.h>

#if 0
#define DYNAMIC_CAST(Type, Expr) dynamic_cast<Type> (Expr)
#else
#define DYNAMIC_CAST(Type, Expr) (Type) (Expr)
#endif

extern void cgal_assertion_fail(const char *, const char *,
                                int, const char *);

extern void cgal_precondition_fail(const char *, const char *,
                                   int, const char *);

extern void cgal_postcondition_fail(const char *, const char *,
                                    int, const char *);

extern void cgal_check_fail(const char *, const char *,
                            int, const char *);


void not_implemented();

#ifdef CGAL_CHECK_ASSERTIONS
#define CGAL_kernel_assertion(EX) \
 ((EX)?((void)0):cgal_assertion_fail( # EX , __FILE__, __LINE__, NULL))

#define CGAL_kernel_assertion_msg(EX,MSG) \
 ((EX)?((void)0):cgal_assertion_fail( # EX , __FILE__, __LINE__, MSG))

#else
#define CGAL_kernel_assertion(EX) ((void)0)
#define CGAL_kernel_assertion_msg(EX,MSG) ((void)0)

#endif /* CGAL_CHECK_ASSERTIONS */



#ifdef CGAL_CHECK_PRECONDITIONS
#define CGAL_kernel_precondition(EX) \
 ((EX)?((void)0):cgal_precondition_fail( # EX , __FILE__, __LINE__, NULL))

#define CGAL_kernel_precondition_msg(EX,MSG) \
 ((EX)?((void)0):cgal_precondition_fail( # EX , __FILE__, __LINE__, MSG))

#else
#define CGAL_kernel_precondition(EX) ((void)0)
#define CGAL_kernel_precondition_msg(EX,MSG) ((void)0)
#endif /* CGAL_CHECK_PRECONDITIONS */


#ifdef CGAL_CHECK_EXACTNESS_PRECONDITIONS
#define CGAL_exactness_precondition(EX) \
 ((EX)?((void)0):cgal_precondition_fail( # EX , __FILE__, __LINE__, NULL))

#define CGAL_exactness_precondition_msg(EX,MSG) \
 ((EX)?((void)0):cgal_precondition_fail( # EX , __FILE__, __LINE__, MSG))
#else
#define CGAL_exactness_precondition(EX) ((void)0)
#define CGAL_exactness_precondition_msg(EX,MSG) ((void)0)
#endif /* CGAL_CHECK_EXACTNESS_PRECONDITIONS */


#ifdef CGAL_CHECK_POSTCONDITIONS
#define CGAL_kernel_postcondition(EX) \
 ((EX)?((void)0):cgal_postcondition_fail( # EX , __FILE__, __LINE__, NULL))

#define CGAL_kernel_postcondition_msg(EX,MSG) \
 ((EX)?((void)0):cgal_postcondition_fail( # EX , __FILE__, __LINE__, MSG))

#else

#define CGAL_kernel_postcondition(EX) ((void)0)
#define CGAL_kernel_postcondition_msg(EX,MSG) ((void)0)
#endif /* CGAL_CHECK_POSTCONDITIONS */


#ifdef CGAL_CHECK_EXACTNESS_POSTCONDITIONS
#define CGAL_exactness_postcondition(EX) \
 ((EX)?((void)0):cgal_postcondition_fail( # EX , __FILE__, __LINE__, NULL))

#define CGAL_exactness_postcondition_msg(EX,MSG) \
 ((EX)?((void)0):cgal_postcondition_fail( # EX , __FILE__, __LINE__, MSG))

#else

#define CGAL_exactness_postcondition(EX) ((void)0)
#define CGAL_exactness_postcondition_msg(EX,MSG) ((void)0)
#endif /* CGAL_CHECK_EXACTNESS_POSTCONDITIONS */


#ifdef CGAL_CHECK_NONDEGENERACY_PRECONDITIONS
#define CGAL_nondegeneracy_precondition(EX) \
 ((EX)?((void)0):cgal_precondition_fail( # EX , __FILE__, __LINE__, \
                           "algorithm works only for nondegenerate objects"))
#else
#define CGAL_nondegeneracy_precondition(EX) ((void)0)
#endif /* CGAL_CHECK_NONDEGENERACY_PRECONDITIONS */


#ifdef CGAL_CHECK_DEGENERACY
#define CGAL_nondegeneracy_assertion \
 is_degenerate() ? cgal_assertion_fail( "! is_degenerate()" , \
                                        __FILE__, __LINE__, NULL)) : ((void)0)
#else

#define CGAL_nondegeneracy_assertion ((void)0)
#endif /* CGAL_CHECK_DEGENERACY */



#ifdef CGAL_CHECK_CHECKS
#define CGAL_kernel_check(EX) \
 ((EX)?((void)0):cgal_check_fail( # EX , __FILE__, __LINE__, NULL))

#define CGAL_kernel_check_msg(EX,MSG) \
 ((EX)?((void)0):cgal_check_fail( # EX , __FILE__, __LINE__, MSG))

#else

#define CGAL_kernel_check(EX) ((void)0)
#define CGAL_kernel_check_msg(EX,MSG) ((void)0)
#endif /* CGAL_CHECK_CHECKS */

extern void cgal_set_assertion_handler(
        void (*handler)(const char *, const char *, int, const char *));

extern void cgal_set_precondition_handler(
        void (*handler)(const char *, const char *, int, const char *));

extern void cgal_set_postcondition_handler(
        void (*handler)(const char *, const char *, int, const char *));

extern void cgal_set_check_handler(
        void (*handler)(const char *, const char *, int, const char *));
#endif
