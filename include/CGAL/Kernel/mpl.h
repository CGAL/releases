// Copyright (c) 2004
// Utrecht University (The Netherlands),
// ETH Zurich (Switzerland),
// INRIA Sophia-Antipolis (France),
// Max-Planck-Institute Saarbruecken (Germany),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org)
//
// $URL: https://github.com/CGAL/cgal/blob/v5.5.3/Kernel_23/include/CGAL/Kernel/mpl.h $
// $Id: mpl.h 0779373 2020-03-26T13:31:46+01:00 Sébastien Loriot
// SPDX-License-Identifier: LGPL-3.0-or-later OR LicenseRef-Commercial
//
//
// Author(s)     : Sylvain Pion

#ifndef CGAL_KERNEL_MPL_H
#define CGAL_KERNEL_MPL_H

#include <CGAL/config.h>

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
