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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/Min_circle_2.h
// package       : Min_circle_2 (3.1.1)
// chapter       : $CGAL_Chapter: Geometric Optimisation $
//
// source        : web/Optimisation/Min_circle_2.aw
// revision      : $Revision: 5.3 $
// revision_date : $Date: 1998/11/16 15:42:39 $
// author(s)     : Sven Schönherr
//                 Bernd Gärtner
//
// coordinator   : ETH Zürich (Bernd Gärtner)
//
// implementation: 2D Smallest Enclosing Circle
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

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
#ifndef CGAL_OPTIMISATION_BASIC_H
#  include <CGAL/optimisation_basic.h>
#endif
#ifndef CGAL_PROTECT_LIST_H
#  include <list.h>
#  define CGAL_PROTECT_LIST_H
#endif
#ifndef CGAL_PROTECT_VECTOR_H
#  include <vector.h>
#  define CGAL_PROTECT_VECTOR_H
#endif
#ifndef CGAL_PROTECT_ALGO_H
#  include <algo.h>
#  define CGAL_PROTECT_ALGO_H
#endif
#ifndef CGAL_PROTECT_IOSTREAM_H
#  include <iostream.h>
#  define CGAL_PROTECT_IOSTREAM_H
#endif

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
    WORKAROUND: The GNU compiler (g++ 2.7.2[.x]) does not accept types
    with scope operator as argument type or return type in class template
    member functions. Therefore, all member functions are implemented in
    the class interface.
    
    // creation
    CGAL_Min_circle_2( const Point*  first,
                       const Point*  last,
                       bool          randomize = false,
                       CGAL_Random&  random    = CGAL_random,
                       const Traits& traits    = Traits());
    CGAL_Min_circle_2( list<Point>::const_iterator first,
                       list<Point>::const_iterator last,
                       bool          randomize = false,
                       CGAL_Random&  random    = CGAL_random,
                       const Traits& traits    = Traits());
    CGAL_Min_circle_2( istream_iterator<Point,ptrdiff_t> first,
                       istream_iterator<Point,ptrdiff_t> last,
                       bool          randomize = false,
                       CGAL_Random&  random    = CGAL_random,
                       const Traits& traits    = Traits())
    CGAL_Min_circle_2( const Traits& traits = Traits());
    CGAL_Min_circle_2( const Point&  p,
                       const Traits& traits = Traits());
    CGAL_Min_circle_2( const Point&  p,
                       const Point&  q,
                       const Traits& traits = Traits());
    CGAL_Min_circle_2( const Point&  p1,
                       const Point&  p2,
                       const Point&  p3,
                       const Traits& traits = Traits());
    ~CGAL_Min_circle_2( );
    
    // access functions
    int  number_of_points        ( ) const;
    int  number_of_support_points( ) const;
    
    Point_iterator  points_begin( ) const;
    Point_iterator  points_end  ( ) const;
    
    Support_point_iterator  support_points_begin( ) const;
    Support_point_iterator  support_points_end  ( ) const;
    
    const Point&  support_point( int i) const;
    
    const Circle&  circle( ) const;
    
    // predicates
    CGAL_Bounded_side  bounded_side( const Point& p) const;
    bool  has_on_bounded_side      ( const Point& p) const;
    bool  has_on_boundary          ( const Point& p) const;
    bool  has_on_unbounded_side    ( const Point& p) const;
    
    bool  is_empty     ( ) const;
    bool  is_degenerate( ) const;
    
    // modifiers
    void  insert( const Point& p);
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
    const Traits&  traits( ) const;
    **************************************************************************/

  private:
    // private data members
    Traits       tco;                           // traits class object
    list<Point>  points;                        // doubly linked list of points
    int          n_support_points;              // number of support points
    Point*       support_points;                // array of support points
    

    // copying and assignment not allowed!
    CGAL_Min_circle_2( const CGAL_Min_circle_2<_Traits>&);
    CGAL_Min_circle_2<_Traits>&
        operator = ( const CGAL_Min_circle_2<_Traits>&);

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
    const Point&
    support_point( int i) const
    {
        CGAL_optimisation_precondition( (i >= 0) &&
                                        (i <  number_of_support_points()));
        return( support_points[ i]);
    }
    // circle
    inline
    const Circle&
    circle( ) const
    {
        return( tco.circle);
    }
    

    // in-circle test predicates
    inline
    CGAL_Bounded_side
    bounded_side( const Point& p) const
    {
        return( tco.circle.bounded_side( p));
    }
    
    inline
    bool
    has_on_bounded_side( const Point& p) const
    {
        return( tco.circle.has_on_bounded_side( p));
    }
    
    inline
    bool
    has_on_boundary( const Point& p) const
    {
        return( tco.circle.has_on_boundary( p));
    }
    
    inline
    bool
    has_on_unbounded_side( const Point& p) const
    {
        return( tco.circle.has_on_unbounded_side( p));
    }

  private:
    // Private member functions
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
    mc( const Point_iterator& last, int n_sp)
    {
        // compute circle through support points
        n_support_points = n_sp;
        compute_circle();
        if ( n_sp == 3) return;
    
        // test first n points
        list<Point>::iterator  point_iter( points.begin());
        for ( ; last != point_iter; ) {
            const Point& p( *point_iter);
    
            // p not in current circle?
            if ( has_on_unbounded_side( p)) {
    
                // recursive call with p as additional support point
                support_points[ n_sp] = p;
                mc( point_iter, n_sp+1);
    
                // move current point to front
                points.splice( points.begin(), points, point_iter++); }
    
            else
                ++point_iter; }
    }

  public:
    // Constructors
    // ------------
    #ifndef CGAL_CFG_NO_MEMBER_TEMPLATES
    
        // STL-like constructor (member template)
        template < class InputIterator >
        CGAL_Min_circle_2( InputIterator first,
                           InputIterator last,
                           bool          randomize = false,
                           CGAL_Random&  random    = CGAL_random,
                           const Traits& traits    = Traits())
            : tco( traits)
        {
            // allocate support points' array
            support_points = new Point[ 3];
    
            // range not empty?
            if ( first != last) {
    
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
    
    #else
    
        // STL-like constructor for C array and vector<Point>
        CGAL_Min_circle_2( const Point*  first,
                           const Point*  last,
                           bool          randomize = false,
                           CGAL_Random&  random    = CGAL_random,
                           const Traits& traits    = Traits())
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
                           const Traits& traits    = Traits())
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
    
        // STL-like constructor for stream iterator istream_iterator<Point>
        CGAL_Min_circle_2( istream_iterator<Point,ptrdiff_t>  first,
                           istream_iterator<Point,ptrdiff_t>  last,
                           bool          randomize = false,
                           CGAL_Random&  random    = CGAL_random,
                           const Traits& traits    = Traits())
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
    
    #endif // CGAL_CFG_NO_MEMBER_TEMPLATES
    
    // default constructor
    inline
    CGAL_Min_circle_2( const Traits& traits = Traits())
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
    CGAL_Min_circle_2( const Point& p, const Traits& traits = Traits())
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
    CGAL_Min_circle_2( const Point& p1,
                       const Point& p2,
                       const Traits& traits = Traits())
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
    CGAL_Min_circle_2( const Point& p1,
                       const Point& p2,
                       const Point& p3,
                       const Traits& traits = Traits())
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
    insert( const Point& p)
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
    #ifndef CGAL_CFG_NO_MEMBER_TEMPLATES
    
        template < class InputIterator >
        void
        insert( InputIterator first, InputIterator last)
        {
            for ( ; first != last; ++first)
                insert( *first);
        }
    
    #else
    
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
    
    #endif // CGAL_CFG_NO_MEMBER_TEMPLATES
    void
    clear( )
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
                            "P is nonempty, \
                             but there are no support points."));
            break;
        
          case 1:
            if ( ( circle().center() != support_point( 0)    ) ||
                 ( ! CGAL_is_zero( circle().squared_radius())) )
                return( CGAL__optimisation_is_valid_fail( verr,
                            "circle differs from the circle \
                             spanned by its single support point."));
            break;
        
          case 2: {
            const Point& p( support_point( 0)),
                         q( support_point( 1));
            
            // p equals q?
            if ( p == q)
                return( CGAL__optimisation_is_valid_fail( verr,
                            "the two support points are equal."));
            
            // segment(p,q) is not diameter?
            if ( ( ! has_on_boundary( p)                                ) ||
                 ( ! has_on_boundary( q)                                ) ||
                 ( tco.orientation( p, q,
                                    circle().center()) != CGAL_COLLINEAR) )
                return( CGAL__optimisation_is_valid_fail( verr,
                            "circle does not have its \
                             two support points as diameter.")); }
            break;
        
          case 3: {
            const Point& p( support_point( 0)),
                         q( support_point( 1)),
                         r( support_point( 2));
            
            // p, q, r not pairwise distinct?
            if ( ( p == q) || ( q == r) || ( r == p))
                return( CGAL__optimisation_is_valid_fail( verr,
                            "at least two of the three \
                             support points are equal."));
            
            // p, q, r collinear?
            if ( tco.orientation( p, q, r) == CGAL_COLLINEAR)
                return( CGAL__optimisation_is_valid_fail( verr,
                            "the three support points are collinear."));
            
            // current circle not equal the unique circle through p,q,r ?
            Circle c( circle());
            c.set( p, q, r);
            if ( circle() != c)
                return( CGAL__optimisation_is_valid_fail( verr,
                            "circle is not the unique circle \
                             through its three support points."));
            
            // circle's center on boundary of triangle(p,q,r)?
            const Point& center( circle().center());
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
                            "circle's center is not in the \
                             convex hull of its three support points.")); }
            break;
        
          default:
            return( CGAL__optimisation_is_valid_fail( verr,
                        "illegal number of support points, \
                         not between 0 and 3."));
        };
        verr << "passed." << endl;
    
        verr << "  object is valid!" << endl;
        return( true);
    }

    // Miscellaneous
    // -------------
    inline
    const Traits&
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
ostream& operator << ( ostream& os, const CGAL_Min_circle_2<_Traits>& mc);

template < class _Traits >
istream& operator >> ( istream& is, CGAL_Min_circle_2<_Traits>      & mc);

#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#  include <CGAL/Min_circle_2.C>
#endif

#endif // CGAL_MIN_CIRCLE_2_H

// ===== EOF ==================================================================
