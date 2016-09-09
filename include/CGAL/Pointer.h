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
// file          : include/CGAL/Pointer.h
// package       : Triangulation (4.69)
// source        : $RCSfile: Pointer.h,v $
// revision      : $Revision: 1.7 $
// revision_date : $Date: 2000/04/14 14:35:19 $
// author(s)     : Olivier Devillers, Mariette Yvinec, Sylvain Pion
//
// coordinator   : Mariette Yvinec
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_POINTER_H
#define CGAL_POINTER_H

#include <iterator>
#include <CGAL/assertions.h>
#include <CGAL/circulator.h>

CGAL_BEGIN_NAMESPACE 

template <class T>
struct Pointer
{
  typedef T value_type;

  //Pointer(const T* p = NULL) : _pointer((T*)p) {}
  Pointer( T* p = NULL) : _pointer((T*)p) {}

  //Pointer& operator=(const T* p)
  Pointer& operator=( T* p)
    {
      ptr() = p;
      return *this;
    }

  Pointer& operator=(const Pointer& p)
    {
      ptr() = p.ptr();
      return *this;
    }

  T& operator*() const { return *ptr(); }
  T* operator->() const { return ptr(); }

  void clear() { ptr() = NULL; }

  void Delete()
    {
      delete ptr();
      clear();
    }

  bool is_null() const { return ptr() == NULL; }

  bool operator==(const Pointer& p) const { return ptr() == p.ptr(); }
  bool operator!=(const Pointer& p) const { return !(*this == p); }

  bool operator==(CGAL_NULL_TYPE n) const
    {
      CGAL_assertion(n == 0);
      return ptr() == NULL;
    }

  bool operator!=(CGAL_NULL_TYPE n) const { return !(*this == n); }
 
  T*& ptr()       { return _pointer; }
  T*  ptr() const { return _pointer; }

  bool operator<(const Pointer& p) const { return ptr() < p.ptr();}

private:
  T* _pointer;
};

CGAL_END_NAMESPACE

#endif // CGAL_POINTER_H
