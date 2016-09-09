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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : include/CGAL/IO/Ostream_iterator.h
// package       : Support_LK (1.17)
// chapter       : $CGAL_Chapter: Support Library Manual ... $
// source        : support.fw
// revision      : $Revision: 1.10 $
// revision_date : $Date: 1998/07/23 15:15:34 $
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

// This proxy is for the CGAL_Ostream_iterator.
template <class T, class Stream>
class CGAL_Ostream_proxy {
    Stream& stream;
public:
    CGAL_Ostream_proxy( Stream& s) : stream(s) {}
    CGAL_Ostream_proxy<T,Stream>&  operator=( const T& t) {
        stream << t;
        return *this;
    }
};

template <class T, class Stream>
class CGAL_Ostream_iterator {
    Stream& stream;
public:
    typedef  T                    value_type;
    typedef  T&                   reference;
    typedef  const T&             const_reference;
    typedef  T*                   pointer;
    typedef  const T*             const_pointer;
    typedef  ptrdiff_t            difference_type;
    typedef  output_iterator_tag  iterator_category;

    CGAL_Ostream_iterator( Stream& s) : stream(s) {}
    CGAL_Ostream_iterator<T,Stream>& operator++()      { return *this;}
    CGAL_Ostream_iterator<T,Stream>  operator++(int)   { return *this;}
    CGAL_Ostream_proxy<T,Stream>     operator*() const {
        return CGAL_Ostream_proxy<T,Stream>(stream);
    }
};

#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
template <class T, class Stream> inline
output_iterator_tag
iterator_category( const CGAL_Ostream_iterator<T,Stream>&) {
    return output_iterator_tag();
}
template <class T, class Stream> inline
T*
value_type( const CGAL_Ostream_iterator<T,Stream>&) {
    return (T*)0;
}
template <class T, class Stream> inline
CGAL_Iterator_tag
CGAL_query_circulator_or_iterator(
    const CGAL_Ostream_iterator<T,Stream>&) {
    return CGAL_Iterator_tag();
}
#endif
#endif // CGAL_IO_OSTREAM_ITERATOR_H //
// EOF //
