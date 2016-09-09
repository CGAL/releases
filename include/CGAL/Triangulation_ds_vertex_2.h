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
// file          : include/CGAL/Triangulation_ds_vertex_2.h
// package       : Triangulation (2.10)
// source        : $Source: /u/alcor/0/prisme_util/CGAL/Local/cvsroot/Triangulation/include/CGAL/Triangulation_ds_vertex_2.h,v $
// revision      : $Revision: 1.4.1.7 $
// revision_date : $Date: 1998/12/09 10:41:34 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_DS_VERTEX_2_H
#define CGAL_TRIANGULATION_DS_VERTEX_2_H

#include <CGAL/Triangulation_short_names_2.h>
#include <CGAL/Triangulation_utils_2.h>
#include <CGAL/Triangulation_ds_circulators_2.h>


template <class Vb, class Fb >
class  CGAL_Triangulation_ds_vertex_2 
  : public Vb,
    public CGAL_Triangulation_cw_ccw_2
{
public:
  typedef typename Vb::Point Point;
  typedef CGAL_Triangulation_ds_vertex_2<Vb,Fb> Vertex;
  typedef CGAL_Triangulation_ds_face_2<Vb,Fb> Face;
  typedef pair< Face*,int> Edge;
  typedef CGAL_Triangulation_ds_face_circulator_2<Vertex,Face> Face_circulator;
  typedef CGAL_Triangulation_ds_vertex_circulator_2<Vertex,Face> 
                                                           Vertex_circulator;
  typedef CGAL_Triangulation_ds_edge_circulator_2<Vertex,Face> Edge_circulator;

  CGAL_Triangulation_ds_vertex_2()
    : Vb()
  {}
    
  CGAL_Triangulation_ds_vertex_2(const Point & p)
    :  Vb(p)
  {}
    
  CGAL_Triangulation_ds_vertex_2(const Point & p, Face * f)
    :  Vb(p, f )
  {}

  // set_point()
  // point()
  //inherited from Vb

  inline 
  void set_face(Face* f)
  {
    Vb::set_face(f);
  }

  inline Face* face() const
  {
    return ( (Face *) (Vb::face()) );
  }
    
  int degree() const
  {
    Face* f = face();
    
    if (f == NULL) {
      return 0;
    }
    int i = f->index(this);
    
    Face* ptr1 = f->neighbor(ccw(i));
    Face* ptr2 = f;
    f = f->neighbor(cw(i));
    
    int count = 2;
    while(ptr1 != f){
      count++;
      i = ptr1->index(ptr2);
      ptr2 = ptr1;
      ptr1 = ptr1->neighbor(cw(i));
    }
    return count;
  }
  
  inline Vertex_circulator incident_vertices() 
  {
    return Vertex_circulator(this, face());
  }
    
  inline Face_circulator incident_faces() 
  {
    return Face_circulator(this, face());
  }
    
  inline Face_circulator incident_faces(const Face* f) 
  {
    return Face_circulator(this, f);
  }
    
  inline Edge_circulator incident_edges() 
  {
    return Edge_circulator(this, face());
  }
       
  inline Edge_circulator incident_edges(const Face* f) 
  {
    return Edge_circulator(this, f);
  }
    
   bool is_valid(bool verbose = false, int level = 0) const
  {
    bool result = Vb::is_valid();
    CGAL_triangulation_assertion(result);
    CGAL_triangulation_assertion(face() != NULL);
    result = result && face()->has_vertex(this);
    return result;
  }
};

#endif //CGAL_TRIANGULATION_DS_VERTEX_2_H
