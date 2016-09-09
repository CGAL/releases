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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/Min_circle_2_adapterC2.h
// package       : Min_circle_2 (3.12)
// chapter       : Geometric Optimisation
//
// source        : web/Min_circle_2.aw
// revision      : $Revision: 1.7 $
// revision_date : $Date: 2001/07/17 11:24:35 $
//
// author(s)     : Sven Schönherr, Bernd Gärtner
// coordinator   : ETH Zürich (Bernd Gärtner)
//
// implementation: traits class adapter for 2D Smallest Enclosing Circle
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_MIN_CIRCLE_2_ADAPTERC2_H
#define CGAL_MIN_CIRCLE_2_ADAPTERC2_H

// includes
#ifndef CGAL_OPTIMISATION_BASIC_H
#  include <CGAL/Optimisation/basic.h>
#endif

CGAL_BEGIN_NAMESPACE

// Class declarations
// ==================
template < class Traits_ >
class Min_circle_2;

template < class PT_, class DA_ >
class Min_circle_2_adapterC2;

template < class PT_, class DA_ >
class _Min_circle_2_adapterC2__Circle;

// Class interface and implementation
// ==================================
template < class PT_, class DA_ >
class Min_circle_2_adapterC2 {
  public:
    // types
    typedef  PT_  PT;
    typedef  DA_  DA;

    // nested types
    typedef  PT                                            Point;
    typedef  CGAL::_Min_circle_2_adapterC2__Circle<PT,DA>  Circle;

  private:
    DA      dao;                                    // data accessor object
    Circle  circle;                                 // current circle
    friend  class CGAL::Min_circle_2< CGAL::Min_circle_2_adapterC2<PT,DA> >;

  public:
    // creation
    Min_circle_2_adapterC2( const DA& da = DA())
        : dao( da), circle( da)
    { }

    // operations
    CGAL::Orientation
    orientation( const Point& p, const Point& q, const Point& r) const
    {
        typedef  typename DA_::FT  FT;
    
        FT  px;
        FT  py;
        FT  qx;
        FT  qy;
        FT  rx;
        FT  ry;
    
        dao.get( p, px, py);
        dao.get( q, qx, qy);
        dao.get( r, rx, ry);
    
        return( static_cast< CGAL::Orientation>(
                  CGAL_NTS sign( ( px-rx) * ( qy-ry) - ( py-ry) * ( qx-rx))));
    }
};

// Nested type `Circle'
template < class PT_, class DA_ >
std::ostream&
operator << ( std::ostream&,
              const CGAL::_Min_circle_2_adapterC2__Circle<PT_,DA_>&);

template < class PT_, class DA_ >
std::istream&
operator >> ( std::istream&,
              CGAL::_Min_circle_2_adapterC2__Circle<PT_,DA_>&);

template < class PT_, class DA_ >
class _Min_circle_2_adapterC2__Circle {
  public:
    // typedefs
    typedef  PT_  PT;
    typedef  DA_  DA;

    typedef  typename DA_::FT  FT;

  private:
    // data members
    DA  dao;                                // data accessor object

    FT  center_x;                           // center's x-coordinate
    FT  center_y;                           // center's y-coordinate
    FT  sqr_rad;                            // squared radius

    // private member functions
    FT
    sqr_dist( const FT& px, const FT& py, const FT& qx, const FT& qy) const
    {
        FT  dx( px - qx);
        FT  dy( py - qy);
        return( dx*dx + dy*dy);
    }

    friend  std::ostream&  operator << CGAL_NULL_TMPL_ARGS ( std::ostream&,
        const CGAL::_Min_circle_2_adapterC2__Circle<PT_,DA_>&);

    friend  std::istream&  operator >> CGAL_NULL_TMPL_ARGS ( std::istream&,
        CGAL::_Min_circle_2_adapterC2__Circle<PT_,DA_>&);

  public:
    // types
    typedef  PT  Point;
    typedef  FT  Distance;

    // creation
    _Min_circle_2_adapterC2__Circle( const DA& da) : dao( da) { }

    void  set( )
    {
        center_x =  FT( 0);
        center_y =  FT( 0);
        sqr_rad  = -FT( 1);
    }

    void  set( const Point& p)
    {
        dao.get( p, center_x, center_y);
        sqr_rad = FT( 0);
    }

    void  set( const Point& p, const Point& q)
    {
        FT  px;
        FT  py;
        FT  qx;
        FT  qy;

        dao.get( p, px, py);
        dao.get( q, qx, qy);

        center_x = ( px+qx) / FT( 2);
        center_y = ( py+qy) / FT( 2);
        sqr_rad  = sqr_dist( px, py, center_x, center_y);
    }

