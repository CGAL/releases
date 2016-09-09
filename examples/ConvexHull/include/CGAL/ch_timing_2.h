// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
//
// 
// 
// 
//
// ----------------------------------------------------------------------------
// release       :
// release_date  :
//
// file          : ch_timing_2.h
// source        : convex_hull_2.lw
// revision      : 1.2.2
// revision_date : 27 Mar 1998
// author(s)     : Stefan Schirra <Stefan.Schirra@@mpi-sb.mpg.de>
//
// coordinator   : MPI, Saarbruecken
// ============================================================================


#ifndef CGAL_CH_TIMING_2_H
#define CGAL_CH_TIMING_2_H

template <class ForwardIterator, class OutputIterator, class Traits>
void
CGAL_ch_timing( ForwardIterator first, ForwardIterator last,
                OutputIterator result,
                int iterations, 
                const Traits& ch_traits);


#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#include <CGAL/ch_timing_2.C>
#endif // CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION

#endif // CGAL_CH_TIMING_2_H

