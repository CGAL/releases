// Copyright (c) 2005  Stanford University (USA).
// All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Kinetic_data_structures/include/CGAL/Kinetic/internal/infinity_or_max.h $
// $Id: infinity_or_max.h 56668 2010-06-09 08:45:58Z sloriot $
// 
//
// Author(s)     : Daniel Russel <drussel@alumni.princeton.edu>

#ifndef CGAL_KINETIC_INFINITY_OR_MAX_H
#define CGAL_KINETIC_INFINITY_OR_MAX_H

#include <limits>

namespace CGAL { namespace Kinetic { namespace internal {
template <class T>
T infinity_or_max()
{
    if (std::numeric_limits<T>::has_infinity) return std::numeric_limits<T>::infinity();
    else return (std::numeric_limits<T>::max)();
}


template <class T>
T infinity_or_max(T)
{
    if (std::numeric_limits<T>::has_infinity) return std::numeric_limits<T>::infinity();
    else return (std::numeric_limits<T>::max)();
}


} } } //namespace CGAL::Kinetic::internal
#endif
