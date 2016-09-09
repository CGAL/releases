// Copyright (c) 1997  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/STL_Extension/src/CGAL/assertions.cpp $
// $Id: assertions.cpp 35750 2007-01-18 13:46:53Z fcacciola $
// 
//
// Author(s)     : Geert-Jan Giezeman and Sven Sch�nherr


#include <CGAL/config.h>
#include <CGAL/assertions.h>
#include <CGAL/exceptions.h>

#include <cstdlib>
#include <iostream>
#include <cassert>

CGAL_BEGIN_NAMESPACE

// not_implemented function
// ------------------------
void
not_implemented()
{
    assert( false);
}

// static behaviour variables
// --------------------------

static Failure_behaviour _error_behaviour   = THROW_EXCEPTION;
static Failure_behaviour _warning_behaviour = CONTINUE;

// standard error handlers
// -----------------------
static
void
_standard_error_handler(
        const char* what,
        const char* expr,
        const char* file,
        int         line,
        const char* msg )
{
    std::cerr << "CGAL error: " << what << " violation!" << std::endl
         << "Expr: " << expr << std::endl
         << "File: " << file << std::endl
         << "Line: " << line << std::endl;
    if ( msg != 0)
        std::cerr << "Explanation:" << msg << std::endl;
}


// standard warning handler
// ------------------------
static
void
_standard_warning_handler( const char *,
                          const char* expr,
                          const char* file,
                          int         line,
                          const char* msg )
{
    std::cerr << "CGAL warning: check violation!" << std::endl
         << "Expr: " << expr << std::endl
         << "File: " << file << std::endl
         << "Line: " << line << std::endl;
    if ( msg != 0)
        std::cerr << "Explanation:" << msg << std::endl;

}

// default handler settings
// ------------------------
static Failure_function
_error_handler = _standard_error_handler;

static Failure_function
_warning_handler = _standard_warning_handler;

// failure functions
// -----------------
void
assertion_fail( const char* expr,
                     const char* file,
                     int         line,
                     const char* msg )
{
    (*_error_handler)("assertion", expr, file, line, msg);
    switch (_error_behaviour) {
    case ABORT:
        CGAL_CLIB_STD::abort();
    case EXIT:
        CGAL_CLIB_STD::exit(1);  // EXIT_FAILURE
    case EXIT_WITH_SUCCESS:
        CGAL_CLIB_STD::exit(0);  // EXIT_SUCCESS
    case THROW_EXCEPTION:
        throw Assertion_exception("CGAL", expr, file, line, msg);
    case CONTINUE:
        ;
    }
}
void assertion_fail( const char* expr, const char* file, int line )
{
  assertion_fail(expr,file,line,"");
}

void
precondition_fail( const char* expr,
                        const char* file,
                        int         line,
                        const char* msg )
{
    (*_error_handler)("precondition", expr, file, line, msg);
    switch (_error_behaviour) {
    case ABORT:
        CGAL_CLIB_STD::abort();
    case EXIT:
        CGAL_CLIB_STD::exit(1);  // EXIT_FAILURE
    case EXIT_WITH_SUCCESS:
        CGAL_CLIB_STD::exit(0);  // EXIT_SUCCESS
    case THROW_EXCEPTION:
        throw Precondition_exception("CGAL", expr, file, line, msg);
    case CONTINUE:
        ;
    }
}
void precondition_fail( const char* expr, const char* file, int line )
{
  precondition_fail(expr,file,line,"");
}

void
postcondition_fail(const char* expr,
                         const char* file,
                         int         line,
                         const char* msg )
{
    (*_error_handler)("postcondition", expr, file, line, msg);
    switch (_error_behaviour) {
    case ABORT:
        CGAL_CLIB_STD::abort();
    case EXIT:
        CGAL_CLIB_STD::exit(1);  // EXIT_FAILURE
    case EXIT_WITH_SUCCESS:
        CGAL_CLIB_STD::exit(0);  // EXIT_SUCCESS
    case THROW_EXCEPTION:
        throw Postcondition_exception("CGAL", expr, file, line, msg);
    case CONTINUE:
        ;
    }
}
void postcondition_fail( const char* expr, const char* file, int line )
{
  postcondition_fail(expr,file,line,"");
}


// warning function
// ----------------
void
warning_fail( const char* expr,
                   const char* file,
                   int         line,
                   const char* msg )
{
    (*_warning_handler)("warning", expr, file, line, msg);
    switch (_warning_behaviour) {
    case ABORT:
        CGAL_CLIB_STD::abort();
    case EXIT:
        CGAL_CLIB_STD::exit(1);  // EXIT_FAILURE
    case EXIT_WITH_SUCCESS:
        CGAL_CLIB_STD::exit(0);  // EXIT_SUCCESS
    case THROW_EXCEPTION:
        throw Warning_exception("CGAL", expr, file, line, msg);
    case CONTINUE:
        ;
    }
}
void warning_fail( const char* expr, const char* file, int line )
{
  warning_fail(expr,file,line,"");
}


// error handler set functions
// ---------------------------
Failure_function
set_error_handler( Failure_function handler)
{
    Failure_function result = _error_handler;
    _error_handler = handler;
    return( result);
}

Failure_function
set_warning_handler( Failure_function handler)
{
    Failure_function result = _warning_handler;
    _warning_handler = handler;
    return( result);
}

Failure_behaviour
set_error_behaviour(Failure_behaviour eb)
{
    Failure_behaviour result = _error_behaviour;
    _error_behaviour = eb;
    return result;
}

Failure_behaviour
set_warning_behaviour(Failure_behaviour eb)
{
    Failure_behaviour result = _warning_behaviour;
    _warning_behaviour = eb;
    return result;
}

CGAL_END_NAMESPACE
