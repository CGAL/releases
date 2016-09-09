// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium

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
// file          : include/CGAL/Random_convex_set_traits_2.h
// package       : Generator (2.40)
// source        : src/rcs/rcs.aw
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2001/07/16 15:50:25 $
// author(s)     : Michael Hoffmann
//
// coordinator   : ETH Zurich (Bernd Gaertner)
//
// Default Traits For Random Convex Point Sets
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#if ! (CGAL_RANDOM_CONVEX_SET_TRAITS_2_H)
#define CGAL_RANDOM_CONVEX_SET_TRAITS_2_H 1

#include <CGAL/Point_2.h>

CGAL_BEGIN_NAMESPACE
template < class Kernel >
struct Random_convex_set_traits_2 {

  typedef typename Kernel::Point_2      Point_2;
  typedef typename Kernel::Direction_2  Direction_2;
  typedef typename Kernel::FT           FT;

  Random_convex_set_traits_2() : _origin( ORIGIN)
  {}

  Point_2
  origin() const
  { return _origin; }

  struct Max_coordinate
  : public CGAL_STD::unary_function< Point_2, FT >
  {
    FT
    operator()( const Point_2& p) const
    { return max( CGAL_NTS  abs( p.x()), CGAL_NTS  abs( p.y())); }
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

template <class Kernel>
struct Random_convex_set_traits : public Random_convex_set_traits_2<Kernel>
{};

template < class OutputIterator, class Point_generator >
inline
OutputIterator
random_convex_set_2( int n,
                     OutputIterator o,
                     const Point_generator& pg)
{
  typedef typename Point_generator::value_type Point_2;
  return CGAL_random_convex_set_2(n, o, pg, reinterpret_cast<Point_2*>(0));
}
template < class OutputIterator, class Point_generator, class R >
inline
OutputIterator
CGAL_random_convex_set_2( int n,
                          OutputIterator o,
                          const Point_generator& pg,
                          Point_2< R >*)
{
  return random_convex_set_2(
    n, o, pg, Random_convex_set_traits_2< R >());
}


CGAL_END_NAMESPACE

#endif // ! (CGAL_RANDOM_CONVEX_SET_TRAITS_2_H)

// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

