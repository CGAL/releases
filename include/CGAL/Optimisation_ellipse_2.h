// ======================================================================
//
// Copyright (c) 1997,1998,1999 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : include/CGAL/Optimisation_ellipse_2.h
// package       : Min_ellipse_2 (3.5.4)
// chapter       : $CGAL_Chapter: Geometric Optimisation $
//
// source        : web/Optimisation/Min_ellipse_2.aw
// revision      : $Revision: 5.22 $
// revision_date : $Date: 1999/12/20 19:06:47 $
// author(s)     : Sven Schönherr
//                 Bernd Gärtner
//
// coordinator   : ETH Zürich (Bernd Gärtner)
//
// implementation: 2D Optimisation Ellipse
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_OPTIMISATION_ELLIPSE_2_H
#define CGAL_OPTIMISATION_ELLIPSE_2_H

// the following include is needed by `to_double()'
#ifndef CGAL_CARTESIAN_H
#  include <CGAL/Cartesian.h>
#endif

// includes
#ifndef CGAL_POINT_2_H
#  include <CGAL/Point_2.h>
#endif
#ifndef CGAL_CONIC_2_H
#  include <CGAL/Conic_2.h>
#endif
#ifndef CGAL_OPTIMISATION_ASSERTIONS_H
#  include <CGAL/Optimisation/assertions.h>
#endif
#ifndef CGAL_IO_FORWARD_DECL_WINDOW_STREAM_H
#  include <CGAL/IO/forward_decl_window_stream.h>
#endif

CGAL_BEGIN_NAMESPACE

// Class declaration
// =================
template < class _R >
class Optimisation_ellipse_2;

// Class interface
// ===============
template < class _R >
class Optimisation_ellipse_2 {
    /*
    friend  std::ostream&  operator << CGAL_NULL_TMPL_ARGS (
        std::ostream&, const Optimisation_ellipse_2<_R>&);
    friend  std::istream&  operator >> CGAL_NULL_TMPL_ARGS (
        std::istream&, Optimisation_ellipse_2<_R> &);
    friend  CGAL::Window_stream& operator << CGAL_NULL_TMPL_ARGS (
        CGAL::Window_stream&, const Optimisation_ellipse_2<_R>&);
    */
  public:
    // types
    typedef           _R                R;
    typedef  typename _R::RT            RT;
    typedef  typename _R::FT            FT;
    typedef           CGAL::Point_2<R>  Point;
    typedef           CGAL::Conic_2<R>  Conic;
    
    /**************************************************************************
    WORKAROUND: Some compilers are unable to match member functions defined
    outside the class template. Therefore, all member functions are implemented
    in the class interface.
    
    // creation
    void  set( );
    void  set( const Point& p);
    void  set( const Point& p,  const Point& q);
    void  set( const Point& p1, const Point& p2, const Point& p3);
    void  set( const Point& p1, const Point& p2,
               const Point& p3, const Point& p4);
    void  set( const Point& p1, const Point& p2,
               const Point& p3, const Point& p4, const Point& p5);
    
    // access functions
    int  number_of_boundary_points()
    
    // equality tests
    bool  operator == ( const Optimisation_ellipse_2<R>& e) const;
    bool  operator != ( const Optimisation_ellipse_2<R>& e) const;
    
    // predicates
    CGAL::Bounded_side  bounded_side( const Point& p) const;
    bool  has_on_bounded_side      ( const Point& p) const;
    bool  has_on_boundary          ( const Point& p) const;
    bool  has_on_unbounded_side    ( const Point& p) const;
    
    bool  is_empty     ( ) const;
    bool  is_degenerate( ) const;
    **************************************************************************/

