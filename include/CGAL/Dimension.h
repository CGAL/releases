// Copyright (c) 2008  INRIA Sophia-Antipolis (France).
// Aviv University (Israel).  All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.6-branch/Kernel_23/include/CGAL/Dimension.h $
// $Id: Dimension.h 51456 2009-08-24 17:10:04Z spion $
//
// Author(s)     : Sylvain Pion

#ifndef CGAL_DIMENSION_H
#define CGAL_DIMENSION_H

#include <CGAL/basic.h>
#include <CGAL/Kernel_traits.h>
#include <climits>

CGAL_BEGIN_NAMESPACE

// These tag classes help dispatching functions based on a geometric dimension.

template < int dim >
struct Dimension_tag
{
  static const int value = dim;
};

struct Dynamic_dimension_tag {};


namespace internal {

  template < typename D >
  struct Dim_value {
    static const int value = D::value;
  };

  template <>
  struct Dim_value <Dynamic_dimension_tag> {};

} // namespace internal


// Ambient_dimension gives access to the dimension of the ambient space of an object.

template < typename T, typename K = typename Kernel_traits<T>::Kernel >
struct Ambient_dimension
  : public internal::Dim_value< typename K::template Ambient_dimension<T>::type >
{
  typedef typename K::template Ambient_dimension<T>::type type;
};


// Feature_dimension gives access to the dimension of an object.

template < typename T, typename K = typename Kernel_traits<T>::Kernel >
struct Feature_dimension
  : public internal::Dim_value< typename K::template Feature_dimension<T>::type >
{
  typedef typename K::template Feature_dimension<T>::type type;
};

CGAL_END_NAMESPACE

#endif // CGAL_DIMENSION_H
