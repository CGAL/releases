// ======================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------
//
// release       : $CGAL_Revision: CGAL-2.2-I-51 $
// release_date  : $CGAL_Date: 2000/10/01 $
//
// file          : include/CGAL/Optimisation_circle_2.h
// package       : Min_circle_2 (3.10.1)
// maintainer    : Sven Sch�nherr <sven@inf.ethz.ch>
// chapter       : $CGAL_Chapter: Geometric Optimisation $
//
// source        : web/Optimisation/Min_circle_2.aw
// revision      : $Revision: 5.29 $
// revision_date : $Date: 2000/09/18 09:56:37 $
//
// author(s)     : Sven Sch�nherr, Bernd G�rtner
// coordinator   : ETH Z�rich (Bernd G�rtner <gaertner@inf.ethz.ch>)
//
// implementation: 2D Optimisation Circle
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
template < class _R >
std::ostream&
operator << ( std::ostream&, const CGAL::Optimisation_circle_2<_R>&);

template < class _R >
std::istream&
operator >> ( std::istream&, CGAL::Optimisation_circle_2<_R>&);

CGAL_END_NAMESPACE

#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#  include <CGAL/Optimisation_circle_2.C>
#endif

#endif // CGAL_OPTIMISATION_CIRCLE_2_H

// ===== EOF ==================================================================
