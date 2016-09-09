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
// file          : include/CGAL/Polygon_2.C
// package       : Polygon (1.10)
// source        :
// revision      : 1.8a
// revision_date : 13 Mar 1998
// author(s)     : Wieger Wesselink
//
// coordinator   : Utrecht University
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#include <CGAL/Polygon_2.h>

//-----------------------------------------------------------------------//
//                          operator==
//-----------------------------------------------------------------------//

template <class _Traits, class _Container1, class _Container2>
bool operator==( const CGAL_Polygon_2<_Traits,_Container1> &x,
                 const CGAL_Polygon_2<_Traits,_Container2> &y )
{
  CGAL_polygon_precondition( (x.size() != 0) || (y.size() != 0));

  if (x.size() != y.size()) return false;

  typename CGAL_Polygon_2<_Traits,_Container1>::Vertex_const_iterator x_iter =
    x.vertices_begin();

  typename CGAL_Polygon_2<_Traits,_Container2>::Vertex_const_iterator y_iter =
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

//-----------------------------------------------------------------------//
//                          operator>>
//-----------------------------------------------------------------------//

template <class _Traits, class _Container>
istream &operator>>(istream &is, CGAL_Polygon_2<_Traits,_Container>& p)
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
ostream &operator<<(ostream &os, const CGAL_Polygon_2<_Traits,_Container>& p)
{
  typename CGAL_Polygon_2<_Traits,_Container>::Vertex_const_iterator i;

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

//-----------------------------------------------------------------------//
//                          transform
//-----------------------------------------------------------------------//

#ifdef CGAL_REP_CLASS_DEFINED
#include <CGAL/Polygon_traits_2.h>
template <class Transformation, class _Traits, class _Container>
CGAL_Polygon_2<_Traits,_Container>
CGAL_transform(const Transformation& t, const CGAL_Polygon_2<_Traits,_Container>& p)
{
  typedef typename CGAL_Polygon_2<_Traits,_Container>::Vertex_const_iterator VI;
  CGAL_Polygon_2<_Traits,_Container> result;
  for (VI i = p.vertices_begin(); i != p.vertices_end(); ++i)
    result.push_back(t(*i));
  return result;
}
#endif // CGAL_REP_CLASS_DEFINED

