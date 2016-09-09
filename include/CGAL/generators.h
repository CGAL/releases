// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// file          : include/CGAL/generators.h
// package       : Generator (2.40)
// chapter       : $CGAL_Chapter: Geometric Object Generators $
// source        : generators.fw
// revision      : $Revision: 1.1.1.1 $
// revision_date : $Date: 2001/02/02 14:49:40 $
// author(s)     : Lutz Kettner
//
// coordinator   : INRIA, Sophia Antipolis
//
// General Generator Support
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_GENERATORS_H
#define CGAL_GENERATORS_H 1

#include <CGAL/basic.h>
#include <cstddef>
#include <cmath>
#include <iterator>
#include <algorithm>
#include <CGAL/function_objects.h>
#include <CGAL/Random.h>

CGAL_BEGIN_NAMESPACE
template < class T >
class Generator_base {
protected:
    T       d_item;
    double  d_range;
public:
    typedef std::input_iterator_tag iterator_category;
    typedef T                       value_type;
    typedef std::ptrdiff_t          difference_type;
    typedef const T*                pointer;
    typedef const T&                reference;
    typedef Generator_base<T>      This;

    Generator_base() {}
    Generator_base( double range) : d_range( range) {}
    Generator_base( const T& item, double range)
        : d_item(item), d_range(range) {}

    bool operator==( const This& base) const {
        return ( d_item == base.d_item);
    }
    bool operator!=( const This& base) const { return ! operator==(base);}
    double    range()      const { return d_range; }
    reference operator*()  const { return d_item; }
    pointer   operator->() const { return & operator*(); }
};

template < class T >
class Random_generator_base : public Generator_base<T> {
protected:
    Random& _rnd;
public:
    typedef  Random_generator_base<T> This;

    Random_generator_base() : _rnd( default_random) {}
    Random_generator_base( double range, Random& rnd)
        : Generator_base<T>( range), _rnd( rnd) {}
    Random_generator_base( const T& item, double range, Random& rnd)
        : Generator_base<T>( item, range), _rnd( rnd) {}
    bool operator==( const This& rb) const {
        return ( _rnd == rb._rnd && Generator_base<T>::operator==(rb));
    }
    bool operator!=( const This& rb) const { return ! operator==(rb); }
};
CGAL_END_NAMESPACE
#endif // CGAL_GENERATORS_H //
// EOF //
