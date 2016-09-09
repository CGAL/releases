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
// file          : include/CGAL/Optimisation_circle_2.h
// package       : Min_circle_2 (3.2.3)
// chapter       : $CGAL_Chapter: Geometric Optimisation $
//
// source        : web/Optimisation/Min_circle_2.aw
// revision      : $Revision: 5.8 $
// revision_date : $Date: 1999/04/19 16:20:38 $
// author(s)     : Sven Schönherr
//                 Bernd Gärtner
//
// coordinator   : ETH Zürich (Bernd Gärtner)
//
// implementation: 2D Optimisation Circle
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_OPTIMISATION_CIRCLE_2_H
#define CGAL_OPTIMISATION_CIRCLE_2_H

// includes
#ifndef CGAL_POINT_2_H
#  include <CGAL/Point_2.h>
#endif
#ifndef CGAL_BASIC_CONSTRUCTIONS_2_H
#  include <CGAL/basic_constructions_2.h>
#endif
#ifndef CGAL_SQUARED_DISTANCE_2_H
#  include <CGAL/squared_distance_2.h>
#endif

CGAL_BEGIN_NAMESPACE

// Class declaration
// =================
template < class _R >
class Optimisation_circle_2;

// Class interface
// ===============
template < class _R >
class Optimisation_circle_2 {
  public:
    // types
    typedef           _R                R;
    typedef           CGAL::Point_2<R>  Point;
    typedef typename  _R::FT            Distance;
    
    /**************************************************************************
    WORKAROUND: The GNU compiler (g++ 2.7.2[.x]) does not accept types
    with scope operator as argument type or return type in class template
    member functions. Therefore, all member functions are implemented in
    the class interface.
    
    // creation
    void  set( );
    void  set( const Point& p);
    void  set( const Point& p, const Point& q);
    void  set( const Point& p, const Point& q, const Point& r);
    void  set( const Point& center, const Distance& squared_radius);
    
    // access functions
    const Point&     center        ( ) const;
    const Distance&  squared_radius( ) const
    
    // equality tests
    bool  operator == ( const Optimisation_circle_2<R>& c) const;
    bool  operator != ( const Optimisation_circle_2<R>& c) const;
    
    // predicates
    CGAL::Bounded_side  bounded_side( const Point& p) const;
    bool  has_on_bounded_side      ( const Point& p) const;
    bool  has_on_boundary          ( const Point& p) const;
    bool  has_on_unbounded_side    ( const Point& p) const;
    
    bool  is_empty     ( ) const;
    bool  is_degenerate( ) const;
    **************************************************************************/

  private:
    // private data members
    Point     _center;
    Distance  _squared_radius;

// ============================================================================

// Class implementation
// ====================

  public:
    // Set functions
    // -------------
    inline
    void
    set( )
    {
        _center         =  Point( CGAL::ORIGIN);
        _squared_radius = -Distance( 1);
    }
    
    inline
    void
    set( const Point& p)
    {
        _center         = p;
        _squared_radius = Distance( 0);
    }
    
    inline
    void
    set( const Point& p, const Point& q)
    {
        _center         = CGAL::midpoint( p, q);
        _squared_radius = CGAL::squared_distance( p, _center);
    }
    
    inline
    void
    set( const Point& p, const Point& q, const Point& r)
    {
        _center         = CGAL::circumcenter( p, q, r);
        _squared_radius = CGAL::squared_distance( p, _center);
    }
    
    inline
    void
    set( const Point& center, const Distance& squared_radius)
    {
        _center         = center;
        _squared_radius = squared_radius;
    }

    // Access functions
    // ----------------
    inline
    const Point&
    center( ) const
    {
        return( _center);
    }
    
    inline
    const Distance&
    squared_radius( ) const
    {
        return( _squared_radius);
    }

    // Equality tests
    // --------------
    bool
    operator == ( const Optimisation_circle_2<R>& c) const
    {
        return( ( _center          == c._center        ) &&
                ( _squared_radius  == c._squared_radius) );
    }
    
    bool
    operator != ( const Optimisation_circle_2<R>& c) const
    {
        return( ! operator==( c));
    }

    // Predicates
    // ----------
    inline
    CGAL::Bounded_side
    bounded_side( const Point& p) const
    {
        return( CGAL::Bounded_side( CGAL::sign(
            _squared_radius - CGAL::squared_distance( p, _center))));
    }
    
    inline
    bool
    has_on_bounded_side( const Point& p) const
    {
        return( CGAL::squared_distance( p, _center) < _squared_radius);
    }
    
    inline
    bool
    has_on_boundary( const Point& p) const
    {
        return( CGAL::squared_distance( p, _center) == _squared_radius);
    }
    
    inline
    bool
    has_on_unbounded_side( const Point& p) const
    {
        return( _squared_radius < CGAL::squared_distance( p, _center));
    }
    
    inline
    bool
    is_empty( ) const
    {
        return( CGAL::is_negative( _squared_radius));
    }
    
    inline
    bool
    is_degenerate( ) const
    {
        return( ! CGAL::is_positive( _squared_radius));
    }
};

// Function declarations
// =====================
// I/O
// ---
template < class _R >
ostream&
operator << ( ostream&, const CGAL::Optimisation_circle_2<_R>&);

template < class _R >
istream&
operator >> ( istream&, CGAL::Optimisation_circle_2<_R>&);

CGAL_END_NAMESPACE

#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#  include <CGAL/Optimisation_circle_2.C>
#endif

#endif // CGAL_OPTIMISATION_CIRCLE_2_H

// ===== EOF ==================================================================
