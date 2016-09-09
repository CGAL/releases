// Copyright (c) 2006  Tel-Aviv University (Israel).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/Minkowski_sum_2/include/CGAL/offset_polygon_2.h $
// $Id: offset_polygon_2.h 37897 2007-04-03 18:34:02Z efif $
//
// Author(s)     : Ron Wein   <wein@post.tau.ac.il>

#ifndef CGAL_OFFSET_POLYGON_H
#define CGAL_OFFSET_POLYGON_H

#include <CGAL/Minkowski_sum_2/Exact_offset_base_2.h>
#include <CGAL/Minkowski_sum_2/Offset_conv_2.h>
#include <CGAL/Minkowski_sum_2/Offset_decomp_2.h>

CGAL_BEGIN_NAMESPACE

/*!
 * Compute the offset of a given simple polygon by a given radius,
 * using the convolution method.
 * Note that as the input polygon may not be convex, its offset may not be 
 * simply connected. The result is therefore represented as a polygon with
 * holes.
 * \param pgn The polygon.
 * \param r The offset radius.
 * \return The offset polygon.
 */
template <class ConicTraits, class Container>
typename Gps_traits_2<ConicTraits>::Polygon_with_holes_2
offset_polygon_2 (const Polygon_2<typename ConicTraits::Rat_kernel,
                                  Container>& pgn,
                  const typename ConicTraits::Rat_kernel::FT& r,
                  const ConicTraits& )
{
  typedef Exact_offset_base_2<ConicTraits, Container>        Base;
  typedef Offset_by_convolution_2<Base>                      Exact_offset_2;
  typedef typename Exact_offset_2::Offset_polygon_2          Offset_polygon_2;

  Base                                               base;
  Exact_offset_2                                     exact_offset (base);
  Offset_polygon_2                                   offset_bound;
  std::list<Offset_polygon_2>                        offset_holes;

  exact_offset (pgn, r, 
                offset_bound, std::back_inserter(offset_holes));

  return (typename Gps_traits_2<ConicTraits>::Polygon_with_holes_2
          (offset_bound, offset_holes.begin(), offset_holes.end()));
}

/*!
 * Compute the offset of a given simple polygon by a given radius,
 * by decomposing it to convex sub-polygons and computing the union of their
 * offsets.
 * Note that as the input polygon may not be convex, its offset may not be 
 * simply connected. The result is therefore represented as a polygon with
 * holes.
 * \param pgn The polygon.
 * \param r The offset radius.
 * \param decomp A functor for decomposing polygons.
 * \return The offset polygon.
 */
template <class ConicTraits, class Container, class DecompositionStrategy>
typename Gps_traits_2<ConicTraits>::Polygon_with_holes_2
offset_polygon_2 (const Polygon_2<typename ConicTraits::Rat_kernel,
                                  Container>& pgn,
                  const typename ConicTraits::Rat_kernel::FT& r,
                  const DecompositionStrategy&,
                  const ConicTraits& )
{
  typedef Exact_offset_base_2<ConicTraits, Container>        Base;
  typedef Offset_by_decomposition_2<Base, DecompositionStrategy>
                                                             Exact_offset_2;
  typedef typename Exact_offset_2::Offset_polygon_2          Offset_polygon_2;

  Base                                               base;
  Exact_offset_2                                     exact_offset (base);
  Offset_polygon_2                                   offset_bound;
  std::list<Offset_polygon_2>                        offset_holes;

  exact_offset (pgn, r,
                offset_bound, std::back_inserter(offset_holes));

  return (typename Gps_traits_2<ConicTraits>::Polygon_with_holes_2
          (offset_bound, offset_holes.begin(), offset_holes.end()));
}

CGAL_END_NAMESPACE

#endif
