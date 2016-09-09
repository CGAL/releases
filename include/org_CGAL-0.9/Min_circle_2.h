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


// file  : include/CGAL/Min_circle_2.h
// source: web/Min_circle_2.aw
// author: Bernd Gärtner, Sven Schönherr
// $Revision: 3.1 $
// $Date: 1997/06/23 13:23:20 $

#ifndef CGAL_MIN_CIRCLE_2_H
#define CGAL_MIN_CIRCLE_2_H

// Class declaration
// =================
template < class _Traits >
class CGAL_Min_circle_2;

// Class interface
// ===============
// includes
#ifndef CGAL_RANDOM_H
#  include <CGAL/Random.h>
#endif
#ifndef CGAL_OPTIMISATION_ASSERTIONS_H
#  include <CGAL/optimisation_assertions.h>
#endif
#ifndef CGAL_OPTIMISATION_MISC_H
#  include <CGAL/optimisation_misc.h>
#endif
#include <list.h>
#include <vector.h>
#include <algo.h>
#include <iostream.h>

template < class _Traits >
class CGAL_Min_circle_2 {
  public:
    // types
    typedef           _Traits                      Traits;
    typedef typename  _Traits::Point               Point;
    typedef typename  _Traits::Circle              Circle;
    typedef typename  list<Point>::const_iterator  Point_iterator;
    typedef           const Point *                Support_point_iterator;
    
    /**************************************************************************
    WORKAROUND: The GNU compiler (g++ 2.7.2[.*]) does not accept types
    with scope operator as argument type or return type in class template
    member functions. Therefore, all member functions are implemented in
    the class interface.
    
    // creation
    CGAL_Min_circle_2( const Point*  first,
                       const Point*  last,
                       bool          randomize = false,
                       CGAL_Random&  random    = CGAL_random,
                       Traits const& traits    = Traits());
    CGAL_Min_circle_2( list<Point>::const_iterator first,
                       list<Point>::const_iterator last,
                       bool          randomize = false,
                       CGAL_Random&  random    = CGAL_random,
                       Traits const& traits    = Traits());
    CGAL_Min_circle_2( istream_iterator<Point,ptrdiff_t> first,
                       istream_iterator<Point,ptrdiff_t> last,
                       bool          randomize = false,
                       CGAL_Random&  random    = CGAL_random,
                       Traits const& traits    = Traits())
    CGAL_Min_circle_2( Traits const& traits = Traits());
    CGAL_Min_circle_2( Point  const& p,
                       Traits const& traits = Traits());
    CGAL_Min_circle_2( Point  const& p,
                       Point  const& q,
                       Traits const& traits = Traits());
    CGAL_Min_circle_2( Point  const& p1,
                       Point  const& p2,
                       Point  const& p3,
                       Traits const& traits = Traits());
    ~CGAL_Min_circle_2( );
    
    // access functions
    int  number_of_points        ( ) const;
    int  number_of_support_points( ) const;
    
    Point_iterator  points_begin( ) const;
    Point_iterator  points_end  ( ) const;
    
    Support_point_iterator  support_points_begin( ) const;
    Support_point_iterator  support_points_end  ( ) const;
    
    Point const&  support_point( int i) const;
    
    Circle const&  circle( ) const;
    
    // predicates
    CGAL_Bounded_side  bounded_side( Point const& p) const;
    bool  has_on_bounded_side      ( Point const& p) const;
    bool  has_on_boundary          ( Point const& p) const;
    bool  has_on_unbounded_side    ( Point const& p) const;
    
    bool  is_empty     ( ) const;
    bool  is_degenerate( ) const;
    
    // modifiers
    void  insert( Point const& p);
    void  insert( const Point* first,
                  const Point* last );
    void  insert( list<Point>::const_iterator first,
                  list<Point>::const_iterator last );
    void  insert( istream_iterator<Point,ptrdiff_t> first,
                  istream_iterator<Point,ptrdiff_t> last );
    void  clear( );
    
    // validity check
    bool  is_valid( bool verbose = false, int level = 0) const;
    
    // miscellaneous
    Traits const&  traits( ) const;
    **************************************************************************/

  private:
    // private data members
    Traits       tco;                           // traits class object
    list<Point>  points;                        // doubly linked list of points
    int          n_support_points;              // number of support points
    Point*       support_points;                // array of support points
    

    // copying and assignment not allowed!
    CGAL_Min_circle_2( CGAL_Min_circle_2<_Traits> const&);
    CGAL_Min_circle_2<_Traits>&
        operator = ( CGAL_Min_circle_2<_Traits> const&);

// ============================================================================

// Class implementation
// ====================

