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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/STL_Extension/include/CGAL/is_iterator.h $
// $Id: is_iterator.h 60844 2011-01-18 10:50:05Z glisse $
// 
//
// Author(s)     : Marc Glisse


#ifndef CGAL_IS_ITERATOR_H
#define CGAL_IS_ITERATOR_H

#include <iterator>
#include <boost/type_traits.hpp>
#include <boost/mpl/has_xxx.hpp>

namespace CGAL {
namespace internal {
BOOST_MPL_HAS_XXX_TRAIT_DEF(iterator_category)
template <class T> struct is_iterator_ {
	enum { value = has_iterator_category<T>::value
	       	|| boost::is_pointer<T>::value }; 
};
template <class T,class U,bool=is_iterator_<T>::value>
struct is_iterator_type_ {
	enum { value=false };
};
template <class T,class U> struct is_iterator_type_<T,U,true> :
	//boost::is_base_of<U,typename std::iterator_traits<T>::iterator_category>
	boost::is_convertible<typename std::iterator_traits<T>::iterator_category,U>
	{};
}

template <class T> struct is_iterator :
	internal::is_iterator_<typename boost::decay<T>::type> {};

template <class T,class Tag> struct is_iterator_type :
	internal::is_iterator_type_<typename boost::decay<T>::type,Tag> {};

}

#endif // CGAL_IS_ITERATOR_H
