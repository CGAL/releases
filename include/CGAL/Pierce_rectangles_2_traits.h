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
// file          : include/CGAL/Pierce_rectangles_2_traits.h
// package       : Matrix_search (1.17)
// chapter       : $CGAL_Chapter: Geometric Optimisation $
// source        : pcenter.aw
// revision      : $Revision: 1.17 $
// revision_date : $Date: 1999/06/01 14:08:06 $
// author(s)     : Michael Hoffmann
//
// coordinator   : ETH Zurich (Bernd Gaertner)
//
// 2-4-Piercing Axis-Parallel 2D-Rectangles
// email         : cgal@cs.uu.nl
//
// ======================================================================

#if ! (PIERCE_RECTANGLES_2_TRAITS_H)
#define PIERCE_RECTANGLES_2_TRAITS_H 1

#ifndef CGAL_POINT_2_H
#include <CGAL/Point_2.h>
#endif // CGAL_POINT_2_H
#ifndef CGAL_ISO_RECTANGLE_2_H
#include <CGAL/Iso_rectangle_2.h>
#endif // CGAL_ISO_RECTANGLE_2_H
#ifndef CGAL_ISO_SQUARE_STATIC_2_H
#include <CGAL/Iso_square_static_2.h>
#endif // CGAL_ISO_SQUARE_STATIC_2_H

CGAL_BEGIN_NAMESPACE

template < class _R >
struct Piercing_traits_cartesian {
  typedef typename _R::FT              FT;
  typedef CGAL::Point_2< _R >          Point_2;
  typedef CGAL::Iso_rectangle_2< _R >  Iso_rectangle_2;

  struct X : public CGAL_STD::unary_function< Point_2, FT >
  {
    FT
    operator()( const Point_2& p) const
    { return p.x(); }
  };
  
  struct Y : public CGAL_STD::unary_function< Point_2, FT >
  {
    FT
    operator()( const Point_2& p) const
    { return p.y(); }
  };
  struct Xmin : public CGAL_STD::unary_function< Iso_rectangle_2, FT >
  {
    FT
    operator()( const Iso_rectangle_2& r) const
    { return r.xmin(); }
  };
  
  struct Xmax : public CGAL_STD::unary_function< Iso_rectangle_2, FT >
  {
    FT
    operator()( const Iso_rectangle_2& r) const
    { return r.xmax(); }
  };
  
  struct Ymin : public CGAL_STD::unary_function< Iso_rectangle_2, FT >
  {
    FT
    operator()( const Iso_rectangle_2& r) const
    { return r.ymin(); }
  };
  
  struct Ymax : public CGAL_STD::unary_function< Iso_rectangle_2, FT >
  {
    FT
    operator()( const Iso_rectangle_2& r) const
    { return r.ymax(); }
  };
  struct Build_point
  : public CGAL_STD::binary_function< FT, FT, Point_2 >
  {
    Point_2
    operator()( const FT& px, const FT& py) const
    { return Point_2( px, py); }
  };
  struct Build_rectangle
  : public CGAL_STD::unary_function< Point_2, Iso_rectangle_2 >
  {
    Iso_rectangle_2
    operator()( const Point_2& p) const
    { return Iso_rectangle_2( p, p); }
  };
}; // Piercing_traits_cartesian
template < class _R >
struct Piercing_traits_homogeneous {
  typedef typename _R::FT              FT;
  typedef CGAL::Point_2< _R >          Point_2;
  typedef CGAL::Iso_rectangle_2< _R >  Iso_rectangle_2;

  struct X : public CGAL_STD::unary_function< Point_2, FT >
  {
    FT
    operator()( const Point_2& p) const
    { return p.x(); }
  };
  
  struct Y : public CGAL_STD::unary_function< Point_2, FT >
  {
    FT
    operator()( const Point_2& p) const
    { return p.y(); }
  };
  struct Xmin : public CGAL_STD::unary_function< Iso_rectangle_2, FT >
  {
    FT
    operator()( const Iso_rectangle_2& r) const
    { return r.xmin(); }
  };
  