  public:
    // Access functions and predicates
    // -------------------------------
    // #points and #support points
    inline
    int
    number_of_points( ) const
    {
        return( points.size());
    }
    
    inline
    int
    number_of_support_points( ) const
    {
        return( n_support_points);
    }

    // is_... predicates
    inline
    bool
    is_empty( ) const
    {
        return( number_of_support_points() == 0);
    }
    
    inline
    bool
    is_degenerate( ) const
    {
        return( number_of_support_points() <  2);
    }

    // access to points and support points
    inline
    Point_iterator
    points_begin( ) const
    {
        return( points.begin());
    }
    
    inline
    Point_iterator
    points_end( ) const
    {
        return( points.end());
    }
    
    inline
    Support_point_iterator
    support_points_begin( ) const
    {
        return( support_points);
    }
    
    inline
    Support_point_iterator
    support_points_end( ) const
    {
        return( support_points+n_support_points);
    }
    
    // random access for support points
    inline
    Point const&
    support_point( int i) const
    {
        CGAL_optimisation_precondition( (i >= 0) &&
                                        (i <  number_of_support_points()));
        return( support_points[ i]);
    }
    // circle
    inline
    Circle const&
    circle( ) const
    {
        return( tco.circle);
    }
    

    // in-circle test predicates
    inline
    CGAL_Bounded_side
    bounded_side( Point const& p) const
    {
        return( tco.circle.bounded_side( p));
    }
    
    inline
    bool
    has_on_bounded_side( Point const& p) const
    {
        return( tco.circle.has_on_bounded_side( p));
    }
    
    inline
    bool
    has_on_boundary( Point const& p) const
    {
        return( tco.circle.has_on_boundary( p));
    }
    
    inline
    bool
    has_on_unbounded_side( Point const& p) const
    {
        return( tco.circle.has_on_unbounded_side( p));
    }

  private:
    // Privat member functions
    // -----------------------
    // compute_circle
    inline
    void
    compute_circle( )
    {
        switch ( n_support_points) {
          case 3:
            tco.circle.set( support_points[ 0],
                            support_points[ 1],
                            support_points[ 2]);
            break;
          case 2:
            tco.circle.set( support_points[ 0], support_points[ 1]);
            break;
          case 1:
            tco.circle.set( support_points[ 0]);
            break;
          case 0:
            tco.circle.set( );
            break;
          default:
            CGAL_optimisation_assertion( ( n_support_points >= 0) &&
                                         ( n_support_points <= 3) ); }
    }

    void
    mc( Point_iterator const& last, int n_sp)
    {
        // compute circle through support points
        n_support_points = n_sp;
        compute_circle();
        if ( n_sp == 3) return;
    
        // test first n points
        list<Point>::iterator  point_iter( points.begin());
        for ( ; last != point_iter; ) {
            Point const& p( *point_iter);
    
            // p not in current circle?
            if ( has_on_unbounded_side( p)) {
    
                // recursive call with p as additional support point
                support_points[ n_sp] = p;
                mc( point_iter, n_sp+1);
    
                // move current point to front
                if ( point_iter != points.begin()) {            // p not first?
                    points.push_front( p);
                    points.erase( point_iter++); }
                else
                    ++point_iter; }
            else
                ++point_iter; }
    }

  public:
    // Constructors
    // ------------
    // STL-like constructor for C array and vector<Point>
    CGAL_Min_circle_2( const Point*  first,
                       const Point*  last,
                       bool          randomize = false,
                       CGAL_Random&  random    = CGAL_random,
                       Traits const& traits    = Traits())
        : tco( traits)
    {
        // allocate support points' array
        support_points = new Point[ 3];
    
        // range not empty?
        if ( ( last-first) > 0) {
    
            // store points
            if ( randomize) {
    
                // shuffle points at random
                vector<Point> v( first, last);
                random_shuffle( v.begin(), v.end(), random);
                copy( v.begin(), v.end(), back_inserter( points)); }
            else
                copy( first, last, back_inserter( points)); }
    
        // compute mc
        mc( points.end(), 0);
    }
    
