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
// file          : include/CGAL/Random_convex_set_traits_2.h
// package       : Generator (2.10)
// source        : src/rcs/rcs.aw
// revision      : $Revision: 1.2 $
// revision_date : $Date: 1998/03/06 16:19:47 $
// author(s)     : Michael Hoffmann
//
// coordinator   : ETH Zurich (Bernd Gaertner)
//
// Default Traits For Random Convex Point Sets
// email         : cgal@cs.uu.nl
//
// ======================================================================

#if ! (CGAL_RANDOM_CONVEX_SET_TRAITS_2_H)
#define CGAL_RANDOM_CONVEX_SET_TRAITS_2_H 1

#ifndef CGAL_POINT_2_H
#include <CGAL/Point_2.h>
#endif

CGAL_BEGIN_NAMESPACE
template < class R >
struct Random_convex_set_traits {

  typedef Point_2< R >      Point_2;
  typedef Direction_2< R >  Direction_2;
  typedef typename R::FT    FT;

  Random_convex_set_traits() : _origin( ORIGIN)
  {}

  Point_2
  origin() const
  { return _origin; }

  struct Max_coordinate
  : public CGAL_STD::unary_function< Point_2, FT >
  {
    FT
    operator()( const Point_2& p) const
    { return std::max( abs( p.x()), abs( p.y())); }
  };

  struct Sum
  : public CGAL_STD::binary_function< Point_2, Point_2, Point_2 >
  {
    Point_2
    operator()( const Point_2& p, const Point_2& q) const
    { return p + (q - ORIGIN); }
  };

  struct Scale
  : public CGAL_STD::binary_function< Point_2, FT, Point_2 >
  {
    Point_2
    operator()( const Point_2& p, const FT& k) const
    { return ORIGIN + (p - ORIGIN) * k; }
  };

  struct Angle_less
  : public CGAL_STD::binary_function< Point_2, Point_2, bool >
  {
    bool
    operator()( const Point_2& p, const Point_2& q) const
    {
      return Direction_2( p - ORIGIN) < Direction_2( q - ORIGIN);
    }
  };

private:
  Point_2 _origin;
};

template < class OutputIterator, class Point_generator >
inline
OutputIterator
random_convex_set_2( int n,
                     OutputIterator o,
                     const Point_generator& pg)
{
  typedef typename Point_generator::value_type Point_2;
  return _random_convex_set_2(
    n, o, pg, CGAL_reinterpret_cast( Point_2*, 0));
}
template < class OutputIterator, class Point_generator, class R >
inline
OutputIterator
_random_convex_set_2( int n,
                      OutputIterator o,
                      const Point_generator& pg,
                      Point_2< R >*)
{
  return random_convex_set_2(
    n, o, pg, Random_convex_set_traits< R >());
}


CGAL_END_NAMESPACE

#endif // ! (CGAL_RANDOM_CONVEX_SET_TRAITS_2_H)

// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

