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
// file          : include/CGAL/Object.h
// package       : Kernel_basic (2.0.11)
// source        : Object.lw 
// revision      : 2.0.2
// revision_date : 14 Mar 1999
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

class Base;
class _Object;
class Object;
template <class T> class Wrapper;


class Base
{
  public:
    virtual       ~Base() {}
#ifdef CGAL_CFG_NO_DYNAMIC_CAST
    virtual int*   type_id() const
                   { return 0; }
#endif // CGAL_CFG_NO_DYNAMIC_CAST
};


template <class T>
class Wrapper : public Base {
  public:
                   Wrapper(const T& object)
                     : _object(object)
                   {}
                   Wrapper() {}

                   operator T()
                   { return _object; }

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


class _Object : public Rep
{
  public:
                  _Object() : _base(0) {}
                  _Object(Base *base) : _base(base) {}
                  ~_Object()
                  {
                    if (_base != 0 ){ delete _base; }
                  }
    Base*    base() const
                  { return _base; }

  private:
    Base*    _base;
};


class Object : public Handle
{
public:
                  Object()
                  { PTR = new _Object(); }
                  Object(Base *base)
                  { PTR = new _Object(base); }
                  Object(const Object& o)
                  : Handle((Handle&)o)
                  {}
    Object&  operator=(const Object& o)
                  {
                    Handle::operator=(o);
                    return *this;
                  }
    _Object* ptr() const
                  { return (_Object *)PTR; }
    bool          is_empty() const 
                  { return ptr()->base() == 0; }
};


template <class T>
Object
make_object(const T& t)
{
    return Object(new Wrapper< T >(t));
}

#ifdef CGAL_CFG_NO_DYNAMIC_CAST
template <class T>
T*
_dynamic_cast(Base *base, const T*)
{
    T dummy;
    if (base == 0) { return (T*) 0; }
    if (dummy.type_id() != base->type_id()) { return (T*) 0; }
    return (T*) base;
}

template <class T>
const T*
_dynamic_cast(const Base *base, const T*)
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
  Wrapper<T>*  wp = _dynamic_cast(o.ptr()->base(),
                                            (Wrapper<T>*) 0);
#else

# ifdef CGAL_CFG_DYNAMIC_CAST_BUG
  Wrapper<T>   instantiate_it;
# endif // CGAL_CFG_DYNAMIC_CAST_BUG

  Wrapper<T>*  wp = dynamic_cast<Wrapper<T>*>(o.ptr()->base());
#endif // CGAL_CFG_NO_DYNAMIC_CAST
  if( wp == 0 ){ return false; }
  t = *(wp);
  return true;
}

CGAL_END_NAMESPACE

#endif // CGAL_OBJECT_H

