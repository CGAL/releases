// ============================================================================
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
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/pierce_rectangles_2.h
// author(s)     : Michael Hoffmann 
//
// email         : cgal@cs.uu.nl
//
// ============================================================================

#if ! (CGAL_PIERCE_RECTANGLES_2_H)
#define CGAL_PIERCE_RECTANGLES_2_H 1

#include <CGAL/circulator.h>
#include <CGAL/function_objects.h>
#include <CGAL/Transform_iterator.h>
#include <algo.h>
#include <vector.h>

//!!! to function_objects.h
template < class T1, class T2 >
struct CGAL_Has_on_unbounded_side
: public binary_function< T1, T2, bool >
{
  bool
  operator()( const T1& a, const T2& b) const
  { return a.has_on_unbounded_side( b); }
};
template < class T1, class T2 >
struct CGAL_Has_on_bounded_side
: public binary_function< T1, T2, bool >
{
  bool
  operator()( const T1& a, const T2& b) const
  { return a.has_on_bounded_side( b); }
};
template < class T1, class T2 >
struct CGAL_Has_on_boundary
: public binary_function< T1, T2, bool >
{
  bool
  operator()( const T1& a, const T2& b) const
  { return a.has_on_boundary( b); }
};

//!!! STL-extensions
template < class T >
struct CGAL_Wastebasket : public output_iterator
{
  typedef CGAL_Wastebasket< T > iterator;

  iterator
  operator=( const T&)
  { return *this; }

  iterator
  operator*()
  { return *this; }

  iterator
  operator++()
  { return *this; }

  iterator
  operator++( int)
  { return *this; }
};

template < class _Traits, class _RandomAccessIC >
class CGAL__Loc_domain {
public:
  // ---------------------------------------------
  // types:

  typedef _Traits           Traits;
  typedef _RandomAccessIC   RandomAccessIC;
  typedef typename _Traits::Iso_rectangle_2
    Iso_rectangle_2;
  typedef typename _Traits::Point_2  Point_2;
  typedef typename _Traits::FT       FT;

  // ---------------------------------------------
  // creation:

  CGAL__Loc_domain( RandomAccessIC b, RandomAccessIC e)
  {
    CGAL_precondition( b != e);
  
    RandomAccessIC i( b);
    r[0] = r[1] = r[2] = r[3] = i;
    while ( ++i != e) {
      check_and_update_border( 0, i);
      check_and_update_border( 1, i);
      check_and_update_border( 2, i);
      check_and_update_border( 3, i);
    }
  
    CGAL_postcondition(
      !(*r[0]).has_on_bounded_side( vertex( 0)) &&
      !(*r[1]).has_on_bounded_side( vertex( 0)));
    CGAL_postcondition(
      !(*r[1]).has_on_bounded_side( vertex( 1)) &&
      !(*r[2]).has_on_bounded_side( vertex( 1)));
    CGAL_postcondition(
      !(*r[2]).has_on_bounded_side( vertex( 2)) &&
      !(*r[3]).has_on_bounded_side( vertex( 2)));
    CGAL_postcondition(
      !(*r[3]).has_on_bounded_side( vertex( 3)) &&
      !(*r[0]).has_on_bounded_side( vertex( 3)));
  }

  // ---------------------------------------------
  // access operations:

  RandomAccessIC
  operator[]( int i) const
  // return defining rectangle (0 <-> left, 1 <-> bottom)
  {
    CGAL_precondition( i >= 0 && i < 4);
    return r[i];
  }

  FT
  xmin() const
  // returns x-coordinate of left border
  { return (*r[0]).xmax(); }

  FT
  ymin() const
  // returns y-coordinate of lower border
  { return (*r[1]).ymax(); }

  FT
  xmax() const
  // returns x-coordinate of right border
  { return (*r[2]).xmin(); }

  FT
  ymax() const
  // returns y-coordinate of upper border
  { return (*r[3]).ymin(); }

  Point_2
  vertex( int i) const
  // PRE: 0 <= i < 4
  // POST: returns one of the four vertices:
  //  0 <=> lower left
  //  1 <=> lower right
  //  2 <=> upper right
  //  3 <=> upper left
  {
    CGAL_precondition( i >= 0 && i < 4);
    typedef typename _Traits::Build_point Build;
    switch( i) {
    case 0:
      return Build()( xmin(), ymin());
    case 1:
      return Build()( xmax(), ymin());
    case 2:
      return Build()( xmax(), ymax());
    // case 3:
    //  return Point_2( xmin(), ymax());
    }
    return Build()( xmin(), ymax());
  }

