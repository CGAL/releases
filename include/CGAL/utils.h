//  Copyright CGAL 1996
//
//  cgal@cs.ruu.nl
//
//  This file is part of an internal release of the CGAL kernel.
//  The code herein may be used and/or copied only in accordance
//  with the terms and conditions stipulated in the agreement
//  under which the code has been supplied or with the written
//  permission of the CGAL Project.
//
//  Look at http://www.cs.ruu.nl/CGAL/ for more information.
//  Please send any bug reports and comments to cgal@cs.ruu.nl
//
//  The code comes WITHOUT ANY WARRANTY; without even the implied
//  warranty of FITNESS FOR A PARTICULAR PURPOSE.
//

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
