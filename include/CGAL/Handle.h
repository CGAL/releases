// Copyright (c) 1999  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source: /CVSROOT/CGAL/Packages/Kernel_23/include/CGAL/Handle.h,v $
// $Revision: 1.10 $ $Date: 2003/10/21 12:18:04 $
// $Name: current_submission $
//
// Author(s)     :

#ifndef CGAL_HANDLE_H
#define CGAL_HANDLE_H

#include <CGAL/Handle_for.h>

CGAL_BEGIN_NAMESPACE

class Rep
{
    friend class Handle;
  protected:
             Rep() { count = 1; }
    virtual ~Rep() {}

    int      count;
};

class Handle
{
  public:
    Handle()
	: PTR(static_cast<Rep*>(0)) {}

    Handle(const Handle& x)
    {
      CGAL_kernel_precondition( x.PTR != static_cast<Rep*>(0) );
      PTR = x.PTR;
      PTR->count++;
    }

    ~Handle()
    {
	if ( PTR && (--PTR->count == 0))
	    delete PTR;
    }

    Handle&
    operator=(const Handle& x)
    {
      CGAL_kernel_precondition( x.PTR != static_cast<Rep*>(0) );
      x.PTR->count++;
      if ( PTR && (--PTR->count == 0))
	  delete PTR;
      PTR = x.PTR;
      return *this;
    }

    int
    refs()  const { return PTR->count; }

    friend unsigned long id(const Handle& x);

  protected:
    Rep* PTR;
};

inline
unsigned long
id(const Handle& x)
{ return reinterpret_cast<unsigned long>(x.PTR); }

template < class T >
inline
bool
identical(const T &t1, const T &t2)
{ return id(t1) == id(t2); }

CGAL_END_NAMESPACE

#endif // CGAL_HANDLE_H
