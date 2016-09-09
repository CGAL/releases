// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/ch_selected_extreme_points_2.h
// package       : Convex_hull_2 (3.34)
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2001/12/05 15:16:16 $
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================


#ifndef CGAL_CH_SELECTED_EXTREME_POINTS_2_H
#define CGAL_CH_SELECTED_EXTREME_POINTS_2_H

#include <CGAL/basic.h>
#include <iterator>


CGAL_BEGIN_NAMESPACE


// traverses the range [|first|,|last|). After execution, the value of |n| is
// an iterator in the range such that |*n| $\ge_{\rm yx}$ |*it| for
// all iterators |it| in the range. Similarly, for |s|, |w|, and |e| 
// the inequations |*s| $\le_{\rm yx}$ |*it|, |*w| $\le_{\rm xy}$ |*it|,
// and |*e| $\ge_{\rm yx}$ |*it| hold respectively for all iterators 
// |it| in the range.
// {\sc traits}: uses |Traits::Less_xy_2| and |Traits::Less_yx_2|.
template <class ForwardIterator, class Traits>
void
ch_nswe_point( ForwardIterator first, ForwardIterator last,
               ForwardIterator& n,
               ForwardIterator& s,
               ForwardIterator& w,
               ForwardIterator& e,
               const Traits& ch_traits);

template <class ForwardIterator>
inline
void
ch_nswe_point( ForwardIterator first, ForwardIterator last,
               ForwardIterator& n,
               ForwardIterator& s,
               ForwardIterator& w,
               ForwardIterator& e)
{
    typedef std::iterator_traits<ForwardIterator> ITraits;
    typedef typename ITraits::value_type          value_type;
    typedef CGAL::Kernel_traits<value_type>       KTraits;
    typedef typename KTraits::Kernel              Kernel;
    ch_nswe_point(first, last, n, s, w, e, Kernel());
}


// traverses the range [|first|,|last|). After execution, the value of |n| is
// an iterator in the range such that |*n| $\ge_{\rm yx}$ |*it| for
// all iterators |it| in the range. Similarly, for |s| the inequation
// |*s| $\le_{\rm yx}$ |*it| holds for all iterators |it| in the range.
// {\sc traits}: uses function object type |Traits::Less_yx_2|.
template <class ForwardIterator, class Traits>
void
ch_ns_point( ForwardIterator first, ForwardIterator last,
             ForwardIterator& n,
             ForwardIterator& s,
             const Traits& ch_traits );

template <class ForwardIterator>
inline
void
ch_ns_point( ForwardIterator first, ForwardIterator last,
             ForwardIterator& n,
             ForwardIterator& s)
{
    typedef std::iterator_traits<ForwardIterator> ITraits;
    typedef typename ITraits::value_type          value_type;
    typedef CGAL::Kernel_traits<value_type>       KTraits;
    typedef typename KTraits::Kernel              Kernel;
    ch_ns_point(first, last, n, s, Kernel());
}


// traverses the range [|first|,|last|). After execution, the value of |w| is
// an iterator in the range such that |*w| $\le_{\rm xy}$ |*it| for
// all iterators |it| in the range. Similarly, for |e| the inequation
// |*e| $\ge_{\rm yx}$ |*it| holds for all iterators |it| in the range.
// {\sc traits}: uses function object type |Traits::Less_xy_2|.
template <class ForwardIterator, class Traits>
void
ch_we_point( ForwardIterator first, ForwardIterator last,
             ForwardIterator& w,
             ForwardIterator& e,
             const Traits& ch_traits );

template <class ForwardIterator>
inline
void
ch_we_point( ForwardIterator first, ForwardIterator last,
             ForwardIterator& w,
             ForwardIterator& e)
{
    typedef std::iterator_traits<ForwardIterator> ITraits;
    typedef typename ITraits::value_type          value_type;
    typedef CGAL::Kernel_traits<value_type>       KTraits;
    typedef typename KTraits::Kernel              Kernel;
    ch_we_point(first, last, w, e, Kernel());
}


// traverses the range [|first|,|last|). After execution, the value of |n| is
// an iterator in the range such that |*n| $\ge_{\rm yx}$ |*it| for
// all iterators |it| in the range. 
// {\sc traits}: uses |Traits::Less_yx_2|.
template <class ForwardIterator, class Traits>
void
ch_n_point( ForwardIterator first, ForwardIterator last,
            ForwardIterator& n,
            const Traits& ch_traits );

template <class ForwardIterator>
inline
void
ch_n_point( ForwardIterator first, ForwardIterator last, ForwardIterator& n)
{
    typedef std::iterator_traits<ForwardIterator> ITraits;
    typedef typename ITraits::value_type          value_type;
    typedef CGAL::Kernel_traits<value_type>       KTraits;
    typedef typename KTraits::Kernel              Kernel;
    ch_n_point(first, last, n, Kernel());
}


// traverses the range [|first|,|last|). After execution, the value of |s| is
// an iterator in the range such that |*s| $\le_{\rm yx}$ |*it| for
// all iterators |it| in the range. 
// {\sc traits}: uses |Traits::Less_yx_2|.
template <class ForwardIterator, class Traits>
void
ch_s_point( ForwardIterator first, ForwardIterator last,
            ForwardIterator& s,
            const Traits& ch_traits );

template <class ForwardIterator>
inline
void
ch_s_point( ForwardIterator first, ForwardIterator last, ForwardIterator& s)
{
    typedef std::iterator_traits<ForwardIterator> ITraits;
    typedef typename ITraits::value_type          value_type;
    typedef CGAL::Kernel_traits<value_type>       KTraits;
    typedef typename KTraits::Kernel              Kernel;
    ch_s_point(first, last, s, Kernel());
}


// traverses the range [|first|,|last|). After execution, the value of |e| is
// an iterator in the range such that |*e| $\ge_{\rm yx}$ |*it| for
// for all iterators |it| in the range.
// {\sc traits}: uses |Traits::Less_xy_2|.
template <class ForwardIterator, class Traits>
void
ch_e_point( ForwardIterator first, ForwardIterator last,
            ForwardIterator& e,
            const Traits& ch_traits );

template <class ForwardIterator>
inline
void
ch_e_point( ForwardIterator first, ForwardIterator last, ForwardIterator& e)
{
    typedef std::iterator_traits<ForwardIterator> ITraits;
    typedef typename ITraits::value_type          value_type;
    typedef CGAL::Kernel_traits<value_type>       KTraits;
    typedef typename KTraits::Kernel              Kernel;
    ch_e_point(first, last, e, Kernel());
}


// traverses the range [|first|,|last|). After execution, the value of |w| is
// an iterator in the range such that |*w| $\le_{\rm yx}$ |*it| for
// for all iterators |it| in the range.
// {\sc traits}: uses |Traits::Less_yx_2|.
template <class ForwardIterator, class Traits>
void
ch_w_point( ForwardIterator first, ForwardIterator last,
            ForwardIterator& w,
            const Traits& ch_traits );

template <class ForwardIterator>
inline
void
ch_w_point( ForwardIterator first, ForwardIterator last, ForwardIterator& w)
{
    typedef std::iterator_traits<ForwardIterator> ITraits;
    typedef typename ITraits::value_type          value_type;
    typedef CGAL::Kernel_traits<value_type>       KTraits;
    typedef typename KTraits::Kernel              Kernel;
    ch_w_point(first, last, w, Kernel());
}

CGAL_END_NAMESPACE

#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#include <CGAL/ch_selected_extreme_points_2.C>
#endif // CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION

#endif // CGAL_CH_SELECTED_EXTREME_POINTS_2_H