  Point_2
  min() const
  // return lexicographically smallest vertex
  // (in analogy to CGAL_Iso_rectangle)
  { return vertex( 0); }

  Point_2
  max() const
  // return lexicographically largest vertex
  // (in analogy to CGAL_Iso_rectangle)
  { return vertex( 2); }

  // ---------------------------------------------
  // update operations:
  
  void
  init( int i, RandomAccessIC f)
  // PRE: 0 <= i < 4
  // POST: set defining rectangle r[i] to f
  {
    CGAL_precondition( i >= 0 && i < 4);
    r[i] = f;
  }
  
  void
  check_and_update_border( int i, RandomAccessIC a)
  // PRE: 0 <= i < 4
  // POST: check whether rectangle *a invalidates
  //   border i. if so, update defining rectangle r[i]
  //   to a.
  {
    CGAL_precondition( i >= 0 && i < 4);
    switch( i) {
    case 0:
      if ( (*a).xmax() < (*r[0]).xmax())
        r[0] = a;
      break;
    case 1:
      if ( (*a).ymax() < (*r[1]).ymax())
        r[1] = a;
      break;
    case 2:
      if ( (*a).xmin() > (*r[2]).xmin())
        r[2] = a;
      break;
    case 3:
      if ( (*a).ymin() > (*r[3]).ymin())
        r[3] = a;
      break;
    }
  }

private:
  // pointer to defining rectangles:
  RandomAccessIC r[4];
}; // class CGAL__Loc_domain
template < class _R >
struct CGAL_Piercing_traits_cartesian {
  typedef typename _R::FT             FT;
  typedef CGAL_Point_2< _R >          Point_2;
  typedef CGAL_Iso_rectangle_2< _R >  Iso_rectangle_2;

  struct X : public unary_function< Point_2, FT >
  {
    FT
    operator()( const Point_2& p)
    { return p.x(); }
  };
  
  struct Y : public unary_function< Point_2, FT >
  {
    FT
    operator()( const Point_2& p)
    { return p.y(); }
  };

  struct Build_point
  : public binary_function< FT, FT, Point_2 >
  {
    Point_2
    operator()( const FT& px, const FT& py)
    { return Point_2( px, py); }
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
    operator()( const Point_2& p)
    { return p.x(); }
  };
  
  struct Y : public unary_function< Point_2, FT >
  {
    FT
    operator()( const Point_2& p)
    { return p.y(); }
  };

  struct Build_point
  : public binary_function< FT, FT, Point_2 >
  {
    Point_2
    operator()( const FT& px, const FT& py)
    {
      return Point_2(
        px.numerator() * py.denominator(),
        py.numerator() * px.denominator(),
        px.denominator() * py.denominator());
    }
  };
}; // CGAL_Piercing_traits_homogeneous
/*
template < class _R >
struct CGAL_Piercing_squares_traits_cartesian {
  typedef _R::FT               FT;
  typedef CGAL_Point_2< _R >   Point_2;
  typedef CGAL_Square_2< _R >  Iso_rectangle_2;

  struct X : public unary_function< Point_2, FT >
  {
    FT
    operator()( const Point_2& p)
    { return p.x(); }
  };
  
  struct Y : public unary_function< Point_2, FT >
  {
    FT
    operator()( const Point_2& p)
    { return p.y(); }
  };

  
};
*/

template < class RandomAccessIC,
           class OutputIterator,
           class Traits >
OutputIterator
CGAL_two_pierce_rectangles(
  RandomAccessIC f,
  RandomAccessIC l,
  OutputIterator o,
  bool& ok,
  const Traits&)
{
  #if defined(CGAL_PCENTER_TRACE)
  cerr << " -- two pierce start --" << endl;
  for ( RandomAccessIC u = f; u != l; ++u)
    cerr << &(*u) << " : " << *u << endl;
  #endif

  CGAL_precondition( f != l);

  // compute location domain:
  typedef CGAL__Loc_domain< Traits, RandomAccessIC > Loc_domain;
  Loc_domain d( f, l);

  return CGAL_two_pierce_rectangles( f, l, d, o, ok);
} // CGAL_two_pierce_rectangles( f, l, o, ok, i)
template < class RandomAccessIC,
           class OutputIterator,
           class Traits >
