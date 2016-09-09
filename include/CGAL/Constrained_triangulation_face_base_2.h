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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/Constrained_triangulation_face_base_2.h
// package       : Triangulation (2.10)
// source        : $Source: /u/alcor/0/prisme_util/CGAL/Local/cvsroot/Triangulation/include/CGAL/Constrained_triangulation_face_base_2.h,v $
// revision      : $Revision: 1.6.1.6 $
// revision_date : $Date: 1998/12/08 16:30:33 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_CONSTRAINED_TRIANGULATION_FACE_BASE_2_H
#define CGAL_CONSTRAINED_TRIANGULATION_FACE_BASE_2_H

#include <CGAL/triangulation_assertions.h>
#include <CGAL/Triangulation_short_names_2.h>


template <class Gt>
class CGAL_Constrained_triangulation_face_base_2
  :  public CGAL_Triangulation_face_base_2<Gt>
{
public:
  typedef Gt Geom_traits;
  typedef CGAL_Triangulation_face_base_2<Gt> Fab;
  typedef CGAL_Constrained_triangulation_face_base_2<Gt> Constrained_face_base;
  typedef typename Gt::Point  Point;

protected:
  bool C[3];
 
public:
  CGAL_Constrained_triangulation_face_base_2()
    : Fab()
  {
    set_constraints(false,false,false);
  }

  CGAL_Constrained_triangulation_face_base_2(void* v0, void* v1, void* v2)
    : Fab(v0,v1,v2)
  {
    set_constraints(false,false,false);
  }

  CGAL_Constrained_triangulation_face_base_2(void* v0, void* v1, void* v2,
					     void* n0, void* n1, void* n2)
    : Fab(v0,v1,v2,n0,n1,n2)
  {
    set_constraints(false,false,false);
  }


  CGAL_Constrained_triangulation_face_base_2(void* v0, void* v1, void* v2,
					     void* n0, void* n1, void* n2,
					     bool c0, bool c1, bool c2 )
    : Fab(v0,v1,v2,n0,n1,n2)
  {
    set_constraints(c0,c1,c2);
  }

  void set_constraints(bool c0, bool c1, bool c2)
  {
    C[0]=c0;
    C[1]=c1;
    C[2]=c2;
  }

  void set_constraint(int i, bool b)
  {
    CGAL_triangulation_precondition( i == 0 || i == 1 || i == 2);
    C[i] = b;
  }
    
  bool is_constrained(int i) const
  {
    return(C[i]);
  }
  
  bool is_valid(bool verbose = false, int level = 0) const
  {
    bool result = Fab::is_valid();
    CGAL_triangulation_assertion(result);
    for(int i = 0; i < 3; i++) {
      Constrained_face_base*  n = (Constrained_face_base*)neighbor(i);
      if(n != NULL){
	 // The following seems natural, but it may fail if the faces
	// this and n are neighbors on two edges (1-dim triangulation,
	// with infinite faces
	// int ni = n->index(this);//
	int ni = cw(n->vertex_index(vertex(cw(i))));
	result = result && ( is_constrained(i) == n->is_constrained(ni));
      }
    }
    return (result);
  }
};

  
#endif //CGAL_CONSTRAINED_TRIANGULATION_FACE_BASE_2_H







