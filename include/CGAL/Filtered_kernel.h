// Copyright (c) 2001  Utrecht University (The Netherlands),
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
// $Source: /CVSROOT/CGAL/Packages/Interval_arithmetic/include/CGAL/Filtered_kernel.h,v $
// $Revision: 1.31 $ $Date: 2003/10/21 15:50:26 $
// $Name: current_submission $
//
// Author(s)     : Sylvain Pion

#ifndef CGAL_FILTERED_KERNEL_H
#define CGAL_FILTERED_KERNEL_H

#include <CGAL/basic.h>
#include <CGAL/Filtered_predicate.h>
#include <CGAL/Cartesian_converter.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Kernel/Type_equality_wrapper.h>
#include <CGAL/MP_Float.h>
#include <CGAL/Quotient.h>

// This file contains the definition of a generic kernel filter.
//
// TODO:
// - at the moment, it's restricted to IA filtering, but this should be
//   generalized to allow other kinds of filters (static...).
// - at the moment, only the predicates are filtered.
//   Constructions will come later.
// - the kernel provides the traits interface, as well as type equality.
//   Having the global functions working is another story...
// - The converters are more a property of the types rather than anything else,
//   so maybe they should not be passed as template parameter, but use a
//   traits-like mecanism ?

CGAL_BEGIN_NAMESPACE

// CK = construction kernel.
// EK = exact kernel called when needed by the filter.
// FK = filtering kernel
template < typename CK, typename Kernel >
class Filtered_kernel_base
  : public CK::template Base<Kernel>::Type
{
    typedef typename CK::template Base<Kernel>::Type   Kernel_base;
    // Hardcoded for now.
    typedef Simple_cartesian<Quotient<MP_Float> >    EK;
    typedef Simple_cartesian<Interval_nt_advanced>   FK;
    typedef Cartesian_converter<Kernel_base, EK>     C2E;
    typedef Cartesian_converter<Kernel_base, FK,
                                To_interval<typename Kernel_base::RT> > C2F;
public:

    template < typename Kernel2 >
    struct Base { typedef Filtered_kernel_base<CK, Kernel2>  Type; };

    // What to do with the tag ?
    // Probably this should not exist, should it ?
    // struct filter_tag{};
    // typedef filter_tag                                     Kernel_tag;
    // typedef typename CK::Kernel_tag                       Kernel_tag;
    // typedef typename CK::Rep_tag                          Rep_tag;

    // We change the predicates.
#define CGAL_Kernel_pred(P, Pf) \
    typedef Filtered_predicate<typename EK::P, typename FK::P, \
	                     C2E, C2F> P; \
    P Pf() const { return P(); }

    // We don't touch the constructions.
#define CGAL_Kernel_cons(Y,Z)

#include <CGAL/Kernel/interface_macros.h>

};

template <class CK>
struct Filtered_kernel_adaptor
  : public Filtered_kernel_base< CK, Filtered_kernel_adaptor<CK> >
{};

template <class CK>
struct Filtered_kernel_without_type_equality
  : public Filtered_kernel_base< CK, Filtered_kernel_without_type_equality<CK> >
{};

template <class CK>
struct Filtered_kernel
  : public Type_equality_wrapper< 
             Filtered_kernel_base< CK, Filtered_kernel<CK> >,
             Filtered_kernel<CK> >
{};

CGAL_END_NAMESPACE

#endif // CGAL_FILTERED_KERNEL_H
