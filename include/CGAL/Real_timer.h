// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/Real_timer.h
// author(s)     : Lutz Kettner  
//
// email         : cgal@cs.uu.nl
//
// ============================================================================

#ifndef CGAL_REAL_TIMER_H
#define CGAL_REAL_TIMER_H 1

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif

#ifndef CGAL_PROTECT_STDLIB_H
#include <stdlib.h>
#define CGAL_PROTECT_STDLIB_H
#endif // CGAL_PROTECT_STDLIB_H
#ifndef CGAL_PROTECT_LIMITS_H
#include <limits.h>
#define CGAL_PROTECT_LIMITS_H
#endif // CGAL_PROTECT_LIMITS_H

// used for gettimeofday()
#ifndef CGAL_PROTECT_SYS_TIME_H
#include <sys/time.h>
#define CGAL_PROTECT_SYS_TIME_H
#endif // CGAL_PROTECT_SYS_TIME_H


// SECTION: A Timer Measuring Real-Time
// ========================================================================
// 
// DEFINITION
// 
// A timer `t' of type CGAL_Real_timer is an object with a state. It is
// either running or it is stopped. The state is controlled with
// `t.start()' and `t.stop()' . The timer counts the time elapsed since
// its creation or last reset. It counts only the time where it is in the
// running state. The time information is given in seconds.

class CGAL_Real_timer {
private:
    double          elapsed;
    struct timeval  started;
    int             _intervals;
    bool            running;
    double          eps;

public:
    CGAL_Real_timer();

    void     start();
    void     stop ();
    void     reset();
    bool     is_running() const { return running; }

    double   time()       const;
    int      intervals()  const { return _intervals; }
    double   precision()  const { return eps; }
    double   max() const        { return double(INT_MAX);}
};


/*****************************************************************************/

// Member functions CGAL_Real_timer
// ================================

inline void
CGAL_Real_timer::start( )
{
    CGAL_assertion( ! running);
    int res = gettimeofday( &started, NULL);
    if ( res < 0) {
	cerr << "CGAL_Real_timer error: gettimeofday() returned -1." 
	     << endl;
	abort();
    }
    running = true;
    ++ _intervals;
}

inline void
CGAL_Real_timer::stop( )
{
    CGAL_assertion( running);
    struct timeval t;
    int res = gettimeofday( &t, NULL);
    if ( res < 0) {
	cerr << "CGAL_Real_timer error: gettimeofday() returned -1." 
	     << endl;
	abort();
    }
    elapsed +=   double(t.tv_sec  - started.tv_sec) 
               + double(t.tv_usec - started.tv_usec) /1000000;
    running  = false;
}

inline void
CGAL_Real_timer::reset( )
{
    _intervals = 0;
    elapsed = 0;
    if ( running) {
	int res = gettimeofday( &started, NULL);
	if ( res < 0) {
	    cerr << "CGAL_Real_timer error: gettimeofday() returned -1." 
		 << endl;
	    abort();
	}
	++ _intervals;
    }
}

inline double
CGAL_Real_timer::time() const {
    if ( running) {
	struct timeval t;
	int res = gettimeofday( &t, NULL);
	if ( res < 0) {
	    cerr << "CGAL_Real_timer error: gettimeofday() returned -1." 
		 << endl;
	    abort();
	}
	return elapsed  + double(t.tv_sec  - started.tv_sec) 
                        + double(t.tv_usec - started.tv_usec) /1000000;
    }
    return elapsed;
}

#endif // CGAL_REAL_TIMER_H //
// EOF //
