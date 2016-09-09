
#ifndef BOOST_MPL_ORDER_HPP_INCLUDED
#define BOOST_MPL_ORDER_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source: /CVSROOT/CGAL/Packages/Boost/include/boost/mpl/order.hpp,v $
// $Date: 2004/11/20 10:39:23 $
// $Revision: 1.1.1.2 $

#include <boost/mpl/order_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/order_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(AssociativeSequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Key)
    >
struct order
    : order_impl< typename sequence_tag<AssociativeSequence>::type >
        ::template apply<AssociativeSequence,Key>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,order,(AssociativeSequence,Key))
};

BOOST_MPL_AUX_NA_SPEC(2, order)

}}

#endif // BOOST_MPL_ORDER_HPP_INCLUDED
