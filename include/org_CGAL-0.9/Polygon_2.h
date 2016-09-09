/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/


// Source: Polygon_2.h
// Author: Wieger Wesselink

#ifndef CGAL_POLYGON_2_H
#define CGAL_POLYGON_2_H

#include <CGAL/bool.h>
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Iso_rectangle_2.h>
#include <CGAL/enum.h>

#include <iterator.h>
#include <CGAL/circulator.h>

#ifndef CGAL_MEMBER_TEMPLATES
#include <vector.h>
#include <list.h>
#endif

//-----------------------------------------------------------------------//
//                  algorithms for sequences of 2D points
//-----------------------------------------------------------------------//

template <class ForwardIterator>
ForwardIterator CGAL_left_vertex_2(ForwardIterator first, ForwardIterator last);

template <class ForwardIterator>
ForwardIterator CGAL_right_vertex_2(ForwardIterator first, ForwardIterator last);

template <class ForwardIterator>
ForwardIterator CGAL_top_vertex_2(ForwardIterator first, ForwardIterator last);

template <class ForwardIterator>
ForwardIterator CGAL_bottom_vertex_2(ForwardIterator first, ForwardIterator last);

template <class InputIterator>
CGAL_Bbox_2 CGAL_bbox_2(InputIterator first, InputIterator last);

template <class ForwardIterator, class Numbertype>
void CGAL_area_2(ForwardIterator first, ForwardIterator last, Numbertype& result);

template <class ForwardIterator>
bool CGAL_is_convex_2(ForwardIterator first, ForwardIterator last);

template <class ForwardIterator>
bool CGAL_is_simple_2(ForwardIterator first, ForwardIterator last);

template <class ForwardIterator, class Point>
CGAL_Oriented_side CGAL_oriented_side_2(ForwardIterator first,
                                        ForwardIterator last,
                                        const Point& point);

template <class ForwardIterator, class Point>
CGAL_Bounded_side CGAL_bounded_side_2(ForwardIterator first,
                                      ForwardIterator last,
                                      const Point& point);

template <class ForwardIterator>
CGAL_Orientation CGAL_orientation_2(ForwardIterator first, ForwardIterator last);

//-----------------------------------------------------------------------//
//                          CGAL_Polygon_2_edge_iterator
//-----------------------------------------------------------------------//
// Ideally the class CGAL_Polygon_2_edge_iterator would be a nested class of
// CGAL_Polygon_2, but this leads to compiler problems with the iterator_category()
// function on SGI compilers...

template <class R, class Container> class CGAL_Polygon_2;

template <class R, class Container>
class CGAL_Polygon_2_edge_iterator {
  public:
    typedef Container::const_iterator const_iterator;
    typedef Container::difference_type difference_type;
  private:
    const Container* container;   // needed for dereferencing the last edge
    const_iterator first_vertex;
  public:
    CGAL_Polygon_2_edge_iterator() {}
    CGAL_Polygon_2_edge_iterator(const Container* c, const_iterator f)
      : container(c), first_vertex(f) {}

    bool operator==(const CGAL_Polygon_2_edge_iterator<R, Container>& x) const {
      return first_vertex == x.first_vertex;
    }

    CGAL_Segment_2<R> operator*() {
      const_iterator second_vertex = first_vertex;
      ++second_vertex;
      if (second_vertex == container->end())
        second_vertex = container->begin();
      return CGAL_Segment_2<R>(*first_vertex, *second_vertex);
    }

    CGAL_Polygon_2_edge_iterator<R, Container>& operator++() {
      ++first_vertex;
      return *this;
    }

    CGAL_Polygon_2_edge_iterator<R, Container> operator++(int) {
      CGAL_Polygon_2_edge_iterator<R, Container> tmp = *this;
      ++*this;
      return tmp;
    }

    CGAL_Polygon_2_edge_iterator<R, Container>& operator--() {
      --first_vertex;
      return *this;
    }

