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
// file          : include/CGAL/Object.h
// package       : Kernel_basic (3.90)
// revision      : $Revision: 1.11 $
// revision_date : $Date: 2002/02/06 19:02:31 $
// author(s)     : Stefan Schirra
//                 Andreas Fabri
//                 Geert-Jan Giezeman
//                 Michael Seel
//                 Sylvain Pion
//
// coordinator   : MPI Saarbruecken, Germany 
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_OBJECT_H
#define CGAL_OBJECT_H

#include <CGAL/Handle_for_virtual.h>

CGAL_BEGIN_NAMESPACE

template <class T>
class Wrapper : public Ref_counted_virtual
{
  public:
    Wrapper(const T& object) : _object(object) {}

    Wrapper() {}

    operator T() const { return _object; }

    ~Wrapper() {}

  private:
    T         _object;
};

class Object
  : public Handle_for_virtual<Ref_counted_virtual>
{
    struct empty{};
    typedef Handle_for_virtual<Ref_counted_virtual> base;

  public:

    struct private_tag{};

    Object()
    {
	initialize_with(Wrapper<empty>());
    }

    template <class T>
    Object(const T&t, private_tag)
    {
	initialize_with(Wrapper<T>(t));
    }

    template <class T>
    bool assign(T &t) const
    {
#ifdef _MSC_VER
      try {
#endif
        const Wrapper<T> *wp = dynamic_cast<const Wrapper<T> *>(Ptr());
        if (wp == NULL)
            return false;
        t = *wp;
#ifdef _MSC_VER
      }
      catch (...) {
          std::cerr << "ERROR : YOUR COMPILER MUST SUPPORT RTTI" << std::endl;
          abort();
      }
#endif
      return true;
    }

    bool
    is_empty() const
    {
	empty E;
	return assign(E);
    }
};


template <class T>
inline
Object
make_object(const T& t)
{
    return Object(t, Object::private_tag());
}

template <class T>
inline
bool
assign(T& t, const Object& o)
{
    return o.assign(t);
}

CGAL_END_NAMESPACE

#endif // CGAL_OBJECT_H
