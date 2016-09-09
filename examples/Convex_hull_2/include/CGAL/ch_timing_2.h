// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------
// release       : $CGAL_Revision: CGAL-2.5-I-154 $
// release_date  : $CGAL_Date: 2003/10/30 $
//
// file          : examples/Convex_hull_2/include/CGAL/ch_timing_2.h
// package       : Convex_hull_2 
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2001/12/05 15:16:09 $
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// ======================================================================


#ifndef CGAL_CH_TIMING_2_H
#define CGAL_CH_TIMING_2_H

#include <CGAL/Timer.h>


CGAL_BEGIN_NAMESPACE
template <class ForwardIterator, class OutputIterator, class Traits>
void
ch_timing( ForwardIterator first, ForwardIterator last,
           OutputIterator result,
           int iterations, 
           const Traits& ch_traits);

CGAL_END_NAMESPACE

#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#include <CGAL/ch_timing_2.C>
#endif // CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION

#endif // CGAL_CH_TIMING_2_H

