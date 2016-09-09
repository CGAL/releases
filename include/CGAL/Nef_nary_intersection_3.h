// Copyright (c) 1997-2002,2005,2008 Max-Planck-Institute Saarbruecken (Germany).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Nef_3/include/CGAL/Nef_nary_intersection_3.h $
// $Id: Nef_nary_intersection_3.h 56667 2010-06-09 07:37:13Z sloriot $
// 
//
// Author(s): Peter Hachenberger

#ifndef CGAL_NEF_NARY_INTERSECTION_3_H
#define CGAL_NEF_NARY_INTERSECTION_3_H

#include <list>

namespace CGAL {

template<class Polyhedron>
class Nef_nary_intersection_3 {

  int inserted;
  std::list<Polyhedron> queue;
  typedef typename std::list<Polyhedron>::iterator pit;
  Polyhedron empty;

 public:
  Nef_nary_intersection_3() : inserted(0) {}
  
  void intersect() {
    pit i1(queue.begin()), i2(i1);
    ++i2;

    Polyhedron tmp(*i1 * *i2);

    queue.pop_front();
    queue.pop_front();
    queue.push_front(tmp);
  }

  void add_polyhedron(const Polyhedron& P) {
    queue.push_front(P);
    ++inserted;
    for(int i=2;(inserted%i) == 0; i*=2) {
      intersect();
    }
  }

  Polyhedron get_intersection() {

    while(queue.size() > 1)
      intersect();
    inserted = 0;
    return queue.front();
  }
};

} //namespace CGAL
#endif // CGAL_NEF_NARY_INTERSECTION_3_H
