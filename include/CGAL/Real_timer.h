// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/Real_timer.h
// package       : Timer (1.1)
// chapter       : $CGAL_Chapter: Timer $
// source        : Timer/web/Real_timer.h
// revision      : $Revision: 1.5 $
// revision_date : $Date: 1999/03/07 21:35:46 $ 
// author(s)     : Lutz Kettner
//
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
    struct timeval  started;
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
    double   precision()  const { return eps; }
    double   max() const        { return double(INT_MAX);}
};


/*****************************************************************************/

// Member functions Real_timer
// ================================

inline void Real_timer::start() {
    CGAL_assertion( ! running);
    int res = gettimeofday( &started, NULL);
    if ( res < 0) {
	cerr << "Real_timer error: gettimeofday() returned -1." << endl;
	std::abort();
    }
    running = true;
    ++ interv;
}

inline void Real_timer::stop() {
    CGAL_assertion(running);
    struct timeval t;
    int res = gettimeofday( &t, NULL);
    if ( res < 0) {
	cerr << "Real_timer error: gettimeofday() returned -1." << endl;
	std::abort();
    }
    elapsed +=   double(t.tv_sec  - started.tv_sec) 
               + double(t.tv_usec - started.tv_usec) / 1000000;
    running  = false;
}

inline void Real_timer::reset() {
    interv = 0;
    elapsed = 0;
    if (running) {
	int res = gettimeofday( &started, NULL);
	if ( res < 0) {
	    cerr << "Real_timer error: gettimeofday() returned -1." << endl;
	    std::abort();
	}
	++ interv;
    }
}

inline double Real_timer::time() const {
    if (running) {
	struct timeval t;
	int res = gettimeofday( &t, NULL);
	if ( res < 0) {
	    cerr << "Real_timer error: gettimeofday() returned -1." << endl;
	    std::abort();
	}
	return elapsed  + double(t.tv_sec  - started.tv_sec) 
                        + double(t.tv_usec - started.tv_usec) / 1000000;
    }
    return elapsed;
}

CGAL_END_NAMESPACE

#endif // CGAL_REAL_TIMER_H //
// EOF //