    CGAL_Polygon_2_edge_iterator<R, Container> operator--(int) {
      CGAL_Polygon_2_edge_iterator<R, Container> tmp = *this;
      --*this;
      return tmp;
    }

//    CGAL_Polygon_2_edge_iterator& operator+=(Container::difference_type n) {
//      first_vertex += n;
//      return *this;
//    }
//
//    CGAL_Polygon_2_edge_iterator& operator-=(Container::difference_type n) {
//      return (*this) -= n;
//    }
//
//    Container::difference_type operator-(const CGAL_Polygon_2_edge_iterator& a) {
//      return first_vertex - a.first_vertex;
//    }
//
//    CGAL_Polygon_2_edge_iterator operator+(Container::difference_type n) {
//      return CGAL_Polygon_2_edge_iterator(container, first_vertex + n);
//    }
//
//    CGAL_Polygon_2_edge_iterator operator-(Container::difference_type n) {
//      return CGAL_Polygon_2_edge_iterator(container, first_vertex - n);
//    }
//
//    bool operator<(const CGAL_Polygon_2_edge_iterator& a) {
//      return first_vertex < a.first_vertex;
//    }
//
//    bool operator>(const CGAL_Polygon_2_edge_iterator& a) {
//      return first_vertex > a.first_vertex;
//    }
//
//    bool operator<=(const CGAL_Polygon_2_edge_iterator& a) {
//      return first_vertex <= a.first_vertex;
//    }
//
//    bool operator>=(const CGAL_Polygon_2_edge_iterator& a) {
//      return first_vertex >= a.first_vertex;
//    }
//
//    CGAL_Segment_2<R> operator[](int n) {
//      return *CGAL_Polygon_2_edge_iterator<R,Container>(container, first_vertex+n);
//    }

    // the global function distance_type can only be defined as a friend function
    // within the class due to compiler problems with g++
    friend difference_type
    distance_type(const CGAL_Polygon_2_edge_iterator<R,Container>&)
      { return Container::difference_type(); }
};

//-----------------------------------------------------------------------//
//                          CGAL_Polygon_2
//-----------------------------------------------------------------------//

template <class R, class Container>
class CGAL_Polygon_2 {
  private:
    Container d_container;

  public:
    typedef Container::value_type value_type;
    typedef Container::difference_type difference_type;

  //------------------------------------------------------------//
  // this construction is required by Sun C++ 4.1
  private:
    typedef Container::iterator iterator;
    typedef Container::const_iterator const_iterator;
  public:
    typedef iterator Vertex_iterator;
    typedef const_iterator Vertex_const_iterator;
  //------------------------------------------------------------//

    typedef CGAL_Bidirectional_circulator_from_container<Container> Vertex_circulator;
    typedef CGAL_Bidirectional_const_circulator_from_container<Container> Vertex_const_circulator;

    typedef CGAL_Polygon_2_edge_iterator<R,Container> Edge_const_iterator;

    class Edge_const_circulator {
      private:
        Vertex_const_circulator first_vertex;
      public:
        Edge_const_circulator() {}
        Edge_const_circulator(Vertex_const_circulator f)
          : first_vertex(f) {}

        bool operator==( CGAL_NULL_TYPE p) const {
            CGAL_kernel_assertion( p == NULL);
            return (first_vertex == NULL);
        }

        bool operator!=( CGAL_NULL_TYPE p) const {
            return !(*this == p);
        }

        bool operator==(const Edge_const_circulator& x) const {
          return first_vertex == x.first_vertex;
        }

        CGAL_Segment_2<R> operator*() {
          Vertex_const_circulator second_vertex = first_vertex;
          ++second_vertex;
          return CGAL_Segment_2<R>(*first_vertex, *second_vertex);
        }

        Edge_const_circulator& operator++() {
          ++first_vertex;
          return *this;
        }

        Edge_const_circulator operator++(int) {
          Edge_const_circulator tmp = *this;
          ++*this;
          return tmp;
        }

        Edge_const_circulator& operator--() {
          --first_vertex;
          return *this;
        }

