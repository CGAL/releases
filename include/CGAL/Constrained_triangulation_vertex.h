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
// file          : include/CGAL/Constrained_triangulation_vertex.h
// author(s)     : Mariette Yvinec
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#ifndef CGAL_CONSTRAINED_TRIANGULATION_VERTEX_H
#define CGAL_CONSTRAINED_TRIANGULATION_VERTEX_H

#include <CGAL/Pointer.h>

/*
#include <CGAL/Constrained_triangulation_face.h>
#include <CGAL/Triangulation_vertex_circulator.h>
#include <CGAL/Triangulation_edge_circulator.h>
#include <CGAL/Triangulation_face_circulator.h>
*/

template < class Ve, class Fa >
class CGAL_Constrained_triangulation_face;

template < class Ve, class Fa >
class CGAL_Triangulation_vertex_circulator;

template < class Ve, class Fa >
class CGAL_Triangulation_edge_circulator;

template < class Ve, class Fa >
class CGAL_Triangulation_face_circulator;

template < class Va, class Fa >
class CGAL_Constrained_triangulation_vertex
  :  public Va
{
public:
    typedef typename Va::Point Point;
    typedef CGAL_Constrained_triangulation_vertex<Va,Fa>  Vertex;
    typedef CGAL_Constrained_triangulation_face<Va,Fa>  Face;
    typedef CGAL_Pointer<Vertex> Vertex_handle;
    typedef typename Face::Face_handle Face_handle;
    typedef CGAL_Triangulation_vertex_circulator<Vertex,Face> Vertex_circulator;
    typedef CGAL_Triangulation_edge_circulator<Vertex,Face> Edge_circulator;
    typedef CGAL_Triangulation_face_circulator<Vertex,Face> Face_circulator;
    CGAL_Constrained_triangulation_vertex()
      : Va()
    {
    }
    
    CGAL_Constrained_triangulation_vertex(const Point & p)
      :  Va(p)
    {
    }
    
    CGAL_Constrained_triangulation_vertex(const Point & p, Face_handle f)
      :  Va(p,(*f).Fa::handle())
    {
    }
    void set_face(Face_handle f)
    {
        Va::set_face( (*f).Fa::handle());
    }
    
    Vertex_handle handle()
    {
            return Vertex_handle(this);
    }
    
    Face_handle face()
    {
           return (Face_handle((Face *) &(*( Va::face() ))) );
    }
    
    Vertex_circulator incident_vertices()
    {
        return Vertex_circulator(handle(), Vertex::face());
    }
    
    Face_circulator incident_faces()
    {
        return Face_circulator(handle(), Vertex::face());
    }
    
    Face_circulator incident_faces(Face_handle f)
    {
        return Face_circulator(handle(), face());
    }
    
    Edge_circulator incident_edges()
    {
        return Edge_circulator(handle(), face());
    }
    
    Edge_circulator incident_edges(Face_handle f)
    {
        return Edge_circulator(handle(), f);
    }
    
};


#endif //CGAL_CONSTRAINED_TRIANGULATION_VERTEX_H

