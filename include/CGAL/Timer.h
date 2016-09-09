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
// file          : include/CGAL/Timer.h
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

#ifndef CGAL_TIMER_H
#define CGAL_TIMER_H 1

#include <CGAL/basic.h>

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
    double      elapsed;
    double      started;
    int         interv;
    bool        running;

    static bool m_failed;

    double   user_process_time() const; // in seconds
    double   compute_precision() const; // in seconds
public:
    Timer() : elapsed(0.0), started(0.0), interv(0), running(false) {}

    void     start();
    void     stop ();
    void     reset();
    bool     is_running() const { return running; }

    double   time()       const;
    int      intervals()  const { return interv; }
    double   precision()  const;
    // Returns timer precison. Computes it dynamically at first call.
    // Returns -1.0 if timer system call fails, which, for a proper coded
    // test towards precision leads to an immediate stop of an otherwise 
    // infinite loop (fixed tolerance * total time >= precision).
    double   max()        const;
};


// -----------------------------------------------------------------------

// Member functions for Timer
// ===========================

inline void Timer::start() {
    CGAL_precondition( ! running);
    started = user_process_time();
    running = true;
    ++ interv;
}

inline void Timer::stop() {
    CGAL_precondition( running);
    double t = user_process_time();
    elapsed += (t - started);
    started = 0.0;
    running = false;
}

inline void Timer::reset() {
    interv  = 0;
    elapsed = 0.0;
    if (running) {
	started = user_process_time();
	++ interv;
    } else {
        started = 0.0;
    }
}

inline double Timer::time() const {
    if (running) {
        double t = user_process_time();
	return elapsed + (t - started);
    }
    return elapsed;
}

CGAL_END_NAMESPACE

#endif // CGAL_TIMER_H //
// EOF //