        Edge_const_circulator operator--(int) {
          Edge_const_circulator tmp = *this;
          --*this;
          return tmp;
        }

//---------------------------------------------------------------------------------
// these methods cause problems with the GNU compiler (since g++ 2.7.2 instantiates
// them even if they are not used)
//
//      Edge_const_circulator& operator+=(Container::difference_type n) {
//        first_vertex += n;
//        return *this;
//      }
//
//      Edge_const_circulator& operator-=(Container::difference_type n) {
//        return (*this) -= n;
//      }
//
//      Container::difference_type operator-(const Edge_const_circulator& a) {
//        return first_vertex - a.first_vertex;
//      }
//
//      Edge_const_circulator operator+(Container::difference_type n) {
//        return Edge_const_circulator(d_container, first_vertex + n);
//      }
//
//      Edge_const_circulator operator-(Container::difference_type n) {
//        return Edge_const_circulator(d_container, first_vertex - n);
//      }
//
//      CGAL_Segment_2<R> operator[](int n) {
//        return *Edge_const_circulator<R,Container>(d_container, first_vertex+n);
//      }
//---------------------------------------------------------------------------------
// are the following functions needed for circulators?
//
//    bool operator<(const Edge_const_circulator& x) {
//      return first_vertex.Get_iterator() < x.first_vertex.Get_iterator();
//    }
//
//    bool operator>(const Edge_const_circulator& x) {
//      return first_vertex.Get_iterator() > x.first_vertex.Get_iterator();
//    }
//
//    bool operator<=(const Edge_const_circulator& x) {
//      return first_vertex.Get_iterator() <= x.first_vertex.Get_iterator();
//    }
//
//    bool operator>=(const Edge_const_circulator& x) {
//      return first_vertex.Get_iterator() >= x.first_vertex.Get_iterator();
//    }
//---------------------------------------------------------------------------------

      // the global function distance_type can only be defined as a friend function
      // within the class due to compiler problems with g++ 2.7.2
      friend inline bidirectional_iterator_tag iterator_category(Edge_const_circulator)
        { return bidirectional_iterator_tag(); }

      friend inline CGAL_Segment_2<R>* value_type(Edge_const_circulator)
        { return (CGAL_Segment_2<R>*)(0); }

      friend Container::difference_type distance_type(const Edge_const_circulator&)
        { return Container::difference_type(); }
    };

    CGAL_Polygon_2();
    CGAL_Polygon_2(const CGAL_Polygon_2<R,Container>& polygon);
    CGAL_Polygon_2(const CGAL_Point_2<R>& point);
    CGAL_Polygon_2(const CGAL_Segment_2<R>& segment);
    CGAL_Polygon_2(const CGAL_Triangle_2<R>& triangle);
    CGAL_Polygon_2(const CGAL_Iso_rectangle_2<R>& rectangle);
    CGAL_Polygon_2<R,Container>& operator=(const CGAL_Polygon_2<R,Container>& polygon);
    ~CGAL_Polygon_2();

#ifdef CGAL_MEMBER_TEMPLATES
    template <class InputIterator>
    CGAL_Polygon_2(InputIterator first, InputIterator last) {
      copy(first, last, back_inserter(d_container));
    }
#else
    CGAL_Polygon_2(vector<value_type>::const_iterator first,
                  vector<value_type>::const_iterator last)
      { copy(first, last, back_inserter(d_container)); }
    CGAL_Polygon_2(vector<value_type>::const_reverse_iterator first,
                  vector<value_type>::const_reverse_iterator last)
      { copy(first, last, back_inserter(d_container)); }
    CGAL_Polygon_2(list<value_type>::const_iterator first,
                  list<value_type>::const_iterator last)
      { copy(first, last, back_inserter(d_container)); }
    CGAL_Polygon_2(list<value_type>::const_reverse_iterator first,
                  list<value_type>::const_reverse_iterator last)
      { copy(first, last, back_inserter(d_container)); }
    CGAL_Polygon_2(vector<value_type>::iterator first,
                  vector<value_type>::iterator last)
      { copy(first, last, back_inserter(d_container)); }
    CGAL_Polygon_2(vector<value_type>::reverse_iterator first,
                  vector<value_type>::reverse_iterator last)
      { copy(first, last, back_inserter(d_container)); }
    CGAL_Polygon_2(list<value_type>::iterator first,
                  list<value_type>::iterator last)
      { copy(first, last, back_inserter(d_container)); }
    CGAL_Polygon_2(list<value_type>::reverse_iterator first,
                  list<value_type>::reverse_iterator last)
      { copy(first, last, back_inserter(d_container)); }
#endif    

