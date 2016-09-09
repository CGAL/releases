// Copyright (c) 1997-2003  Utrecht University (The Netherlands),
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
// $Source: /CVSROOT/CGAL/Packages/Interval_arithmetic/include/CGAL/Arithmetic_filter/predicates/Regular_triangulation_rtH2.h,v $
// $Revision: 1.49 $ $Date: 2003/10/21 12:17:29 $
// $Name: CGAL_3_0_1  $
//
// Author(s)     : Sylvain Pion

// This file is automatically generated by
// scripts/filtered_predicates_generator.pl

#ifndef CGAL_ARITHMETIC_FILTER_REGULAR_TRIANGULATION_RTH2_H
#define CGAL_ARITHMETIC_FILTER_REGULAR_TRIANGULATION_RTH2_H

#include <CGAL/Profile_counter.h>

CGAL_BEGIN_NAMESPACE
template <class ET> class Lazy_exact_nt;
CGAL_END_NAMESPACE

CGAL_BEGIN_NAMESPACE

#ifndef CGAL_CFG_MATCHING_BUG_2
template < class CGAL_IA_CT, class CGAL_IA_ET, bool CGAL_IA_PROTECTED,
           class CGAL_IA_CACHE >
#else
static
#endif
/*  */
Oriented_side
power_testH2(
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &phx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &phy,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &phw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &pwt,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &qhx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &qhy,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &qhw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &qwt,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &rhx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &rhy,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &rhw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &rwt,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &thx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &thy,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &thw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &twt)
{
  try
  {
    CGAL_PROFILER("IA power_testH2 calls");
    Protect_FPU_rounding<CGAL_IA_PROTECTED> Protection;
    return power_testH2(
		phx.interval(),
		phy.interval(),
		phw.interval(),
		pwt.interval(),
		qhx.interval(),
		qhy.interval(),
		qhw.interval(),
		qwt.interval(),
		rhx.interval(),
		rhy.interval(),
		rhw.interval(),
		rwt.interval(),
		thx.interval(),
		thy.interval(),
		thw.interval(),
		twt.interval());
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    CGAL_PROFILER("IA power_testH2 failures");
    Protect_FPU_rounding<!CGAL_IA_PROTECTED> Protection(CGAL_FE_TONEAREST);
    return power_testH2(
		phx.exact(),
		phy.exact(),
		phw.exact(),
		pwt.exact(),
		qhx.exact(),
		qhy.exact(),
		qhw.exact(),
		qwt.exact(),
		rhx.exact(),
		rhy.exact(),
		rhw.exact(),
		rwt.exact(),
		thx.exact(),
		thy.exact(),
		thw.exact(),
		twt.exact());
  }
}

#ifndef CGAL_CFG_MATCHING_BUG_2
template < class ET >
/*  */
Oriented_side
power_testH2(
    const Lazy_exact_nt<ET> &phx,
    const Lazy_exact_nt<ET> &phy,
    const Lazy_exact_nt<ET> &phw,
    const Lazy_exact_nt<ET> &pwt,
    const Lazy_exact_nt<ET> &qhx,
    const Lazy_exact_nt<ET> &qhy,
    const Lazy_exact_nt<ET> &qhw,
    const Lazy_exact_nt<ET> &qwt,
    const Lazy_exact_nt<ET> &rhx,
    const Lazy_exact_nt<ET> &rhy,
    const Lazy_exact_nt<ET> &rhw,
    const Lazy_exact_nt<ET> &rwt,
    const Lazy_exact_nt<ET> &thx,
    const Lazy_exact_nt<ET> &thy,
    const Lazy_exact_nt<ET> &thw,
    const Lazy_exact_nt<ET> &twt)
{
  try
  {
    CGAL_PROFILER("Lazy IA power_testH2 calls");
    Protect_FPU_rounding<true> Protection;
    return power_testH2(
		phx.interval(),
		phy.interval(),
		phw.interval(),
		pwt.interval(),
		qhx.interval(),
		qhy.interval(),
		qhw.interval(),
		qwt.interval(),
		rhx.interval(),
		rhy.interval(),
		rhw.interval(),
		rwt.interval(),
		thx.interval(),
		thy.interval(),
		thw.interval(),
		twt.interval());
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    CGAL_PROFILER("Lazy IA power_testH2 failures");
    Protect_FPU_rounding<false> Protection(CGAL_FE_TONEAREST);
    return power_testH2(
		phx.exact(),
		phy.exact(),
		phw.exact(),
		pwt.exact(),
		qhx.exact(),
		qhy.exact(),
		qhw.exact(),
		qwt.exact(),
		rhx.exact(),
		rhy.exact(),
		rhw.exact(),
		rwt.exact(),
		thx.exact(),
		thy.exact(),
		thw.exact(),
		twt.exact());
  }
}
#endif

