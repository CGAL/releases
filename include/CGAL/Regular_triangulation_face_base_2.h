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
// file          : include/CGAL/Regular_triangulation_face_base_2.h
// package       : Triangulation (3.17)
// source        : $RCSfile: Regular_triangulation_face_base_2.h,v $
// revision      : $Revision: 1.1.1.6 $
// revision_date : $Date: 1999/04/30 14:09:22 $
// author(s)     : Frederic Fichel, Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_REGULAR_TRIANGULATION_FACE_BASE_2_H
#define CGAL_REGULAR_TRIANGULATION_FACE_BASE_2_H

#include <CGAL/triangulation_assertions.h>
#include <CGAL/Triangulation_short_names_2.h>

CGAL_BEGIN_NAMESPACE


template <class Gt>
class Regular_triangulation_face_base_2
  :  public Triangulation_face_base_2<Gt>
{
public:
  typedef Gt Geom_traits;
  typedef Triangulation_face_base_2<Gt> Fbase;
  typedef Regular_triangulation_face_base_2<Gt> Regular_face_base;
  typedef typename Gt::Point  Point;
  typedef std::list<Point> Point_list;

protected:
 Point_list  plist;

public:
 Regular_triangulation_face_base_2()
    : Fbase(), plist()
  {}

  Regular_triangulation_face_base_2(void* v0, void* v1, void* v2)
    : Fbase(v0,v1,v2),plist() 
  { }

  Regular_triangulation_face_base_2(void* v0, void* v1, void* v2,
					     void* n0, void* n1, void* n2)
    : Fbase(v0,v1,v2,n0,n1,n2), plist()
  { }

  ~Regular_triangulation_face_base_2()
  { 
    plist.clear();
  }

  Point_list& point_list()
  {
    return plist;
  }

};

CGAL_END_NAMESPACE 

#endif // CGAL_REGULAR_TRIANGULATION_FACE_BASE_2_H
