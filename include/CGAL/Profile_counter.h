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
// file          : include/CGAL/Profile_counter.h
// package       : Interval_arithmetic (4.141)
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2001/10/03 16:55:10 $
// author(s)     : Sylvain Pion
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_PROFILE_COUNTER_H
#define CGAL_PROFILE_COUNTER_H

// This file contains the class Profile_counter which is able to keep track
// of a number, and prints a message in the destructor.
// Typically, it can be used as a profile counter in a static variable.

#include <CGAL/basic.h>

CGAL_BEGIN_NAMESPACE

struct Profile_counter
{
    Profile_counter(const char *ss)
	: i(0), s(ss) {}

    void operator++() { ++i; }

    ~Profile_counter()
    {
	std::cerr << "Profile counter : " << s << " = " << i << std::endl;
    }

private:
    unsigned int i;
    const char *s;
};

#ifdef CGAL_PROFILE
#  define CGAL_PROFILER(X, Y) static CGAL::Profile_counter X(Y); ++X;
#else
#  define CGAL_PROFILER(X, Y)
#endif

CGAL_END_NAMESPACE

#endif // CGAL_PROFILE_COUNTER_H
