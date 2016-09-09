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
// file          : include/CGAL/Handle.h
// author(s)     :
//
// email         : cgal@cs.uu.nl
//
// ============================================================================
 

#ifndef CGAL_HANDLE_H
#define CGAL_HANDLE_H

#if defined(CGAL_USE_LEDA) && !defined(CGAL_NO_LEDA_HANDLE)

#ifndef CGAL_PROTECT_LEDA_BASIC_H
#include <LEDA/basic.h>
#define CGAL_PROTECT_LEDA_BASIC_H
#endif // CGAL_PROTECT_LEDA_BASIC_H

typedef handle_base CGAL_Handle;
typedef handle_rep  CGAL_Rep;

template < class T >
inline
bool
CGAL_identical(const T &t1, const T &t2)
{ return t1.id() == t2.id(); }

#else

#ifdef CGAL_DEBUG_HANDLE_REP
#ifndef CGAL_PROTECT_IOSTREAM_H
#include <iostream.h>
#define CGAL_PROTECT_IOSTREAM_H
#endif // CGAL_PROTECT_IOSTREAM_H
#endif // CGAL_DEBUG_HANDLE_REP

class CGAL_Rep
{

friend class CGAL_Handle;

#ifdef CGAL_DEBUG_HANDLE_REP
public:
#else
protected:
#endif // CGAL_DEBUG_HANDLE_REP
  int  count;

  CGAL_Rep()
  {
#ifdef CGAL_DEBUG_HANDLE_REP
    cout << "CGAL_Rep() " << this << endl;
#endif // CGAL_DEBUG_HANDLE_REP
    count = 1;
  }

  virtual ~CGAL_Rep()
  {
#ifdef CGAL_DEBUG_HANDLE_REP
    cout << "~CGAL_Rep() " << this << endl;
#endif // CGAL_DEBUG_HANDLE_REP
  }

};


class CGAL_Handle
{
#ifdef CGAL_DEBUG_HANDLE_REP
public:
#else
protected:
#endif // CGAL_DEBUG_HANDLE_REP
  CGAL_Rep* PTR;

public:
  CGAL_Handle()
  {
    PTR = (CGAL_Rep*)0xefefefef;
#ifdef CGAL_DEBUG_HANDLE_REP
    cout << "CGAL_Handle() " << this << endl;
#endif // CGAL_DEBUG_HANDLE_REP
  }
  CGAL_Handle(const CGAL_Handle& x)
  {
#ifdef CGAL_DEBUG_HANDLE_REP
    cout << "CGAL_Handle(CGAL_Handle) " << this << ": PTR "
         << PTR << " = " << &x << ": PTR " << x.PTR << endl;
#endif // CGAL_DEBUG_HANDLE_REP
    CGAL_kernel_precondition( x.PTR != 0 );
    PTR = x.PTR;
    PTR->count++;
  }

  ~CGAL_Handle()
  {
#ifdef CGAL_DEBUG_HANDLE_REP
    cout << "~CGAL_Handle " << this << ": PTR " << PTR << " count: ";
    if (PTR) cout << PTR->count << endl;
#endif // CGAL_DEBUG_HANDLE_REP
    if (PTR && --PTR->count == 0)
    {
      delete PTR;
    }
  }

  CGAL_Handle& operator=(const CGAL_Handle& x)
  {
#ifdef CGAL_DEBUG_HANDLE_REP
    cout << "CGAL_Handle::operator= " << this << ": PTR "
         << PTR << " = " << &x << ": PTR " << x.PTR << endl;
#endif // CGAL_DEBUG_HANDLE_REP
    x.PTR->count++;
    if (PTR && --PTR->count == 0)
      {
        delete PTR; // left side may be 0
      }
    PTR = x.PTR;
    return *this;
  }

  int refs()  const { return PTR->count; }


  friend unsigned long CGAL_id(const CGAL_Handle& x);

};

inline
unsigned long
CGAL_id(const CGAL_Handle& x)
{ return (unsigned long)x.PTR; }


template < class T >
inline
bool
CGAL_identical(const T &t1, const T &t2)
{ return CGAL_id(t1) == CGAL_id(t2); }

#endif // defined(CGAL_USE_LEDA) && !defined(CGAL_NO_LEDA_HANDLE)
#endif // CGAL_HANDLE_H
