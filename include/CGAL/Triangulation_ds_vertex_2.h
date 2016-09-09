// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/Triangulation_ds_vertex_2.h
// package       : Triangulation_2 (7.32)
// source        : $RCSfile: Triangulation_ds_vertex_2.h,v $
// revision      : $Revision: 1.17 $
// revision_date : $Date: 2002/01/24 14:24:29 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_DS_VERTEX_2_H
#define CGAL_TRIANGULATION_DS_VERTEX_2_H

#include <CGAL/Triangulation_short_names_2.h>

CGAL_BEGIN_NAMESPACE

template <class Tds>
class  Triangulation_ds_vertex_2 
  : public Tds::Vertex_base,    
    public Triangulation_cw_ccw_2
{
public:
  typedef typename Tds::Vertex_base        Vb;
  typedef typename Tds::Vertex             Vertex;
  typedef typename Tds::Face               Face;
  typedef typename Tds::Edge               Edge;
  typedef typename Tds::Vertex_handle      Vertex_handle;
  typedef typename Tds::Face_handle        Face_handle;
  typedef typename Tds::Vertex_circulator  Vertex_circulator;
  typedef typename Tds::Face_circulator    Face_circulator;
  typedef typename Tds::Edge_circulator    Edge_circulator;
  //typedef typename Vb::Point               Point;
 
  //CREATORS
  Triangulation_ds_vertex_2() : Vb() {}

  //SETTING
  void set_face(Face_handle f)  { Vb::set_face(&*f);}

  //ACCESS
  //Vertex_handle handle() const {return &*this;}
  Vertex_handle handle() {return const_cast<Vertex*>(this); }
  Face_handle face() const {return static_cast<Face*>(Vb::face()) ;}
  int degree(); //should be const

  // the following should be const
  // when Face_circulator, Vertex_circulator and Edge_circulator
  // are created from 
  // Face_const_handle and Face_const_vertex
  Vertex_circulator incident_vertices()     
    {return Vertex_circulator(this);}
 
  Vertex_circulator incident_vertices( Face_handle f)  
    {return Vertex_circulator(this,f);}
  
  Face_circulator incident_faces()  
    { return Face_circulator(this) ;}
  
  Face_circulator incident_faces( Face_handle f)    
    { return Face_circulator(this, f);}
  
  Edge_circulator incident_edges()   
    { return Edge_circulator(this);}
  
  Edge_circulator incident_edges( Face_handle f)  
    { return Edge_circulator(this, f);}
  
  bool is_valid(bool verbose = false, int level = 0);

};

template <class Tds>
int
Triangulation_ds_vertex_2 <Tds> ::
degree() //const
{
  int count = 0;
  Vertex_circulator vc = incident_vertices(), done(vc);
  if ( ! vc.is_empty()) {
    do { 
      count += 1;
    } while (++vc != done);
  }
  return count;
}


    
template <class Tds>
bool 
Triangulation_ds_vertex_2<Tds> ::  
is_valid(bool verbose, int level) 
{
  bool result = Vb::is_valid(verbose, level);
  CGAL_triangulation_assertion(result);
  if (face() != NULL) { // face==NULL if dim <0
    result = result && face()->has_vertex(handle());
  }
  return result;
}

CGAL_END_NAMESPACE

#endif //CGAL_TRIANGULATION_DS_VERTEX_2_H
