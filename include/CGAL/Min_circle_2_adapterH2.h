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
// file          : include/CGAL/Min_circle_2_adapterH2.h
// package       : Min_circle_2 (3.5.3)
// chapter       : $CGAL_Chapter: Geometric Optimisation $
//
// source        : web/Optimisation/Min_circle_2.aw
// revision      : $Revision: 5.22 $
// revision_date : $Date: 1999/12/20 19:06:47 $
// author(s)     : Sven Sch�nherr
//                 Bernd G�rtner
//
// coordinator   : ETH Z�rich (Bernd G�rtner)
//
// implementation: traits class adapter for 2D Smallest Enclosing Circle
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_MIN_CIRCLE_2_ADAPTERH2_H
#define CGAL_MIN_CIRCLE_2_ADAPTERH2_H

// includes
#ifndef CGAL_OPTIMISATION_BASIC_H
#  include <CGAL/Optimisation/basic.h>
#endif

CGAL_BEGIN_NAMESPACE

// Class declarations
// ==================
template < class _Traits >
class Min_circle_2;

template < class _PT, class _DA >
class Min_circle_2_adapterH2;

template < class _PT, class _DA >
class _Min_circle_2_adapterH2__Circle;

// Class interface and implementation
// ==================================
template < class _PT, class _DA >
class Min_circle_2_adapterH2 {
  public:
    // types
    typedef  _PT  PT;
    typedef  _DA  DA;

    // nested types
    typedef  PT                                           Point;
    typedef  CGAL::_Min_circle_2_adapterH2__Circle<PT,DA>  Circle;

  private:
    DA      dao;                                    // data accessor object
    Circle  circle;                                 // current circle
    friend  class CGAL::Min_circle_2< CGAL::Min_circle_2_adapterH2<PT,DA> >;

  public:
    // creation
    Min_circle_2_adapterH2( const DA& da = DA())
        : dao( da), circle( da)
    { }

    // operations
    CGAL::Orientation
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
    
        return( CGAL_static_cast( CGAL::Orientation,
                    CGAL::sign( ( phx*rhw - rhx*phw) * ( qhy*rhw - rhy*qhw)
                             - ( phy*rhw - rhy*phw) * ( qhx*rhw - rhx*qhw))));
    }
};

// Nested type `Circle'
template < class _PT, class _DA >
std::ostream&
operator << ( std::ostream&,
              const CGAL::_Min_circle_2_adapterH2__Circle<_PT,_DA>&);

template < class _PT, class _DA >
std::istream&
operator >> ( std::istream&,
              CGAL::_Min_circle_2_adapterH2__Circle<_PT,_DA>&);

template < class _PT, class _DA >
class _Min_circle_2_adapterH2__Circle {
  public:
    // typedefs
    typedef  _PT  PT;
    typedef  _DA  DA;

    typedef  typename _DA::RT             RT;
    typedef           CGAL::Quotient<RT>  FT;

  private:
    // data members
    DA  dao;                                // data accessor object

    RT  center_hx;                          // center's hx-coordinate
    RT  center_hy;                          // center's hy-coordinate
    RT  center_hw;                          // center's hw-coordinate
    FT  sqr_rad;                            // squared radius

    // private member functions
    FT
    sqr_dist( const RT& phx, const RT& phy, const RT& phw,
              const RT& qhx, const RT& qhy, const RT& qhw) const
    {
        RT  dhx( phx*qhw - qhx*phw);
        RT  dhy( phy*qhw - qhy*phw);
        RT  dhw( phw*qhw);
        return( FT( dhx*dhx + dhy*dhy, dhw*dhw));
    }

    friend  std::ostream&  operator << CGAL_NULL_TMPL_ARGS ( std::ostream&,
        const CGAL::_Min_circle_2_adapterH2__Circle<_PT,_DA>&);

    friend  std::istream&  operator >> CGAL_NULL_TMPL_ARGS ( std::istream&,
        CGAL::_Min_circle_2_adapterH2__Circle<_PT,_DA>&);

  public:
    // types
    typedef  PT  Point;
    typedef  FT  Distance;

    // creation
    _Min_circle_2_adapterH2__Circle( const DA& da) : dao( da) { }

    void  set( )
    {
        center_hx =  RT( 0);
        center_hy =  RT( 0);
        center_hw =  RT( 1);
        sqr_rad   = -FT( 1);
    }

