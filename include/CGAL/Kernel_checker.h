// ======================================================================
//
// Copyright (c) 2001 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/Kernel_checker.h
// package       : Interval_arithmetic (4.141)
// revision      : $Revision: 1.7 $
// revision_date : $Date: 2001/10/10 12:04:19 $
// author(s)     : Sylvain Pion
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_KERNEL_CHECKER_H
#define CGAL_KERNEL_CHECKER_H

// This file contains the definition of a kernel traits checker.
//
// TODO:
// - At the moment, only predicates are checked.  To handle constructions as
//   well, the best approach is probably to have objects be pairs, and do
//   everything in parallel.
//   So the template parameter will be a comparator, not a converter.

#include <CGAL/basic.h>
#include <utility>

CGAL_BEGIN_NAMESPACE

// Class used by Kernel_checker.
template <class O1, class O2, class Conv>
class Predicate_checker
{
    const O1 & o1;
    const O2 & o2;
    Conv c;

public:

    Predicate_checker(const O1 &oo1 = O1(), const O2 &oo2 = O2())
	: o1(oo1), o2(oo2) {}

    typedef typename O1::result_type result_type;

    template <class A1, class A2>
    result_type
    operator()(const A1 &a1, const A2 &a2) const
    {
	typename O1::result_type res1 = o1(a1, a2);
	typename O2::result_type res2 = o2(c(a1), c(a2));
	if (res1 != res2)
	{
	    std::cerr << "Kernel_checker error : " << res1 << " != " << res2
		      << " for the inputs : " << std::endl;
	    std::cerr << a1 << ", " << a2 << std::endl;
#ifdef __GNUG__
	    std::cerr << __PRETTY_FUNCTION__ << std::endl;
#endif
	    CGAL_kernel_assertion(false);
	}
	return res1;
    }

    template <class A1, class A2, class A3>
    result_type
    operator()(const A1 &a1, const A2 &a2, const A3 &a3) const
    {
	typename O1::result_type res1 = o1(a1, a2, a3);
	typename O2::result_type res2 = o2(c(a1), c(a2), c(a3));
	if (res1 != res2)
	{
	    std::cerr << "Kernel_checker error : " << res1 << " != " << res2
		      << " for the inputs : " << std::endl;
	    std::cerr << a1 << ", " << a2 << ", " << a3 << std::endl;
#ifdef __GNUG__
	    std::cerr << __PRETTY_FUNCTION__ << std::endl;
#endif
	    CGAL_kernel_assertion(false);
	}
	return res1;
    }

    template <class A1, class A2, class A3, class A4>
    result_type
    operator()(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4) const
    {
	typename O1::result_type res1 = o1(a1, a2, a3, a4);
	typename O2::result_type res2 = o2(c(a1), c(a2), c(a3), c(a4));
	if (res1 != res2)
	{
	    std::cerr << "Kernel_checker error : " << res1 << " != " << res2
		      << " for the inputs : " << std::endl;
	    std::cerr << a1 << ", " << a2 << ", " << a3 << ", " << a4
		      << std::endl;
#ifdef __GNUG__
	    std::cerr << __PRETTY_FUNCTION__ << std::endl;
#endif
	    CGAL_kernel_assertion(false);
	}
	return res1;
    }

    template <class A1, class A2, class A3, class A4, class A5>
    result_type
    operator()(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4,
	       const A5 &a5) const
    {
	typename O1::result_type res1 = o1(a1, a2, a3, a4, a5);
	typename O2::result_type res2 = o2(c(a1), c(a2), c(a3), c(a4), c(a5));
	if (res1 != res2)
	{
	    std::cerr << "Kernel_checker error : " << res1 << " != " << res2
		      << " for the inputs : " << std::endl;
	    std::cerr << a1 << ", " << a2 << ", " << a3 << ", " << a4
		      << ", " << a5 << std::endl;
#ifdef __GNUG__
	    std::cerr << __PRETTY_FUNCTION__ << std::endl;
#endif
	    CGAL_kernel_assertion(false);
	}
	return res1;
    }

    // Same thing with more arguments...
};

// For now, we inherit all geometric objects and constructions from K1, and
// just overload the predicates.
template <class K1, class K2, class Conv>
class Kernel_checker
  : public K1
{
    typedef K1     Kernel1;
    typedef K2     Kernel2;

    Kernel2 k2;

    typedef Conv   c;

    // typedef std::pair<K1::Point_2, K2::Point_2>  Point_2;
    // ...  Same thing for all objects.

#define CGAL_check_pred(X, Y) \
    typedef Predicate_checker<typename K1::X, typename K2::X, Conv> X; \
    X Y() const { return X(K1::Y(), k2.Y()); }

#define CGAL_Kernel_pred(X,Y,Z) CGAL_check_pred(Y, Z)
#define CGAL_Kernel_cons(X,Y,Z)
#define CGAL_Kernel_pred2(W,X,Y,Z) CGAL_check_pred(Y, Z)
#define CGAL_Kernel_cons2(W,X,Y,Z)

public:

#include <CGAL/Kernel/interface_macros.h>
};

CGAL_END_NAMESPACE

#endif // CGAL_KERNEL_CHECKER_H
