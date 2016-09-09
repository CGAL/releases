// ======================================================================
//
// Copyright (c) 1998, 1999, 2000 The CGAL Consortium

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
// file          : include/CGAL/Extremal_polygon_traits_2.h
// package       : Matrix_search (1.49)
// chapter       : $CGAL_Chapter: Geometric Optimisation $
// source        : mon_search.aw
// revision      : $Revision: 1.47 $
// revision_date : $Date: 2001/07/12 07:17:53 $
// author(s)     : Michael Hoffmann
//
// coordinator   : ETH
//
// Predefined Traits classes for Extremal Polygon Computation
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#if ! (CGAL_EXTREMAL_POLYGON_TRAITS_2_H)
#define CGAL_EXTREMAL_POLYGON_TRAITS_2_H 1

#include <CGAL/Optimisation/assertions.h>
#include <CGAL/squared_distance_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/functional.h>

CGAL_BEGIN_NAMESPACE
template < class K_ >
struct Extremal_polygon_area_traits_2 {
  typedef          K_                                K;
  typedef typename K::FT                             FT;
  typedef typename K::Point_2                        Point_2;
#ifdef CGAL_OPTIMISATION_EXPENSIVE_PRECONDITION_TAG
  typedef typename K::Less_xy_2                      Less_xy_2;
  typedef typename K::Orientation_2                  Orientation_2;
#endif // CGAL_OPTIMISATION_EXPENSIVE_PRECONDITION_TAG

  struct Kgon_triangle_area {
    typedef Arity_tag< 3 >  Arity;
    typedef FT              result_type;
  
    Kgon_triangle_area(const K& k_) : k(k_) {}
  
    result_type
    operator()(const Point_2& p, const Point_2& q, const Point_2& r) const
    { return CGAL_NTS abs(k.compute_area_2_object()(
      k.construct_triangle_2_object()(p, q, r))); }
  protected:
    K k;
  };

  typedef Kgon_triangle_area                         Baseop;
  typedef typename Bind< Baseop, Point_2, 3 >::Type  Operation;

  Extremal_polygon_area_traits_2() {}
  Extremal_polygon_area_traits_2(const K& k_) : k(k_) {}

  int min_k() const { return 3; }

  FT
  init( const Point_2&, const Point_2&) const
  { return FT( 0); }

  Operation
  operation( const Point_2& p) const
  { return bind_3(Baseop(k), p); }

#ifndef CGAL_CFG_NO_MEMBER_TEMPLATES
  template < class RandomAccessIC, class OutputIterator >
#else
  typedef typename std::vector< Point_2 >::iterator
    RandomAccessIC;
  typedef typename std::vector< int >::reverse_iterator
    OutputIterator;
#endif
  OutputIterator
  compute_min_k_gon( RandomAccessIC points_begin,
                     RandomAccessIC points_end,
                     FT& max_area,
                     OutputIterator o) const
  // RandomAccessIC is a random access iterator or
  // circulator with value_type Point_2.
  // OutputIterator accepts int as value_type.
  //
  // PRE: n := | [points_begin, points_end) | >= min_k() and
  //  the points described by the range [points_begin, points_end)
  //  form the boundary of a convex polygon oriented counterclockwise.
  //
  // POST: write indices of the points from [points_begin, points_end)
  //  forming a min_k()-gon rooted at points_begin[0]
  //  of maximum area to o in counterclockwise order and return
  //  the past-the-end iterator for that range (== o + min_k()).
  {
    int number_of_points(
      iterator_distance( points_begin, points_end));
    CGAL_optimisation_precondition( number_of_points > min_k());
    
    // this gives the area of the triangle of two points with
    // the root:
    Operation op( operation( points_begin[0]));
    
    int p1( 1);
    int p2( 2);
    
    // maximal triangle so far (and the corresponding points):
    max_area = op( points_begin[p1], points_begin[p2]);
    int opt_p1( p1);
    int opt_p2( p2);
    
    // maximal triangle containing p1 so far:
    FT tmp_area( max_area);
    
    for (;;) {
      while ( p2 + 1 < number_of_points &&
              tmp_area < op( points_begin[p1], points_begin[p2+1])) {
        tmp_area = op( points_begin[p1], points_begin[++p2]);
      }
      if ( tmp_area > max_area) {
        max_area = tmp_area;
        opt_p1 = p1;
        opt_p2 = p2;
      }
      if ( ++p1 == number_of_points - 1)
        break;
      if ( p2 == p1)
        ++p2;
      tmp_area = op( points_begin[p1], points_begin[p2]);
    } // for (;;)
    
    // give result:
    *o++ = opt_p2;
    *o++ = opt_p1;
    *o++ = 0;
    return o;
  } // compute_min_k_gon( ... )

#ifdef CGAL_OPTIMISATION_EXPENSIVE_PRECONDITION_TAG
  Less_xy_2 less_xy_2_object() const { return k.less_xy_2_object(); }

