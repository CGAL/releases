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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Minkowski_sum_2/include/CGAL/Minkowski_sum_2/Decomposition_strategy_adapter.h $
// $Id: Decomposition_strategy_adapter.h 56667 2010-06-09 07:37:13Z sloriot $
//
// Author(s)     : Ron Wein   <wein@post.tau.ac.il>

#ifndef CGAL_POLYGON_DECOMPOSITION_STRATEGY_ADAPTER_H
#define CGAL_POLYGON_DECOMPOSITION_STRATEGY_ADAPTER_H

#include <CGAL/basic.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Partition_traits_2.h>
#include <CGAL/partition_2.h>

namespace CGAL {

struct Tag_optimal_convex_parition
{
  bool    dummy;
};

struct Tag_approx_convex_parition
{
  bool    dummy;
};

struct Tag_Greene_convex_parition
{
  bool    dummy;
};

/*!
 * \class
 * An adapter of the global planar polygonal partitioning functions
 * to a decomposition strategy-class.
 */
template <class Kernel_, class Container_, class StrategyTag_>
class Polygon_decomposition_strategy_adapter
{
public:
        
  typedef Kernel_                                  Kernel;
  typedef CGAL::Polygon_2<Kernel, Container_>      Polygon_2;
  typedef typename Kernel::Point_2                 Point_2;
  typedef StrategyTag_                             Strategy_tag;

protected:

  typedef Partition_traits_2<Kernel>               Traits_2;
  typedef typename Traits_2::Polygon_2             Traits_polygon_2;

  // Data members:
  Traits_2           traits;

public:

  /*! Default constructor. */
  Polygon_decomposition_strategy_adapter () :
    traits()
  {}
  
  /*!
   * Decompose a simple polygon to convex sub-polygons.
   * \param pgn The input polygon.
   * \param oi An output iterator of convex polygons.
   * \return A past-the-end iterator for the sub-polygons.
   */
  template <class OutputIterator>
  OutputIterator operator() (const Polygon_2& pgn,
                             OutputIterator oi) const
  {
    std::list<Traits_polygon_2>                           pgns;
    typename std::list<Traits_polygon_2>::const_iterator  pgn_it;

    if (pgn.orientation() == CLOCKWISE)
    {
      // Make a local copy of the polygon, and reverse the order of its
      // vertices to make it counterclockwise oriented.
      Polygon_2        my_pgn = pgn;

      my_pgn.reverse_orientation();

      // Perform the decomposition.
      _decompose (my_pgn, Strategy_tag(), std::back_inserter (pgns));
    }
    else
    {
      // Perform the decomposition on the original polygon.
      _decompose (pgn, Strategy_tag(), std::back_inserter (pgns));
    }

    // Copy the polygons to the output iterator.
    for (pgn_it = pgns.begin(); pgn_it != pgns.end(); ++pgn_it)
    {
      *oi = Polygon_2 (pgn_it->vertices_begin(), pgn_it->vertices_end());
      ++oi;
    }

    return (oi);
  }

private:

  /*!
   * Decompose the given counter clockwise-oriented polygon using the optimal
   * convex-partition method.
   */
  template <class OutputIterator>
  OutputIterator _decompose (const Polygon_2& pgn,
                             Tag_optimal_convex_parition ,
                             OutputIterator oi) const
  {
    return (optimal_convex_partition_2 (pgn.vertices_begin(),
                                        pgn.vertices_end(),
                                        oi,
                                        traits));
  }

  /*!
   * Decompose the given counter clockwise-oriented polygon using the
   * approximated convex-partition method.
   */
  template <class OutputIterator>
  OutputIterator _decompose (const Polygon_2& pgn,
                             Tag_approx_convex_parition ,
                             OutputIterator oi) const
  {
    return (approx_convex_partition_2 (pgn.vertices_begin(),
                                       pgn.vertices_end(),
                                       oi,
                                       traits));
  }

  /*!
   * Decompose the given counter clockwise-oriented polygon using Greene's
   * approximated convex-partition method.
   */
  template <class OutputIterator>
  OutputIterator _decompose (const Polygon_2& pgn,
                             Tag_Greene_convex_parition ,
                             OutputIterator oi) const
  {
    return (greene_approx_convex_partition_2 (pgn.vertices_begin(),
                                              pgn.vertices_end(),
                                              oi,
                                              traits));
  }
};

} //namespace CGAL

#endif