    void  set( const Point& p, const Point& q, const Point& r)
    {
        FT  px;
        FT  py;
        FT  qx;
        FT  qy;
        FT  rx;
        FT  ry;

        dao.get( p, px, py);
        dao.get( q, qx, qy);
        dao.get( r, rx, ry);

        FT  qx_px( qx - px);
        FT  qy_py( qy - py);
        FT  rx_px( rx - px);
        FT  ry_py( ry - py);

        FT  p2   ( px*px + py*py);
        FT  q2_p2( qx*qx + qy*qy - p2);
        FT  r2_p2( rx*rx + ry*ry - p2);
        FT  denom( ( qx_px*ry_py - rx_px*qy_py) * FT( 2));

        center_x = ( q2_p2*ry_py - r2_p2*qy_py) / denom;
        center_y = ( r2_p2*qx_px - q2_p2*rx_px) / denom;
        sqr_rad  = sqr_dist( px, py, center_x, center_y);
    }

    // predicates
    CGAL::Bounded_side
    bounded_side( const Point& p) const
    {
        FT  px;
        FT  py;
        dao.get( p, px, py);
        return( CGAL::Bounded_side(
         CGAL_NTS sign( sqr_rad - sqr_dist( px, py, center_x, center_y))));
    }

    bool
    has_on_bounded_side( const Point& p) const
    {
        FT  px;
        FT  py;
        dao.get( p, px, py);
        return( sqr_dist( px, py, center_x, center_y) < sqr_rad);
    }

    bool
    has_on_boundary( const Point& p) const
    {
        FT  px;
        FT  py;
        dao.get( p, px, py);
        return( sqr_dist( px, py, center_x, center_y) == sqr_rad);
    }

    bool
    has_on_unbounded_side( const Point& p) const
    {
        FT  px;
        FT  py;
        dao.get( p, px, py);
        return( sqr_rad < sqr_dist( px, py, center_x, center_y));
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
        const CGAL::_Min_circle_2_adapterC2__Circle<PT_,DA_>& c) const
    {
        return( ( center_x == c.center_x) &&
                ( center_y == c.center_y) &&
                ( sqr_rad  == c.sqr_rad ) );
    }

    bool
    operator != (
        const CGAL::_Min_circle_2_adapterC2__Circle<PT_,DA_>& c) const
    {
        return( ! ( *this == c));
    }

    Point
    center( ) const
    {
        Point  p;
        dao.set( p, center_x, center_y);
        return( p);
    }

    const Distance&
    squared_radius( ) const
    {
        return( sqr_rad);
    }
};

// I/O
template < class PT_, class DA_ >
std::ostream&
operator << ( std::ostream& os,
              const CGAL::_Min_circle_2_adapterC2__Circle<PT_,DA_>& c)
{
    switch ( CGAL::get_mode( os)) {

      case CGAL::IO::PRETTY:
        os << "CGAL::Min_circle_2_adapterC2::Circle( "
           << c.center_x << ", "
           << c.center_y << ", "
           << c.sqr_rad  << ')';
        break;

      case CGAL::IO::ASCII:
        os << c.center_x << ' ' << c.center_y << ' ' << c.sqr_rad;
        break;

      case CGAL::IO::BINARY:
        CGAL::write( os, c.center_x);
        CGAL::write( os, c.center_y);
        CGAL::write( os, c.sqr_rad);
        break;

      default:
        CGAL_optimisation_assertion_msg( false,
                                         "CGAL::get_mode( os) invalid!");
        break; }

    return( os);
}

template < class PT_, class DA_ >
std::istream&
operator >> ( std::istream& is,
              CGAL::_Min_circle_2_adapterC2__Circle<PT_,DA_>& c)
{
    switch ( CGAL::get_mode( is)) {

      case CGAL::IO::PRETTY:
        cerr << std::endl;
        cerr << "Stream must be in ascii or binary mode" << std::endl;
        break;

      case CGAL::IO::ASCII:
        is >> c.center_x >> c.center_y >> c.sqr_rad;
        break;

      case CGAL::IO::BINARY:
        CGAL::read( is, c.center_x);
        CGAL::read( is, c.center_y);
        CGAL::read( is, c.sqr_rad);
        break;

      default:
        CGAL_optimisation_assertion_msg( false,
                                         "CGAL::IO::mode invalid!");
        break; }

    return( is);
}

CGAL_END_NAMESPACE

#endif // CGAL_MIN_CIRCLE_2_ADAPTERC2_H

// ===== EOF ==================================================================