  Orientation_2 orientation_2_object() const
  { return k.orientation_2_object(); }
#endif // CGAL_OPTIMISATION_EXPENSIVE_PRECONDITION_TAG

protected:
  K k;
};

CGAL_END_NAMESPACE
#include <CGAL/Optimisation/assertions.h>
#include <cmath>
#ifdef CGAL_USE_LEDA
#include <CGAL/leda_real.h>
#endif // CGAL_USE_LEDA
CGAL_BEGIN_NAMESPACE

template < class FT_ >
struct Sqrt : public CGAL_STD::binary_function< FT_, FT_, FT_ >
{
  typedef Arity_tag< 1 > Arity;
  typedef FT_  FT;
  FT operator()(const FT& x) const { return CGAL_NTS sqrt(x); }
};
template < class K_ >
struct Extremal_polygon_perimeter_traits_2 {
  typedef          K_                                K;
  typedef typename K::FT                             FT;
  typedef typename K::Point_2                        Point_2;
#ifdef CGAL_OPTIMISATION_EXPENSIVE_PRECONDITION_TAG
  typedef typename K::Less_xy_2                    Less_xy_2;
  typedef typename K::Orientation_2                Orientation_2;
#endif // CGAL_OPTIMISATION_EXPENSIVE_PRECONDITION_TAG

  struct Kgon_triangle_perimeter {
    typedef Arity_tag< 3 >  Arity;
    typedef FT              result_type;
  
    Kgon_triangle_perimeter(const K& k_): k(k_) {}
  
    result_type
    operator()(const Point_2& p, const Point_2& q, const Point_2& r) const
    { return dist(p, r) + dist(p, q) - dist(q, r); }
  
  private:
    result_type dist(const Point_2& p, const Point_2& q) const
    { return CGAL_NTS sqrt(k.compute_squared_distance_2_object()(p, q)); }
  
  protected:
    K k;
  };

  typedef Kgon_triangle_perimeter                    Baseop;
  typedef typename Bind< Baseop, Point_2, 3 >::Type  Operation;

  Extremal_polygon_perimeter_traits_2() {}
  Extremal_polygon_perimeter_traits_2(const K& k_) : k(k_) {}

  int min_k() const { return 2; }

  FT
  init( const Point_2& p, const Point_2& r) const
  { return operation( r)( p, r); }

  Operation
  operation( const Point_2& p) const
  { return bind_3( Baseop(k), p); }

#ifndef CGAL_CFG_NO_MEMBER_TEMPLATES
  template < class RandomAccessIC, class OutputIterator >
#else
  typedef typename std::vector< Point_2 >::iterator
    RandomAccessIC;
  typedef typename std::vector< int >::reverse_iterator
    OutputIterator;
#endif
  OutputIterator
  compute_min_k_gon( RandomAccessIC points_begin,
                     RandomAccessIC points_end,
                     FT& max_perimeter,
                     OutputIterator o) const
  // RandomAccessIC is a random access iterator or
  // circulator with value_type Point_2.
  // OutputIterator accepts int as value_type.
  //
  // PRE: n := | [points_begin, points_end) | >= min_k() and
  //  the points described by the range [points_begin, points_end)
  //  form the boundary of a convex polygon oriented counterclockwise.
  //
  // POST: write indices of the points from [points_begin, points_end)
  //  forming a min_k()-gon rooted at points_begin[0] of maximum
  //  perimeter to o in counterclockwise order, set max_perimeter
  //  to twice this perimeter and return the past-the-end iterator
  //  for the range (== o + min_k()).
  {
#ifndef CGAL_CFG_NO_NAMESPACE
    using std::less;
    using std::max_element;
#endif

    CGAL_optimisation_precondition_code(
      int number_of_points(
        iterator_distance( points_begin, points_end));)
    CGAL_optimisation_precondition( number_of_points > min_k());
    
    // kind of messy, but first we have to have something
    // like Distance (function object) ...
    RandomAccessIC maxi(
      max_element(
        points_begin + 1,
        points_end,
        compose(
          less< FT >(),
          bind_2(operation(points_begin[0]), points_begin[0]),
          bind_2(operation(points_begin[0]), points_begin[0]))));
    
    // give result:
    max_perimeter = operation(*points_begin)(*maxi, *points_begin);
    *o++ = iterator_distance(points_begin, maxi);
    *o++ = 0;
    
    return o;
  } // compute_min_k_gon( ... )

#ifdef CGAL_OPTIMISATION_EXPENSIVE_PRECONDITION_TAG
  Less_xy_2 less_xy_2_object() const { return k.less_xy_2_object(); }

