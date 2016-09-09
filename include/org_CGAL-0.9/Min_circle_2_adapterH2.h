/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/


// file  : include/CGAL/Min_circle_2_adapterH2.h
// source: web/Min_circle_2.aw
// author: Bernd Gärtner, Sven Schönherr
// $Revision: 3.2 $
// $Date: 1997/06/24 12:42:19 $

#ifndef CGAL_MIN_CIRCLE_2_ADAPTERH2_H
#define CGAL_MIN_CIRCLE_2_ADAPTERH2_H

// Class declarations
// ==================
template < class _PT, class _DA >
class CGAL_Min_circle_2_adapterH2;

template < class _PT, class _DA >
class CGAL__Min_circle_2_adapterH2__Circle;

template < class _Traits >
class CGAL_Min_circle_2;

// Class interface and implementation
// ==================================
// includes
#ifndef CGAL_BASIC_H
#  include <CGAL/basic.h>
#endif
#ifndef CGAL_OPTIMISATION_ASSERTIONS_H
#  include <CGAL/optimisation_assertions.h>
#endif

template < class _PT, class _DA >
class CGAL_Min_circle_2_adapterH2 {
  public:
    // types
    typedef  _PT  PT;
    typedef  _DA  DA;

    // nested types
    typedef  PT                                           Point;
    typedef  CGAL__Min_circle_2_adapterH2__Circle<PT,DA>  Circle;

  private:
    DA      dao;                                    // data accessor object
    Circle  circle;                                 // current circle
    friend  class CGAL_Min_circle_2< CGAL_Min_circle_2_adapterH2<PT,DA> >;

  public:
    // creation
    CGAL_Min_circle_2_adapterH2( DA const& da = DA())
        : dao( da), circle( da)
    { }

