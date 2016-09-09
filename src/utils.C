//  Copyright CGAL 1996
//
//  cgal@cs.ruu.nl
//
//  This file is part of an internal release of the CGAL kernel.
//  The code herein may be used and/or copied only in accordance
//  with the terms and conditions stipulated in the agreement
//  under which the code has been supplied or with the written
//  permission of the CGAL Project.
//
//  Look at http://www.cs.ruu.nl/CGAL/ for more information.
//  Please send any bug reports and comments to cgal@cs.ruu.nl
//
//  The code comes WITHOUT ANY WARRANTY; without even the implied
//  warranty of FITNESS FOR A PARTICULAR PURPOSE.
//

#include <CGAL/misc.h>
#include <stdlib.h>
#include <LEDA/basic.h>
#include <CGAL/utils.h>
#include <iostream.h>

void not_implemented()
{
    assert(false);
}

void standard_assertion_handler(
        const char *expr, const char *file, int line, const char *msg)
{
  cerr << "The assertion\n   " << expr << "\nis violated\n"
       <<"File: " << file
       << ".\nLine: " << line << '\n';

  if (msg != 0) {
    cerr << "Explanation:\n" << msg <<'\n';
  }
}

void standard_precondition_handler(
        const char *expr, const char *file, int line, const char *msg)
{
    cerr << "The precondition:\n   "<< expr << "\nis not satisfied.\n"
         << "File: " << file
         << "\nLine: " << line <<"\n";

    if (msg != 0) {
    cerr << "Explanation:\n" << msg << '\n';
    }
}

void standard_postcondition_handler(
        const char *expr, const char *file, int line, const char *msg)
{
    cerr << "The postcondition:\n   "<< expr << "\nis not satisfied.\n"
        << "File: " << file
         << "\nLine: " << line << '\n';

    if (msg != 0) {
    cerr << "Explanation:\n" << msg << '\n';
    }
}

void standard_check_handler(
        const char *expr, const char *file, int line, const char *msg)
{
    cerr << "The check:\n   "<< expr << "\nfailed.\n"
         << "File: " << file
         << "\nLine: " << line << '\n';

    if (msg != 0) {
    cerr << "Explanation:\n" << msg <<'\n';
    }
}

typedef void (*failure_function)(const char *, const char *,
                                 int, const char *);

static failure_function assertion_handler
                = standard_assertion_handler;

static failure_function precondition_handler
                = standard_precondition_handler;

static failure_function postcondition_handler
                = standard_postcondition_handler;

static failure_function check_handler
                = standard_check_handler;


void cgal_assertion_fail(const char *expr, const char *file,
                         int line, const char *msg)
{
    (*assertion_handler)(expr, file, line, msg);
    abort();
}

void cgal_precondition_fail(const char *expr, const char *file,
                            int line, const char *msg)
{
    (*precondition_handler)(expr, file, line, msg);
    abort();
}

void cgal_postcondition_fail(const char *expr, const char *file,
                             int line, const char *msg)
{
    (*postcondition_handler)(expr, file, line, msg);
    abort();
}

void cgal_check_fail(const char *expr, const char *file,
                     int line, const char *msg)
{
    (*check_handler)(expr, file, line, msg);
    abort();
}

void cgal_set_assertion_handler(
        void (*handler)(const char *, const char *, int, const char *))
{
    assertion_handler = handler;
}

void cgal_set_precondition_handler(
        void (*handler)(const char *, const char *, int, const char *))
{
    precondition_handler = handler;
}

void cgal_set_postcondition_handler(
        void (*handler)(const char *, const char *, int, const char *))
{
    postcondition_handler = handler;
}

void cgal_set_check_handler(
        void (*handler)(const char *, const char *, int, const char *))
{
    check_handler = handler;
}