  /* private: */
    // private data members
    int    n_boundary_points;                   // number of boundary points
    Point  boundary_point1, boundary_point2;    // two boundary points
    Conic  conic1, conic2;                      // two conics
    RT     dr, ds, dt, du, dv, dw;              // the gradient vector
    

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
        n_boundary_points = 0;
    }
    
    inline
    void
    set( const Point& p)
    {
        n_boundary_points = 1;
        boundary_point1   = p;
    }
    
    inline
    void
    set( const Point& p, const Point& q)
    {
        n_boundary_points = 2;
        boundary_point1   = p;
        boundary_point2   = q;
    }
    
    inline
    void
    set( const Point& p1, const Point& p2, const Point& p3)
    {
        n_boundary_points = 3;
        conic1.set_ellipse( p1, p2, p3);
    }
    
    inline
    void
    set( const Point& p1, const Point& p2, const Point& p3, const Point& p4)
    {
        n_boundary_points = 4;
        Conic::set_two_linepairs( p1, p2, p3, p4, conic1, conic2);
        dr = RT( 0);
        ds = conic1.r() * conic2.s() - conic2.r() * conic1.s(),
        dt = conic1.r() * conic2.t() - conic2.r() * conic1.t(),
        du = conic1.r() * conic2.u() - conic2.r() * conic1.u(),
        dv = conic1.r() * conic2.v() - conic2.r() * conic1.v(),
        dw = conic1.r() * conic2.w() - conic2.r() * conic1.w();
    }
    
    inline
    void
    set( const Point&, const Point&,
         const Point&, const Point&, const Point& p5)
    {
        n_boundary_points = 5;
        conic1.set( conic1, conic2, p5);
        conic1.analyse();
    }

    // Access functions
    // ----------------
    inline
    int
    number_of_boundary_points( ) const
    {
        return( n_boundary_points);
    }
    
    Conic_2< Cartesian< double > >
    to_double( ) const
    {
        CGAL_optimisation_precondition( ! is_degenerate());
    
        double t = 0.0;
    
        if ( n_boundary_points == 4)
            t = conic1.vol_minimum( dr, ds, dt, du, dv, dw);
    
        Conic_2<R> c( conic1);
        Conic_2< Cartesian<double> > e;
        e.set( CGAL::to_double( c.r()) + t*CGAL::to_double( dr),
               CGAL::to_double( c.s()) + t*CGAL::to_double( ds),
               CGAL::to_double( c.t()) + t*CGAL::to_double( dt),
               CGAL::to_double( c.u()) + t*CGAL::to_double( du),
               CGAL::to_double( c.v()) + t*CGAL::to_double( dv),
               CGAL::to_double( c.w()) + t*CGAL::to_double( dw));
    
        return( e);
    }

    // Equality tests
    // --------------
    bool
    operator == ( const Optimisation_ellipse_2<R>& e) const
    {
        if ( n_boundary_points != e.n_boundary_points)
            return( false);
    
        switch ( n_boundary_points) {
          case 0:
            return( true);
          case 1:
            return( boundary_point1 == e.boundary_point1);
          case 2:
            return(    (    ( boundary_point1 == e.boundary_point1)
                         && ( boundary_point2 == e.boundary_point2))
                    || (    ( boundary_point1 == e.boundary_point2)
                         && ( boundary_point2 == e.boundary_point1)));
          case 3:
          case 5:
            return( conic1 == e.conic1);
          case 4:
            return(    (    ( conic1 == e.conic1)
                         && ( conic2 == e.conic2))
                    || (    ( conic1 == e.conic2)
                         && ( conic2 == e.conic1)));
          default:
            CGAL_optimisation_assertion(    ( n_boundary_points >= 0)
                                         && ( n_boundary_points <= 5)); }
        // keeps g++ happy
        return( false);
    }
    
    inline
    bool
    operator != ( const Optimisation_ellipse_2<R>& e) const
    {
        return( ! operator == ( e));
    }

    // Predicates
    // ----------
    inline
    CGAL::Bounded_side
    bounded_side( const Point& p) const
    {
        switch ( n_boundary_points) {
          case 0:
            return( CGAL::ON_UNBOUNDED_SIDE);
          case 1:
            return( ( p == boundary_point1) ?
                           CGAL::ON_BOUNDARY : CGAL::ON_UNBOUNDED_SIDE);
          case 2:
            return(    ( p == boundary_point1)
                    || ( p == boundary_point2)
                    || ( CGAL::are_ordered_along_line(
                             boundary_point1, p, boundary_point2)) ?
                         CGAL::ON_BOUNDARY : CGAL::ON_UNBOUNDED_SIDE);
          case 3:
          case 5:
            return( conic1.convex_side( p));
          case 4: {
            Conic c;
            c.set( conic1, conic2, p);
            c.analyse();
            if ( ! c.is_ellipse()) {
                c.set_ellipse( conic1, conic2);
                c.analyse();
                return( c.convex_side( p)); }
            else {
                int tau_star = c.vol_derivative( dr, ds, dt, du, dv, dw);
                return( CGAL::Bounded_side( CGAL::sign( tau_star))); } }
          default:
            CGAL_optimisation_assertion( ( n_boundary_points >= 0) &&
                                         ( n_boundary_points <= 5) ); }
        // keeps g++ happy
        return( CGAL::Bounded_side( 0));
    }
    
    inline
    bool
    has_on_bounded_side( const Point& p) const
    {
        return( bounded_side( p) == CGAL::ON_BOUNDED_SIDE);
    }
    
    inline
    bool
    has_on_boundary( const Point& p) const
    {
        return( bounded_side( p) == CGAL::ON_BOUNDARY);
    }
    
    inline
    bool
    has_on_unbounded_side( const Point& p) const
    {
        return( bounded_side( p) == CGAL::ON_UNBOUNDED_SIDE);
    }
    
    inline
    bool
    is_empty( ) const
    {
        return( n_boundary_points == 0);
    }
    
    inline
    bool
    is_degenerate( ) const
    {
        return( n_boundary_points < 3);
    }
};

// Function declarations
// =====================
// I/O
// ---
template < class _R >
std::ostream&
operator << ( std::ostream&, const CGAL::Optimisation_ellipse_2<_R>&);

template < class _R >
std::istream&
operator >> ( std::istream&, CGAL::Optimisation_ellipse_2<_R>&);

CGAL_END_NAMESPACE

#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#  include <CGAL/Optimisation_ellipse_2.C>
#endif

#endif // CGAL_OPTIMISATION_ELLIPSE_2_H

// ===== EOF ==================================================================
