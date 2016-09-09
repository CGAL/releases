// ======================================================================
//
// Copyright (c) 1998, 1999, 2000 The CGAL Consortium

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
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/All_furthest_neighbors_traits_2.h
// package       : Matrix_search (1.43)
// chapter       : $CGAL_Chapter: Geometric Optimisation $
// source        : mon_search.aw
// revision      : $Revision: 1.44 $
// revision_date : $Date: 2000/09/15 07:25:29 $
// author(s)     : Michael Hoffmann
//
// coordinator   : ETH
//
// Compute all furthest neighbors for the vertices of a convex polygon
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#if ! (CGAL_ALL_FURTHEST_NEIGHBORS_TRAITS_2_H)
#define CGAL_ALL_FURTHEST_NEIGHBORS_TRAITS_2_H 1

#include <CGAL/basic.h>
#include <CGAL/Optimisation/assertions.h>
//!!! this should go into function_objects.h
#include <functional>
#include <CGAL/squared_distance_2.h>

CGAL_BEGIN_NAMESPACE

template < class T1, class T2 >
struct Squared_distance
: public CGAL_STD::binary_function< T1, T2, typename T1::R::FT >
{
  typename T1::R::FT
  operator()(const T1& t1, const T2& t2) const
  { return squared_distance(t1, t2); }
};

CGAL_END_NAMESPACE
#ifdef CGAL_CFG_NO_MEMBER_TEMPLATES
#include <vector>
#endif
CGAL_BEGIN_NAMESPACE

template < class R_ >
class All_furthest_neighbors_default_traits_2 {
public:
  typedef R_                                    R;
  typedef Point_2< R >                          Point_2;
  typedef Squared_distance< Point_2, Point_2 >  Distance;

#ifdef CGAL_CFG_NO_MEMBER_TEMPLATES
  typedef typename std::vector< Point_2 >::iterator
    RandomAccessIC;
  typedef typename std::vector< int >::reverse_iterator
    OutputIterator;
#endif

  // return distance object
  Distance distance_object() const { return d; }

  #ifndef CGAL_CFG_NO_MEMBER_TEMPLATES
  template < class RandomAccessIC >
  #endif
  bool
  is_convex( RandomAccessIC points_begin,
             RandomAccessIC points_end) const
  // PRE: value_type of RandomAccessIC is Point_2
  // POST: return true, iff the points [ points_begin, points_end)
  //   form a convex chain.
  {
    typedef Polygon_traits_2< R >        P_traits;
    typedef std::vector< Point_2 >       Cont;
    typedef Polygon_2< P_traits, Cont >  Polygon_2;
  
    Polygon_2 p( points_begin, points_end);
    return p.is_convex();
  } // is_convex( points_begin, points_end)

private:
  Distance d;
};

template < class RandomAccessIC, class OutputIterator >
inline
OutputIterator
all_furthest_neighbors_2( RandomAccessIC points_begin,
                          RandomAccessIC points_end,
                          OutputIterator o)
{
  typedef typename std::iterator_traits< RandomAccessIC >::value_type::R R;
  return
  all_furthest_neighbors_2(
    points_begin,
    points_end,
    o,
    All_furthest_neighbors_default_traits_2< R >());
} // all_furthest_neighbors_2( ... )

// backwards compatibility
template < class RandomAccessIC, class OutputIterator >
inline
OutputIterator
all_furthest_neighbors( RandomAccessIC points_begin,
                        RandomAccessIC points_end,
                        OutputIterator o)
{ return all_furthest_neighbors_2( points_begin, points_end, o); }

CGAL_END_NAMESPACE

#endif // ! (CGAL_ALL_FURTHEST_NEIGHBORS_TRAITS_2_H)

// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