    //--------------------------------------------------------
    //             Traversal of a polygon
    //--------------------------------------------------------

    Vertex_iterator vertices_begin()
      { return d_container.begin(); }

    Vertex_iterator vertices_end()
      { return d_container.end(); }

    Vertex_const_iterator vertices_begin() const
      { return d_container.begin(); }

    Vertex_const_iterator vertices_end() const
      { return d_container.end(); }

    Vertex_circulator vertices_circulator()
      { return Vertex_circulator(&d_container, d_container.begin()); }

    Vertex_const_circulator vertices_circulator() const
      { return Vertex_const_circulator(&d_container, d_container.begin()); }

    Edge_const_circulator edges_circulator() const
      { return Edge_const_circulator(vertices_circulator()); }

    Edge_const_iterator edges_begin() const
      { return Edge_const_iterator(&d_container, d_container.begin()); }

    Edge_const_iterator edges_end() const
      { return Edge_const_iterator(&d_container, d_container.end()); }

    //--------------------------------------------------------
    //             Access Functions
    //--------------------------------------------------------
    int size() const
      { return d_container.size(); }

    bool is_empty() const
      { return d_container.empty(); }

    const Container& container() const { return d_container; }

//---------------------------------------------------------------------------------
// these methods cause problems with the GNU compiler (since g++ 2.7.2 instantiates
// them even if they are not used)
//
//    const CGAL_Point_2<R>& operator[](int n) const
//      { return d_container[n]; }
//
//    const CGAL_Point_2<R>& vertex(int n) const
//      { return d_container[n]; }
//
//    CGAL_Segment_2<R> edge(int n) const
//      { return CGAL_Segment_2<R>(..., ...); }
//---------------------------------------------------------------------------------

    //--------------------------------------------------------
    //             Geometric predicates
    //--------------------------------------------------------

    bool is_simple() const
      { return CGAL_is_simple_2(d_container.begin(), d_container.end()); }

    bool is_convex() const
      { return CGAL_is_convex_2(d_container.begin(), d_container.end()); }

    CGAL_Orientation orientation() const
      { return CGAL_orientation_2(d_container.begin(), d_container.end()); }

    CGAL_Oriented_side oriented_side(const value_type& value) const
      { return CGAL_oriented_side_2(d_container.begin(), d_container.end(), value); }

    CGAL_Bounded_side bounded_side(const value_type& value) const
      { return CGAL_bounded_side_2(d_container.begin(), d_container.end(), value); }

    CGAL_Bbox_2 bbox() const
      {  return CGAL_bbox_2(d_container.begin(), d_container.end()); }

    R::FT area() const {
      R::FT area(0);
      CGAL_area_2(d_container.begin(), d_container.end(), area);
      return area;
    }

    Vertex_const_iterator left_vertex() const
      { return CGAL_left_vertex_2(d_container.begin(), d_container.end()); }

    Vertex_iterator left_vertex()
      { return CGAL_left_vertex_2(d_container.begin(), d_container.end()); }

    Vertex_const_iterator right_vertex() const
      { return CGAL_right_vertex_2(d_container.begin(), d_container.end()); }

    Vertex_iterator right_vertex()
      { return CGAL_right_vertex_2(d_container.begin(), d_container.end()); }

    Vertex_const_iterator top_vertex() const
      { return CGAL_top_vertex_2(d_container.begin(), d_container.end()); }

    Vertex_iterator top_vertex()
      { return CGAL_top_vertex_2(d_container.begin(), d_container.end()); }

    Vertex_const_iterator bottom_vertex() const
      { return CGAL_bottom_vertex_2(d_container.begin(), d_container.end()); }

