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
// file          : include/CGAL/Triangulation_ds_vertex_2.h
// package       : Triangulation_2 (5.18)
// source        : $RCSfile: Triangulation_ds_vertex_2.h,v $
// revision      : $Revision: 1.14 $
// revision_date : $Date: 2000/08/21 12:26:53 $
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

#include <utility>
#include <CGAL/Triangulation_short_names_2.h>
#include <CGAL/Triangulation_utils_2.h>
#include <CGAL/Triangulation_ds_circulators_2.h>

CGAL_BEGIN_NAMESPACE

template <class Vb, class Fb >
class  Triangulation_ds_face_2 ;

template <class Vb, class Fb >
class  Triangulation_ds_vertex_2 
  : public Vb,
    public Triangulation_cw_ccw_2
{
public:
  typedef Vb Vertex_base;
  typedef Fb Face_base;
  typedef typename Vertex_base::Point Point;
  typedef Triangulation_ds_vertex_2<Vertex_base,Fb> Vertex;
  typedef Triangulation_ds_face_2<Vertex_base,Fb> Face;
  typedef std::pair< Face*,int> Edge;
  typedef Triangulation_ds_face_circulator_2<Vertex,Face> Face_circulator;
  typedef Triangulation_ds_vertex_circulator_2<Vertex,Face> 
                                                           Vertex_circulator;
  typedef Triangulation_ds_edge_circulator_2<Vertex,Face> Edge_circulator;

  //CREATORS
  Triangulation_ds_vertex_2() : Vertex_base() {}
  Triangulation_ds_vertex_2(const Point & p) :  Vertex_base(p)  {}
  Triangulation_ds_vertex_2(const Point & p, Face * f) : Vertex_base(p, f )  {}

  //SETTING
  void set_face(Face* f)  { Vertex_base::set_face(f);  }

  //ACCESS
  Face* face() const {return ( static_cast<Face *>(Vertex_base::face()) );}
  int degree() const ;

  inline Vertex_circulator incident_vertices() const    {
    return Vertex_circulator(this);
  }
  inline Vertex_circulator incident_vertices(const Face* f) const  {
    return Vertex_circulator(this,f);
  }
  inline Face_circulator incident_faces() const  {
    return Face_circulator(this);
  }
  inline Face_circulator incident_faces(const Face* f) const   {
    return Face_circulator(this, f);
  }
  inline Edge_circulator incident_edges() const  {
    return Edge_circulator(this);
  }
  inline Edge_circulator incident_edges(const Face* f) const {
    return Edge_circulator(this, f);
  }

  bool is_valid(bool verbose = false, int level = 0) const;

};

template <class Vb, class Fb >
int
Triangulation_ds_vertex_2 <Vb,Fb> ::
degree() const
{
  int count = 0;
  Vertex_circulator vc = incident_vertices(), done(vc);
  if ( ! vc. is_empty()) {
    do { 
      count += 1;
    } while (++vc != done);
  }
  return count;
}

// template <class Vb, class Fb >
// inline
// Triangulation_ds_vertex_circulator_2<Triangulation_ds_vertex_2<Vb,Fb>,
//                                      Triangulation_ds_face_2<Vb,Fb> >
// Triangulation_ds_vertex_2<Vb,Fb> ::
// incident_vertices() const
// {
//   return Vertex_circulator(this);
// }
    
// template <class Vb, class Fb >
// inline
// Triangulation_ds_vertex_circulator_2<Triangulation_ds_vertex_2<Vb,Fb>,
//                                      Triangulation_ds_face_2<Vb,Fb> >
// Triangulation_ds_vertex_2<Vb,Fb> ::
// incident_vertices(const Face* f) const
// {
//   return Vertex_circulator(this,f);
// }

// template <class Vb, class Fb >
// inline
// Triangulation_ds_face_circulator_2<Triangulation_ds_vertex_2<Vb,Fb>,
//                                    Triangulation_ds_face_2<Vb,Fb> >
// Triangulation_ds_vertex_2<Vb,Fb> ::
// incident_faces() const
// {
//   return Face_circulator(this);
// }
    
// template <class Vb, class Fb >
// inline
// Triangulation_ds_face_circulator_2<Triangulation_ds_vertex_2<Vb,Fb>,
//                                    Triangulation_ds_face_2<Vb,Fb> >
// Triangulation_ds_vertex_2<Vb,Fb> ::
// incident_faces(const Face* f) const
// {
//   return Face_circulator(this, f);
// }
    
// template <class Vb, class Fb >
// inline
// Triangulation_ds_edge_circulator_2<Triangulation_ds_vertex_2<Vb,Fb>,
//                                    Triangulation_ds_face_2<Vb,Fb> >
// Triangulation_ds_vertex_2<Vb,Fb> ::  
// incident_edges() const
// {
//   return Edge_circulator(this);
// }
       
// template <class Vb, class Fb >
// inline
// Triangulation_ds_edge_circulator_2<Triangulation_ds_vertex_2<Vb,Fb>,
//                                    Triangulation_ds_face_2<Vb,Fb> >
// Triangulation_ds_vertex_2<Vb,Fb> ::  
// incident_edges(const Face* f) const
// {
//   return Edge_circulator(this, f);
// }
    
template <class Vb, class Fb >
bool 
Triangulation_ds_vertex_2<Vb,Fb> ::  
is_valid(bool verbose, int level) const
{
  bool result = Vertex_base::is_valid(verbose, level);
  CGAL_triangulation_assertion(result);
  if (face() != NULL) { // face==NULL if dim <0
    result = result && face()->has_vertex(this);
  }
  return result;
}

CGAL_END_NAMESPACE

#endif //CGAL_TRIANGULATION_DS_VERTEX_2_H
