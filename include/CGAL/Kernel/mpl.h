// Copyright (c) 2004  Utrecht University (The Netherlands),
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Kernel_23/include/CGAL/Kernel/mpl.h $
// $Id: mpl.h 56667 2010-06-09 07:37:13Z sloriot $
// 
//
// Author(s)     : Sylvain Pion

#ifndef CGAL_KERNEL_MPL_H
#define CGAL_KERNEL_MPL_H

#include <CGAL/basic.h>

// Some tools for basic template metaprogramming.
// These bits should move to CGAL/mpl.h in STL_Extension, or taken from Boost.

namespace CGAL {

// The additionnal int parameter is to obtain different types.
template < typename A, typename B, int = 0 >
struct First_if_different {
  typedef A Type;
};

template < typename A, int i >
struct First_if_different<A, A, i> {
  struct Type{};
};

} //namespace CGAL

#endif