    Vertex_iterator bottom_vertex()
      { return CGAL_bottom_vertex_2(d_container.begin(), d_container.end()); }

//    Vertex_circulator has_vertex(const value_type& value)
//      { iterator i = return find(d_container.begin(), d_container.end(), value);
//        return Vertex_circulator(&d_container, i); }
//    Vertex_const_circulator has_vertex(const value_type& value) const
//      { const_iterator i = find(d_container.begin(), d_container.end(), value);
//        return Vertex_const_circulator(&d_container, i); }

    bool is_counterclockwise_oriented() const
      { return orientation() == CGAL_COUNTERCLOCKWISE; }

    bool is_clockwise_oriented() const
      { return orientation() == CGAL_CLOCKWISE; }

    bool is_collinear_oriented() const
      { return orientation() == CGAL_COLLINEAR; }

    bool has_on_positive_side(const CGAL_Point_2<R>& q) const
      { return oriented_side(q) == CGAL_ON_POSITIVE_SIDE; }

    bool has_on_negative_side(const CGAL_Point_2<R>& q) const
      { return oriented_side(q) == CGAL_ON_NEGATIVE_SIDE; }

    bool has_on_boundary(const CGAL_Point_2<R>& q) const
      { return bounded_side(q) == CGAL_ON_BOUNDARY; }

    bool has_on_bounded_side(const CGAL_Point_2<R>& q) const
      { return bounded_side(q) == CGAL_ON_BOUNDED_SIDE; }

    bool has_on_unbounded_side(const CGAL_Point_2<R>& q) const
      { return bounded_side(q) == CGAL_ON_UNBOUNDED_SIDE; }

    //--------------------------------------------------------
    //             Update Operations
    //--------------------------------------------------------

    Vertex_iterator insert(Vertex_iterator position, const value_type& x)
      { return d_container.insert(position,x); }

    void insert(Vertex_iterator position, Vertex_iterator first, Vertex_iterator last)
      { d_container.insert(position, first, last); }

    void insert(Vertex_iterator position, int n, const value_type& x)
      { d_container.insert(position, n, x); }

    void erase(Vertex_iterator position)
      { d_container.erase(position); }

    void erase(Vertex_iterator first, Vertex_iterator last)
      { d_container.erase(first,last); }

    void append(const value_type& x)
      { d_container.insert(d_container.end(), x); }

    void reverse_orientation()
      {
        if (size() <= 1)
          return;

        Container::iterator i = d_container.begin();
        reverse(++i, d_container.end());
      }

    //--------------------------------------------------------
    //             Miscellaneous
    //--------------------------------------------------------

    CGAL_Polygon_2<R,Container> transform(const CGAL_Aff_transformation_2<R>& t) const
      {
        CGAL_Polygon_2<R,Container> result;
        for (Vertex_const_iterator i = vertices_begin(); i != vertices_end(); ++i)
          result.append(t(*i));
        return result;
      }

    bool identical(const CGAL_Polygon_2<R,Container> &q) const
      { return this == &q; }
};

//-----------------------------------------------------------------------//
//               globally defined operators for CGAL_Polygon_2
//-----------------------------------------------------------------------//

template <class R, class Container>
istream &operator>>(istream &is, CGAL_Polygon_2<R,Container>&);

template <class R, class Container>
ostream &operator<<(ostream &os, const CGAL_Polygon_2<R,Container>&);

template <class R, class Container1, class Container2>
bool operator==( const CGAL_Polygon_2<R,Container1> &x, const
CGAL_Polygon_2<R,Container2>
&y );

template <class R, class Container1, class Container2>
inline bool operator!=( const CGAL_Polygon_2<R,Container1> &x, const
CGAL_Polygon_2<R,Container2> &y );

//-----------------------------------------------------------------------//
//                         implementation
//-----------------------------------------------------------------------//

#ifdef CGAL_INCLUDE_TEMPLATE_CODE
#include "Polygon_2.C"
#endif

template <class R, class Container>
inline
bidirectional_iterator_tag
iterator_category(const CGAL_Polygon_2_edge_iterator<R, Container>&)
{
  return bidirectional_iterator_tag();
}

template <class R, class Container>
inline
CGAL_Segment_2<R>
value_type(const CGAL_Polygon_2_edge_iterator<R,Container>&)
{
  return CGAL_Segment_2<R>();
}

