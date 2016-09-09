// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/Polygon_2.C
// package       : Polygon (2.19)
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

#include <CGAL/Polygon_2.h>

//-----------------------------------------------------------------------//
//                          operator==
//-----------------------------------------------------------------------//

CGAL_BEGIN_NAMESPACE

template <class Traits_P, class Container1_P, class Container2_P>
bool operator==( const Polygon_2<Traits_P,Container1_P> &x,
                 const Polygon_2<Traits_P,Container2_P> &y )
{
  CGAL_polygon_precondition( (x.size() != 0) || (y.size() != 0));

  if (x.size() != y.size()) return false;
  typename Polygon_2<Traits_P,Container1_P>::Vertex_const_iterator x_iter =
    x.vertices_begin();

  typename Polygon_2<Traits_P,Container2_P>::Vertex_const_iterator y_iter =
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

template <class Traits_P, class Container_P>
std::istream &operator>>(std::istream &is, Polygon_2<Traits_P,Container_P>& p)
{
  int n; // number of vertices
  is >> n;
  typename Traits_P::Point_2 point;
 
  if (is) {
      p.erase(p.vertices_begin(),p.vertices_end());
      for (int i=0; i<n; i++) {
        is >> point;
        p.push_back(point);
      }
  }
 
  return is;
}

//-----------------------------------------------------------------------//
//                          operator<<
//-----------------------------------------------------------------------//

template <class Traits_P, class Container_P>
std::ostream &operator<<(std::ostream &os, const Polygon_2<Traits_P,Container_P>& p)
{
  typename Polygon_2<Traits_P,Container_P>::Vertex_const_iterator i;

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
      os << "Polygon_2(" << std::endl;
      for (i = p.vertices_begin(); i != p.vertices_end(); ++i) {
        os << "  " << *i << std::endl;
      }
      os << ")" << std::endl;
      return os;
  }
}

CGAL_END_NAMESPACE

//-----------------------------------------------------------------------//
//                          transform
//-----------------------------------------------------------------------//

#ifdef CGAL_REP_CLASS_DEFINED
#include <CGAL/Polygon_traits_2.h>

CGAL_BEGIN_NAMESPACE

template <class Transformation, class Traits_P, class Container_P>
Polygon_2<Traits_P,Container_P>
transform(const Transformation& t, const Polygon_2<Traits_P,Container_P>& p)
{
  typedef typename Polygon_2<Traits_P,Container_P>::Vertex_const_iterator VI;
  Polygon_2<Traits_P,Container_P> result;
  for (VI i = p.vertices_begin(); i != p.vertices_end(); ++i)
    result.push_back(t(*i));
  return result;
}

CGAL_END_NAMESPACE

#endif // CGAL_REP_CLASS_DEFINED

