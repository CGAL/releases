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
// file          : include/CGAL/Random_access_adaptor.h
// package       : STL_Extension (1.17)
// chapter       : $CGAL_Chapter: STL Extensions for CGAL $
// source        : stl_extension.fw
// revision      : $Revision: 1.12 $
// revision_date : $Date: 1998/10/08 14:35:33 $
// author(s)     : Lutz Kettner
//
// coordinator   : INRIA, Sophia Antipolis
//
// Random Access Adaptor provides random access for sequences.
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_RANDOM_ACCESS_ADAPTOR_H
#define CGAL_RANDOM_ACCESS_ADAPTOR_H 1
#ifndef CGAL_PROTECT_VECTOR_H
#include <vector.h>
#define CGAL_PROTECT_VECTOR_H
#endif // CGAL_PROTECT_VECTOR_H
#ifndef CGAL_CIRCULATOR_H
#include <CGAL/circulator.h>
#endif // CGAL_CIRCULATOR_H

template < class IC>
class CGAL_Random_access_adaptor {

// DEFINITION
//
// The class CGAL_Random_access_adaptor<IC> provides a random access
// for data structures. Either the data structure supports random access
// iterators or circulators where this class maps function calls to the
// iterator or circulator, or a STL `vector' is used to provide the random
// access. The iterator or circulator of the data structure are of type
// `IC'.
//
// CREATION

protected:
    typedef vector< IC> Index;
    Index   index;
    IC      start;

public:
    typedef typename Index::size_type  size_type;

    void init_index( IC i, const IC& j, forward_iterator_tag);
    void init_index( const IC& i, const IC& j, bidirectional_iterator_tag){
        init_index( i, j, forward_iterator_tag());
    }
    void init_index( const IC& i, const IC&, random_access_iterator_tag){
        start = i;
    }
    void init_index( const IC& i, const IC& j) {
        init_index( i, j, iterator_category( i));
    }


    void reserve( size_type r, forward_iterator_tag) {
        index.reserve( r);
    }
    void reserve( size_type r, bidirectional_iterator_tag){
        reserve( r, forward_iterator_tag());
    }
    void reserve( size_type, random_access_iterator_tag){}


    void push_back( const IC& k, forward_iterator_tag) {
        index.push_back(k);
    }
    void push_back( const IC& k, bidirectional_iterator_tag){
        push_back( k, forward_iterator_tag());
    }
    void push_back( const IC&, random_access_iterator_tag){}


    const IC& find( size_type n, forward_iterator_tag) const {
        // returns inverse index of k.
        CGAL_assertion( n < index.size());
        return index[n];
    }
    const IC& find( size_type n, bidirectional_iterator_tag) const {
        return find( n, forward_iterator_tag());
    }
#ifndef CGAL_CFG_NO_LAZY_INSTANTIATION
    IC  find( size_type n, random_access_iterator_tag) const {
        return start + n;
    }
#endif

    typedef IC   iterator;
    typedef IC   Circulator;

    CGAL_Random_access_adaptor() : start(IC()) {}
        // invalid index.

    CGAL_Random_access_adaptor( const IC& i) : start(i) {}
        // empty random access index initialized to start at i.

    CGAL_Random_access_adaptor( const IC& i, const IC& j) : start(i) {
        // random access index initialized with range [i,j).
        init_index( i, j);
    }

    void reserve( size_type r) { reserve( r, iterator_category( IC()));}
        // reserve r entries, if a `vector' is used internally.

// OPERATIONS

    IC  find( size_type n) const {
        // returns inverse index of k.
        return find( n, iterator_category( IC()));
    }

    IC  operator[]( size_type n) const { return find(n); }

    void push_back( const IC& k) {
        // adds k at the end of the indices.
        push_back( k, iterator_category( k));
    }
};

template < class IC>
void
CGAL_Random_access_adaptor< IC>::init_index( IC i, const IC& j,
                                            forward_iterator_tag) {
    if ( ! CGAL_is_empty_range( i, j)) {
        do {
            index.push_back( i);
        } while ((++i) != (j));
    }
}
#endif // CGAL_RANDOM_ACCESS_ADAPTOR_H //
// EOF //
