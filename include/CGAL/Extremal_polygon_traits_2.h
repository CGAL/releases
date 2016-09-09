// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/Extremal_polygon_traits_2.h
// package       : Matrix_search (1.17)
// chapter       : $CGAL_Chapter: Geometric Optimisation $
// source        : mon_search.aw
// revision      : $Revision: 1.17 $
// revision_date : $Date: 1999/06/01 14:08:03 $
// author(s)     : Michael Hoffmann
//
// coordinator   : ETH Zurich (Bernd Gaertner)
//
// Predefined Traits classes for Extremal Polygon Computation
// email         : cgal@cs.uu.nl
//
// ======================================================================

#if ! (EXTREMAL_POLYGON_TRAITS_2_H)
#define EXTREMAL_POLYGON_TRAITS_2_H 1

#ifndef CGAL_OPTIMISATION_ASSERTIONS_H
#include <CGAL/optimisation_assertions.h>
#endif // CGAL_OPTIMISATION_ASSERTIONS_H
#ifndef CGAL_SQUARED_DISTANCE_2_H
#include <CGAL/squared_distance_2.h>
#endif // CGAL_SQUARED_DISTANCE_2_H
#ifndef CGAL_POLYGON_2_H
#include <CGAL/Polygon_2.h>
#endif // CGAL_POLYGON_2_H
#ifndef CGAL_FUNCTION_OBJECTS_H
#include <CGAL/function_objects.h>
#endif // CGAL_FUNCTION_OBJECTS_H

CGAL_BEGIN_NAMESPACE
template < class R > inline
#ifndef CGAL_CFG_RETURN_TYPE_BUG_1
typename R::FT
#else
R_FT_return(R)
#endif
Kgon_triangle_area( const Point_2< R >& p,
                         const Point_2< R >& q,
                         const Point_2< R >& r)
{
  return abs( p.x() * ( q.y() - r.y()) +
                   q.x() * ( r.y() - p.y()) +
                   r.x() * ( p.y() - q.y()));
}

template < class _R >
class _Kgon_area_operator
: public CGAL_STD::binary_function< Point_2< _R >,
                                    Point_2< _R >,
                                    typename _R::FT >
{
public:
  typedef _R                 R;
  typedef Point_2< R >  Point_2;
  typedef typename R::FT     FT;

  _Kgon_area_operator( const Point_2& p)
  : root( p)
  {}

  FT
  operator()( const Point_2& p, const Point_2& q) const
  { return Kgon_triangle_area( p, q, root); }

private:
  const Point_2& root;
};



template < class _R >
class Kgon_area_traits
{
public:
  typedef          _R                   R;
  typedef          Point_2< R >    Point_2;
  typedef typename _R::FT               FT;
  typedef _Kgon_area_operator< R > Operation;

  int
  min_k() const
  { return 3; }

  FT
  init( const Point_2&, const Point_2&) const
  { return FT( 0); }

  Operation
  operation( const Point_2& p) const
  { return Operation( p); }

#ifndef CGAL_CFG_NO_MEMBER_TEMPLATES
  template < class RandomAccessIC, class OutputIterator >
#else
  typedef typename vector< Point_2 >::iterator
    RandomAccessIC;
  typedef typename vector< int >::reverse_iterator
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
  // POST: write the points of [points_begin, points_end)
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
    typedef vector< Point_2 >            Cont;
    typedef Polygon_2< P_traits, Cont >  Polygon_2;
  
    Polygon_2 p( points_begin, points_end);
    return p.is_convex();
  } // is_convex( points_begin, points_end)

};

CGAL_END_NAMESPACE
#ifndef CGAL_OPTIMISATION_ASSERTIONS_H
#include <CGAL/optimisation_assertions.h>
#endif // CGAL_OPTIMISATION_ASSERTIONS_H
#ifndef CGAL_PROTECT_CMATH
#include <cmath>
#define CGAL_PROTECT_CMATH
#endif
#ifdef CGAL_USE_LEDA
#ifndef CGAL_LEDA_REAL_H
#include <CGAL/leda_real.h>
#endif // CGAL_LEDA_REAL_H
#endif
CGAL_BEGIN_NAMESPACE

#ifndef CGAL_CFG_NO_NAMESPACE
inline double
sqrt( double x)
{ return ::sqrt( x); }

#ifdef CGAL_USE_LEDA
inline leda_real
sqrt( const leda_real& x)
{ return ::sqrt( x); }
#endif
#endif

