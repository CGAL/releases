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
// file          : include/CGAL/Polygon_2_edge_iterator.h
// package       : Polygon (4.2.4)
// source        : 
// revision      : 1.8a
// revision_date : 13 Mar 1998
// author(s)     : Wieger Wesselink
//
// coordinator   : Utrecht University
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_POLYGON_2_EDGE_ITERATOR_H
#define CGAL_POLYGON_2_EDGE_ITERATOR_H

#include <iterator>
#include <CGAL/circulator.h>

CGAL_BEGIN_NAMESPACE

//-----------------------------------------------------------------------//
//                          Polygon_2_edge_iterator
//-----------------------------------------------------------------------//
// Ideally the class Polygon_2_edge_iterator would be a nested class of
// Polygon_2, but this leads to compiler problems with SGI C++ 4.0
// with the iterator_category() function

template <class _Traits, class _Container> class Polygon_2;

template <class _Traits, class _Container>
class Polygon_2_edge_iterator {
  public:
    typedef _Traits Traits;
    typedef typename _Traits::Segment_2 Segment_2;
    typedef _Container Container;
    typedef typename _Container::const_iterator const_iterator;
    typedef typename _Container::difference_type difference_type;
  private:
    const _Container* container;   // needed for dereferencing the last edge
    const_iterator first_vertex;   // points to the first vertex of the edge
  public:
    Polygon_2_edge_iterator() {}
    Polygon_2_edge_iterator(const _Container* c, const_iterator f)
      : container(c), first_vertex(f) {}

    bool operator==(
      const Polygon_2_edge_iterator<_Traits, _Container>& x) const
    {
      return first_vertex == x.first_vertex;
    }
    
    bool operator!=(
      const Polygon_2_edge_iterator<_Traits, _Container>& x) const
    {
      return !(first_vertex == x.first_vertex);
    }

    Segment_2 operator*() {
      const_iterator second_vertex = first_vertex;
      ++second_vertex;
      if (second_vertex == container->end())
        second_vertex = container->begin();
      typename Traits::Construct_segment_2 construct_segment_2 = 
            Traits().construct_segment_2_object();
      return construct_segment_2(*first_vertex, *second_vertex);
    }

    Polygon_2_edge_iterator<_Traits, _Container>& operator++() {
      ++first_vertex;
      return *this;
    }

    Polygon_2_edge_iterator<_Traits, _Container> operator++(int) {
      Polygon_2_edge_iterator<_Traits, _Container> tmp = *this;
      ++*this;
      return tmp;
    }

    Polygon_2_edge_iterator<_Traits, _Container>& operator--() {
      --first_vertex;
      return *this;
    }

    Polygon_2_edge_iterator<_Traits, _Container> operator--(int) {
      Polygon_2_edge_iterator<_Traits, _Container> tmp = *this;
      --*this;
      return tmp;
    }

#ifndef CGAL_CFG_NO_LAZY_INSTANTIATION
// random access iterator requirements
    Polygon_2_edge_iterator<_Traits, _Container>&
    operator+=(difference_type n) {
      first_vertex += n;
      return *this;
    }

    Polygon_2_edge_iterator<_Traits, _Container>
    operator+(difference_type n) {
      return Polygon_2_edge_iterator<_Traits, _Container>(
        container, first_vertex + n);
    }

    Polygon_2_edge_iterator<_Traits, _Container>&
    operator-=(difference_type n) {
      return (*this) -= n;
    }

    Polygon_2_edge_iterator<_Traits, _Container>
    operator-(difference_type n) {
      return Polygon_2_edge_iterator<_Traits, _Container>(
        container, first_vertex - n);
    }

    difference_type
    operator-(const Polygon_2_edge_iterator<_Traits, _Container>& a) {
      return first_vertex - a.first_vertex;
    }

    Segment_2 operator[](int n) {
      return *Polygon_2_edge_iterator<_Traits, _Container>(
        container, first_vertex+n);
    }

    bool operator<(const Polygon_2_edge_iterator<_Traits, _Container>& a)
    {
      return first_vertex < a.first_vertex;
    }

    bool operator>(const Polygon_2_edge_iterator<_Traits, _Container>& a)
    {
      return first_vertex > a.first_vertex;
    }

    bool operator<=(const Polygon_2_edge_iterator<_Traits, _Container>& a)
    {
      return first_vertex <= a.first_vertex;
    }

    bool operator>=(const Polygon_2_edge_iterator<_Traits, _Container>& a)
    {
      return first_vertex >= a.first_vertex;
    }
#endif

};


template <class _Traits,  class _Container>
typename _Container::difference_type
distance_type(const Polygon_2_edge_iterator<_Traits,_Container>&)
{ return _Container::difference_type(); }

template <class _Traits,  class _Container>
typename _Traits::Segment_2*
value_type(const Polygon_2_edge_iterator<_Traits,_Container>&)
{ return (typename _Traits::Segment_2 *)(0); }


//-----------------------------------------------------------------------//
//                          implementation
//-----------------------------------------------------------------------//

//--------------------------------------------------------------------//
// Comment: the iterator category of a Polygon_2_edge_iterator should
// be equal to the iterator category of the corresponding container, but this
// cannot be implemented (???).
//--------------------------------------------------------------------//

#ifdef CGAL_CFG_NO_ITERATOR_TRAITS 
template <class _Traits, class _Container>
inline
bidirectional_iterator_tag
iterator_category(const Polygon_2_edge_iterator<_Traits, _Container>&)
{
  return bidirectional_iterator_tag();
}

#endif // CGAL_CFG_NO_ITERATOR_TRAITS

//--------------------------------------------------------------------//
// I don't know how to implement the following function:
//
// template <class _Traits, class _Container>
// inline
// Polygon_2_edge_iterator<_Traits, _Container>
// operator+(_Container::difference_type n,
//           Polygon_2_edge_iterator<_Traits, _Container>& a)
// { return a+n; }
//--------------------------------------------------------------------//

CGAL_END_NAMESPACE

#endif