OutputIterator
CGAL_two_pierce_rectangles(
  RandomAccessIC f,
  RandomAccessIC l,
  const CGAL__Loc_domain< Traits, RandomAccessIC >& d,
  OutputIterator o,
  bool& ok)
{
  CGAL_precondition( f != l);

  // typedefs:
  typedef typename Traits::Point_2
    Point_2;
  typedef typename Traits::Iso_rectangle_2
    Iso_rectangle_2;
  typedef CGAL_Has_on_unbounded_side< Iso_rectangle_2, Point_2 >
    Has_on_unbounded_side;

  #if defined(CGAL_PCENTER_TRACE)
  cerr << " ++ 2 pierce start ++" << endl;
  for ( RandomAccessIC u = f; u != l; ++u)
    cerr << &(*u) << " : " << *u << endl;
  cerr << "LocDomain is " << d.vertex( 0) << " --> " <<
    d.vertex( 2) << endl;
  /*
  CGAL_Window_stream W;
  W.init( -1024 / 5, 1024 + 1024 / 5, -1024 / 5);
  W << CGAL_RED;
  WindowOutput( W, f, l);
  W << CGAL_GREEN;
  W << Iso_rectangle_2( d.vertex( 0), d.vertex( 2));
  double x, y;
  while ( W.read_mouse( x, y) != -1) {}
  */
  #endif

  if ( !(*d[0]).has_on_unbounded_side( d.vertex( 0)) &&
       !(*d[1]).has_on_unbounded_side( d.vertex( 0)) &&
       !(*d[2]).has_on_unbounded_side( d.vertex( 0)) &&
       !(*d[3]).has_on_unbounded_side( d.vertex( 0))) {
    // the location domain is degenerate
    // and [f,l) is one-pierceable
    *o++ = d.vertex( 0);
    ok = true;
    return o;
  }
  // check, if {d.vertex( 0), d.vertex( 2)}
  // form a piercing set
  if ( l == find_if(
    f,
    l,
    compose2( logical_and< bool >(),
              bind2nd( Has_on_unbounded_side(),
                       d.vertex( 0)),
              bind2nd( Has_on_unbounded_side(),
                       d.vertex( 2)))))
  {
    // {d.vertex( 0), d.vertex( 2)} is a piercing set
    *o++ = d.vertex( 0);
    *o++ = d.vertex( 2);
    ok = true;
    return o;
  }
  // check, if {d.vertex( 1), d.vertex( 3)}
  // form a piercing set
  if ( l == find_if(
    f,
    l,
    compose2( logical_and< bool >(),
              bind2nd( Has_on_unbounded_side(),
                       d.vertex( 1)),
              bind2nd( Has_on_unbounded_side(),
                       d.vertex( 3)))))
  {
    // {d.vertex( 1), d.vertex( 3)} is a piercing set
    *o++ = d.vertex( 1);
    *o++ = d.vertex( 3);
    ok = true;
    return o;
  }

  // no piercing set exists:
  ok = false;
  return o;
} // CGAL_two_pierce_rectangles( f, l, d, o, ok)
template < class _Traits >
class CGAL_Two_piercing_algorithm {
public:
  // don't touch these typedefs ;)
  // Traits is not enough for sunpro ...
  typedef _Traits                            Traits;
  typedef typename _Traits::Iso_rectangle_2  Iso_rectangle_2;
  typedef typename _Traits::Point_2          Point_2;
  typedef typename _Traits::FT               FT;
  typedef typename _Traits::X                X;
  typedef typename _Traits::Y                Y;

#ifndef CGAL_CFG_NO_MEMBER_TEMPLATES
  template < class RandomAccessIC, class OutputIterator >
#else
  typedef vector< Iso_rectangle_2 >::iterator
    RandomAccessIC;
  typedef back_insert_iterator< vector< Point_2 > >
    OutputIterator;

  CGAL_Wastebasket< Point_2 >
  operator()(
    RandomAccessIC f,
    RandomAccessIC l,
    CGAL_Wastebasket< Point_2 > o,
    bool& ok)
  
  {
    return CGAL_two_pierce_rectangles( f, l, o, ok, Traits());
  }

#endif // CGAL_CFG_NO_MEMBER_TEMPLATES

  OutputIterator
  operator()(
    RandomAccessIC f,
    RandomAccessIC l,
    OutputIterator o,
    bool& ok)
  
  {
    return CGAL_two_pierce_rectangles( f, l, o, ok, Traits());
  }

#ifndef CGAL_CFG_NO_MEMBER_TEMPLATES
  template < class RandomAccessIC, class OutputIterator >
#endif // CGAL_CFG_NO_MEMBER_TEMPLATES
  OutputIterator
  operator()(
    RandomAccessIC f,
    RandomAccessIC l,
    const CGAL__Loc_domain< Traits, RandomAccessIC >& d,
    OutputIterator o,
    bool& ok)
  { return CGAL_two_pierce_rectangles( f, l, d, o, ok); }

}; // class CGAL_Two_piercing_algorithm


#endif // ! (CGAL_PIERCE_RECTANGLES_2_H)

// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

