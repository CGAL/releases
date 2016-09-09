// Copyright (c) 2011  INRIA Saclay Ile-de-France (France).
// All rights reserved.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/releases/CGAL-3.9-branch/STL_Extension/include/CGAL/is_convertible.h $
// $Id: is_convertible.h 61559 2011-03-08 10:27:31Z glisse $
// 
//
// Author(s)     : Marc Glisse


#ifndef CGAL_IS_CONVERTIBLE_H
#define CGAL_IS_CONVERTIBLE_H

#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/is_convertible.hpp>
#ifdef CGAL_USE_GMPXX
#include <gmpxx.h>
#endif

namespace CGAL {

template<class From,class To>struct is_implicit_convertible
        : boost::is_convertible<From,To> {};

#ifdef CGAL_USE_GMPXX
// Work around a gmpxx misfeature
template<class T>struct is_implicit_convertible<__gmp_expr<mpq_t,T>,mpz_class>
        : boost::false_type {};
#endif

// TODO: add is_explicit_convertible (using boost::is_constructible?)
}

#endif // CGAL_IS_CONVERTIBLE_H
