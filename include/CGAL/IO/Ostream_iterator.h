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
// file          : include/CGAL/IO/Ostream_iterator.h
// package       : Stream_support (2.3)
// chapter       : $CGAL_Chapter: Stream Support $
// source        : support.fw
// revision      : $Revision: 2.1 $
// revision_date : $Date: 1999/03/05 15:59:34 $
// author(s)     : Lutz Kettner
//
// coordinator   : INRIA, Sophia Antipolis
//
// A General Ostream_iterator
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_IO_OSTREAM_ITERATOR_H
#define CGAL_IO_OSTREAM_ITERATOR_H 1
#ifndef CGAL_CIRCULATOR_H
#include <CGAL/circulator.h>
#endif

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
#endif // CGAL_IO_OSTREAM_ITERATOR_H //
// EOF //
