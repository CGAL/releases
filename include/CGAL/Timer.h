// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/Timer.h
// package       : Timer (1.8)
// revision      : 1.8
// revision_date : 11 August 2000 
// author(s)     : Lutz Kettner  
//                 Matthias Baesken
// coordinator   : INRIA, Sophia Antipolis
//
// A timer class to measure cpu time of user-processes.
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_TIMER_H
#define CGAL_TIMER_H 1

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif
#ifndef CGAL_PROTECT_CSTDLIB
#include <cstdlib>
#define CGAL_PROTECT_CSTDLIB
#endif
#ifndef CGAL_PROTECT_CLIMITS
#include <climits>
#define CGAL_PROTECT_CLIMITS
#endif

// used for clock()
#ifndef CGAL_PROTECT_CTIME
#include <ctime>
#define CGAL_PROTECT_CTIME
#endif

CGAL_BEGIN_NAMESPACE

// SECTION: A Timer for User-Process Time
// ========================================================================
// 
// DEFINITION
// 
// A timer `t' of type Timer is an object with a state. It is either
// running or it is stopped. The state is controlled with `t.start()'
// and `t.stop()'. The timer counts the time elapsed since its creation
// or last reset. It counts only the time where it is in the running
// state. The time information is given in seconds.

class Timer {
private:
    CGAL_CLIB_STD::clock_t  elapsed;
    CGAL_CLIB_STD::clock_t  started;
    int           interv;
    bool          running;

public:
    Timer() : elapsed(0), started(0), interv(0), running(false) {}

    void     start();
    void     stop ();
    void     reset();
    bool     is_running() const { return running; }

    double   time()       const;
    int      intervals()  const { return interv; }
    double   precision()  const { return 0.01; }
    double   max() const        { return 2146.0;}
};


/*****************************************************************************/

// Member functions Timer
// ===========================

inline void Timer::start() {
    CGAL_assertion( ! running);
    started = CGAL_CLIB_STD::clock();
    if (started == (CGAL_CLIB_STD::clock_t)-1) {
        // possible on Solaris according to man-page
#if defined (_MSC_VER)
	std::cout << "Timer error: CGAL_CLIB_STD::clock() returned -1.\n";
#else
	std::cerr << "Timer error: CGAL_CLIB_STD::clock() returned -1.\n";
#endif
	CGAL_CLIB_STD::abort();
    }
    running = true;
    ++ interv;
}

inline void Timer::stop() {
    CGAL_assertion( running);
    elapsed += CGAL_CLIB_STD::clock() - started;
    running  = false;
}

inline void Timer::reset() {
    interv = 0;
    elapsed = 0;
    if (running) {
	started = CGAL_CLIB_STD::clock();
	++ interv;
    }
}

inline double Timer::time() const {
    if (running) {
	return double( elapsed  + CGAL_CLIB_STD::clock() - started) / CLOCKS_PER_SEC;
    }
    return double(elapsed) / CLOCKS_PER_SEC;
}

CGAL_END_NAMESPACE

#endif // CGAL_TIMER_H //
// EOF //
