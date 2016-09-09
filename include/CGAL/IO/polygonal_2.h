
// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.1
// release_date  : 2000, January 11
// 
// source        : polygonal.fw
// file          : include/CGAL/IO/polygonal_2.h
// package       : window (2.5.8)
// revision      : 2.5.8
// revision_date : 13 Jan 2000 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_IO_POLYGONAL_2_H
#define CGAL_IO_POLYGONAL_2_H

#include <CGAL/basic.h>
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/convex_hull_traits_2.h>
#include <CGAL/stl_extensions.h>
#include <CGAL/ch_value_type.h>

CGAL_BEGIN_NAMESPACE

//---------------------- Polygon --------------------------

template <class Stream, class ForwardIterator, class Traits>
void
send_to_stream_as_polygon(Stream& W,
                          ForwardIterator first, ForwardIterator last,
                          const Traits& );


template <class Stream, class ForwardIterator, class R>
inline
void
_send_to_stream_as_polygon(Stream& W,
                           ForwardIterator first, ForwardIterator last,
                           Point_2<R>* )
{ send_to_stream_as_polygon(W, first, last, convex_hull_traits_2<R>() ); }


template <class Stream, class ForwardIterator>
inline
void
send_to_stream_as_polygon(Stream& W,
                          ForwardIterator first, ForwardIterator last)
{ _send_to_stream_as_polygon(W, first, last, ch_value_type(first)); }


template <class Stream, class ForwardIterator, class Traits>
void
send_to_stream_as_polygon(Stream& W,
                          ForwardIterator first, ForwardIterator last,
                          const Traits& )
{
  typedef  typename Traits::Segment_2   Segment2;
  if (first == last) return;
  ForwardIterator it   = first;
  ForwardIterator fifi = CGAL::successor(first);
  while ( fifi != last )
  {
      W << Segment2(*it,*fifi);
      it = fifi++;
  }
  W << Segment2(*it,*first);
  return;
}


//---------------------- Polyline --------------------------


template <class Stream, class ForwardIterator, class Traits>
void
send_to_stream_as_polyline(Stream& W,
                           ForwardIterator first, ForwardIterator last,
                           const Traits& );


template <class Stream, class ForwardIterator, class R>
inline
void
_send_to_stream_as_polyline(Stream& W,
                            ForwardIterator first, ForwardIterator last,
                            Point_2<R>* )
{ send_to_stream_as_polyline(W, first, last, convex_hull_traits_2<R>() ); }


template <class Stream, class ForwardIterator>
inline
void
send_to_stream_as_polyline(Stream& W,
                           ForwardIterator first, ForwardIterator last)
{ _send_to_stream_as_polyline(W, first, last, ch_value_type(first)); }


template <class Stream, class ForwardIterator, class Traits>
void
send_to_stream_as_polyline(Stream& W,
                           ForwardIterator first, ForwardIterator last,
                           const Traits& )
{
  typedef  typename Traits::Segment_2   Segment2;
  if (first == last) return;
  ForwardIterator it   = first;
  ForwardIterator fifi = CGAL::successor(first);
  while ( fifi != last )
  {
      W << Segment2(*it,*fifi);
      it = fifi++;
  }
  return;
}
CGAL_END_NAMESPACE


#endif // CGAL_IO_POLYGONAL_2_H
