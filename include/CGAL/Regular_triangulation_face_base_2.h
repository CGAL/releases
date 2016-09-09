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
// file          : include/CGAL/Regular_triangulation_face_base_2.h
// package       : Triangulation (4.69)
// source        : $RCSfile: Regular_triangulation_face_base_2.h,v $
// revision      : $Revision: 1.9 $
// revision_date : $Date: 2000/06/30 09:22:03 $
// author(s)     : Frederic Fichel, Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_REGULAR_TRIANGULATION_FACE_BASE_2_H
#define CGAL_REGULAR_TRIANGULATION_FACE_BASE_2_H

#include <list>
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
  typedef typename Gt::Weighted_point   Weighted_point;
  typedef std::list<Weighted_point>     Weighted_point_list;

protected:
 Weighted_point_list  plist;

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

  Weighted_point_list& point_list()
  {
    return plist;
  }

};

CGAL_END_NAMESPACE 

#endif // CGAL_REGULAR_TRIANGULATION_FACE_BASE_2_H
