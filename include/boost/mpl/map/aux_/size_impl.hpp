
#ifndef BOOST_MPL_MAP_AUX_SIZE_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_SIZE_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source: /CVSROOT/CGAL/Packages/Boost/include/boost/mpl/map/aux_/size_impl.hpp,v $
// $Date: 2004/11/20 10:42:13 $
// $Revision: 1.1.1.1 $

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct size_impl< aux::map_tag >
{
    template< typename Map > struct apply
        : Map::size
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_SIZE_IMPL_HPP_INCLUDED