#ifndef CGAL_CFG_MATCHING_BUG_2
template < class CGAL_IA_CT, class CGAL_IA_ET, bool CGAL_IA_PROTECTED,
           class CGAL_IA_CACHE >
#else
static
#endif
/*  */
Oriented_side
power_testH2(
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &phx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &phy,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &phw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &pwt,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &qhx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &qhy,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &qhw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &qwt,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &thx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &thy,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &thw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &twt)
{
  try
  {
    CGAL_PROFILER("IA power_testH2 calls");
    Protect_FPU_rounding<CGAL_IA_PROTECTED> Protection;
    return power_testH2(
		phx.interval(),
		phy.interval(),
		phw.interval(),
		pwt.interval(),
		qhx.interval(),
		qhy.interval(),
		qhw.interval(),
		qwt.interval(),
		thx.interval(),
		thy.interval(),
		thw.interval(),
		twt.interval());
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    CGAL_PROFILER("IA power_testH2 failures");
    Protect_FPU_rounding<!CGAL_IA_PROTECTED> Protection(CGAL_FE_TONEAREST);
    return power_testH2(
		phx.exact(),
		phy.exact(),
		phw.exact(),
		pwt.exact(),
		qhx.exact(),
		qhy.exact(),
		qhw.exact(),
		qwt.exact(),
		thx.exact(),
		thy.exact(),
		thw.exact(),
		twt.exact());
  }
}

#ifndef CGAL_CFG_MATCHING_BUG_2
template < class ET >
/*  */
Oriented_side
power_testH2(
    const Lazy_exact_nt<ET> &phx,
    const Lazy_exact_nt<ET> &phy,
    const Lazy_exact_nt<ET> &phw,
    const Lazy_exact_nt<ET> &pwt,
    const Lazy_exact_nt<ET> &qhx,
    const Lazy_exact_nt<ET> &qhy,
    const Lazy_exact_nt<ET> &qhw,
    const Lazy_exact_nt<ET> &qwt,
    const Lazy_exact_nt<ET> &thx,
    const Lazy_exact_nt<ET> &thy,
    const Lazy_exact_nt<ET> &thw,
    const Lazy_exact_nt<ET> &twt)
{
  try
  {
    CGAL_PROFILER("Lazy IA power_testH2 calls");
    Protect_FPU_rounding<true> Protection;
    return power_testH2(
		phx.interval(),
		phy.interval(),
		phw.interval(),
		pwt.interval(),
		qhx.interval(),
		qhy.interval(),
		qhw.interval(),
		qwt.interval(),
		thx.interval(),
		thy.interval(),
		thw.interval(),
		twt.interval());
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    CGAL_PROFILER("Lazy IA power_testH2 failures");
    Protect_FPU_rounding<false> Protection(CGAL_FE_TONEAREST);
    return power_testH2(
		phx.exact(),
		phy.exact(),
		phw.exact(),
		pwt.exact(),
		qhx.exact(),
		qhy.exact(),
		qhw.exact(),
		qwt.exact(),
		thx.exact(),
		thy.exact(),
		thw.exact(),
		twt.exact());
  }
}
#endif

CGAL_END_NAMESPACE

#endif // CGAL_ARITHMETIC_FILTER_REGULAR_TRIANGULATION_RTH2_H