    // STL-like constructor for list<Point>
    CGAL_Min_circle_2( list<Point>::const_iterator first,
                       list<Point>::const_iterator last,
                       bool          randomize = false,
                       CGAL_Random&  random    = CGAL_random,
                       Traits const& traits    = Traits())
        : tco( traits)
    {
        // allocate support points' array
        support_points = new Point[ 3];
    
        // compute number of points
        list<Point>::size_type n = 0;
        CGAL__distance( first, last, n);
        if ( n > 0) {
    
            // store points
            if ( randomize) {
    
                // shuffle points at random
                vector<Point> v;
                v.reserve( n);
                copy( first, last, back_inserter( v));
                random_shuffle( v.begin(), v.end(), random);
                copy( v.begin(), v.end(), back_inserter( points)); }
            else
                copy( first, last, back_inserter( points)); }
    
        // compute mc
        mc( points.end(), 0);
    }
    
    // STL-like constructor for input stream iterator istream_iterator<Point>
    CGAL_Min_circle_2( istream_iterator<Point,ptrdiff_t>  first,
                       istream_iterator<Point,ptrdiff_t>  last,
                       bool          randomize = false,
                       CGAL_Random&  random    = CGAL_random,
                       Traits const& traits    = Traits())
        : tco( traits)
    {
        // allocate support points' array
        support_points = new Point[ 3];
    
        // range not empty?
        if ( first != last) {
    
            // store points
            if ( randomize) {
    
                // shuffle points at random
                vector<Point> v;
                copy( first, last, back_inserter( v));
                random_shuffle( v.begin(), v.end(), random);
                copy( v.begin(), v.end(), back_inserter( points)); }
            else
                copy( first, last, back_inserter( points)); }
    
        // compute mc
        mc( points.end(), 0);
    }
    
    
    // default constructor
    inline
    CGAL_Min_circle_2( Traits const& traits = Traits())
        : tco( traits), n_support_points( 0)
    {
        // allocate support points' array
        support_points = new Point[ 3];
    
        // initialize circle
        tco.circle.set();
    
        CGAL_optimisation_postcondition( is_empty());
    }
    
    // constructor for one point
    inline
    CGAL_Min_circle_2( Point const& p, Traits const& traits = Traits())
        : tco( traits), points( 1, p), n_support_points( 1)
    {
        // allocate support points' array
        support_points = new Point[ 3];
    
        // initialize circle
        support_points[ 0] = p;
        tco.circle.set( p);
    
        CGAL_optimisation_postcondition( is_degenerate());
    }
    
    // constructor for two points
    inline
    CGAL_Min_circle_2( Point const& p1,
                       Point const& p2,
                       Traits const& traits = Traits())
        : tco( traits)
    {
        // allocate support points' array
        support_points = new Point[ 3];
    
        // store points
        points.push_back( p1);
        points.push_back( p2);
    
        // compute mc
        mc( points.end(), 0);
    }
    
    // constructor for three points
    inline
    CGAL_Min_circle_2( Point const& p1,
                       Point const& p2,
                       Point const& p3,
                       Traits const& traits = Traits())
        : tco( traits)
    {
        // allocate support points' array
        support_points = new Point[ 3];
    
        // store points
        points.push_back( p1);
        points.push_back( p2);
        points.push_back( p3);
    
        // compute mc
        mc( points.end(), 0);
    }
    

    // Destructor
    // ----------
    inline
    ~CGAL_Min_circle_2( )
    {
        // free support points' array
        delete[] support_points;
    }

    // Modifiers
    // ---------
    void
    insert( Point const& p)
    {
        // p not in current circle?
        if ( has_on_unbounded_side( p)) {
    
            // p new support point
            support_points[ 0] = p;
    
            // recompute mc
            mc( points.end(), 1);
    
            // store p as the first point in list
            points.push_front( p); }
        else
    
            // append p to the end of the list
            points.push_back( p);
    }
    inline
    void
    insert( const Point* first, const Point* last)
    {
        for ( ; first != last; ++first)
            insert( *first);
    }
    
    inline
    void
    insert( list<Point>::const_iterator first,
            list<Point>::const_iterator last )
    {
        for ( ; first != last; ++first)
            insert( *first);
    }
    
    inline
    void
    insert( istream_iterator<Point,ptrdiff_t>  first,
            istream_iterator<Point,ptrdiff_t>  last )
    {
        for ( ; first != last; ++first)
            insert( *first);
    }
    void  clear( )
    {
        points.erase( points.begin(), points.end());
        n_support_points = 0;
        tco.circle.set();
    }
    

