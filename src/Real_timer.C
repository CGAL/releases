// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// file          : src/Real_timer.C
// package       : Timer (2.8)
// revision      : 1.9
// revision_date : 4 April 2001 
// author(s)     : Lutz Kettner  
//                 Matthias Baesken
// coordinator   : INRIA, Sophia Antipolis
//
// A timer class to measure real-time.
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#include <CGAL/Real_timer.h>

#if defined (_MSC_VER)
#define CGAL_PROTECT_SYS_TIME_H
#include <sys/timeb.h>
#include <sys/types.h>
#endif

#if defined (__BORLANDC__)
#define CGAL_PROTECT_SYS_TIME_H
#include <sys/timeb>
#include <ctype> 
#endif

#if defined (__MWERKS__)
#define CGAL_PROTECT_SYS_TIME_H
#include <ctime>
#endif

// If none of the above PC compilers, use POSIX fct. gettimeofday()
#ifndef CGAL_PROTECT_SYS_TIME_H
#include <sys/time.h>
#define CGAL_PROTECT_SYS_TIME_H
#endif // CGAL_PROTECT_SYS_TIME_H


CGAL_BEGIN_NAMESPACE


// Static member variable for Real_timer
// =====================================

bool Real_timer::m_failed = false;

// Member functions for Real_timer
// =====================================

double Real_timer::get_real_time() const {
    // Depends on the operating system.
    // Returns a (weakly ;-) monotone increasing time in seconds (with
    // possible wrap-around in case of overflow, see max()), or 0.0
    // if the system call for the time failed. If the system call
    // failed the static flag 'm_failed' is set and can be used
    // by the caller.
#if   defined(_MSC_VER)
    struct _timeb  t;
    _ftime(&t);  
    return double(t.time) + double(t.millitm) / 1000.0;
#elif defined(__BORLANDC__)
    struct timeb t;
    ftime(&t);  
    return double(t.time) + double(t.millitm) / 1000.0;
#elif defined(__MWERKS__)
    static bool initialized = false;
    static CGAL_CLIB_STD::time_t t_begin;
    if ( ! initialized) {
        CGAL_CLIB_STD::time_t tt;
        CGAL_CLIB_STD::time(&tt);
        struct std::tm* lt = CGAL_CLIB_STD::localtime(&tt);
        /// we copy them because mktime can modify
        struct std::tm t = *lt;
        t_begin = CGAL_CLIB_STD::mktime(&t);
    }
    CGAL_CLIB_STD::time_t tt;
    CGAL_CLIB_STD::time(&tt);
    struct std::tm* lt = CGAL_CLIB_STD::localtime(&tt);
    /// we copy them because mktime can modify
    struct std::tm t = *lt;
    CGAL_CLIB_STD::time_t t_end = CGAL_CLIB_STD::mktime(&t);
    return CGAL_CLIB_STD::difftime(t_end, t_begin);
#else // ! _MSC_VER && ! __BORLANDC__ && ! __MWERKS__ //
    struct timeval t;
    int ret = gettimeofday( &t, NULL);
    CGAL_warning_msg( ret == 0, "Call to gettimeofday() in class "
                      "CGAL::Real_timer failed - timings will be 0.");
    if ( ret == 0) {
        return double(t.tv_sec) + double(t.tv_usec) / 1000000;
    }
    m_failed = true;
    return 0.0;
#endif // ! _MSC_VER && ! __BORLANDC__ && ! __MWERKS__ //
}

double Real_timer::compute_precision() const {
    // Computes timer precision in seconds dynamically. Note that
    // the timer system call is probably non-trivial and will show
    // up in this time here (probably for one call). But that is just
    // fine that the call to the timer itself if reported as noise 
    // in the precision.
    double min_res = DBL_MAX;
    for ( int i = 0; i < 5; ++i) {
        double current = get_real_time();
        if ( m_failed)
            return -1.0;
        double next    = get_real_time();
        while ( current >= next) { // wait until timer increases
            next = get_real_time();
            if ( m_failed)
                return -1.0;
        }
        // Get the minimum timing difference of all runs.
        if ( min_res > next - current)
            min_res = next - current;
    }
    return min_res;
}

double Real_timer::precision() const {
    // computes precision upon first call
    // returns -1.0 if timer system call fails.
    static double prec = compute_precision();
    return prec;
}

CGAL_END_NAMESPACE

// EOF //
