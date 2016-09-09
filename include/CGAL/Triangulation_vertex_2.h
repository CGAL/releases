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
// file          : include/CGAL/Triangulation_vertex_2.h
// package       : Triangulation (2.10)
// source        : $Source: /u/alcor/0/prisme_util/CGAL/Local/cvsroot/Triangulation/include/CGAL/Triangulation_vertex_2.h,v $
// revision      : $Revision: 1.2.1.6 $
// revision_date : $Date: 1998/12/03 17:11:35 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_VERTEX_2_H
#define CGAL_TRIANGULATION_VERTEX_2_H

#include <CGAL/Pointer.h>
#include <CGAL/Triangulation_short_names_2.h>
#include <CGAL/Triangulation_default_data_structure_2.h>
#include <CGAL/Triangulation_circulators_2.h>


template < class Gt, class Tds >
class CGAL_Triangulation_face_2;

template < class Gt, class Tds >
class CGAL_Triangulation_vertex_handle_2;

template < class Gt, class Tds >
class CGAL_Triangulation_face__handle_2;

template<class Gt,  class Tds>
class CGAL_Triangulation_face_circulator_2;

template<class Gt,  class Tds>
class CGAL_Triangulation_vertex_circulator_2;

template<class Gt, class Tds>
class CGAL_Triangulation_edge_circulator_2;


template<class Gt, class Tds >
class CGAL_Triangulation_vertex_2
  : public Tds::Vertex
{
public:
  
  typedef Tds Triangulation_data_structure;

  typedef Gt  Geom_traits;
  typedef typename Geom_traits::Point Point;
  typedef typename Geom_traits::Segment Segment;
  typedef typename Geom_traits::Triangle Triangle;

  typedef typename Tds::Vertex Ve;
  typedef typename Tds::Face Fa;

  typedef CGAL_Triangulation_face_2<Gt,Tds> Face;
  typedef CGAL_Triangulation_vertex_2<Gt,Tds> Vertex;
  
  typedef CGAL_Triangulation_vertex_handle_2<Gt,Tds> Vertex_handle;
  typedef CGAL_Triangulation_face_handle_2<Gt,Tds> Face_handle;
  typedef pair<Face_handle, int>     Edge;

  typedef CGAL_Triangulation_face_circulator_2<Gt,Tds>      Face_circulator;
  typedef CGAL_Triangulation_edge_circulator_2<Gt,Tds>      Edge_circulator;
  typedef CGAL_Triangulation_vertex_circulator_2<Gt,Tds>    Vertex_circulator;

  
  CGAL_Triangulation_vertex_2()
     : Ve()
  {}

  CGAL_Triangulation_vertex_2(const Point & p)
    :  Ve(p)
  {}
    
  CGAL_Triangulation_vertex_2(const Point & p, const Face_handle& f)
    :  Ve(p, &(*f))
  {}

  inline void set_face(const Face_handle& f)
  {
    Ve::set_face(&(*f));
  }
    
    
  inline Face_handle face() const
  {
        return  (Face *)Ve::face();
  }
        
  inline Vertex_handle handle() const
  {
    return Vertex_handle(this);
  }
      
  //inherited :
  // cw(i), ccw(i)
  // degree(), point(), is_on_boundary, set_point(p)

  inline Vertex_circulator incident_vertices() const
  {
    return Vertex_circulator(handle(), face());
  }

  inline Vertex_circulator incident_vertices(const Face_handle& f) const
  {
    return Vertex_circulator(handle(), f);
  } 

  inline 
  Face_circulator incident_faces() const
  {
    return Face_circulator(handle(), face());
  }
    
  inline Face_circulator incident_faces(const Face_handle& f) const
  {
    return Face_circulator(handle(), f);
  }
    
  inline Edge_circulator incident_edges() const
  {
    return Edge_circulator(handle(), face());
  }
 
  inline Edge_circulator incident_edges(const Face_handle& f) const
  {
    return Edge_circulator(handle(), f);
  }
    
};
#endif //CGAL_TRIANGULATION_VERTEX_2_H
