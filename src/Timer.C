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
// file          : src/Timer.C
// package       : Timer (2.8)
// revision      : 1.9
// revision_date : 4 April 2001 
// author(s)     : Lutz Kettner  
//                 Matthias Baesken
// coordinator   : INRIA, Sophia Antipolis
//
// A timer class to measure cpu time of user-processes.
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#include <CGAL/Timer.h>

// Determine if the POSIX function getrusage is available, otherwise
// use the previous solution based on std::clock().
// First, detect POSIX. We cannot reliably use "unistd.h", 
// but limits.h is part of the C standard.
#include <climits>
#ifdef _POSIX_ARG_MAX // now that should be POSIX
#include <unistd.h>
#ifdef _POSIX_VERSION
#ifdef _XOPEN_UNIX // XSI: X/Open System Interfaces Extension
#define CGAL__GETRUSAGE 1
#endif
#endif
#endif


#ifdef CGAL__GETRUSAGE
// types, function prototype and constants for the POSIX function
// int getrusage (int who, struct rusage *usage);
#include <sys/resource.h>
// For the numerical limits
#else //  CGAL__GETRUSAGE //
// used for clock()
#include <ctime>
#endif //  CGAL__GETRUSAGE //

// For the numerical limits
#include <float.h>


CGAL_BEGIN_NAMESPACE


// Static member variable for Timer
// =====================================

bool Timer::m_failed = false;

// Member functions for Timer
// =====================================

double Timer::user_process_time() const {
    // Depends on the operating system.
    // Returns a (weakly ;-) monotone increasing time in seconds (with
    // possible wrap-around in case of overflow, see max()), or 0.0
    // if the system call for the time failed. If the system call
    // failed the static flag 'm_failed' is set and can be used
    // by the caller.
#ifdef CGAL__GETRUSAGE
    struct rusage usage;
    int ret = getrusage( RUSAGE_SELF, &usage);
    CGAL_warning_msg( ret == 0, "Call to getrusage() in class CGAL::Timer "
                      "failed - timings will be 0.");
    if ( ret == 0) {
        return double( usage.ru_utime.tv_sec)               // seconds
             + double( usage.ru_utime.tv_usec) / 1000000.0; // microseconds
    }
#else // CGAL__GETRUSAGE //
    CGAL_CLIB_STD::clock_t clk = CGAL_CLIB_STD::clock();
    CGAL_warning_msg( clk != (CGAL_CLIB_STD::clock_t)-1,
        "Call to clock() in class CGAL::Timer failed - timings will be 0.");
    if ( clk != (CGAL_CLIB_STD::clock_t)-1) {
        return double(clk) / CLOCKS_PER_SEC;
    }        
#endif // CGAL__GETRUSAGE //
    m_failed = true;
    return 0.0;
}

double Timer::compute_precision() const {
    // Computes timer precision in seconds dynamically. Note that
    // the timer system call is probably non-trivial and will show
    // up in this time here (probably for one call). But that is just
    // fine that the call to the timer itself if reported as noise 
    // in the precision.
    double min_res = DBL_MAX;
    for ( int i = 0; i < 5; ++i) {
        double current = user_process_time();
        if ( m_failed)
            return -1.0;
        double next    = user_process_time();
        while ( current >= next) { // wait until timer increases
            next = user_process_time();
            if ( m_failed)
                return -1.0;
        }
        // Get the minimum timing difference of all runs.
        if ( min_res > next - current)
            min_res = next - current;
    }
    return min_res;
}

double Timer::precision() const {
    // computes precision upon first call
    // returns -1.0 if timer system call fails.
    static double prec = compute_precision();
    return prec;
}

double Timer::max() const { 
    // Depends on the operating system.
#ifdef CGAL__GETRUSAGE
    return DBL_MAX;
#else // CGAL__GETRUSAGE //
    return 2146.0;
#endif // CGAL__GETRUSAGE //
}

CGAL_END_NAMESPACE

// EOF //
