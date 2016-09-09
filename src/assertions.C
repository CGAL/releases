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
// file          : src/assertions.C
// author(s)     : Geert-Jan Giezeman and Sven Schönherr
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#include <stdlib.h>
#include <CGAL/assertions.h>
#include <CGAL/config.h>
#include <iostream.h>

#include <assert.h>

// not_implemented function
// ------------------------
void
not_implemented()
{
    assert( false);
}

// static behaviour variables
// --------------------------

static CGAL_Failure_behaviour CGAL__error_behaviour = CGAL_ABORT;
static CGAL_Failure_behaviour CGAL__warning_behaviour = CGAL_CONTINUE;

// standard error handlers
// -----------------------
static
void
CGAL__standard_error_handler(
        const char* what,
        const char* expr,
        const char* file,
        int         line,
        const char* msg )
{
    cerr << "CGAL error: " << what << " violation!" << endl
         << "Expr: " << expr << endl
         << "File: " << file << endl
         << "Line: " << line << endl;
    if ( msg != 0)
        cerr << "Explanation:" << msg << endl;
}


// standard warning handler
// ------------------------
static
void
CGAL__standard_warning_handler( const char *,
                          const char* expr,
                          const char* file,
                          int         line,
                          const char* msg )
{
    cerr << "CGAL warning: check violation!" << endl
         << "Expr: " << expr << endl
         << "File: " << file << endl
         << "Line: " << line << endl;
    if ( msg != 0)
        cerr << "Explanation:" << msg << endl;

}

// default handler settings
// ------------------------
static CGAL_Failure_function
CGAL__error_handler = CGAL__standard_error_handler;

static CGAL_Failure_function
CGAL__warning_handler = CGAL__standard_warning_handler;

// failure functions
// -----------------
void
CGAL_assertion_fail( const char* expr,
                     const char* file,
                     int         line,
                     const char* msg )
{
    (*CGAL__error_handler)("assertion", expr, file, line, msg);
    switch (CGAL__error_behaviour) {
    case CGAL_ABORT:
        abort();
    case CGAL_EXIT:
        exit(1);  // EXIT_FAILURE
    case CGAL_CONTINUE:
        ;
    }
}

void
CGAL_precondition_fail( const char* expr,
                        const char* file,
                        int         line,
                        const char* msg )
{
    (*CGAL__error_handler)("precondition", expr, file, line, msg);
    switch (CGAL__error_behaviour) {
    case CGAL_ABORT:
        abort();
    case CGAL_EXIT:
        exit(1);  // EXIT_FAILURE
    case CGAL_CONTINUE:
        ;
    }
}

void
CGAL_postcondition_fail(const char* expr,
                         const char* file,
                         int         line,
                         const char* msg )
{
    (*CGAL__error_handler)("postcondition", expr, file, line, msg);
    switch (CGAL__error_behaviour) {
    case CGAL_ABORT:
        abort();
    case CGAL_EXIT:
        exit(1);  // EXIT_FAILURE
    case CGAL_CONTINUE:
        ;
    }
}


// warning function
// ----------------
void
CGAL_warning_fail( const char* expr,
                   const char* file,
                   int         line,
                   const char* msg )
{
    (*CGAL__warning_handler)("warning", expr, file, line, msg);
    switch (CGAL__warning_behaviour) {
    case CGAL_ABORT:
        abort();
    case CGAL_EXIT:
        exit(1);  // EXIT_FAILURE
    case CGAL_CONTINUE:
        ;
    }
}


// error handler set functions
// ---------------------------
CGAL_Failure_function
CGAL_set_error_handler( CGAL_Failure_function handler)
{
    CGAL_Failure_function result = CGAL__error_handler;
    CGAL__error_handler = handler;
    return( result);
}

CGAL_Failure_function
CGAL_set_warning_handler( CGAL_Failure_function handler)
{
    CGAL_Failure_function result = CGAL__warning_handler;
    CGAL__warning_handler = handler;
    return( result);
}

CGAL_Failure_behaviour
CGAL_set_error_behaviour(CGAL_Failure_behaviour eb)
{
    CGAL_Failure_behaviour result = CGAL__error_behaviour;
    CGAL__error_behaviour = eb;
    return result;
}

CGAL_Failure_behaviour
CGAL_set_warning_behaviour(CGAL_Failure_behaviour eb)
{
    CGAL_Failure_behaviour result = CGAL__warning_behaviour;
    CGAL__warning_behaviour = eb;
    return result;
}