template <class R, class Container>
inline
CGAL_Polygon_2<R,Container>::CGAL_Polygon_2()
{ }

template <class R, class Container>
inline
CGAL_Polygon_2<R,Container>::CGAL_Polygon_2(const CGAL_Polygon_2<R,Container>& polygon)
  : d_container(polygon.d_container)
{ }

template <class R, class Container>
inline
CGAL_Polygon_2<R,Container>::CGAL_Polygon_2(const CGAL_Point_2<R>& point)
{
  append(point);
}

template <class R, class Container>
inline
CGAL_Polygon_2<R,Container>::CGAL_Polygon_2(const CGAL_Segment_2<R>& segment)
{
  append(segment[0]);
  append(segment[1]);
}

template <class R, class Container>
inline
CGAL_Polygon_2<R,Container>::CGAL_Polygon_2(const CGAL_Triangle_2<R>& triangle)
{
  append(triangle[0]);
  append(triangle[1]);
  append(triangle[2]);
}

template <class R, class Container>
inline
CGAL_Polygon_2<R,Container>::CGAL_Polygon_2(const CGAL_Iso_rectangle_2<R>& rectangle)
{
  append(rectangle[0]);
  append(rectangle[1]);
  append(rectangle[2]);
  append(rectangle[3]);
}

template <class R, class Container>
inline
CGAL_Polygon_2<R,Container>&
CGAL_Polygon_2<R,Container>::operator=(const CGAL_Polygon_2<R,Container>& polygon)
{
  d_container = polygon.d_container;
  return *this;
}

template <class R, class Container>
inline
CGAL_Polygon_2<R,Container>::~CGAL_Polygon_2()
{ }

template <class R, class Container1, class Container2>
inline
bool
operator!=( const CGAL_Polygon_2<R,Container1> &x, const CGAL_Polygon_2<R,Container2> &y )
{
  return !(x==y);
}

template <class R, class Container1, class Container2>
bool operator==( const CGAL_Polygon_2<R,Container1> &x,
                 const CGAL_Polygon_2<R,Container2> &y )
{
  CGAL_kernel_precondition( (x.size() != 0) || (y.size() != 0));

  if (x.size() != y.size()) return false;

  CGAL_Polygon_2<R,Container1>::Vertex_const_iterator x_iter = x.vertices_begin();
  CGAL_Polygon_2<R,Container2>::Vertex_const_iterator y_iter =
    find(y.vertices_begin(), y.vertices_end(), *x.vertices_begin());

  // if y doesn't contain the first point of x ...
  if (y_iter == y.vertices_end()) return false;

  ++x_iter;
  ++y_iter;

  while (y_iter != y.vertices_end()) {
    if (*x_iter != *y_iter) return false;
    ++x_iter;
    ++y_iter;
  }

  y_iter = y.vertices_begin();
  while (x_iter != x.vertices_end()) {
    if (*x_iter != *y_iter) return false;
    ++x_iter;
    ++y_iter;
  }

  return true;
}

template <class R, class Container>
istream &operator>>(istream &is, CGAL_Polygon_2<R,Container>& p)
{
  int n; // number of vertices
  is >> n;

  R::Point_2 point;

  for (int i=0; i<n; i++) {
    is >> point;
    p.append(point);
  }

  return is;
}

template <class R, class Container>
ostream &operator<<(ostream &os, const CGAL_Polygon_2<R,Container>& p)
{
  CGAL_Polygon_2<R,Container>::Vertex_const_iterator i;

  switch(os.iword(CGAL_IO::mode)) {
    case CGAL_IO::ASCII :
      os << p.size() << ' ';
      for (i = p.vertices_begin(); i != p.vertices_end(); ++i) {
        os << *i << ' ';
      }
      return os;

    case CGAL_IO::BINARY :
      os << p.size();
      for (i = p.vertices_begin(); i != p.vertices_end(); ++i) {
        os << *i;
      }
      return os;

    default:
      os << "Polygon_2(" << endl;
      for (i = p.vertices_begin(); i != p.vertices_end(); ++i) {
        os << "  " << *i << endl;
      }
      os << ")" << endl;
      return os;
  }
}

#endif

