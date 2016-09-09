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
// file          : include/CGAL/Real_timer.h
// package       : Timer (1.8)
// revision      : 1.8
// revision_date : 11 August 2000 
// author(s)     : Lutz Kettner
//                 Matthias Baesken
// coordinator   : INRIA, Sophia Antipolis
//
// A timer class to measure real-time.
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_REAL_TIMER_H
#define CGAL_REAL_TIMER_H 1

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif

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

#if !defined (_MSC_VER) && !defined(__BORLANDC__)
    typedef struct timeval  Timetype;
#else
#if defined (_MSC_VER)
    typedef struct _timeb   Timetype; //MSC
#else
    typedef struct timeb    Timetype; //Borland
#endif 
#endif

    const inline int get_time(Timetype* t) const;
    const inline void report_err() const;
    const inline double recalc_time(const Timetype& t) const;
    double          elapsed;
    Timetype        started;
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

// private member functions.
// all the platform-specific functions are encapsulated here.

const inline int Real_timer::get_time(Timetype* t) const {
#if !defined(_MSC_VER) && !defined(__BORLANDC__)
  return gettimeofday( t, NULL);
#else
#if defined (_MSC_VER)
    _ftime(t);  
#else
    ftime(t);  
#endif
  return 0;
#endif 
}

const inline void Real_timer::report_err() const {
 #if !defined (_MSC_VER) && !defined(__BORLANDC__)
  std::cerr << "Real_timer error: gettimeofday() returned -1.\n"
	    << std::endl;
  CGAL_CLIB_STD::abort();
#else
  std::cout << "Real_timer error!.\n" << std::endl;
#endif
}

const inline double Real_timer::recalc_time(const Timetype& t) const {
#if !defined(_MSC_VER) && !defined(__BORLANDC__)
  return double(t.tv_sec  - started.tv_sec) 
    + double(t.tv_usec - started.tv_usec) / 1000000;
#else
  return ((double)(t.time - started.time)) 
    + ((double)(t.millitm - started.millitm))/1000.0;
#endif
}

// Member functions Real_timer
// ================================

inline void Real_timer::start() {
    CGAL_assertion( ! running);
    int res=0;
    res = get_time(&started);
    if ( res < 0) report_err();
    running = true;
    ++ interv;
}

inline void Real_timer::stop() {
    CGAL_assertion(running);
    Timetype t;
    int res=0;
    res = get_time(&t);
    if ( res < 0) report_err();
    elapsed += recalc_time(t);
    running  = false;
}

inline void Real_timer::reset() {
    interv = 0;
    elapsed = 0;
    if (running) {
	int res = 0;
        res = get_time(&started);
	if ( res < 0)  report_err();
	++ interv;
    }
}

inline double Real_timer::time() const {
  if (running) {
    Timetype t;
    int res = 0;
    res = get_time(&t);
    if ( res < 0) report_err();
    return elapsed + recalc_time(t);
  }
  return elapsed;
}

CGAL_END_NAMESPACE

#endif // CGAL_REAL_TIMER_H //
// EOF //
