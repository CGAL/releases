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
// file          : include/CGAL/Pointer.h
// package       : Triangulation_2 (7.32)
// source        : $RCSfile: Pointer.h,v $
// revision      : $Revision: 1.11 $
// revision_date : $Date: 2002/04/09 11:29:43 $
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
  typedef void     iterator_category;
  typedef T        value_type;
  typedef void     difference_type;
  typedef T*       pointer;
  typedef T&       reference;
  

  //Pointer(const T* p = NULL) : _pointer((T*)p) {}
  //Pointer( T* p = NULL) : _pointer((T*)p) {}
  Pointer() : _pointer(NULL) {}
  Pointer( const T* p) : _pointer(const_cast<T*>(p)) {}

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

  bool operator==(CGAL_NULL_TYPE CGAL_assertion_code(n) ) const
    {
      CGAL_assertion(n == 0);
      return ptr() == NULL;
    }

  bool operator!=(CGAL_NULL_TYPE n) const { return !(*this == n); }
 
  T*& ptr()       { return _pointer; }
  T*  ptr() const { return _pointer; }

  bool operator<(const Pointer& p) const { return ptr() < p.ptr();}
  bool operator>(const Pointer& p) const { return ptr() > p.ptr();}

private:
  T* _pointer;
};

CGAL_END_NAMESPACE

#endif // CGAL_POINTER_H
