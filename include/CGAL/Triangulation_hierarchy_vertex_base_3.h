// ======================================================================
//
// Copyright (c) 1998, 2001 The CGAL Consortium

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
// file          : include/CGAL/Triangulation_hierarchy_vertex_base_3.h
// package       : Triangulation_3 (1.83)
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2001/06/21 18:03:30 $
// author(s)     : Olivier Devillers
//                 Sylvain Pion
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_HIERARCHY_VERTEX_BASE_3_H
#define CGAL_TRIANGULATION_HIERARCHY_VERTEX_BASE_3_H

#include <CGAL/basic.h>
#include <CGAL/Triangulation_short_names_3.h>

CGAL_BEGIN_NAMESPACE

template < class Vbb>
class Triangulation_hierarchy_vertex_base_3
  : public Vbb
{
public:
  typedef Vbb                      V_Base;
  typedef typename V_Base::Point   Point;

  Triangulation_hierarchy_vertex_base_3()
    : V_Base(), _up(0), _down(0) {}

  Triangulation_hierarchy_vertex_base_3(const Point & p, void* f)
    : V_Base(p,f), _up(0), _down(0) {}

  Triangulation_hierarchy_vertex_base_3(const Point & p)
    : V_Base(p), _up(0), _down(0) {}

  void* up() const {return _up;}
  void* down() const {return _down;}
  void set_up(void *u) {_up=u;}
  void set_down(void *d) {if (this) _down=d;}

private:
  void* _up;    // same vertex one level above
  void* _down;  // same vertex one level below
};

CGAL_END_NAMESPACE

#endif // CGAL_TRIANGULATION_HIERARCHY_VERTEX_BASE_3_H
