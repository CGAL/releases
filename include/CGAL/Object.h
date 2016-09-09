// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
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
// ----------------------------------------------------------------------
//
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : include/CGAL/Object.h
// package       : Kernel_basic (1.2)
// source        : Object.lw 
// revision      : 1.2
// revision_date : 12 Jun 1998
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

class CGAL_Base;
class CGAL__Object;
class CGAL_Object;
template <class T> class CGAL_Wrapper;


class CGAL_Base
{
  public:
    virtual       ~CGAL_Base() {}
#ifdef CGAL_CFG_NO_DYNAMIC_CAST
    virtual int*   type_id() const
                   { return 0; }
#endif // CGAL_CFG_NO_DYNAMIC_CAST
};


template <class T>
class CGAL_Wrapper : public CGAL_Base {
  public:
                   CGAL_Wrapper(const T& object)
                     : _object(object)
                   {}
                   CGAL_Wrapper() {}

                   operator T()
                   { return _object; }

    virtual        ~CGAL_Wrapper() {}
#ifdef CGAL_CFG_NO_DYNAMIC_CAST
    virtual int*   type_id() const;
#endif // CGAL_CFG_NO_DYNAMIC_CAST
  private:
    T              _object;
};

#ifdef CGAL_CFG_NO_DYNAMIC_CAST
template <class T>
int*
CGAL_Wrapper<T>::type_id() const
{
  static int type_base;
  return &type_base;
}
#endif // CGAL_CFG_NO_DYNAMIC_CAST


class CGAL__Object : public CGAL_Rep
{
  public:
                  CGAL__Object() : _base(0) {}
                  CGAL__Object(CGAL_Base *base) : _base(base) {}
                  ~CGAL__Object()
                  {
                    if (_base != 0 ){ delete _base; }
                  }
    CGAL_Base*    base() const
                  { return _base; }

  private:
    CGAL_Base*    _base;
};


class CGAL_Object : public CGAL_Handle
{
public:
                  CGAL_Object()
                  { PTR = new CGAL__Object(); }
                  CGAL_Object(CGAL_Base *base)
                  { PTR = new CGAL__Object(base); }
                  CGAL_Object(const CGAL_Object& o)
                  : CGAL_Handle((CGAL_Handle&)o)
                  {}
    CGAL_Object&  operator=(const CGAL_Object& o)
                  {
                    CGAL_Handle::operator=(o);
                    return *this;
                  }
    CGAL__Object* ptr() const
                  { return (CGAL__Object *)PTR; }
    bool          is_empty() const 
                  { return ptr()->base() == 0; }
};


template <class T>
CGAL_Object
CGAL_make_object(const T& t)
{
    return CGAL_Object(new CGAL_Wrapper< T >(t));
}

#ifdef CGAL_CFG_NO_DYNAMIC_CAST
template <class T>
T*
CGAL__dynamic_cast(CGAL_Base *base, const T*)
{
    T dummy;
    if (base == 0) { return (T*) 0; }
    if (dummy.type_id() != base->type_id()) { return (T*) 0; }
    return (T*) base;
}

template <class T>
const T*
CGAL__dynamic_cast(const CGAL_Base *base, const T*)
{
    T dummy;
    if (base == 0) { return (T*) 0; }
    if (dummy.type_id() != base->type_id()) { return (const T*) 0; }
    return (const T*) base;
}
#endif // CGAL_CFG_NO_DYNAMIC_CAST

template <class T>
bool
CGAL_assign(T& t, const CGAL_Object& o)
{
#ifdef CGAL_CFG_NO_DYNAMIC_CAST
  CGAL_Wrapper<T>*  wp = CGAL__dynamic_cast(o.ptr()->base(),
                                            (CGAL_Wrapper<T>*) 0);
#else

# ifdef CGAL_CFG_DYNAMIC_CAST_BUG
  CGAL_Wrapper<T>   instantiate_it;
# endif // CGAL_CFG_DYNAMIC_CAST_BUG

  CGAL_Wrapper<T>*  wp = dynamic_cast<CGAL_Wrapper<T>*>(o.ptr()->base());
#endif // CGAL_CFG_NO_DYNAMIC_CAST
  if( wp == 0 ){ return false; }
  t = *(wp);
  return true;
}

#endif // CGAL_OBJECT_H

