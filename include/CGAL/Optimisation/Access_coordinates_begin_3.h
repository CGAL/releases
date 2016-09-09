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
// file          : include/CGAL/Optimisation/Access_coordinates_begin_3.h
// package       : Optimisation_basic (3.8.10)
//
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2001/03/21 18:29:00 $
//
// author(s)     : Sven Schönherr
// coordinator   : ETH Zürich (Bernd Gärtner)
//
// implementation: 3D data accessor `coordinates'
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_OPTIMISATION_ACCESS_COORDINATES_BEGIN_3_H
#define CGAL_OPTIMISATION_ACCESS_COORDINATES_BEGIN_3_H

// includes
#ifndef CGAL_POINT_3_H
#  include <CGAL/Point_3.h>
#endif

CGAL_BEGIN_NAMESPACE

// Class declarations
// ==================
template < class R_ >
class Access_coordinates_begin_3;

template < class R_ >
class Point_3_coordinate_iterator;

// Class interfaces
// ================
template < class R_ >
class Point_3_coordinate_iterator {
  public:
    // self
    typedef  R_                         R;
    typedef  Point_3_coordinate_iterator<R>
                                        Self;

    // types
    typedef  typename R::Point_3        Point;

    // iterator types
    typedef  typename R::RT             value_type;
    typedef  ptrdiff_t                  difference_type;
    typedef  value_type*                pointer;
    typedef  value_type&                reference;
    typedef  std::random_access_iterator_tag
                                        iterator_category;

    // forward operations
    Point_3_coordinate_iterator( const Point&  point = Point(),
                                 int           index = 0)
        : p( point), i( index) { }

    bool        operator == ( const Self& it) const { return ( i == it.i);}
    bool        operator != ( const Self& it) const { return ( i != it.i);}

    value_type  operator *  ( ) const { return p.homogeneous( i); }

    Self&       operator ++ (    ) {                   ++i; return *this; }
    Self        operator ++ ( int) { Self tmp = *this; ++i; return tmp;   }

    // bidirectional operations
    Self&       operator -- (    ) {                   --i; return *this; }
    Self        operator -- ( int) { Self tmp = *this; --i; return tmp;   }

    // random access operations
    Self&       operator += ( int n) { i += n; return *this; }
    Self&       operator -= ( int n) { i -= n; return *this; }

    Self        operator +  ( int n) const
                                     { Self tmp = *this; return tmp += n; }
    Self        operator -  ( int n) const
                                     { Self tmp = *this; return tmp -= n; }

    difference_type
                operator -  ( const Self& it) const { return i - it.i; }

    value_type  operator [] ( int n) const { return p.homogeneous( i+n); }

    bool   operator <  ( const Self&) const { return ( i <  it.i); }
    bool   operator >  ( const Self&) const { return ( i >  it.i); }
    bool   operator <= ( const Self&) const { return ( i <= it.i); }
    bool   operator >= ( const Self&) const { return ( i >= it.i); }

private:
    const Point&  p;
    int           i;
};

template < class R_ >
class Access_coordinates_begin_3 {
  public:
    // self
    typedef  R_                         R;
    typedef  Access_coordinates_begin_3<R>
                                        Self;

    // types
    typedef  typename R::Point_3        Point;
    typedef  Point_3_coordinate_iterator<R>
                                        Coordinate_iterator;

    // unary function class types
    typedef  Coordinate_iterator        result_type;
    typedef  Point                      argument_type;

    // creation
    Access_coordinates_begin_3( ) { }

    // operations
    Coordinate_iterator
    operator() ( const Point& p) const { return Coordinate_iterator( p); }
};

CGAL_END_NAMESPACE

#endif // CGAL_OPTIMISATION_ACCESS_COORDINATES_BEGIN_3_H

// ===== EOF ==================================================================
