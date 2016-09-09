// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/generators.h
// package       : Generator (2.10)
// chapter       : $CGAL_Chapter: Geometric Object Generators $
// source        : generators.fw
// revision      : $Revision: 1.13 $
// revision_date : $Date: 1999/04/20 15:58:18 $
// author(s)     : Lutz Kettner
//
// coordinator   : INRIA, Sophia Antipolis
//
// General Generator Support
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_GENERATORS_H
#define CGAL_GENERATORS_H 1
#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif
#ifndef CGAL_PROTECT_CSTDDEF
#include <cstddef>
#define CGAL_PROTECT_CSTDDEF
#endif
#ifndef CGAL_PROTECT_CMATH
#include <cmath>
#define CGAL_PROTECT_CMATH
#endif
#ifndef CGAL_PROTECT_ITERATOR
#include <iterator>
#define CGAL_PROTECT_ITERATOR
#endif
#ifndef CGAL_PROTECT_ALGORITHM
#include <algorithm>
#define CGAL_PROTECT_ALGORITHM
#endif
#ifndef CGAL_FUNCTION_OBJECTS_H
#include <CGAL/function_objects.h>
#endif
#ifndef CGAL_RANDOM_H
#include <CGAL/Random.h>
#endif

CGAL_BEGIN_NAMESPACE
template < class T >
class _Generator_base {
protected:
    T       d_item;
    double  d_range;
public:
    typedef std::input_iterator_tag iterator_category;
    typedef T                       value_type;
    typedef std::ptrdiff_t          difference_type;
    typedef const T*                pointer;
    typedef const T&                reference;
    typedef _Generator_base<T>      This;

    _Generator_base() {}
    _Generator_base( double range) : d_range( range) {}
    _Generator_base( const T& item, double range)
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
class _Random_generator_base : public _Generator_base<T> {
protected:
    Random& _rnd;
public:
    typedef  _Random_generator_base<T> This;

    _Random_generator_base() : _rnd( default_random) {}
    _Random_generator_base( double range, Random& rnd)
        : _Generator_base<T>( range), _rnd( rnd) {}
    _Random_generator_base( const T& item, double range, Random& rnd)
        : _Generator_base<T>( item, range), _rnd( rnd) {}
    bool operator==( const This& rb) const {
        return ( _rnd == rb._rnd && _Generator_base<T>::operator==(rb));
    }
    bool operator!=( const This& rb) const { return ! operator==(rb); }
};
CGAL_END_NAMESPACE
#endif // CGAL_GENERATORS_H //
// EOF //
