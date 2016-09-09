
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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.3
// release_date  : 2001, August 13
// 
// file          : include/CGAL/IO/polygonal_2.h
// package       : window (2.8.10)
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2001/01/09 18:57:23 $
// author(s)     : Stefan Schirra
//
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
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
#include <CGAL/circulator.h>

namespace CGAL {

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



template <class Stream, class Circulator, class Traits>
void
send_to_stream_as_polygon(Stream& W,
                          Circulator C,
                          const Forward_circulator_tag&,
                          const Traits& );


template <class Stream, class Circulator, class R>
inline
void
_send_to_stream_as_polygon(Stream& W,
                           Circulator C,
                           const Forward_circulator_tag& ct,
                           Point_2<R>* )
{ send_to_stream_as_polygon(W, C, ct, R() ); }


template <class Stream, class Circulator>
inline
void
send_to_stream_as_polygon(Stream& W,
                          Circulator C,
                          const Forward_circulator_tag& ct)
{ _send_to_stream_as_polygon(W, C, ct, ch_value_type(C)); }


template <class Stream, class Circulator, class Traits>
void
send_to_stream_as_polygon(Stream& W,
                          Circulator C,
                          const Forward_circulator_tag&,
                          const Traits& )
{
  typedef  typename Traits::Segment_2   Segment2;
  if ( is_empty_range(C,C) ) return;
  Circulator start = C;
  do
  {
    W << Segment2(*C, *successor(C));
    ++C;
  } while ( C != start );
}


} // namespace CGAL


#endif // CGAL_IO_POLYGONAL_2_H
