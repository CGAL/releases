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


// file  : include/CGAL/Min_circle_2_adapterC2.h
// source: web/Min_circle_2.aw
// author: Bernd Gärtner, Sven Schönherr
// $Revision: 3.2 $
// $Date: 1997/06/24 12:42:19 $

#ifndef CGAL_MIN_CIRCLE_2_ADAPTERC2_H
#define CGAL_MIN_CIRCLE_2_ADAPTERC2_H

// Class declarations
// ==================
template < class _PT, class _DA >
class CGAL_Min_circle_2_adapterC2;

template < class _PT, class _DA >
class CGAL__Min_circle_2_adapterC2__Circle;

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
class CGAL_Min_circle_2_adapterC2 {
  public:
    // types
    typedef  _PT  PT;
    typedef  _DA  DA;

    // nested types
    typedef  PT                                           Point;
    typedef  CGAL__Min_circle_2_adapterC2__Circle<PT,DA>  Circle;

  private:
    DA      dao;                                    // data accessor object
    Circle  circle;                                 // current circle
    friend  class CGAL_Min_circle_2< CGAL_Min_circle_2_adapterC2<PT,DA> >;

  public:
    // creation
    CGAL_Min_circle_2_adapterC2( DA const& da = DA())
        : dao( da), circle( da)
    { }

    // operations
    CGAL_Orientation
    orientation( Point const& p, Point const& q, Point const& r) const
    {
        typedef  _DA::FT  FT;
    
        FT  px;
        FT  py;
        FT  qx;
        FT  qy;
        FT  rx;
        FT  ry;
    
        dao.get( p, px, py);
        dao.get( q, qx, qy);
        dao.get( r, rx, ry);
    
        return( CGAL_static_cast( CGAL_Orientation,
                    CGAL_sign( ( px-rx) * ( qy-ry) - ( py-ry) * ( qx-rx))));
    }
};

// Nested type `Circle'
template < class _PT, class _DA >
class CGAL__Min_circle_2_adapterC2__Circle {
  public:
    // typedefs
    typedef  _PT  PT;
    typedef  _DA  DA;

    typedef  _DA::FT  FT;

  private:
    // data members
    DA  dao;                                // data accessor object

    FT  center_x;                           // center's x-coordinate
    FT  center_y;                           // center's y-coordinate
    FT  sqr_rad;                            // squared radius

    // private member functions
    FT
    sqr_dist( FT const& px, FT const& py, FT const& qx, FT const& qy) const
    {
        FT  dx( px - qx);
        FT  dy( py - qy);
        return( dx*dx + dy*dy);
    }

  public:
    // types
    typedef  PT  Point;
    typedef  FT  Distance;

    // creation
    CGAL__Min_circle_2_adapterC2__Circle( DA const& da) : dao( da) { }

    void  set( )
    {
        center_x =  FT( 0);
        center_y =  FT( 0);
        sqr_rad  = -FT( 1);
    }

    void  set( Point const& p)
    {
        dao.get( p, center_x, center_y);
        sqr_rad = FT( 0);
    }

    void  set( Point const& p, Point const& q)
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

    void  set( Point const& p, Point const& q, Point const& r)
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
    CGAL_Bounded_side
    bounded_side( Point const& p) const
    {
        FT  px;
        FT  py;
        dao.get( p, px, py);
        return( CGAL_static_cast( CGAL_Bounded_side,
            CGAL_sign( sqr_dist( px, py, center_x, center_y) - sqr_rad)));
    }

    bool
    has_on_bounded_side( Point const& p) const
    {
        FT  px;
        FT  py;
        dao.get( p, px, py);
        return( sqr_dist( px, py, center_x, center_y) < sqr_rad);
    }

    bool
    has_on_boundary( Point const& p) const
    {
        FT  px;
        FT  py;
        dao.get( p, px, py);
        return( sqr_dist( px, py, center_x, center_y) == sqr_rad);
    }

    bool
    has_on_unbounded_side( Point const& p) const
    {
        FT  px;
        FT  py;
        dao.get( p, px, py);
        return( sqr_rad < sqr_dist( px, py, center_x, center_y));
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
        CGAL__Min_circle_2_adapterC2__Circle<_PT,_DA> const& c) const
    {
        return( ( center_x == c.center_x) &&
                ( center_y == c.center_y) &&
                ( sqr_rad  == c.sqr_rad ) );
    }

    Point
    center( ) const
    {
        Point  p;
        dao.set( p, center_x, center_y);
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
                  CGAL__Min_circle_2_adapterC2__Circle<_PT,_DA> const& c)
    {
        switch ( CGAL_get_mode( os)) {

          case CGAL_IO::PRETTY:
            os << "CGAL_Min_circle_2_adapterC2::Circle( "
               << c.center_x << ", "
               << c.center_y << ", "
               << c.sqr_rad  << ')';
            break;

          case CGAL_IO::ASCII:
            os << c.center_x << ' ' << c.center_y << ' ' << c.sqr_rad;
            break;

          case CGAL_IO::BINARY:
            CGAL_write( os, c.center_x);
            CGAL_write( os, c.center_y);
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
                  CGAL__Min_circle_2_adapterC2__Circle<_PT,_DA>& c)
    {
        switch ( CGAL_get_mode( is)) {

          case CGAL_IO::PRETTY:
            cerr << endl;
            cerr << "Stream must be in ascii or binary mode" << endl;
            break;

          case CGAL_IO::ASCII:
            is >> c.center_x >> c.center_y >> c.sqr_rad;
            break;

          case CGAL_IO::BINARY:
            CGAL_read( is, c.center_x);
            CGAL_read( is, c.center_y);
            CGAL_read( is, c.sqr_rad);
            break;

          default:
            CGAL_optimisation_assertion_msg( false,
                                             "CGAL_IO::mode invalid!");
            break; }

        return( is);
    }
};

#endif // CGAL_MIN_CIRCLE_2_ADAPTERC2_H

// ===== EOF ==================================================================
