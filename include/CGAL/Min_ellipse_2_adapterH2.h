// ======================================================================
//
// Copyright (c) 1997,1998 The CGAL Consortium
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
// file          : include/CGAL/Min_ellipse_2_adapterH2.h
// package       : Min_ellipse_2 (3.0.2)
// chapter       : $CGAL_Chapter: Geometric Optimisation $
//
// source        : web/Optimisation/Min_ellipse_2.aw
// revision      : $Revision: 5.1 $
// revision_date : $Date: 1998/07/02 17:55:03 $
// author(s)     : Sven Schönherr
//                 Bernd Gärtner
//
// coordinator   : ETH Zürich (Bernd Gärtner)
//
// implementation: traits class adapter for 2D Smallest Enclosing Ellipse
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_MIN_ELLIPSE_2_ADAPTERH2_H
#define CGAL_MIN_ELLIPSE_2_ADAPTERH2_H

// Class declarations
// ==================
template < class _Traits >
class CGAL_Min_ellipse_2;

template < class _PT, class _DA >
class CGAL_Min_ellipse_2_adapterH2;

template < class _PT, class _DA >
class CGAL__Min_ellipse_2_adapterH2__Ellipse;

// Class interface and implementation
// ==================================
// includes
#ifndef CGAL_CONICHPA2_H
#  include <CGAL/ConicHPA2.h>
#endif
#ifndef CGAL_OPTIMISATION_ASSERTIONS_H
#  include <CGAL/optimisation_assertions.h>
#endif

template < class PT, class DA >
bool
CGAL_are_ordered_along_lineH2( const PT& p, const PT& q, const PT& r,
                               const DA& da)
{
    typedef  typename DA::RT  RT;

    RT  phx;
    RT  phy;
    RT  phw;
    RT  qhx;
    RT  qhy;
    RT  qhw;
    RT  rhx;
    RT  rhy;
    RT  rhw;

    da.get( p, phx, phy, phw);
    da.get( q, qhx, qhy, qhw);
    da.get( r, rhx, rhy, rhw);

    // p,q,r collinear?
    if ( ! CGAL_is_zero(   ( phx*rhw - rhx*phw) * ( qhy*rhw - rhy*qhw)
                         - ( phy*rhw - rhy*phw) * ( qhx*rhw - rhx*qhw)))
        return( false);

    // p,q,r vertical?
    if ( phx*rhw != rhx*phw)
        return(    ( ( phx*qhw < qhx*phw) && ( qhx*rhw < rhx*qhw))
                || ( ( rhx*qhw < qhx*rhw) && ( qhx*phw < phx*qhw)));
    else
        return(    ( ( phy*qhw < qhy*phw) && ( qhy*rhw < rhy*qhw))
                || ( ( rhy*qhw < qhy*rhw) && ( qhy*phw < phy*qhw)));
}

template < class _PT, class _DA >
class CGAL_Min_ellipse_2_adapterH2 {
  public:
    // types
    typedef  _PT  PT;
    typedef  _DA  DA;

    // nested types
    typedef  PT                                             Point;
    typedef  CGAL__Min_ellipse_2_adapterH2__Ellipse<PT,DA>  Ellipse;

  private:
    DA      dao;                                    // data accessor object
    Ellipse ellipse;                                // current ellipse
    friend class CGAL_Min_ellipse_2< CGAL_Min_ellipse_2_adapterH2<PT,DA> >;

  public:
    // creation
    CGAL_Min_ellipse_2_adapterH2( const DA& da = DA())
        : dao( da), ellipse( da)
    { }

    // operations
    CGAL_Orientation
    orientation( const Point& p, const Point& q, const Point& r) const
    {
        typedef  typename _DA::RT  RT;
    
        RT  phx;
        RT  phy;
        RT  phw;
        RT  qhx;
        RT  qhy;
        RT  qhw;
        RT  rhx;
        RT  rhy;
        RT  rhw;
    
        dao.get( p, phx, phy, phw);
        dao.get( q, qhx, qhy, qhw);
        dao.get( r, rhx, rhy, rhw);
    
        return( CGAL_static_cast( CGAL_Orientation,
                    CGAL_sign( ( phx*rhw - rhx*phw) * ( qhy*rhw - rhy*qhw)
                             - ( phy*rhw - rhy*phw) * ( qhx*rhw - rhx*qhw))));
    }
};

// Nested type `Ellipse'
template < class _PT, class _DA >
class CGAL__Min_ellipse_2_adapterH2__Ellipse {
  public:
    // typedefs
    typedef  _PT  PT;
    typedef  _DA  DA;

    typedef           CGAL_ConicHPA2< PT, DA>  CT;
    typedef  typename _DA::RT                  RT;

  private:
    // data members
    int  n_boundary_points;                 // number of boundary points
    PT   boundary_point1, boundary_point2;  // two boundary points
    CT   conic1, conic2;                    // two conics
    RT   dr, ds, dt, du, dv, dw;            // the gradient vector

  public:
    // types
    typedef  PT  Point;

    // creation
    CGAL__Min_ellipse_2_adapterH2__Ellipse( const DA& da)
        : conic1( da), conic2( da)
    { }

    void
    set( )
    {
        n_boundary_points = 0;
    }

    void
    set( const Point& p)
    {
        n_boundary_points = 1;
        boundary_point1   = p;
    }

    void
    set( const Point& p, const Point& q)
    {
        n_boundary_points = 2;
        boundary_point1   = p;
        boundary_point2   = q;
    }

    void
    set( const Point& p1, const Point& p2, const Point& p3)
    {
        n_boundary_points = 3;
        conic1.set_ellipse( p1, p2, p3);
    }

