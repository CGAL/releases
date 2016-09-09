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
// file          : include/CGAL/Polygon_2.C
// package       : Polygon (2.4.7)
// source        :
// revision      : 1.8a
// revision_date : 13 Mar 1998
// author(s)     : Wieger Wesselink
//
// coordinator   : Utrecht University
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_POLYGON_2_H
#include <CGAL/Polygon_2.h>
#endif // CGAL_POLYGON_2_H

//-----------------------------------------------------------------------//
//                          operator==
//-----------------------------------------------------------------------//

CGAL_BEGIN_NAMESPACE

template <class _Traits, class _Container1, class _Container2>
bool operator==( const Polygon_2<_Traits,_Container1> &x,
                 const Polygon_2<_Traits,_Container2> &y )
{
  CGAL_polygon_precondition( (x.size() != 0) || (y.size() != 0));

  if (x.size() != y.size()) return false;

  typename Polygon_2<_Traits,_Container1>::Vertex_const_iterator x_iter =
    x.vertices_begin();

  typename Polygon_2<_Traits,_Container2>::Vertex_const_iterator y_iter =
    std::find(y.vertices_begin(), y.vertices_end(), *x.vertices_begin());

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

//-----------------------------------------------------------------------//
//                          operator>>
//-----------------------------------------------------------------------//

template <class _Traits, class _Container>
istream &operator>>(istream &is, Polygon_2<_Traits,_Container>& p)
{
  int n; // number of vertices
  is >> n;

  typename _Traits::Point_2 point;

  for (int i=0; i<n; i++) {
    is >> point;
    p.push_back(point);
  }

  return is;
}

//-----------------------------------------------------------------------//
//                          operator<<
//-----------------------------------------------------------------------//

template <class _Traits, class _Container>
ostream &operator<<(ostream &os, const Polygon_2<_Traits,_Container>& p)
{
  typename Polygon_2<_Traits,_Container>::Vertex_const_iterator i;

  switch(os.iword(IO::mode)) {
    case IO::ASCII :
      os << p.size() << ' ';
      for (i = p.vertices_begin(); i != p.vertices_end(); ++i) {
        os << *i << ' ';
      }
      return os;

    case IO::BINARY :
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

CGAL_END_NAMESPACE

//-----------------------------------------------------------------------//
//                          transform
//-----------------------------------------------------------------------//

#ifdef CGAL_REP_CLASS_DEFINED
#ifndef CGAL_POLYGON_TRAITS_2_H
#include <CGAL/Polygon_traits_2.h>
#endif // CGAL_POLYGON_TRAITS_2_H

CGAL_BEGIN_NAMESPACE

template <class Transformation, class _Traits, class _Container>
Polygon_2<_Traits,_Container>
transform(const Transformation& t, const Polygon_2<_Traits,_Container>& p)
{
  typedef typename Polygon_2<_Traits,_Container>::Vertex_const_iterator VI;
  Polygon_2<_Traits,_Container> result;
  for (VI i = p.vertices_begin(); i != p.vertices_end(); ++i)
    result.push_back(t(*i));
  return result;
}

CGAL_END_NAMESPACE

#endif // CGAL_REP_CLASS_DEFINED

