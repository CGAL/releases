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
// file          : include/CGAL/Inverse_index.h
// package       : STL_Extension (2.6)
// chapter       : $CGAL_Chapter: STL Extensions for CGAL $
// source        : stl_extension.fw
// revision      : $Revision: 1.3 $
// revision_date : $Date: 1999/04/07 18:31:32 $
// author(s)     : Lutz Kettner
//
// coordinator   : INRIA, Sophia Antipolis
//
// Inverse_Index adaptor enumerates sequences.
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_INVERSE_INDEX_H
#define CGAL_INVERSE_INDEX_H 1
#ifndef CGAL_CIRCULATOR_H
#include <CGAL/circulator.h>  // Needed for circulator categories.
#endif // CGAL_CIRCULATOR_H
#ifndef CGAL_PROTECT_MAP
#include <map>
#define CGAL_PROTECT_MAP
#endif

CGAL_BEGIN_NAMESPACE

template < class IC>
class Inverse_index {

// DEFINITION
//
// The class Inverse_index<IC,T> constructs an inverse index for a
// given range [i,j) of two iterators or circulators of type `IC' with the
// value type `T'. The first element I in the
// range [i,j) has the index 0. Consecutive elements are numbered
// incrementally. The inverse index provides a query for a given iterator
// or circulator k to retrieve its index number. For random access
// iterators or circulators, it is done in constant time by subtracting i.
// For other iterator categories, an STL `map' is used, which results in a
// log j-i query time. A comparison operator `operator<' is needed for
// `T*'.
//
// CREATION

protected:
    typedef std::map< const void*, std::size_t, std::less<const void*> >
            Index;
    Index   idx;
    IC      start;
    typedef typename Index::iterator        Index_iterator;
    typedef typename Index::const_iterator  Index_const_iterator;
    typedef typename Index::value_type      Item;

private:
    void ini_idx( IC i, const IC& j, std::input_iterator_tag);
    void ini_idx( const IC& i, const IC& j, std::forward_iterator_tag){
        ini_idx( i, j, std::input_iterator_tag());
    }
    void ini_idx(const IC& i,const IC& j, std::bidirectional_iterator_tag){
        ini_idx( i, j, std::input_iterator_tag());
    }
    void ini_idx( const IC& i, const IC& j, Forward_circulator_tag) {
        ini_idx( i, j, std::input_iterator_tag());
    }
    void ini_idx( const IC& i, const IC& j, Bidirectional_circulator_tag){
        ini_idx( i, j, std::input_iterator_tag());
    }
    void ini_idx( const IC&, const IC&, std::random_access_iterator_tag){}
    void ini_idx( const IC&, const IC&, Random_access_circulator_tag){}

public:
    void init_index( const IC& i, const IC& j) {
        ini_idx( i, j, std::iterator_category( i));
    }

private:
    void push_back( const IC& k, std::input_iterator_tag) {
        std::size_t d = idx.size();
        idx[ &*k] = d;
    }
    void push_back( const IC& k, std::forward_iterator_tag){
        push_back( k, std::input_iterator_tag());
    }
    void push_back( const IC& k, std::bidirectional_iterator_tag){
        push_back( k, std::input_iterator_tag());
    }
    void push_back( const IC& k, Forward_circulator_tag){
        push_back( k, std::input_iterator_tag());
    }
    void push_back( const IC& k, Bidirectional_circulator_tag){
        push_back( k, std::input_iterator_tag());
    }
    void push_back( const IC&, std::random_access_iterator_tag){}
    void push_back( const IC&, Random_access_circulator_tag){}

public:
    void push_back( const IC& k) {
        // adds k at the end of the indices.
        push_back( k, std::iterator_category( k));
    }

    std::size_t find( const IC& k, std::random_access_iterator_tag) const {
        return std::size_t(k - start);
    }
    std::size_t find( const IC& k, Random_access_circulator_tag) const {
        return std::size_t(k - start);
    }
    std::size_t find( const IC& k, std::input_iterator_tag) const {
        // returns inverse index of k.
        Index_const_iterator i = idx.find( &*k);
        CGAL_assertion( i != idx.end());
        return (*i).second;
    }
    std::size_t find( const IC& k, std::forward_iterator_tag) const {
        return find( k, std::input_iterator_tag());
    }
    std::size_t find( const IC& k, std::bidirectional_iterator_tag) const {
        return find( k, std::input_iterator_tag());
    }
    std::size_t find( const IC& k, Forward_circulator_tag) const {
        return find( k, std::input_iterator_tag());
    }
    std::size_t find( const IC& k, Bidirectional_circulator_tag) const {
        return find( k, std::input_iterator_tag());
    }

    typedef IC           iterator;
    typedef IC           Circulator;
    typedef std::size_t  size_type;

    Inverse_index() : start(IC()) {}
        // invalid index.

    Inverse_index( const IC& i) : start(i) {};
        // empty inverse index initialized to start at i.

    Inverse_index( const IC& i, const IC& j) : start(i) {
        // inverse index initialized with range [i,j).
        init_index( i, j);
    }

// OPERATIONS

    std::size_t operator[]( const IC& k) const {
        // returns inverse index of k.
#ifndef CGAL_CFG_NO_ITERATOR_TRAITS
        typedef typename std::iterator_traits<IC>::iterator_category
            category;
        return find( k, category());
#else
        return find( k, std::iterator_category( k));
#endif
    }
};

template < class IC>
void
Inverse_index< IC>::ini_idx( IC i, const IC& j, std::input_iterator_tag) {
    std::size_t n = 0;
    Index_iterator hint = idx.begin();
    if ( ! is_empty_range( i, j)) {
        do {
            hint = idx.insert( hint, Item( &*i, n));
            n++;
        } while ((++i) != (j));
    }
}

CGAL_END_NAMESPACE
#endif // CGAL_INVERSE_INDEX_H //
// EOF //
