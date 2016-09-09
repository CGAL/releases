// Copyright (c) 2009  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/STL_Extension/include/CGAL/tuple.h $
// $Id: tuple.h 49063 2009-04-30 17:28:55Z sloriot $
//
// Author(s)     : Sebastien Loriot, Sylvain Pion

#ifndef CGAL_TUPLE_H
#define CGAL_TUPLE_H

// A wrapper around C++0x, TR1 or Boost tuple<>.
// Together with the Is_in_tuple<> tool.

#include <CGAL/config.h>

#ifndef CGAL_CFG_NO_CPP0X_TUPLE
#  include <tuple>
#elif !defined CGAL_CFG_NO_TR1_TUPLE
#  include <tr1/tuple>
#else
#  include <boost/tuple/tuple.hpp>
#endif

CGAL_BEGIN_NAMESPACE

namespace cpp0x {

#ifndef CGAL_CFG_NO_CPP0X_TUPLE
using std::tuple;
using std::make_tuple;
using std::tie;
using std::get;
#elif !defined CGAL_CFG_NO_TR1_TUPLE
using std::tr1::tuple;
using std::tr1::make_tuple;
using std::tr1::tie;
using std::tr1::get;
#else
using boost::tuple;
using boost::make_tuple;
using boost::tie;
using boost::get;
#endif

} // cpp0x

#ifndef CGAL_CFG_NO_CPP0X_VARIADIC_TEMPLATES

// Tool to test whether a type V is among the types of a tuple<...> = T.
template <typename V, typename T>
struct Is_in_tuple;

template <typename V, typename T0, typename... T>
struct Is_in_tuple <V, cpp0x::tuple<T0, T...> >
{
  static const bool value = Is_in_tuple<V, cpp0x::tuple<T...> >::value;
};

template <typename V, typename... T>
struct Is_in_tuple <V, cpp0x::tuple<V, T...> >
{
  static const bool value = true;
};

template <typename V>
struct Is_in_tuple <V, cpp0x::tuple<> >
{
  static const bool value = false;
};

#else

// Non-variadic version

template <typename V,typename T>
struct Is_in_tuple;

template <typename V,typename T0,typename T1>
struct Is_in_tuple <V,cpp0x::tuple<T0,T1> >
{
  static const bool value = Is_in_tuple<V,cpp0x::tuple<T1> >::value;
};

template <typename V, typename T0,typename T1,typename T2>
struct Is_in_tuple <V, cpp0x::tuple<T0,T1,T2> >
{
  static const bool value = Is_in_tuple<V,cpp0x::tuple<T1,T2> >::value;
};

template <typename V, typename T0,typename T1,typename T2,typename T3>
struct Is_in_tuple <V, cpp0x::tuple<T0,T1,T2,T3> >
{
  static const bool value = Is_in_tuple<V,cpp0x::tuple<T1,T2,T3> >::value;
};

template <typename V, typename T0,typename T1,typename T2,typename T3,typename T4>
struct Is_in_tuple <V, cpp0x::tuple<T0,T1,T2,T3,T4> >
{
  static const bool value = Is_in_tuple<V,cpp0x::tuple<T1,T2,T3,T4> >::value;
};

template <typename V, typename T0,typename T1,typename T2,typename T3,typename T4,typename T5>
struct Is_in_tuple <V, cpp0x::tuple<T0,T1,T2,T3,T4,T5> >
{
  static const bool value = Is_in_tuple<V,cpp0x::tuple<T1,T2,T3,T4,T5> >::value;
};

template <typename V, typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6>
struct Is_in_tuple <V, cpp0x::tuple<T0,T1,T2,T3,T4,T5,T6> >
{
  static const bool value = Is_in_tuple<V,cpp0x::tuple<T1,T2,T3,T4,T5,T6> >::value;
};


//Conclusions

template <typename V,typename T1>
struct Is_in_tuple <V,cpp0x::tuple<T1> >
{
  static const bool value = false;
};

template <typename V>
struct Is_in_tuple <V,cpp0x::tuple<V> >
{
  static const bool value = true;
};

template <typename V,typename T1>
struct Is_in_tuple <V,cpp0x::tuple<V,T1> >
{
  static const bool value = true;
};

template <typename V,typename T1,typename T2>
struct Is_in_tuple <V,cpp0x::tuple<V,T1,T2> >
{
  static const bool value = true;
};

template <typename V,typename T1,typename T2,typename T3>
struct Is_in_tuple <V,cpp0x::tuple<V,T1,T2,T3> >
{
  static const bool value = true;
};

template <typename V,typename T1,typename T2,typename T3,typename T4>
struct Is_in_tuple <V,cpp0x::tuple<V,T1,T2,T3,T4> >
{
  static const bool value = true;
};

template <typename V,typename T1,typename T2,typename T3,typename T4,typename T5>
struct Is_in_tuple <V,cpp0x::tuple<V,T1,T2,T3,T4,T5> >
{
  static const bool value = true;
};

template <typename V,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6>
struct Is_in_tuple <V,cpp0x::tuple<V,T1,T2,T3,T4,T5,T6> >
{
  static const bool value = true;
};


#endif 

CGAL_END_NAMESPACE

#endif // CGAL_TUPLE_H
