
#include <assert.h>
#include <stdlib.h>
//#include <bool.h>
#include <LEDA/basic.h>
#include <CGAL/utils.h>
#include <iostream.h>

void not_implemented()
{
    assert(false);
}

void standard_assertion_handler(
        const char *expr, const char *file, int line)
{
    cerr << "The assertion:\n   "<<expr<<"\n was not true.\n Line: "
        << line << ". File: " << file <<".\n";
}

void standard_precondition_handler(
        const char *expr, const char *file, int line)
{
    cerr << "The precondition:\n   "<<expr<<"\n was not true.\n Line: "
        << line << ". File: " << file <<".\n";
}

void standard_postcondition_handler(
        const char *expr, const char *file, int line)
{
    cerr << "The postcondition:\n   "<<expr<<"\n was not true.\n Line: "
        << line << ". File: " << file <<".\n";
}

void standard_check_handler(const char *expr, const char *file, int line)
{
    cerr << "The check:\n   "<<expr<<"\n was not true.\n Line: "
        << line << ". File: " << file <<".\n";
}

typedef void (*failure_function)(const char *, const char *, int);

static failure_function assertion_handler
                = standard_assertion_handler;

static failure_function precondition_handler
                = standard_precondition_handler;

static failure_function postcondition_handler
                = standard_postcondition_handler;

static failure_function check_handler
                = standard_check_handler;


void cgal_assertion_fail(const char *msg, const char *file, int line)
{
    (*assertion_handler)(msg, file, line);
    abort();
}

void cgal_precondition_fail(const char *msg, const char *file, int line)
{
    (*precondition_handler)(msg, file, line);
    abort();
}

void cgal_postcondition_fail(const char *msg, const char *file, int line)
{
    (*postcondition_handler)(msg, file, line);
    abort();
}

void cgal_check_fail(const char *msg, const char *file, int line)
{
    (*check_handler)(msg, file, line);
    abort();
}

void cgal_set_assertion_handler(
        void (*handler)(const char *, const char *, int))
{
    assertion_handler = handler;
}

void cgal_set_precondition_handler(
        void (*handler)(const char *, const char *, int))
{
    precondition_handler = handler;
}

void cgal_set_postcondition_handler(
        void (*handler)(const char *, const char *, int))
{
    postcondition_handler = handler;
}

void cgal_set_check_handler(
        void (*handler)(const char *, const char *, int))
{
    check_handler = handler;
}

