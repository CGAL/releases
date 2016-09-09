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
// file          : include/CGAL/IO/Istream_iterator.h
// package       : Stream_support (2.15)
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2001/01/18 16:47:32 $
// author(s)     : Lutz Kettner
//
// coordinator   : INRIA, Sophia Antipolis
//
// A General Istream_iterator
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_IO_ISTREAM_ITERATOR_H
#define CGAL_IO_ISTREAM_ITERATOR_H

#include <CGAL/circulator.h>

CGAL_BEGIN_NAMESPACE

template <class T, class Stream>
class Istream_iterator {
protected:
    Stream* stream;
    T value;
    void read() {
        if ( stream) {
            if ( *stream) {
                *stream >> value;
                if ( ! *stream)
                    stream = 0;
            } else
                stream = 0;
        }
    }
public:
    typedef  T                           value_type;
    typedef  const T&                    reference;
    typedef  const T&                    const_reference;
    typedef  const T*                    pointer;
    typedef  const T*                    const_pointer;
    typedef  std::size_t                 size_type;
    typedef  std::ptrdiff_t              difference_type;
    typedef  std::input_iterator_tag     iterator_category;
    typedef  Istream_iterator<T,Stream>  Self;

    Istream_iterator() : stream(0) {}
    Istream_iterator( Stream& s) : stream(&s) { read(); }
    bool      operator==( const Self& i) const {
                  return stream == i.stream;
    }
   bool      operator!=( const Self& i) const {
                  return stream != i.stream;
    }

    reference operator*()  const { return value; }
#ifdef  CGAL_ARROW_OPERATOR
    pointer   operator->() const { return &(operator*()); }
#endif
    Self&     operator++()      {
                  read();
                  return *this;
    }
    Self      operator++(int)   {
                  Self tmp = *this;
                  read();
                  return tmp;
    }
};

#ifdef CGAL_CFG_NO_ITERATOR_TRAITS
template <class T, class Stream> inline
std::input_iterator_tag
iterator_category( const Istream_iterator<T,Stream>&) {
    return std::input_iterator_tag();
}
template <class T, class Stream> inline
T*
value_type( const Istream_iterator<T,Stream>&) {
    return (T*)0;
}
template <class T, class Stream> inline
std::ptrdiff_t*
distance_type( const Istream_iterator<T,Stream>&) {
    return (std::ptrdiff_t*)0;
}
template <class T, class Stream> inline
Iterator_tag
query_circulator_or_iterator(
    const Istream_iterator<T,Stream>&) {
    return Iterator_tag();
}
#endif

CGAL_END_NAMESPACE

#endif // CGAL_IO_ISTREAM_ITERATOR_H
