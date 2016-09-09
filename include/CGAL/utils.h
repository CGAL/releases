
#ifndef CGAL_UTILS_H
#define CGAL_UTILS_H

#include <assert.h>

#if 0
#define DYNAMIC_CAST(Type, Expr) dynamic_cast<Type> (Expr)
#else
#define DYNAMIC_CAST(Type, Expr) (Type) (Expr)
#endif

extern void cgal_assertion_fail(const char *, const char *, int);
extern void cgal_precondition_fail(const char *, const char *, int);
extern void cgal_postcondition_fail(const char *, const char *, int);
extern void cgal_check_fail(const char *, const char *, int);

void not_implemented();

#ifdef CGAL_CHECK_ASSERTIONS
#define CGAL_kernel_assertion(EX) \
 ((EX)?((void)0):cgal_assertion_fail( # EX , __FILE__, __LINE__))
#else
#define CGAL_kernel_assertion(EX) ((void)0)
#endif /* CGAL_CHECK_ASSERTIONS */

#ifdef CGAL_CHECK_PRECONDITIONS
#define CGAL_kernel_precondition(EX) \
 ((EX)?((void)0):cgal_precondition_fail( # EX , __FILE__, __LINE__))
#else
#define CGAL_kernel_precondition(EX) ((void)0)
#endif /* CGAL_CHECK_PRECONDITIONS */


#ifdef CGAL_CHECK_EXACTNESS_PRECONDITIONS
#define CGAL_exactness_precondition(EX) \
 ((EX)?((void)0):cgal_precondition_fail( # EX , __FILE__, __LINE__))
#else
#define CGAL_exactness_precondition(EX) ((void)0)
#endif /* CGAL_CHECK_EXACTNESS_PRECONDITIONS */


#ifdef CGAL_CHECK_POSTCONDITIONS
#define CGAL_kernel_postcondition(EX) \
 ((EX)?((void)0):cgal_postcondition_fail( # EX , __FILE__, __LINE__))
#else
#define CGAL_kernel_postcondition(EX) ((void)0)
#endif /* CGAL_CHECK_POSTCONDITIONS */


#ifdef CGAL_CHECK_EXACTNESS_POSTCONDITIONS
#define CGAL_exactness_postcondition(EX) \
 ((EX)?((void)0):cgal_postcondition_fail( # EX , __FILE__, __LINE__))
#else
#define CGAL_exactness_postcondition(EX) ((void)0)
#endif /* CGAL_CHECK_EXACTNESS_POSTCONDITIONS */


#ifdef CGAL_CHECK_NONDEGENERACY_PRECONDITIONS
#define CGAL_nondegeneracy_precondition(EX) \
 ((EX)?((void)0):cgal_precondition_fail( # EX , __FILE__, __LINE__))
#else
#define CGAL_nondegeneracy_precondition(EX) ((void)0)
#endif /* CGAL_CHECK_NONDEGENERACY_PRECONDITIONS */


#ifdef CGAL_CHECK_DEGENERACY
#define CGAL_nondegeneracy_assertion \
 is_degenerate() ? cgal_assertion_fail( "degenerate object" ,
                                        __FILE__, __LINE__)) : ((void)0)
#else
#define CGAL_nondegeneracy_assertion ((void)0)
#endif /* CGAL_CHECK_DEGENERACY */



#ifdef CGAL_CHECK_CHECKS
#define CGAL_kernel_check(EX) \
 ((EX)?((void)0):cgal_check_fail( # EX , __FILE__, __LINE__))
#else
#define CGAL_kernel_check(EX) ((void)0)
#endif /* CGAL_CHECK_CHECKS */

extern void cgal_set_assertion_handler(
        void (*handler)(const char *, const char *, int));

extern void cgal_set_precondition_handler(
        void (*handler)(const char *, const char *, int));

extern void cgal_set_postcondition_handler(
        void (*handler)(const char *, const char *, int));

extern void cgal_set_check_handler(
        void (*handler)(const char *, const char *, int));
#endif