  struct Xmax : public CGAL_STD::unary_function< Iso_rectangle_2, FT >
  {
    FT
    operator()( const Iso_rectangle_2& r) const
    { return r.xmax(); }
  };
  
  struct Ymin : public CGAL_STD::unary_function< Iso_rectangle_2, FT >
  {
    FT
    operator()( const Iso_rectangle_2& r) const
    { return r.ymin(); }
  };
  
  struct Ymax : public CGAL_STD::unary_function< Iso_rectangle_2, FT >
  {
    FT
    operator()( const Iso_rectangle_2& r) const
    { return r.ymax(); }
  };
  struct Build_point
  : public CGAL_STD::binary_function< FT, FT, Point_2 >
  {
    Point_2
    operator()( const FT& px, const FT& py) const
    {
      if ( px.denominator() == py.denominator())
        return Point_2( px.numerator(), py.numerator(), py.denominator());
      else
        return Point_2( px.numerator() * py.denominator(),
                        py.numerator() * px.denominator(),
                        px.denominator() * py.denominator());
    }
  };
  struct Build_rectangle
  : public CGAL_STD::unary_function< Point_2, Iso_rectangle_2 >
  {
    Iso_rectangle_2
    operator()( const Point_2& p) const
    { return Iso_rectangle_2( p, p); }
  };
}; // Piercing_traits_homogeneous
template < class _R >
struct Piercing_squares_traits_cartesian
: public Piercing_traits_cartesian< _R >
{
  typedef Piercing_traits_cartesian< _R >  Base;
  typedef Base::Point_2                    Point_2;
  typedef CGAL::Iso_square_static_2< _R >  Iso_rectangle_2;

  struct Xmin : public CGAL_STD::unary_function< Iso_rectangle_2, FT >
  {
    FT
    operator()( const Iso_rectangle_2& r) const
    { return r.xmin(); }
  };
  
  struct Xmax : public CGAL_STD::unary_function< Iso_rectangle_2, FT >
  {
    FT
    operator()( const Iso_rectangle_2& r) const
    { return r.xmax(); }
  };
  
  struct Ymin : public CGAL_STD::unary_function< Iso_rectangle_2, FT >
  {
    FT
    operator()( const Iso_rectangle_2& r) const
    { return r.ymin(); }
  };
  
  struct Ymax : public CGAL_STD::unary_function< Iso_rectangle_2, FT >
  {
    FT
    operator()( const Iso_rectangle_2& r) const
    { return r.ymax(); }
  };
  struct Build_rectangle
  : public CGAL_STD::unary_function< Point_2, Iso_rectangle_2 >
  {
    Iso_rectangle_2
    operator()( const Point_2& p) const
    { return Iso_rectangle_2( p); }
  };
};
template < class _R >
struct Piercing_squares_traits_homogeneous
: public Piercing_traits_homogeneous< _R >
{
  typedef Piercing_traits_homogeneous< _R >  Base;
  typedef Base::Point_2                      Point_2;
  typedef CGAL::Iso_square_static_2< _R >    Iso_rectangle_2;

  struct Xmin : public CGAL_STD::unary_function< Iso_rectangle_2, FT >
  {
    FT
    operator()( const Iso_rectangle_2& r) const
    { return r.xmin(); }
  };
  
  struct Xmax : public CGAL_STD::unary_function< Iso_rectangle_2, FT >
  {
    FT
    operator()( const Iso_rectangle_2& r) const
    { return r.xmax(); }
  };
  
  struct Ymin : public CGAL_STD::unary_function< Iso_rectangle_2, FT >
  {
    FT
    operator()( const Iso_rectangle_2& r) const
    { return r.ymin(); }
  };
  
  struct Ymax : public CGAL_STD::unary_function< Iso_rectangle_2, FT >
  {
    FT
    operator()( const Iso_rectangle_2& r) const
    { return r.ymax(); }
  };
  struct Build_rectangle
  : public CGAL_STD::unary_function< Point_2, Iso_rectangle_2 >
  {
    Iso_rectangle_2
    operator()( const Point_2& p) const
    { return Iso_rectangle_2( p); }
  };
};
CGAL_END_NAMESPACE


#endif // ! (PIERCE_RECTANGLES_2_TRAITS_H)

// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