  Orientation_2 orientation_2_object() const
  { return k.orientation_2_object(); }
#endif // CGAL_OPTIMISATION_EXPENSIVE_PRECONDITION_TAG

protected:
  K k;
};


template < class RandomAccessIC, class OutputIterator >
inline
OutputIterator
maximum_area_inscribed_k_gon_2(
  RandomAccessIC points_begin,
  RandomAccessIC points_end,
  int k,
  OutputIterator o)
//
// preconditions:
// --------------
//  * Traits fulfills the requirements for an extremal polygon
//    traits class
//  * the range [points_begin, points_end) of size n > 0
//    describes the vertices of a convex polygon $P$
//    enumerated clock- or counterclockwise
//  * R is a CGAL representation class
//  * value_type of RandomAccessIC is Point_2<R>
//  * OutputIterator accepts Point_2<R> as value_type
//  * k >= 3
//
// functionality:
// --------------
// computes maximum area inscribed k-gon $P_k$
// of the polygon $P$,
// writes the indices (relative to points_begin)
// of $P_k$'s vertices to o and
// returns the past-the-end iterator of that sequence.
{
  typedef typename std::iterator_traits< RandomAccessIC >::value_type::R R;
  return extremal_polygon_2(
    points_begin,
    points_end,
    k,
    o,
    Extremal_polygon_area_traits_2< R >());
} // maximum_area_inscribed_k_gon_2( ... )

// backwards compatibility
template < class RandomAccessIC, class OutputIterator >
inline
OutputIterator
maximum_area_inscribed_k_gon(
  RandomAccessIC points_begin,
  RandomAccessIC points_end,
  int k,
  OutputIterator o)
{
  return maximum_area_inscribed_k_gon_2(
    points_begin, points_end, k, o);
} // maximum_area_inscribed_k_gon( ... )

template < class RandomAccessIC, class OutputIterator >
inline
OutputIterator
maximum_perimeter_inscribed_k_gon_2(
  RandomAccessIC points_begin,
  RandomAccessIC points_end,
  int k,
  OutputIterator o)
//
// preconditions:
// --------------
//  * Traits fulfills the requirements for an extremal polygon
//    traits class
//  * the range [points_begin, points_end) of size n > 0
//    describes the vertices of a convex polygon $P$
//    enumerated clock- or counterclockwise
//  * R is a CGAL representation class
//  * value_type of RandomAccessIC is Point_2<R>
//  * OutputIterator accepts Point_2<R> as value_type
//  * k >= 2
//
// functionality:
// --------------
// computes maximum perimeter inscribed k-gon $P_k$
// of the polygon $P$,
// writes the indices (relative to points_begin)
// of $P_k$'s vertices to o and
// returns the past-the-end iterator of that sequence.
{
  typedef typename std::iterator_traits< RandomAccessIC >::value_type::R R;
  return extremal_polygon_2(
    points_begin,
    points_end,
    k,
    o,
    Extremal_polygon_perimeter_traits_2< R >());
} // maximum_perimeter_inscribed_k_gon_2( ... )

// backwards compatibility
template < class RandomAccessIC, class OutputIterator >
inline
OutputIterator
maximum_perimeter_inscribed_k_gon(
  RandomAccessIC points_begin,
  RandomAccessIC points_end,
  int k,
  OutputIterator o)
{
  return maximum_perimeter_inscribed_k_gon_2(
    points_begin, points_end, k, o);
} // maximum_perimeter_inscribed_k_gon( ... )

CGAL_END_NAMESPACE

#endif // ! (CGAL_EXTREMAL_POLYGON_TRAITS_2_H)

// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

