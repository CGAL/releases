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
// file          : include/CGAL/IO/Ostream_iterator.h
// package       : Stream_support (2.15)
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2001/01/18 16:47:34 $
// author(s)     : Lutz Kettner
//
// coordinator   : INRIA, Sophia Antipolis
//
// A General Ostream_iterator
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_IO_OSTREAM_ITERATOR_H
#define CGAL_IO_OSTREAM_ITERATOR_H

#include <CGAL/circulator.h>

CGAL_BEGIN_NAMESPACE

// This proxy is for the Ostream_iterator.
template <class T, class Stream>
class Ostream_proxy {
    Stream& stream;
public:
    Ostream_proxy( Stream& s) : stream(s) {}
    Ostream_proxy<T,Stream>&  operator=( const T& t) {
        stream << t;
        return *this;
    }
};

template <class T, class Stream>
class Ostream_iterator {
    Stream& stream;
public:
    typedef  T                         value_type;
    typedef  T&                        reference;
    typedef  const T&                  const_reference;
    typedef  T*                        pointer;
    typedef  const T*                  const_pointer;
    typedef  std::ptrdiff_t            difference_type;
    typedef  std::output_iterator_tag  iterator_category;

    Ostream_iterator( Stream& s) : stream(s) {}
    Ostream_iterator<T,Stream>& operator++()      { return *this;}
    Ostream_iterator<T,Stream>  operator++(int)   { return *this;}
    Ostream_proxy<T,Stream>     operator*() const {
        return Ostream_proxy<T,Stream>(stream);
    }
};

#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
template <class T, class Stream> inline
std::output_iterator_tag
iterator_category( const Ostream_iterator<T,Stream>&) {
    return std::output_iterator_tag();
}
template <class T, class Stream> inline
T*
value_type( const Ostream_iterator<T,Stream>&) {
    return (T*)0;
}
template <class T, class Stream> inline
Iterator_tag
query_circulator_or_iterator(
    const Ostream_iterator<T,Stream>&) {
    return Iterator_tag();
}
#endif

CGAL_END_NAMESPACE

#endif // CGAL_IO_OSTREAM_ITERATOR_H
