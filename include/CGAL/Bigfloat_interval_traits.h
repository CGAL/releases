// Copyright (c) 2006-2008 Max-Planck-Institute Saarbruecken (Germany).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Number_types/include/CGAL/Bigfloat_interval_traits.h $
// $Id: Bigfloat_interval_traits.h 47264 2008-12-08 06:25:14Z hemmer $
//
//
// Author(s)     : Michael Hemmer   <hemmer@mpi-inf.mpg.de>
//                 Ron Wein         <wein@post.tau.ac.il>


#ifndef CGAL_BIGFLOAT_INTERVAL_TRAITS_H
#define CGAL_BIGFLOAT_INTERVAL_TRAITS_H

#include<CGAL/basic.h>

CGAL_BEGIN_NAMESPACE

// TODO: rename this into MPFI_traits ? 
// add a better rounding control 

template<typename BigfloatInterval> class Bigfloat_interval_traits;

template<typename BFI> inline long get_significant_bits(BFI bfi) {
    typename Bigfloat_interval_traits<BFI>::Get_significant_bits 
        get_significant_bits;
    return get_significant_bits(bfi);
}

template<typename BFI> inline long set_precision(BFI,long prec) {
    typename Bigfloat_interval_traits<BFI>::Set_precision set_precision;
    return set_precision(prec);
}

template<typename BFI> inline long get_precision(BFI) {
    typename Bigfloat_interval_traits<BFI>::Get_precision get_precision;
    return get_precision();
}

CGAL_END_NAMESPACE

#endif // CGAL_BIGFLOAT_INTERVAL_TRAITS_H
