// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/Polygon_2_edge_circulator.h
// author(s)     : Wieger Wesselink 
//
// email         : cgal@cs.uu.nl
//
// ============================================================================

#ifndef CGAL_POLYGON_2_EDGE_CIRCULATOR_H
#define CGAL_POLYGON_2_EDGE_CIRCULATOR_H

#include <iterator.h>
#include <CGAL/circulator.h>
#include <CGAL/polygon_assertions.h>

//-----------------------------------------------------------------------//
//                          CGAL_Polygon_2_const_edge_circulator
//-----------------------------------------------------------------------//
// Ideally the class CGAL_Polygon_2_const_edge_circulator would be a nested
// class of CGAL_Polygon_2, but this leads to compiler problems with
// SGI C++ 4.0 with the iterator_category() function

template <class _Traits, class _Container> class CGAL_Polygon_2;

template <class _Traits, class _Container>
class CGAL_Polygon_2_const_edge_circulator {
  public:
    typedef _Traits Traits;
    typedef typename _Traits::Segment_2 Segment_2;
    typedef _Container Container;
    typedef CGAL_Bidirectional_const_circulator_from_container<_Container>
            Vertex_const_circulator;

    typedef Segment_2                            value_type;
    typedef typename _Container::difference_type difference_type;
    typedef typename _Container::size_type       size_type;
    typedef Segment_2*                           pointer;
    typedef const Segment_2*                     const_pointer;
    typedef Segment_2&                           reference;
    typedef const Segment_2&                     const_reference;
    typedef CGAL_Bidirectional_circulator_tag    iterator_category;

  private:
    Vertex_const_circulator first_vertex;

  public:
    CGAL_Polygon_2_const_edge_circulator() {}

    CGAL_Polygon_2_const_edge_circulator(Vertex_const_circulator f)
      : first_vertex(f) {}

    bool operator==( CGAL_NULL_TYPE p ) const {
      CGAL_polygon_assertion( p == NULL);
      return (first_vertex == NULL);
    }

    bool operator!=( CGAL_NULL_TYPE p ) const
    {
      return !(*this == p);
    }

    bool
    operator==(
      const CGAL_Polygon_2_const_edge_circulator<_Traits, _Container>& x) const
    {
      return first_vertex == x.first_vertex;
    }

    Segment_2 operator*()
    {
      Vertex_const_circulator second_vertex = first_vertex;
      ++second_vertex;
      return Segment_2(*first_vertex, *second_vertex);
    }

    CGAL_Polygon_2_const_edge_circulator<_Traits, _Container>& operator++()
    {
      ++first_vertex;
      return *this;
    }

    CGAL_Polygon_2_const_edge_circulator<_Traits, _Container> operator++(int)
    {
      CGAL_Polygon_2_const_edge_circulator<_Traits, _Container> tmp = *this;
      ++*this;
      return tmp;
    }

    CGAL_Polygon_2_const_edge_circulator<_Traits, _Container>& operator--()
    {
      --first_vertex;
      return *this;
    }

    CGAL_Polygon_2_const_edge_circulator<_Traits, _Container> operator--(int)
    {
      CGAL_Polygon_2_const_edge_circulator<_Traits, _Container> tmp = *this;
      --*this;
      return tmp;
    }

#ifndef CGAL_CFG_NO_LAZY_INSTANTIATION
// random access iterator requirements
    CGAL_Polygon_2_const_edge_circulator<_Traits, _Container>&
    operator+=(difference_type n)
    {
      first_vertex += n;
      return *this;
    }

    CGAL_Polygon_2_const_edge_circulator<_Traits, _Container>
    operator+(difference_type n)
    {
      return CGAL_Polygon_2_const_edge_circulator<_Traits, _Container>(
        container, first_vertex + n);
    }

    CGAL_Polygon_2_const_edge_circulator<_Traits, _Container>&
    operator-=(difference_type n)
    {
      return (*this) -= n;
    }

    CGAL_Polygon_2_const_edge_circulator<_Traits, _Container>
    operator-(difference_type n)
    {
      return CGAL_Polygon_2_const_edge_circulator<_Traits, _Container>(
        container, first_vertex - n);
    }

    difference_type
    operator-(
      const CGAL_Polygon_2_const_edge_circulator<_Traits, _Container>& a)
    {
      return first_vertex - a.first_vertex;
    }

    Segment_2 operator[](int n)
    {
      return *CGAL_Polygon_2_const_edge_circulator<_Traits, _Container>(
        container, first_vertex+n);
    }

    bool operator<(
      const CGAL_Polygon_2_const_edge_circulator<_Traits, _Container>& a)
    {
      return first_vertex < a.first_vertex;
    }

    bool operator>(
      const CGAL_Polygon_2_const_edge_circulator<_Traits, _Container>& a)
    {
      return first_vertex > a.first_vertex;
    }

    bool operator<=(
      const CGAL_Polygon_2_const_edge_circulator<_Traits, _Container>& a)
    {
      return first_vertex <= a.first_vertex;
    }

    bool operator>=(
      const CGAL_Polygon_2_const_edge_circulator<_Traits, _Container>& a)
    {
      return first_vertex >= a.first_vertex;
    }
#endif

    // the global function distance_type can only be defined as a friend
    // function within the class due to compiler problems with g++
    friend difference_type
    distance_type(
      const CGAL_Polygon_2_const_edge_circulator<_Traits,_Container>&)
    {
      return difference_type();
    }

    friend
    Segment_2* value_type(
      const CGAL_Polygon_2_const_edge_circulator<_Traits,_Container>&)
    {
      return (Segment_2*)(0);
    }
};

//-----------------------------------------------------------------------//
//                          implementation
//-----------------------------------------------------------------------//

//--------------------------------------------------------------------//
// Comment: the iterator category of a CGAL_Polygon_2_const_edge_circulator
// should be equal to the iterator category of the corresponding container,
// but this cannot be implemented (???).
//--------------------------------------------------------------------//
template <class _Traits, class _Container>
inline
CGAL_Bidirectional_circulator_tag
iterator_category(
  const CGAL_Polygon_2_const_edge_circulator<_Traits, _Container>&)
{
  return CGAL_Bidirectional_circulator_tag();
}

//--------------------------------------------------------------------//
// I don't know how to implement the following function:
//
// template <class _Traits, class _Container>
// inline
// CGAL_Polygon_2_const_edge_circulator<_Traits, _Container>
// operator+(_Container::difference_type n,
//           CGAL_Polygon_2_const_edge_circulator<_Traits, _Container>& a)
// { return a+n; }
//--------------------------------------------------------------------//

#endif

