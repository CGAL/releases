
#ifndef BOOST_MPL_AUX_CONFIG_STATIC_CONSTANT_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_STATIC_CONSTANT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source: /CVSROOT/CGAL/Packages/Boost/include/boost/mpl/aux_/config/static_constant.hpp,v $
// $Date: 2004/11/20 10:39:42 $
// $Revision: 1.1.1.2 $

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
// BOOST_STATIC_CONSTANT is defined here:
#   include <boost/config.hpp>
#else
// undef the macro for the preprocessing mode
#   undef BOOST_STATIC_CONSTANT
#endif

#endif // BOOST_MPL_AUX_CONFIG_STATIC_CONSTANT_HPP_INCLUDED