    void
    set( const Point& p1, const Point& p2,
         const Point& p3, const Point& p4)
    {
        n_boundary_points = 4;
        CT::set_two_linepairs( p1, p2, p3, p4, conic1, conic2);
        dr = RT( 0);
        ds = conic1.r() * conic2.s() - conic2.r() * conic1.s(),
        dt = conic1.r() * conic2.t() - conic2.r() * conic1.t(),
        du = conic1.r() * conic2.u() - conic2.r() * conic1.u(),
        dv = conic1.r() * conic2.v() - conic2.r() * conic1.v(),
        dw = conic1.r() * conic2.w() - conic2.r() * conic1.w();
    }

    void
    set( const Point&, const Point&,
         const Point&, const Point&, const Point& p5)
    {
        n_boundary_points = 5;
        conic1.set( conic1, conic2, p5);
        conic1.analyse();
    }

    // predicates
    CGAL_Bounded_side
    bounded_side( const Point& p) const
    {
        switch ( n_boundary_points) {
          case 0:
            return( CGAL_ON_UNBOUNDED_SIDE);
          case 1:
            return( ( p == boundary_point1) ?
                           CGAL_ON_BOUNDARY : CGAL_ON_UNBOUNDED_SIDE);
          case 2:
            return(    ( p == boundary_point1)
                    || ( p == boundary_point2)
                    || ( CGAL_are_ordered_along_lineH2( boundary_point1, p,
                                           boundary_point2, conic1.da())) ?
                                CGAL_ON_BOUNDARY : CGAL_ON_UNBOUNDED_SIDE);
          case 3:
          case 5:
            return( conic1.convex_side( p));
          case 4: {
            CT c( conic1.da());
            c.set( conic1, conic2, p);
            c.analyse();
            if ( ! c.is_ellipse()) {
                c.set_ellipse( conic1, conic2);
                c.analyse();
                return( c.convex_side( p)); }
            else {
                int tau_star = -c.vol_derivative( dr, ds, dt, du, dv, dw);
                return( CGAL_static_cast( CGAL_Bounded_side,
                                          CGAL_sign( tau_star))); } }
          default:
            CGAL_optimisation_assertion( ( n_boundary_points >= 0) &&
                                         ( n_boundary_points <= 5) ); }
        // keeps g++ happy
        return( CGAL_Bounded_side( 0));
    }

    bool
    has_on_bounded_side( const Point& p) const
    {
        return( bounded_side( p) == CGAL_ON_BOUNDED_SIDE);
    }

    bool
    has_on_boundary( const Point& p) const
    {
        return( bounded_side( p) == CGAL_ON_BOUNDARY);
    }

    bool
    has_on_unbounded_side( const Point& p) const
    {
        return( bounded_side( p) == CGAL_ON_UNBOUNDED_SIDE);
    }

    bool
    is_empty( ) const
    {
        return( n_boundary_points == 0);
    }

    bool
    is_degenerate( ) const
    {
        return( n_boundary_points < 3);
    }

    // additional operations for checking
    bool
    operator == (
        const CGAL__Min_ellipse_2_adapterH2__Ellipse<_PT,_DA>& e) const
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

    // I/O
    friend
    ostream&
    operator << ( ostream& os,
                  const CGAL__Min_ellipse_2_adapterH2__Ellipse<_PT,_DA>& e)
    {
        const char* const  empty       = "";
        const char* const  pretty_head =
                                 "CGAL_Min_ellipse_2_adapterH2::Ellipse( ";
        const char* const  pretty_sep  = ", ";
        const char* const  pretty_tail = ")";
        const char* const  ascii_sep   = " ";

        const char*  head = empty;
        const char*  sep  = empty;
        const char*  tail = empty;

        switch ( CGAL_get_mode( os)) {
          case CGAL_IO::PRETTY:
            head = pretty_head;
            sep  = pretty_sep;
            tail = pretty_tail;
            break;
          case CGAL_IO::ASCII:
            sep  = ascii_sep;
            break;
          case CGAL_IO::BINARY:
            break;
          default:
            CGAL_optimisation_assertion_msg( false,
                                            "CGAL_get_mode( os) invalid!");
            break; }

        os << head << e.n_boundary_points;
        switch ( e.n_boundary_points) {
          case 0:
            break;
          case 1:
            os << sep << e.boundary_point1;
            break;
          case 2:
            os << sep << e.boundary_point1
               << sep << e.boundary_point2;
            break;
          case 3:
          case 5:
            os << sep << e.conic1;
            break;
          case 4:
            os << sep << e.conic1
               << sep << e.conic2;
            break; }
        os << tail;

        return( os);
    }

    friend
    istream&
    operator >> ( istream& is,
                  CGAL__Min_ellipse_2_adapterH2__Ellipse<_PT,_DA>& e)
    {
        switch ( CGAL_get_mode( is)) {

          case CGAL_IO::PRETTY:
            cerr << endl;
            cerr << "Stream must be in ascii or binary mode" << endl;
            break;

          case CGAL_IO::ASCII:
          case CGAL_IO::BINARY:
            CGAL_read( is, e.n_boundary_points);
            switch ( e.n_boundary_points) {
              case 0:
                break;
              case 1:
                is >> e.boundary_point1;
                break;
              case 2:
                is >> e.boundary_point1
                   >> e.boundary_point2;
                break;
              case 3:
              case 5:
                is >> e.conic1;
                break;
              case 4:
                is >> e.conic1
                   >> e.conic2;
                break; }
            break;

          default:
            CGAL_optimisation_assertion_msg( false,
                                             "CGAL_IO::mode invalid!");
            break; }

        return( is);
    }
};

#endif // CGAL_MIN_ELLIPSE_2_ADAPTERH2_H

// ===== EOF ==================================================================
