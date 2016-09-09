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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/STL_Extension/include/CGAL/Handle.h $
// $Id: Handle.h 56667 2010-06-09 07:37:13Z sloriot $
// 
//
// Author(s)     : Sylvain Pion

#ifndef CGAL_HANDLE_H
#define CGAL_HANDLE_H

#include <cstddef>
#include <CGAL/Handle_for.h>
#include <CGAL/assertions.h>

namespace CGAL {

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
    
    typedef std::ptrdiff_t Id_type ;
    
    Handle()
	: PTR(static_cast<Rep*>(0)) {}

    Handle(const Handle& x)
    {
      CGAL_precondition( x.PTR != static_cast<Rep*>(0) );
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
      CGAL_precondition( x.PTR != static_cast<Rep*>(0) );
      x.PTR->count++;
      if ( PTR && (--PTR->count == 0))
	  delete PTR;
      PTR = x.PTR;
      return *this;
    }

    int
    refs()  const { return PTR->count; }

    Id_type id() const { return PTR - static_cast<Rep*>(0); }

    bool identical(const Handle& h) const { return PTR == h.PTR; }

  protected:
    Rep* PTR;
};

//inline Handle::Id_type id(const Handle& x) { return x.id() ; }

inline bool identical(const Handle &h1, const Handle &h2) { return h1.identical(h2); }

} //namespace CGAL

#endif // CGAL_HANDLE_H
