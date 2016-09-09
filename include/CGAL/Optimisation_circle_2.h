// ======================================================================
//
// Copyright (c) 1997-2001 The CGAL Consortium

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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/Optimisation_circle_2.h
// package       : Min_circle_2 (3.15)
// chapter       : Geometric Optimisation
//
// source        : web/Min_circle_2.aw
// revision      : $Revision: 1.7 $
// revision_date : $Date: 2001/07/17 11:24:33 $
//
// author(s)     : Sven Schönherr, Bernd Gärtner
// coordinator   : ETH Zürich (Bernd Gärtner)
//
// implementation: 2D Optimisation Circle
// email         : contact@cgal.org
// www           : http://www.cgal.org
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
template < class K_ >
class Optimisation_circle_2;

// Class interface
// ===============
template < class K_ >
class Optimisation_circle_2 {
  public:
    // types
    typedef           K_                K;
    typedef           CGAL::Point_2<K>  Point;
    typedef typename  K_::FT            Distance;
    
    /**************************************************************************
    WORKAROUND: Some compilers are unable to match member functions defined
    outside the class template. Therefore, all member functions are implemented
    in the class interface.
    
    // creation
    Optimisation_circle_2( );
    
    void  set( );
    void  set( const Point& p);
    void  set( const Point& p, const Point& q);
    void  set( const Point& p, const Point& q, const Point& r);
    void  set( const Point& center, const Distance& squared_radius);
    
    // access functions
    const Point&     center        ( ) const;
    const Distance&  squared_radius( ) const
    
    // equality tests
    bool  operator == ( const Optimisation_circle_2<K>& c) const;
    bool  operator != ( const Optimisation_circle_2<K>& c) const;
    
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
    // Constructor
    // -----------
    inline
    Optimisation_circle_2( )
    { }

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
    operator == ( const Optimisation_circle_2<K>& c) const
    {
        return( ( _center          == c._center        ) &&
                ( _squared_radius  == c._squared_radius) );
    }
    
    bool
    operator != ( const Optimisation_circle_2<K>& c) const
    {
        return( ! operator==( c));
    }

    // Predicates
    // ----------
    inline
    CGAL::Bounded_side
    bounded_side( const Point& p) const
    {
        return( CGAL::Bounded_side( CGAL_NTS sign(
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
template < class K_ >
std::ostream&
operator << ( std::ostream&, const CGAL::Optimisation_circle_2<K_>&);

template < class K_ >
std::istream&
operator >> ( std::istream&, CGAL::Optimisation_circle_2<K_>&);

CGAL_END_NAMESPACE

#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#  include <CGAL/Optimisation_circle_2.C>
#endif

#endif // CGAL_OPTIMISATION_CIRCLE_2_H

// ===== EOF ==================================================================
