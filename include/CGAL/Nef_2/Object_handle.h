// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

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
// file          : include/CGAL/Nef_2/Object_handle.h
// package       : Nef_2 (1.18)
// coordinator   : Michael Seel     
// revision      : $Revision: 1.6 $
// revision_date : $Date: 2002/03/22 15:19:58 $
// author(s)     : Stefan Schirra
//                 Andreas Fabri
//                 Geert-Jan Giezeman
//                 Michael Seel
//                 Sylvain Pion
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_OBJECT_HANDLE_H
#define CGAL_OBJECT_HANDLE_H

#include <CGAL/Handle_for_virtual.h>
#include <CGAL/circulator.h>

CGAL_BEGIN_NAMESPACE

template <class T>
class Handle_wrapper : public Ref_counted_virtual
{
  public:
    Handle_wrapper(const T& object) : _object(object) {}
    Handle_wrapper() {}
    operator T() const { return _object; }
    ~Handle_wrapper() {}
  private:
  T _object;
};


class Object_handle
  : public Handle_for_virtual<Ref_counted_virtual>
{
  struct empty{};
  typedef Handle_for_virtual<Ref_counted_virtual> base;
public:
  Object_handle()
  { initialize_with(Handle_wrapper<empty>()); }

  template <class T>
  Object_handle(const T&t)
  { initialize_with(Handle_wrapper<T>(t)); }

  template <class T>
  bool assign(T &t) const
  {
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
    try {
#endif
      const Handle_wrapper<T> *wp = 
	dynamic_cast<const Handle_wrapper<T> *>(Ptr());
      if ( wp == static_cast<Handle_wrapper<T> *>(0) )
	return false;
      t = *(wp);
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
    }
    catch (...) {
      std::cerr << "ERROR : YOUR COMPILER MUST SUPPORT RTTI" << std::endl;
      abort();
    }
#endif
    return true;
  }

  bool is_empty() const
  { empty E; return assign(E); }
  bool operator==(CGAL_NULL_TYPE n) const
  { CGAL_assertion(n == 0); return is_empty(); }
  bool operator!=(CGAL_NULL_TYPE n) const
  { CGAL_assertion(n == 0); return !is_empty(); }

};

template <class T>
inline bool assign(T& t, const Object_handle& o)
{ return o.assign(t); }

CGAL_END_NAMESPACE

#endif // CGAL_OBJECT_HANDLE_H
