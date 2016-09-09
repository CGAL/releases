// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium

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
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : include/CGAL/Object.h
// package       : Kernel_basic (2.9)
// source        : Object.lw 
// revision      : 2.6
// revision_date : 10 Sep 1999
// author(s)     : Stefan.Schirra
//                 Andreas Fabri (original version)
//                 Geert-Jan Giezeman
//                 Michael Seel
//
// coordinator   : MPI Saarbruecken, Germany 
//
// modifications : 29.10.97  by Stefan Schirra and Michael Seel
//                 04.11.97  by Geert-Jan Giezeman
//                 04.01.98  by Stefan Schirra
//                 10.09.99
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_OBJECT_H
#define CGAL_OBJECT_H

#ifndef CGAL_HANDLE_H
#include <CGAL/Handle.h>
#endif // CGAL_HANDLE_H

CGAL_BEGIN_NAMESPACE

class Object_base;
class Object_rep;
class Object;
template <class T> class Wrapper;


class Object_base
{
  public:
    virtual        ~Object_base() {}
#ifdef CGAL_CFG_NO_DYNAMIC_CAST
    virtual int*   type_id() const { return 0; }
#endif // CGAL_CFG_NO_DYNAMIC_CAST
};


template <class T>
class Wrapper : public Object_base 
{
  public:
                   Wrapper(const T& object) : _object(object) {}
                   Wrapper() {}
                   operator T() { return _object; }
    virtual        ~Wrapper() {}
#ifdef CGAL_CFG_NO_DYNAMIC_CAST
    virtual int*   type_id() const;
#endif // CGAL_CFG_NO_DYNAMIC_CAST
  private:
    T              _object;
};


#ifdef CGAL_CFG_NO_DYNAMIC_CAST
template <class T>
int*
Wrapper<T>::type_id() const
{
  static int type_base;
  return &type_base;
}
#endif // CGAL_CFG_NO_DYNAMIC_CAST


class Object_rep : public Rep
{
  public:
                  Object_rep() : _base(0) {}
                  Object_rep(Object_base *base) : _base(base) {}
                  ~Object_rep() { if (_base != 0 ){ delete _base; } }
    Object_base*  base() const { return _base; }

  private:
    Object_base*  _base;
};


class Object : public Handle
{
public:
                  Object() { PTR = new Object_rep(); }
                  Object(Object_base *base) { PTR = new Object_rep(base); }
                  Object(const Object& o) : Handle((Handle&)o) {}

    Object&       operator=(const Object& o)
                  {
                    Handle::operator=(o);
                    return *this;
                  }
    Object_rep*   ptr() const { return (Object_rep *)PTR; }
    bool          is_empty() const { return ptr()->base() == 0; }
};


template <class T>
Object
make_object(const T& t)
{ return Object(new Wrapper< T >(t)); }

#ifdef CGAL_CFG_NO_DYNAMIC_CAST
template <class T>
T*
_dynamic_cast(Object_base *base, const T*)
{
  T dummy;
  if (base == 0) { return (T*) 0; }
  if (dummy.type_id() != base->type_id()) { return (T*) 0; }
  return (T*) base;
}

template <class T>
const T*
_dynamic_cast(const Object_base *base, const T*)
{
  T dummy;
  if (base == 0) { return (T*) 0; }
  if (dummy.type_id() != base->type_id()) { return (const T*) 0; }
  return (const T*) base;
}
#endif // CGAL_CFG_NO_DYNAMIC_CAST


template <class T>
bool
assign(T& t, const Object& o)
{
#ifdef CGAL_CFG_NO_DYNAMIC_CAST
  Wrapper<T>*  wp = _dynamic_cast(o.ptr()->base(), (Wrapper<T>*) 0);
#else

# ifdef CGAL_CFG_DYNAMIC_CAST_BUG
  Wrapper<T>   instantiate_it;
# endif // CGAL_CFG_DYNAMIC_CAST_BUG

  Wrapper<T>*  wp = dynamic_cast<Wrapper<T>*>(o.ptr()->base());
#endif // CGAL_CFG_NO_DYNAMIC_CAST
  if( wp == 0 ) { return false; }
  t = *(wp);
  return true;
}

CGAL_END_NAMESPACE

#endif // CGAL_OBJECT_H

