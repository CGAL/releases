// Copyright (c) 2006-2008  Max-Planck-Institute Saarbruecken (Germany)
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.6-branch/Number_types/include/CGAL/utils.h $
// $Id: utils.h 53015 2009-11-13 09:50:04Z spion $
//
//
// Author(s)     : Michael Hemmer <hemmer@mpi-sb.mpg.de>

#ifndef CGAL_UTILS_H
#define CGAL_UTILS_H

#include <CGAL/number_type_basic.h>

CGAL_BEGIN_NAMESPACE

// use Min
template< class T >
inline T min BOOST_PREVENT_MACRO_SUBSTITUTION
( const T& x , const T& y) {
    return Min<T>()( x , y );
}

template< class T , class Compare >
inline T min BOOST_PREVENT_MACRO_SUBSTITUTION
( const T& x , const T& y, const Compare& c) {
    return Min<T, Compare>(c)( x , y );
}

// use Max
template< class T >
inline T max BOOST_PREVENT_MACRO_SUBSTITUTION
( const T& x , const T& y) {
    return Max<T>()( x , y );
}

template< class T , class Compare >
inline T max BOOST_PREVENT_MACRO_SUBSTITUTION
( const T& x , const T& y, const Compare& c) {
    return Max<T, Compare>(c)( x , y );
}

// use Is_valid
template< class T >
inline bool is_valid( const T& x ) {
  return Is_valid< T >()( x );
}

CGAL_END_NAMESPACE

#endif // CGAL_UTILS_H
