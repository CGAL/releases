// Copyright (c) 2000,2001,2002,2003  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
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
// $Source: /CVSROOT/CGAL/Packages/Cartesian_kernel/include/CGAL/Cartesian.h,v $
// $Revision: 1.41 $ $Date: 2003/10/21 12:14:12 $
// $Name: current_submission $
//
// Author(s)     : Herve Bronnimann, Sylvain Pion

#ifndef CGAL_CARTESIAN_H
#define CGAL_CARTESIAN_H

#include <CGAL/Cartesian/Cartesian_base.h>
#include <CGAL/Handle_for.h>
#include <CGAL/Kernel/Type_equality_wrapper.h>

CGAL_BEGIN_NAMESPACE

template < typename FT_, typename Kernel >
struct Cartesian_base_ref_count
  : public Cartesian_base< Kernel >
{
    typedef FT_                                           RT;
    typedef FT_                                           FT;

    // The mecanism that allows to specify reference-counting or not.
    template < typename T >
    struct Handle { typedef Handle_for<T>    type; };

    template < typename Kernel2 >
    struct Base { typedef Cartesian_base_ref_count<FT_, Kernel2>  Type; };

    // TODO: cleanup (use Rational_traits<> instead)
    static   FT make_FT(const RT & num, const RT& denom) { return num/denom;}
    static   FT make_FT(const RT & num)                  { return num;}
    static   RT FT_numerator(const FT &r)                { return r;}
    static   RT FT_denominator(const FT &)               { return RT(1);}
};

template < typename FT_ >
struct Cartesian
  : public Type_equality_wrapper<
                Cartesian_base_ref_count<FT_, Cartesian<FT_> >,
                Cartesian<FT_> >
{};

CGAL_END_NAMESPACE

CGAL_ITERATOR_TRAITS_POINTER_SPEC_TEMPLATE(CGAL::Cartesian)

#endif // CGAL_CARTESIAN_H
