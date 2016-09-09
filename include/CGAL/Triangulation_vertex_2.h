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
// file          : include/CGAL/Triangulation_vertex_2.h
// package       : Triangulation (4.69)
// source        : $RCSfile: Triangulation_vertex_2.h,v $
// revision      : $Revision: 1.10 $
// revision_date : $Date: 2000/06/08 15:10:30 $
//
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_VERTEX_2_H
#define CGAL_TRIANGULATION_VERTEX_2_H

#include <utility>
#include <CGAL/Pointer.h>
#include <CGAL/Triangulation_short_names_2.h>
#include <CGAL/Triangulation_default_data_structure_2.h>
#include <CGAL/Triangulation_circulators_2.h>

CGAL_BEGIN_NAMESPACE 

template < class Gt, class Tds >
class Triangulation_face_2;

template < class Gt, class Tds >
class Triangulation_vertex_handle_2;

template < class Gt, class Tds >
class Triangulation_face__handle_2;

template<class Gt,  class Tds>
class Triangulation_face_circulator_2;

template<class Gt,  class Tds>
class Triangulation_vertex_circulator_2;

template<class Gt, class Tds>
class Triangulation_edge_circulator_2;


template<class Gt, class Tds >
class Triangulation_vertex_2  : public Tds::Vertex
{
public:
  
  typedef Tds Triangulation_data_structure;

  typedef Gt  Geom_traits;
  typedef typename Geom_traits::Point_2 Point;
  typedef typename Geom_traits::Segment_2 Segment;
  typedef typename Geom_traits::Triangle_2 Triangle;

  typedef typename Tds::Vertex Ve;
  typedef typename Tds::Face Fa;

  typedef Triangulation_face_2<Gt,Tds> Face;
  typedef Triangulation_vertex_2<Gt,Tds> Tr_vertex;
  
  typedef Triangulation_vertex_handle_2<Gt,Tds> Vertex_handle;
  typedef Triangulation_face_handle_2<Gt,Tds> Face_handle;
  typedef std::pair<Face_handle, int>     Edge;

  typedef Triangulation_face_circulator_2<Gt,Tds>      Face_circulator;
  typedef Triangulation_edge_circulator_2<Gt,Tds>      Edge_circulator;
  typedef Triangulation_vertex_circulator_2<Gt,Tds>    Vertex_circulator;

  
  Triangulation_vertex_2()     : Ve()   {}
  Triangulation_vertex_2(const Point & p)    :  Ve(p)   {}
  Triangulation_vertex_2(const Point & p, const Face_handle& f)
    :  Ve(p, &(*f))
  {}

  void set_face(const Face_handle& f);
  Face_handle face() const;
  Vertex_handle handle() const;
        
  //inherited :
  // cw(i), ccw(i)
  // degree(), point(), is_on_boundary, set_point(p)

  Vertex_circulator incident_vertices() const;
  Vertex_circulator incident_vertices(Face_handle f) const;
  Face_circulator incident_faces() const;
  Face_circulator incident_faces(Face_handle f) const;
  Edge_circulator incident_edges() const;
  Edge_circulator incident_edges(Face_handle f) const;
   
};

template<class Gt, class Tds>
inline void
Triangulation_vertex_2<Gt,Tds>::
set_face(const Face_handle& f)
{
  Ve::set_face(&(*f));
}
    
template<class Gt, class Tds>
inline   
Triangulation_face_handle_2<Gt,Tds>
Triangulation_vertex_2<Gt,Tds>::
face() const
{
  return  (Face *)Ve::face();
}
        
template<class Gt, class Tds>
inline   
Triangulation_vertex_handle_2<Gt,Tds>
Triangulation_vertex_2<Gt,Tds>::
handle() const
{
  Tr_vertex * ncthis = (Tr_vertex *) this;
  return Vertex_handle(ncthis);
}
      
template<class Gt, class Tds>
inline   
Triangulation_vertex_circulator_2<Gt,Tds>
Triangulation_vertex_2<Gt,Tds>:: 
incident_vertices() const
{
  return Vertex_circulator(handle(), face());
}

template<class Gt, class Tds>
inline   
Triangulation_vertex_circulator_2<Gt,Tds>
Triangulation_vertex_2<Gt,Tds>::
incident_vertices(Face_handle f) const
{
  return Vertex_circulator(handle(), f);
} 

template<class Gt, class Tds>
inline   
Triangulation_face_circulator_2<Gt,Tds>
Triangulation_vertex_2<Gt,Tds>::
incident_faces() const
{
  return Face_circulator(handle(), face());
}
    
template<class Gt, class Tds>
inline   
Triangulation_face_circulator_2<Gt,Tds>
Triangulation_vertex_2<Gt,Tds>::
incident_faces(Face_handle f) const
{
  return Face_circulator(handle(), f);
}
    
template<class Gt, class Tds>
inline   
Triangulation_edge_circulator_2<Gt,Tds>
Triangulation_vertex_2<Gt,Tds>:: 
incident_edges() const
{
  return Edge_circulator(handle(), face());
}
 
template<class Gt, class Tds>
inline   
Triangulation_edge_circulator_2<Gt,Tds>
Triangulation_vertex_2<Gt,Tds>:: 
incident_edges(Face_handle f) const
{
  return Edge_circulator(handle(), f);
}

CGAL_END_NAMESPACE

#endif //CGAL_TRIANGULATION_VERTEX_2_H