    // operations
    CGAL_Orientation
    orientation( Point const& p, Point const& q, Point const& r) const
    {
        typedef  _DA::RT  RT;
    
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

// Nested type `Circle'
template < class _PT, class _DA >
class CGAL__Min_circle_2_adapterH2__Circle {
  public:
    // typedefs
    typedef  _PT  PT;
    typedef  _DA  DA;

    typedef  _DA::RT            RT;
    typedef  CGAL_Quotient<RT>  FT;

  private:
    // data members
    DA  dao;                                // data accessor object

    RT  center_hx;                          // center's hx-coordinate
    RT  center_hy;                          // center's hy-coordinate
    RT  center_hw;                          // center's hw-coordinate
    FT  sqr_rad;                            // squared radius

    // private member functions
    FT
    sqr_dist( RT const& phx, RT const& phy, RT const& phw,
              RT const& qhx, RT const& qhy, RT const& qhw) const
    {
        RT  dhx( phx*qhw - qhx*phw);
        RT  dhy( phy*qhw - qhy*phw);
        RT  dhw( phw*qhw);
        return( FT( dhx*dhx + dhy*dhy, dhw*dhw));
    }

  public:
    // types
    typedef  PT  Point;
    typedef  FT  Distance;

    // creation
    CGAL__Min_circle_2_adapterH2__Circle( DA const& da) : dao( da) { }

    void  set( )
    {
        center_hx =  RT( 0);
        center_hy =  RT( 0);
        center_hw =  RT( 1);
        sqr_rad   = -FT( 1);
    }

    void  set( Point const& p)
    {
        dao.get( p, center_hx, center_hy, center_hw);
        sqr_rad = FT( 0);
    }

    void  set( Point const& p, Point const& q)
    {
        RT  phx;
        RT  phy;
        RT  phw;
        RT  qhx;
        RT  qhy;
        RT  qhw;

        dao.get( p, phx, phy, phw);
        dao.get( q, qhx, qhy, qhw);
        center_hx = ( phx*qhw + qhx*phw);
        center_hy = ( phy*qhw + qhy*phw);
        center_hw = ( phw*qhw * RT( 2));
        sqr_rad   = sqr_dist( phx, phy, phw,
                              center_hx, center_hy, center_hw);
    }

    void  set( Point const& p, Point const& q, Point const& r)
    {
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

        RT  qhx_phx( qhx*phw - phx*qhw);
        RT  qhy_phy( qhy*phw - phy*qhw);    // denominator: qhw*phw

        RT  rhx_phx( rhx*phw - phx*rhw);
        RT  rhy_phy( rhy*phw - phy*rhw);    // denominator: rhw*phw

        RT  phw2( phw*phw);
        RT  qhw2( qhw*qhw);
        RT  rhw2( rhw*rhw);

        RT  p2( phx*phx + phy*phy);         // denominator: phw2

        RT  q2_p2( ( qhx*qhx + qhy*qhy) * phw2 - p2 * qhw2);
                                            // denominator: qhw2*phw2

        RT  r2_p2( ( rhx*rhx + rhy*rhy) * phw2 - p2 * rhw2);
                                            // denominator: rhw2*phw2

        center_hx = q2_p2*rhy_phy * rhw - r2_p2*qhy_phy * qhw;
        center_hy = r2_p2*qhx_phx * qhw - q2_p2*rhx_phx * rhw;
        center_hw = ( qhx_phx*rhy_phy - rhx_phx*qhy_phy)
                      * phw*qhw*rhw * RT( 2);
        sqr_rad   = sqr_dist( phx, phy, phw,
                              center_hx, center_hy, center_hw);
    }

    // predicates
    CGAL_Bounded_side
    bounded_side( Point const& p) const
    {
        RT  phx;
        RT  phy;
        RT  phw;
        dao.get( p, phx, phy, phw);
        return( CGAL_static_cast( CGAL_Bounded_side,
                    CGAL_sign( sqr_dist( phx, phy, phw,
                                         center_hx, center_hy, center_hw)
                               - sqr_rad)));
    }

    bool
    has_on_bounded_side( Point const& p) const
    {
        RT  phx;
        RT  phy;
        RT  phw;
        dao.get( p, phx, phy, phw);
        return( sqr_dist( phx, phy, phw,
                          center_hx, center_hy, center_hw) < sqr_rad);
    }

    bool
    has_on_boundary( Point const& p) const
    {
        RT  phx;
        RT  phy;
        RT  phw;
        dao.get( p, phx, phy, phw);
        return( sqr_dist( phx, phy, phw,
                          center_hx, center_hy, center_hw) == sqr_rad);
    }

    bool
    has_on_unbounded_side( Point const& p) const
    {
        RT  phx;
        RT  phy;
        RT  phw;
        dao.get( p, phx, phy, phw);
        return( sqr_rad < sqr_dist( phx, phy, phw,
                                    center_hx, center_hy, center_hw));
    }

    bool
    is_empty( ) const
    {
        return( CGAL_is_negative( sqr_rad));
    }

    bool
    is_degenerate( ) const
    {
        return( ! CGAL_is_positive( sqr_rad));
    }

    // additional operations for checking
    bool
    operator == (
        CGAL__Min_circle_2_adapterH2__Circle<_PT,_DA> const& c) const
    {
        return( ( center_hx*c.center_hw == c.center_hx*center_hw) &&
                ( center_hy*c.center_hw == c.center_hy*center_hw) &&
                ( sqr_rad  == c.sqr_rad ) );
    }

    Point
    center( ) const
    {
        Point  p;
        dao.set( p, center_hx, center_hy, center_hw);
        return( p);
    }

    Distance const&
    squared_radius( ) const
    {
        return( sqr_rad);
    }

    // I/O
    friend
    ostream&
    operator << ( ostream& os,
                  CGAL__Min_circle_2_adapterH2__Circle<_PT,_DA> const& c)
    {
        switch ( CGAL_get_mode( os)) {

          case CGAL_IO::PRETTY:
            os << "CGAL_Min_circle_2_adapterH2::Circle( "
               << c.center_hx << ", "
               << c.center_hy << ", "
               << c.center_hw << ", "
               << c.sqr_rad   << ')';
            break;

          case CGAL_IO::ASCII:
            os << c.center_hx << ' '
               << c.center_hy << ' '
               << c.center_hw << ' '
               << c.sqr_rad;
            break;

          case CGAL_IO::BINARY:
            CGAL_write( os, c.center_hx);
            CGAL_write( os, c.center_hy);
            CGAL_write( os, c.center_hw);
            CGAL_write( os, c.sqr_rad);
            break;

          default:
            CGAL_optimisation_assertion_msg( false,
                                            "CGAL_get_mode( os) invalid!");
            break; }

        return( os);
    }

    friend
    istream&
    operator >> ( istream& is,
                  CGAL__Min_circle_2_adapterH2__Circle<_PT,_DA>& c)
    {
        switch ( CGAL_get_mode( is)) {

          case CGAL_IO::PRETTY:
            cerr << endl;
            cerr << "Stream must be in ascii or binary mode" << endl;
            break;

          case CGAL_IO::ASCII:
            is >> c.center_hx >> c.center_hy >> c.center_hw >> c.sqr_rad;
            break;

          case CGAL_IO::BINARY:
            CGAL_read( is, c.center_hx);
            CGAL_read( is, c.center_hy);
            CGAL_read( is, c.center_hw);
            CGAL_read( is, c.sqr_rad);
            break;

          default:
            CGAL_optimisation_assertion_msg( false,
                                             "CGAL_IO::mode invalid!");
            break; }

        return( is);
    }
};

#endif // CGAL_MIN_CIRCLE_2_ADAPTERH2_H

// ===== EOF ==================================================================
