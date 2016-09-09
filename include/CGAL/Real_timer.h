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
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : include/CGAL/Real_timer.h
// package       : Timer (1.5)
// author(s)     : Lutz Kettner
//                 Matthias Baesken
// coordinator   : INRIA, Sophia Antipolis
//
// A timer class to measure real-time.
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_REAL_TIMER_H
#define CGAL_REAL_TIMER_H 1

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

#if defined (_MSC_VER)
#define CGAL_PROTECT_SYS_TIME_H
#include <sys/timeb.h>
#include <sys/types.h>
#endif

// used for gettimeofday()
#ifndef CGAL_PROTECT_SYS_TIME_H
#include <sys/time.h>
#define CGAL_PROTECT_SYS_TIME_H
#endif // CGAL_PROTECT_SYS_TIME_H

CGAL_BEGIN_NAMESPACE

// SECTION: A Timer Measuring Real-Time
// ========================================================================
// 
// DEFINITION
// 
// A timer `t' of type Real_timer is an object with a state. It is
// either running or it is stopped. The state is controlled with
// `t.start()' and `t.stop()' . The timer counts the time elapsed since
// its creation or last reset. It counts only the time where it is in the
// running state. The time information is given in seconds.

class Real_timer {
private:
    double          elapsed;

#if !defined (_MSC_VER)
    struct timeval  started;
#else
    struct _timeb   started;
#endif

    int             interv;
    bool            running;
    double          eps;

public:
    Real_timer() : elapsed(0), interv(0), running(false) {}

    void     start();
    void     stop ();
    void     reset();
    bool     is_running() const { return running; }

    double   time()       const;
    int      intervals()  const { return interv; }
    double   precision()  const 
    { 
      return -1;
	  // change it ...
    }
    double   max() const        { return double(INT_MAX);}
};


/*****************************************************************************/

// Member functions Real_timer
// ================================

inline void Real_timer::start() {
    CGAL_assertion( ! running);
    int res=0;

#if !defined (_MSC_VER)
    res = gettimeofday( &started, NULL);
#else
    _ftime(&started);  
#endif    

    if ( res < 0) {
#if !defined (_MSC_VER)
	std::cerr << "Real_timer error: gettimeofday() returned -1.\n";
	CGAL_CLIB_STD::abort();
#endif
    }
    running = true;
    ++ interv;
}

inline void Real_timer::stop() {
    CGAL_assertion(running);

#if !defined (_MSC_VER)
    struct timeval t;
#else
    struct _timeb t;
#endif

   int res=0;

#if !defined (_MSC_VER)
    res = gettimeofday( &t, NULL);
#else
    _ftime(&t);
#endif

    if ( res < 0) {
#if !defined (_MSC_VER)
	std::cerr << "Real_timer error: gettimeofday() returned -1.\n";
	CGAL_CLIB_STD::abort();
#endif
    }

#if !defined (_MSC_VER)
    elapsed +=   double(t.tv_sec  - started.tv_sec) 
               + double(t.tv_usec - started.tv_usec) / 1000000;
#else
    elapsed += ((double)(t.time - started.time)) + ((double)(t.millitm - started.millitm))/1000.0;
#endif

    running  = false;
}

inline void Real_timer::reset() {
    interv = 0;
    elapsed = 0;
    if (running) {
	int res = 0;

#if !defined(_MSC_VER)
        res = gettimeofday( &started, NULL);
#else
        _ftime(&started);
#endif        

	if ( res < 0) {
#if !defined (_MSC_VER)
	    std::cerr << "Real_timer error: gettimeofday() returned -1.\n";
	    CGAL_CLIB_STD::abort();
#else
	    std::cout << "Real_timer error!.\n";
#endif
	}
	++ interv;
    }
}

inline double Real_timer::time() const {
    if (running) {

#if !defined (_MSC_VER)
	struct timeval t;
#else
    struct _timeb t;
#endif

	int res = 0;

#if !defined(_MSC_VER)
        res = gettimeofday( &t, NULL);
#else
        _ftime(&t);
#endif 

	if ( res < 0) {
#if !defined(_MSC_VER)
	    std::cerr << "Real_timer error: gettimeofday() returned -1.\n";
	    CGAL_CLIB_STD::abort();
#endif
	}
#if !defined(_MSC_VER)
	return elapsed  + double(t.tv_sec  - started.tv_sec) 
                        + double(t.tv_usec - started.tv_usec) / 1000000;
#else
        return elapsed  + ((double)(t.time - started.time)) 
			            + ((double)(t.millitm - started.millitm))/1000.0;
#endif
    }
    return elapsed;
}

CGAL_END_NAMESPACE

#endif // CGAL_REAL_TIMER_H //
// EOF //