    // Validity check
    // --------------
    bool
    is_valid( bool verbose = false, int level = 0) const
    {
        CGAL_Verbose_ostream verr( verbose);
        verr << endl;
        verr << "CGAL_Min_circle_2<Traits>::" << endl;
        verr << "is_valid( true, " << level << "):" << endl;
        verr << "  |P| = " << number_of_points()
             << ", |S| = " << number_of_support_points() << endl;
    
        // containment check (a)
        verr << "  a) containment check..." << flush;
        Point_iterator point_iter;
        for ( point_iter  = points_begin();
              point_iter != points_end();
              ++point_iter)
            if ( has_on_unbounded_side( *point_iter))
                return( CGAL__optimisation_is_valid_fail( verr,
                            "circle does not contain all points"));
        verr << "passed." << endl;
    
        // support set checks (b)+(c)
        verr << "  b)+c) support set checks..." << flush;
        switch( number_of_support_points()) {
        
          case 0:
            if ( ! is_empty())
                return( CGAL__optimisation_is_valid_fail( verr,
                            "P is nonempty, but there are no support points."));
            break;
        
          case 1:
            if ( ( circle().center() != support_point( 0)    ) ||
                 ( ! CGAL_is_zero( circle().squared_radius())) )
                return( CGAL__optimisation_is_valid_fail( verr,
               "circle differs from the circle spanned by its single support point."));
            break;
        
          case 2: {
            Point const& p( support_point( 0)),
                         q( support_point( 1));
            
            // p equals q?
            if ( p == q)
                return( CGAL__optimisation_is_valid_fail( verr,
                            "the two support points are equal."));
            
            // segment(p,q) is not diameter?
            if ( ( ! has_on_boundary( p)                                      ) ||
                 ( ! has_on_boundary( q)                                      ) ||
                 ( tco.orientation( p, q, circle().center()) != CGAL_COLLINEAR) )
                return( CGAL__optimisation_is_valid_fail( verr,
                          "circle does not have its two support points as diameter.")); }
            break;
        
          case 3: {
            Point const& p( support_point( 0)),
                         q( support_point( 1)),
                         r( support_point( 2));
            
            // p, q, r not pairwise distinct?
            if ( ( p == q) || ( q == r) || ( r == p))
                return( CGAL__optimisation_is_valid_fail( verr,
                            "at least two of the three support points are equal."));
            
            // p, q, r collinear?
            if ( tco.orientation( p, q, r) == CGAL_COLLINEAR)
                return( CGAL__optimisation_is_valid_fail( verr,
                            "the three support points are collinear."));
            
            // current circle not equal the unique circle through p,q,r ?
            Circle c( circle());
            c.set( p, q, r);
            if ( circle() != c)
                return( CGAL__optimisation_is_valid_fail( verr,
                 "circle is not the unique circle through its three support points."));
            
            // circle's center on boundary of triangle(p,q,r)?
            Point const& center( circle().center());
            CGAL_Orientation o_pqz = tco.orientation( p, q, center);
            CGAL_Orientation o_qrz = tco.orientation( q, r, center);
            CGAL_Orientation o_rpz = tco.orientation( r, p, center);
            if ( ( o_pqz == CGAL_COLLINEAR) ||
                 ( o_qrz == CGAL_COLLINEAR) ||
                 ( o_rpz == CGAL_COLLINEAR) )
                return( CGAL__optimisation_is_valid_fail( verr,
                            "one of the three support points is redundant."));
            
            // circle's center not inside triangle(p,q,r)?
            if ( ( o_pqz != o_qrz) || ( o_qrz != o_rpz) || ( o_rpz != o_pqz))
                return( CGAL__optimisation_is_valid_fail( verr,
            "circle's center is not in the convex hull of its three support points.")); }
            break;
        
          default:
            return( CGAL__optimisation_is_valid_fail( verr,
                        "illegal number of support points, not between 0 and 3."));
        };
        verr << "passed." << endl;
    
        verr << "  object is valid!" << endl;
        return( true);
    }

    // Miscellaneous
    // -------------
    inline
    Traits const&
    traits( ) const
    {
        return( tco);
    }
};

// Function declarations
// =====================
// I/O
// ---
template < class _Traits >
ostream& operator << ( ostream& os, CGAL_Min_circle_2<_Traits> const& mc);

template < class _Traits >
istream& operator >> ( istream& is, CGAL_Min_circle_2<_Traits>      & mc);

#ifdef CGAL_INCLUDE_TEMPLATE_CODE
#  include <CGAL/Min_circle_2.C>
#endif

#endif // CGAL_MIN_CIRCLE_2_H

// ===== EOF ==================================================================
