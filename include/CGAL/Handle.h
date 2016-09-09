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
// source        : Handle.fw
// file          : include/CGAL/Handle.h
// package       : Kernel_basic (2.0.11)
// revision      : 2.0.11
// revision_date : 06 May 1999 
// author(s)     :
//
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : cgal@cs.uu.nl
//
// ======================================================================
 

#ifndef CGAL_HANDLE_H
#define CGAL_HANDLE_H

#if defined(CGAL_USE_LEDA) && !defined(CGAL_NO_LEDA_HANDLE)

#ifndef CGAL_PROTECT_LEDA_BASIC_H
#include <LEDA/basic.h>
#define CGAL_PROTECT_LEDA_BASIC_H
#endif // CGAL_PROTECT_LEDA_BASIC_H

#ifdef CGAL_DEBUG_HANDLE_REP
#include <iostream>
#endif // CGAL_DEBUG_HANDLE_REP

CGAL_BEGIN_NAMESPACE

typedef handle_base Handle;
typedef handle_rep  Rep;

// XXX using this flag is a dirty hack; should be revised XXX 
#ifndef CGAL_CFG_NO_NAMESPACE 
template < class T >
inline
bool
identical(const T &t1, const T &t2)
{ return t1.id() == t2.id(); }
#endif // CGAL_CFG_NO_NAMESPACE

CGAL_END_NAMESPACE


#else

CGAL_BEGIN_NAMESPACE

class Rep
{

friend class Handle;

#ifdef CGAL_DEBUG_HANDLE_REP
public:
#else
protected:
#endif // CGAL_DEBUG_HANDLE_REP
  int  count;

  Rep()
  {
#ifdef CGAL_DEBUG_HANDLE_REP
    cout << "Rep() " << this << endl;
#endif // CGAL_DEBUG_HANDLE_REP
    count = 1;
  }

  virtual ~Rep()
  {
#ifdef CGAL_DEBUG_HANDLE_REP
    cout << "~Rep() " << this << endl;
#endif // CGAL_DEBUG_HANDLE_REP
  }

};


class Handle
{
#ifdef CGAL_DEBUG_HANDLE_REP
public:
#else
protected:
#endif // CGAL_DEBUG_HANDLE_REP
  Rep* PTR;

public:
  Handle()
  {
    PTR = (Rep*)0xefefefef;
#ifdef CGAL_DEBUG_HANDLE_REP
    cout << "Handle() " << this << endl;
#endif // CGAL_DEBUG_HANDLE_REP
  }
  Handle(const Handle& x)
  {
#ifdef CGAL_DEBUG_HANDLE_REP
    cout << "Handle(Handle) " << this << ": PTR "
         << PTR << " = " << &x << ": PTR " << x.PTR << endl;
#endif // CGAL_DEBUG_HANDLE_REP
    CGAL_kernel_precondition( x.PTR != 0 );
    PTR = x.PTR;
    PTR->count++;
  }

  ~Handle()
  {
#ifdef CGAL_DEBUG_HANDLE_REP
    cout << "~Handle " << this << ": PTR " << PTR << " count: ";
    if (PTR) cout << PTR->count << endl;
#endif // CGAL_DEBUG_HANDLE_REP
    if (PTR && --PTR->count == 0)
    {
      delete PTR;
    }
  }

  Handle& operator=(const Handle& x)
  {
#ifdef CGAL_DEBUG_HANDLE_REP
    cout << "Handle::operator= " << this << ": PTR "
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


  friend unsigned long id(const Handle& x);

};

inline
unsigned long
id(const Handle& x)
{ return (unsigned long)x.PTR; }


template < class T >
inline
bool
identical(const T &t1, const T &t2)
{ return id(t1) == id(t2); }

CGAL_END_NAMESPACE


#endif // defined(CGAL_USE_LEDA) && !defined(CGAL_NO_LEDA_HANDLE)
#endif // CGAL_HANDLE_H
