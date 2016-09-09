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
// file          : include/CGAL/Constrained_triangulation_traits_2.h
// author(s)     : Mariette Yvinec
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#ifndef CGAL_CONSTRAINED_TRIANGULATION_TRAITS_2_H
#define CGAL_CONSTRAINED_TRIANGULATION_TRAITS_2_H

#include <CGAL/Constrained_triangulation_vertex.h>
#include <CGAL/Constrained_triangulation_face.h>

template < class T >
class CGAL_Constrained_triangulation_traits_2
  : public T
{
public:
    typedef typename T::Rep Rep;
    typedef typename T::Point Point;
    typedef typename T::Segment Segment;
    typedef typename T::Triangle Triangle;

    typedef typename T::Distance Distance;

    typedef CGAL_Constrained_triangulation_vertex
      <typename T::Vertex,typename T::Face> Vertex;
    typedef CGAL_Constrained_triangulation_face
      <typename T::Vertex,typename T::Face> Face;
    typedef typename Vertex::Vertex_handle Vertex_handle;
    typedef typename Face::Face_handle Face_handle;

    typedef pair<Point,Point> Constraint;
};

#endif // CGAL_CONSTRAINED_TRIANGULATION_TRAITS_2_H
