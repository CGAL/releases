// Copyright (c) 2007-09  INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Point_set_processing_3/include/CGAL/value_type_traits.h $
// $Id: value_type_traits.h 48163 2009-02-20 13:17:26Z lsaboret $
//
// Author(s) : Alberto Ganesh Barbati and Laurent Saboret

#ifndef CGAL_VALUE_TYPE_TRAITS_H
#define CGAL_VALUE_TYPE_TRAITS_H

#include <iterator>

CGAL_BEGIN_NAMESPACE


/// Traits class to get the value type of any iterator,
/// including an output iterator.
/// Based on code posted by Alberto Ganesh Barbati at
/// http://www.adras.com/Why-no-std-back-insert-iterator-value-type.t2639-153-3.html
///
/// Usage is:
/// typedef typename value_type_traits<Iter>::type value_type;

template <class T>
struct value_type_traits
{
  typedef typename std::iterator_traits<T>::value_type type;
};

template <class T>
struct value_type_traits<std::back_insert_iterator<T> >
{
  typedef typename T::value_type type;
};


CGAL_END_NAMESPACE

#endif // CGAL_VALUE_TYPE_TRAITS_H