    void  set( const Point& p)
    {
        dao.get( p, center_hx, center_hy, center_hw);
        sqr_rad = FT( 0);
    }

    void  set( const Point& p, const Point& q)
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

    void  set( const Point& p, const Point& q, const Point& r)
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
    CGAL::Bounded_side
    bounded_side( const Point& p) const
    {
        RT  phx;
        RT  phy;
        RT  phw;
        dao.get( p, phx, phy, phw);
        return( CGAL::Bounded_side( CGAL::sign(
            sqr_rad - sqr_dist( phx, phy, phw,
                                center_hx, center_hy, center_hw))));
    }

    bool
    has_on_bounded_side( const Point& p) const
    {
        RT  phx;
        RT  phy;
        RT  phw;
        dao.get( p, phx, phy, phw);
        return( sqr_dist( phx, phy, phw,
                          center_hx, center_hy, center_hw) < sqr_rad);
    }

    bool
    has_on_boundary( const Point& p) const
    {
        RT  phx;
        RT  phy;
        RT  phw;
        dao.get( p, phx, phy, phw);
        return( sqr_dist( phx, phy, phw,
                          center_hx, center_hy, center_hw) == sqr_rad);
    }

    bool
    has_on_unbounded_side( const Point& p) const
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
        return( CGAL::is_negative( sqr_rad));
    }

    bool
    is_degenerate( ) const
    {
        return( ! CGAL::is_positive( sqr_rad));
    }

    // additional operations for checking
    bool
    operator == (
        const CGAL::_Min_circle_2_adapterH2__Circle<_PT,_DA>& c) const
    {
        return( ( center_hx*c.center_hw == c.center_hx*center_hw) &&
                ( center_hy*c.center_hw == c.center_hy*center_hw) &&
                ( sqr_rad  == c.sqr_rad ) );
    }

    bool
    operator != (
        const CGAL::_Min_circle_2_adapterH2__Circle<_PT,_DA>& c) const
    {
        return( ! ( *this == c));
    }

    Point
    center( ) const
    {
        Point  p;
        dao.set( p, center_hx, center_hy, center_hw);
        return( p);
    }

    const Distance&
    squared_radius( ) const
    {
        return( sqr_rad);
    }
};

// I/O
template < class _PT, class _DA >
std::ostream&
operator << ( std::ostream& os,
              const CGAL::_Min_circle_2_adapterH2__Circle<_PT,_DA>& c)
{
    switch ( CGAL::get_mode( os)) {

      case CGAL::IO::PRETTY:
        os << "CGAL::Min_circle_2_adapterH2::Circle( "
           << c.center_hx << ", "
           << c.center_hy << ", "
           << c.center_hw << ", "
           << c.sqr_rad   << ')';
        break;

      case CGAL::IO::ASCII:
        os << c.center_hx << ' '
           << c.center_hy << ' '
           << c.center_hw << ' '
           << c.sqr_rad;
        break;

      case CGAL::IO::BINARY:
        CGAL::write( os, c.center_hx);
        CGAL::write( os, c.center_hy);
        CGAL::write( os, c.center_hw);
        CGAL::write( os, c.sqr_rad);
        break;

      default:
        CGAL_optimisation_assertion_msg( false,
                                        "CGAL::get_mode( os) invalid!");
        break; }

    return( os);
}

template < class _PT, class _DA >
std::istream&
operator >> ( std::istream& is,
              CGAL::_Min_circle_2_adapterH2__Circle<_PT,_DA>& c)
{
    switch ( CGAL::get_mode( is)) {

      case CGAL::IO::PRETTY:
        cerr << std::endl;
        cerr << "Stream must be in ascii or binary mode" << std::endl;
        break;

      case CGAL::IO::ASCII:
        is >> c.center_hx >> c.center_hy >> c.center_hw >> c.sqr_rad;
        break;

      case CGAL::IO::BINARY:
        CGAL::read( is, c.center_hx);
        CGAL::read( is, c.center_hy);
        CGAL::read( is, c.center_hw);
        CGAL::read( is, c.sqr_rad);
        break;

      default:
        CGAL_optimisation_assertion_msg( false,
                                         "CGAL::IO::mode invalid!");
        break; }

    return( is);
}

CGAL_END_NAMESPACE

#endif // CGAL_MIN_CIRCLE_2_ADAPTERH2_H

// ===== EOF ==================================================================
