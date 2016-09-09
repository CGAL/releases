// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : include/CGAL/Pierce_rectangles_2_traits.h
// package       : Matrix_search (1.7)
// chapter       : $CGAL_Chapter: Geometric Optimisation $
// source        : pcenter.aw
// revision      : $Revision: 1.7 $
// revision_date : $Date: 1998/07/23 16:53:47 $
// author(s)     : Michael Hoffmann
//
// coordinator   : ETH Zurich (Bernd Gaertner)
//
// 2-4-Piercing Axis-Parallel 2D-Rectangles
// email         : cgal@cs.uu.nl
//
// ======================================================================

#if ! (CGAL_PIERCE_RECTANGLES_2_TRAITS_H)
#define CGAL_PIERCE_RECTANGLES_2_TRAITS_H 1

#ifndef CGAL_POINT_2_H
#include <CGAL/Point_2.h>
#endif // CGAL_POINT_2_H
#ifndef CGAL_ISO_RECTANGLE_2_H
#include <CGAL/Iso_rectangle_2.h>
#endif // CGAL_ISO_RECTANGLE_2_H
#ifndef CGAL_ISO_SQUARE_STATIC_2_H
#include <CGAL/Iso_square_static_2.h>
#endif // CGAL_ISO_SQUARE_STATIC_2_H

template < class _R >
struct CGAL_Piercing_traits_cartesian {
  typedef typename _R::FT             FT;
  typedef CGAL_Point_2< _R >          Point_2;
  typedef CGAL_Iso_rectangle_2< _R >  Iso_rectangle_2;

  struct X : public unary_function< Point_2, FT >
  {
    FT
    operator()( const Point_2& p) const
    { return p.x(); }
  };
  
  struct Y : public unary_function< Point_2, FT >
  {
    FT
    operator()( const Point_2& p) const
    { return p.y(); }
  };
  struct Xmin : public unary_function< Iso_rectangle_2, FT >
  {
    FT
    operator()( const Iso_rectangle_2& r) const
    { return r.xmin(); }
  };
  
  struct Xmax : public unary_function< Iso_rectangle_2, FT >
  {
    FT
    operator()( const Iso_rectangle_2& r) const
    { return r.xmax(); }
  };
  
  struct Ymin : public unary_function< Iso_rectangle_2, FT >
  {
    FT
    operator()( const Iso_rectangle_2& r) const
    { return r.ymin(); }
  };
  
  struct Ymax : public unary_function< Iso_rectangle_2, FT >
  {
    FT
    operator()( const Iso_rectangle_2& r) const
    { return r.ymax(); }
  };
  struct Build_point
  : public binary_function< FT, FT, Point_2 >
  {
    Point_2
    operator()( const FT& px, const FT& py) const
    { return Point_2( px, py); }
  };
  struct Build_rectangle
  : public unary_function< Point_2, Iso_rectangle_2 >
  {
    Iso_rectangle_2
    operator()( const Point_2& p) const
    { return Iso_rectangle_2( p, p); }
  };
}; // CGAL_Piercing_traits_cartesian
template < class _R >
struct CGAL_Piercing_traits_homogeneous {
  typedef typename _R::FT             FT;
  typedef CGAL_Point_2< _R >          Point_2;
  typedef CGAL_Iso_rectangle_2< _R >  Iso_rectangle_2;

  struct X : public unary_function< Point_2, FT >
  {
    FT
    operator()( const Point_2& p) const
    { return p.x(); }
  };
  
  struct Y : public unary_function< Point_2, FT >
  {
    FT
    operator()( const Point_2& p) const
    { return p.y(); }
  };
  struct Xmin : public unary_function< Iso_rectangle_2, FT >
  {
    FT
    operator()( const Iso_rectangle_2& r) const
    { return r.xmin(); }
  };
  
  struct Xmax : public unary_function< Iso_rectangle_2, FT >
  {
    FT
    operator()( const Iso_rectangle_2& r) const
    { return r.xmax(); }
  };
  
  struct Ymin : public unary_function< Iso_rectangle_2, FT >
  {
    FT
    operator()( const Iso_rectangle_2& r) const
    { return r.ymin(); }
  };
  
  struct Ymax : public unary_function< Iso_rectangle_2, FT >
  {
    FT
    operator()( const Iso_rectangle_2& r) const
    { return r.ymax(); }
  };
  struct Build_point
  : public binary_function< FT, FT, Point_2 >
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
  : public unary_function< Point_2, Iso_rectangle_2 >
  {
    Iso_rectangle_2
    operator()( const Point_2& p) const
    { return Iso_rectangle_2( p, p); }
  };
}; // CGAL_Piercing_traits_homogeneous
template < class _R >
struct CGAL_Piercing_squares_traits_cartesian
: public CGAL_Piercing_traits_cartesian< _R >
{
  typedef CGAL__Iso_square_static_2< _R >  Iso_rectangle_2;

  struct Xmin : public unary_function< Iso_rectangle_2, FT >
  {
    FT
    operator()( const Iso_rectangle_2& r) const
    { return r.xmin(); }
  };
  
  struct Xmax : public unary_function< Iso_rectangle_2, FT >
  {
    FT
    operator()( const Iso_rectangle_2& r) const
    { return r.xmax(); }
  };
  
  struct Ymin : public unary_function< Iso_rectangle_2, FT >
  {
    FT
    operator()( const Iso_rectangle_2& r) const
    { return r.ymin(); }
  };
  
  struct Ymax : public unary_function< Iso_rectangle_2, FT >
  {
    FT
    operator()( const Iso_rectangle_2& r) const
    { return r.ymax(); }
  };
  struct Build_rectangle
  : public unary_function< Point_2, Iso_rectangle_2 >
  {
    Iso_rectangle_2
    operator()( const Point_2& p) const
    { return Iso_rectangle_2( p); }
  };
};
template < class _R >
struct CGAL_Piercing_squares_traits_homogeneous
: public CGAL_Piercing_traits_homogeneous< _R >
{
  typedef CGAL__Iso_square_static_2< _R >  Iso_rectangle_2;

  struct Xmin : public unary_function< Iso_rectangle_2, FT >
  {
    FT
    operator()( const Iso_rectangle_2& r) const
    { return r.xmin(); }
  };
  
  struct Xmax : public unary_function< Iso_rectangle_2, FT >
  {
    FT
    operator()( const Iso_rectangle_2& r) const
    { return r.xmax(); }
  };
  
  struct Ymin : public unary_function< Iso_rectangle_2, FT >
  {
    FT
    operator()( const Iso_rectangle_2& r) const
    { return r.ymin(); }
  };
  
  struct Ymax : public unary_function< Iso_rectangle_2, FT >
  {
    FT
    operator()( const Iso_rectangle_2& r) const
    { return r.ymax(); }
  };
  struct Build_rectangle
  : public unary_function< Point_2, Iso_rectangle_2 >
  {
    Iso_rectangle_2
    operator()( const Point_2& p) const
    { return Iso_rectangle_2( p); }
  };
};


#endif // ! (CGAL_PIERCE_RECTANGLES_2_TRAITS_H)

// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

