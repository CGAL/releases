// ======================================================================
//
// Copyright (c) 1997, 1998, 1999, 2000 The CGAL Consortium

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
// file          : include/CGAL/Inverse_index.h
// package       : STL_Extension (2.34)
// chapter       : $CGAL_Chapter: STL Extensions for CGAL $
// source        : stl_extension.fw
// revision      : $Revision: 1.27 $
// revision_date : $Date: 2001/07/23 08:38:59 $
// author(s)     : Michael Hoffmann
//                 Lutz Kettner
//
// coordinator   : ETH
//
// Inverse_Index adaptor enumerates sequences.
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_INVERSE_INDEX_H
#define CGAL_INVERSE_INDEX_H 1
#include <CGAL/circulator.h>  // Needed for circulator categories.
#include <map>

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

protected:
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
#if !defined(CGAL_CFG_NO_ITERATOR_TRAITS) || \
    defined(CGAL_LIMITED_ITERATOR_TRAITS_SUPPORT)
    typedef typename std::iterator_traits<IC>::iterator_category ICC;
    ini_idx( i, j, ICC());
#else
    ini_idx( i, j, std::iterator_category( i));
#endif
  }

protected:
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
#if !defined(CGAL_CFG_NO_ITERATOR_TRAITS) || \
    defined(CGAL_LIMITED_ITERATOR_TRAITS_SUPPORT)
    typedef typename std::iterator_traits<IC>::iterator_category ICC;
    push_back( k, ICC());
#else
    push_back( k, std::iterator_category( k));
#endif
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
  std::size_t find( const IC& k, std::bidirectional_iterator_tag
  #if defined( _MSC_VER ) && (_MSC_VER < 1300 )
   , int dummy=0
  #endif //_MSC_VER
  ) const {
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
#if !defined(CGAL_CFG_NO_ITERATOR_TRAITS) || \
    defined(CGAL_LIMITED_ITERATOR_TRAITS_SUPPORT)
    typedef typename std::iterator_traits<IC>::iterator_category
      category;
    return find( k, category());
#else
    return find( k, std::iterator_category( k));
#endif
  }
};

#if (defined(__GNUC__) && (__GNUC__ >= 3))
template < class IC>
void
Inverse_index< IC>::ini_idx( IC i, const IC& j, std::input_iterator_tag) {
  std::size_t n = 0;
  if ( ! is_empty_range( i, j)) {
    do {
      idx.insert(Item( &*i, n));
      n++;
    } while ((++i) != (j));
  }
}
#else
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
#endif // (__GNUC__ >= 3)

CGAL_END_NAMESPACE
#endif // CGAL_INVERSE_INDEX_H //
// EOF //
