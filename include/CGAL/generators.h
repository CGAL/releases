// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
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
// file          : include/CGAL/generators.h
// package       : Random (1.12)
// chapter       : $CGAL_Chapter: Random Sources and Geometric Object Genera. $
// source        : generators.fw
// revision      : $Revision: 1.9 $
// revision_date : $Date: 1998/02/11 17:26:45 $
// author(s)     : Lutz Kettner
//
// coordinator   : INRIA, Sophia Antipolis
//
// General Generator Support
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_GENERATORS_H
#define CGAL_GENERATORS_H 1
#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif
#ifndef CGAL_PROTECT_STDDEF_H
#include <stddef.h>
#define CGAL_PROTECT_STDDEF_H
#endif // CGAL_PROTECT_STDDEF_H
#ifndef CGAL_PROTECT_MATH_H
#include <math.h>
#define CGAL_PROTECT_MATH_H
#endif // CGAL_PROTECT_MATH_H
#ifndef CGAL_PROTECT_ITERATOR_H
#include <iterator.h>
#define CGAL_PROTECT_ITERATOR_H
#endif // CGAL_PROTECT_ITERATOR_H
#ifndef CGAL_PROTECT_ALGO_H
#include <algo.h>
#define CGAL_PROTECT_ALGO_H
#endif // CGAL_PROTECT_ALGO_H
#ifndef CGAL_FUNCTION_OBJECTS_H
#include <CGAL/function_objects.h>
#endif
#ifndef CGAL_RANDOM_H
#include <CGAL/Random.h>
#endif

template < class T >
class CGAL__Generator_base : public input_iterator<T,size_t> {
protected:
    T            d_item;
    double       d_range;
public:
    typedef  T  value_type;
    typedef  CGAL__Generator_base<T> This;

    CGAL__Generator_base() {}
    CGAL__Generator_base( double range)
        : d_range( range) {}
    CGAL__Generator_base( const T& item, double range)
        : d_item(item), d_range( range) {}

    bool operator==( const This& base) const {
        return ( d_item == base.d_item);
    }
    bool operator!=( const This& base) const {
        return ! operator==( base);
    }
    double   range() const     { return d_range; }
    const T& operator*() const { return d_item; }
#ifdef  CGAL_ARROW_OPERATOR
    const T* operator->() const { return & operator*(); }
#endif
};

template < class T >
class CGAL__Random_generator_base : public CGAL__Generator_base<T> {
protected:
    CGAL_Random& _rnd;
public:
    typedef  CGAL__Random_generator_base<T> This;

    CGAL__Random_generator_base() : _rnd( CGAL_random) {}
    CGAL__Random_generator_base( double range, CGAL_Random& rnd)
        : CGAL__Generator_base<T>( range), _rnd( rnd) {}
    CGAL__Random_generator_base( const T& item,
                                 double range,
                                 CGAL_Random& rnd)
        : CGAL__Generator_base<T>( item, range), _rnd( rnd) {}
    bool operator==( const This& rb) const {
        return ( _rnd == rb._rnd &&
                 CGAL__Generator_base<T>::operator==(rb));
    }
    bool operator!=( const This& rb) const {
        return ! operator==( rb);
    }
};
#endif // CGAL_GENERATORS_H //
// EOF //