template < class _FT >
struct Sqrt
: public CGAL_STD::binary_function< _FT, _FT, _FT >
{
  typedef _FT  FT;

  FT
  operator()( const FT& x) const
  { return CGAL::sqrt( x); }

};
template < class _R >
class _Kgon_perimeter_operator
: public CGAL_STD::binary_function< Point_2< _R >,
                                    Point_2< _R >,
                                    typename _R::FT >
{
public:
  typedef _R              R;
  typedef Point_2< R >    Point_2;
  typedef typename R::FT  FT;

  _Kgon_perimeter_operator( const Point_2& p)
  : root( p)
  {}

  FT
  operator()( const Point_2& p, const Point_2& q) const
  { return dist( p, root) + dist( p, q) - dist( q, root); }

private:
  static
  FT
  dist( const Point_2& p, const Point_2& q)
  { return CGAL::sqrt( squared_distance( p, q)); }

  const Point_2& root;
};


template < class _R >
class Kgon_perimeter_traits
{
public:
  typedef          _R                    R;
  typedef          Point_2< R >          Point_2;
  typedef typename _R::FT                FT;
  typedef _Kgon_perimeter_operator< R >  Operation;

  int
  min_k() const
  { return 2; }

  FT
  init( const Point_2& p, const Point_2& r) const
  { return operation( r)( p, r); }

  Operation
  operation( const Point_2& p) const
  { return Operation( p); }

#ifndef CGAL_CFG_NO_MEMBER_TEMPLATES
  template < class RandomAccessIC, class OutputIterator >
#else
  typedef typename vector< Point_2 >::iterator
    RandomAccessIC;
  typedef typename vector< int >::reverse_iterator
    OutputIterator;
#endif
  OutputIterator
  compute_min_k_gon( RandomAccessIC points_begin,
                     RandomAccessIC points_end,
                     FT& max_perimeter,
                     OutputIterator o) const
  // RandomAccessIC is a random access iterator or
  // circulator with value_type Point_2.
  // OutputIterator has value_type Point_2.
  //
  // PRE: n := | [points_begin, points_end) | >= min_k() and
  //  the points described by the range [points_begin, points_end)
  //  form the boundary of a convex polygon oriented counterclockwise.
  //
  // POST: write the points of [points_begin, points_end)
  //  forming a min_k()-gon rooted at points_begin[0] of maximum
  //  perimeter to o in counterclockwise order and return the
  //  past-the-end iterator for that range (== o + min_k()).
  {
#ifndef CGAL_CFG_NO_NAMESPACE
    using std::bind2nd;
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
        compose2_2(
          less< FT >(),
          bind2nd( operation( points_begin[0]), points_begin[0]),
          bind2nd( operation( points_begin[0]), points_begin[0]))));
    
    // give result:
    *o++ = iterator_distance( points_begin, maxi);
    *o++ = 0;
    
    return o;
  } // compute_min_k_gon( ... )

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
    typedef vector< Point_2 >            Cont;
    typedef Polygon_2< P_traits, Cont >  Polygon_2;
  
    Polygon_2 p( points_begin, points_end);
    return p.is_convex();
  } // is_convex( points_begin, points_end)

};


template < class RandomAccessIC,
           class OutputIterator >
inline
OutputIterator
maximum_area_inscribed_k_gon(
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
//  * value_type of RandomAccessIC (=: Point_2)
//    is Point_2<R> for some representation class R
//  * OutputIterator accepts Point_2 as value_type
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
  return _CGAL_maximum_area_inscribed_k_gon(
    points_begin,
    points_end,
    k,
    o,
    std::value_type( points_begin));
} // maximum_area_inscribed_k_gon( ... )

template < class RandomAccessIC,
           class OutputIterator,
           class R >
inline
OutputIterator
_CGAL_maximum_area_inscribed_k_gon(
  RandomAccessIC points_begin,
  RandomAccessIC points_end,
  int k,
  OutputIterator o,
  Point_2< R >*)
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
  return extremal_polygon(
    points_begin,
    points_end,
    k,
    o,
    Kgon_area_traits< R >());
} // _CGAL_maximum_area_inscribed_k_gon( ... )

template < class RandomAccessIC,
           class OutputIterator >
inline
OutputIterator
maximum_perimeter_inscribed_k_gon(
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
//  * value_type of RandomAccessIC (=: Point_2)
//    is Point_2<R> for some representation class R
//  * OutputIterator accepts Point_2 as value_type
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
  return _CGAL_maximum_perimeter_inscribed_k_gon(
    points_begin,
    points_end,
    k,
    o,
    std::value_type( points_begin));
} // maximum_perimeter_inscribed_k_gon( ... )

template < class RandomAccessIC,
           class OutputIterator,
           class R >
inline
OutputIterator
_CGAL_maximum_perimeter_inscribed_k_gon(
  RandomAccessIC points_begin,
  RandomAccessIC points_end,
  int k,
  OutputIterator o,
  Point_2< R >*)
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
  return extremal_polygon(
    points_begin,
    points_end,
    k,
    o,
    Kgon_perimeter_traits< R >());
} // _CGAL_maximum_perimeter_inscribed_k_gon( ... )

CGAL_END_NAMESPACE

#endif // ! (EXTREMAL_POLYGON_TRAITS_2_H)

// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

