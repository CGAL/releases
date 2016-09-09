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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : include/CGAL/Constrained_triangulation_face.h
// package       : Triangulation (1.23)
// source        : web/Constrained_triangulation_face.fw
// revision      : $Revision: 1.8 $
// revision_date : $Date: 1998/02/11 19:07:58 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Herve Bronnimann
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_CONSTRAINED_TRIANGULATION_FACE_H
#define CGAL_CONSTRAINED_TRIANGULATION_FACE_H

#include <CGAL/triangulation_assertions.h>
#include <CGAL/Pointer.h>
#include <CGAL/Constrained_triangulation_vertex.h>

template <class Va, class Fa>
class CGAL_Constrained_triangulation_face
  :  public Fa
{
private:
    bool C[3];
public:
    typedef CGAL_Constrained_triangulation_vertex<Va,Fa> Vertex;
    typedef CGAL_Constrained_triangulation_face<Va,Fa> Face;
    typedef typename Vertex::Vertex_handle Vertex_handle;
    typedef CGAL_Pointer<Face> Face_handle;
    CGAL_Constrained_triangulation_face() : Fa()
    {
        set_constrained(false,false,false);
    }
    
    CGAL_Constrained_triangulation_face(Vertex_handle v0,
                                        Vertex_handle v1,
                                        Vertex_handle v2) : Fa()
    {
        set_vertices(v0,v1,v2);
        set_constrained(false,false,false);
    }
    
    CGAL_Constrained_triangulation_face(Vertex_handle v0,
                                        Vertex_handle v1,
                                        Vertex_handle v2,
                                        Face_handle n0,
                                        Face_handle n1,
                                        Face_handle n2) : Fa()
    {
        set_vertices(v0,v1,v2);
        set_neighbors(n0,n1,n2);
        set_constrained(false,false,false);
    }
    
    CGAL_Constrained_triangulation_face(Vertex_handle v0,
                                        Vertex_handle v1,
                                        Vertex_handle v2,
                                        Face_handle n0,
                                        Face_handle n1,
                                        Face_handle n2,
                                        bool c0, bool c1, bool c2) : Fa()
    {
        set_vertices(v0,v1,v2);
        set_neighbors(n0,n1,n2);
        set_constrained(c0,c1,c2);
    }
    Face_handle handle() const
    {
        return Face_handle(this);
    }
    
    void set_vertices(Vertex_handle v0,
                      Vertex_handle v1,
                      Vertex_handle v2)
    {
        Fa::set_vertices((*v0).Va::handle(), (*v1).Va::handle(), (*v2).Va::handle());
    }
    
    void set_neighbors(Face_handle n0,
                       Face_handle n1,
                       Face_handle n2)
    {
        Fa::set_neighbor((*n0).handle(), (*n1).handle(), (*n2).handle());
    }
    
    void set_vertex(int i, Vertex_handle v)
    {
        Fa::set_vertex(i, (*v).Va::handle());
    }
    
    void set_neighbor(int i, Face_handle n)
    {
        Fa::set_neighbor(i,(*n).Fa::handle());
    }
    
    void set_constrained(bool c0, bool c1, bool c2)
    {
        C[0]=c0;
        C[1]=c1;
        C[2]=c2;
    }
    
    Vertex_handle vertex(int i) const
    {
        return (Vertex_handle((Vertex *) &(*( Fa::vertex(i) ))) );
    }
    
    bool has_vertex(Vertex_handle v)
    {
        return Fa::has_vertex((*v).Va::handle());
    }
    
    bool has_vertex(Vertex_handle v, int& i)
    {
        return Fa::has_vertex((*v).Va::handle(),i);
    }
    
    int index(Vertex_handle v) const
    {
        return Fa::index((*v).Va::handle());
    }
    
    Face_handle neighbor(int i) const
    {
        return (Face_handle( (Face *) &(*( Fa::neighbor(i) ))) );
    }
    
    
    bool has_neighbor(Face_handle n) const
    {
        return Fa::has_neighbor((*n).Fa::handle());
    }
    
    bool has_neighbor(Face_handle n, int& i) const
    {
        return Fa::has_neighbor((*n).Fa::handle(),i);
    }
    
    int index(Face_handle n) const
    {
        return Fa::index((*n).Fa::handle());
    }
    
    void insert(Vertex_handle v)
    {
        Fa::insert((*v).Va::handle());
    }
    
    bool insert(Vertex_handle v, int i)
    {
        Fa::insert((*v).Va::handle(),i);
    }
    
    
    bool remove(Vertex_handle &v)
    {
        Fa::remove((*v).Va::handle());
    }
    
    bool is_constrained(int i)
    {
        return(C[i]);
    }
    
    void set_constrained(int i, bool b)
    {
        CGAL_triangulation_precondition( i == 0 || i == 1 || i == 2);
        C[i] = b;
    }
    
    
    bool is_valid(bool verbose = false, int level = 0)
    {
        bool result = Fa::is_valid();
        CGAL_triangulation_assertion(result);
        for(int i = 0; i < 3; i++) {
          Face_handle n = neighbor(i);
           if(n != NULL){
             int ni = n->index(handle());
             result = result && ( is_constrained(i) == n->is_constrained(ni));
           }
          }
        return (result);
    }
    bool is_removable()
    {
     return ( vertex(1) == vertex(2) &&
              neighbor(1)!= NULL && neighbor(2)!= NULL);
    }
    
    void remove_flat()  // must be followed by a Delete() in calling code
    {
      assert(vertex(1) == vertex(2));
      Face_handle f2= neighbor(2);
      Face_handle f1= neighbor(1);
      if ( f2 != NULL) { set_neighbor( f2->index(this->handle()), f1);}
      if ( f1 != NULL) { set_neighbor( f1->index(this->handle()), f2);}
      (vertex(0))->set_face( f2 != NULL ? f2 : f1 );
      return;
    }
    
    
};


#endif //CGAL_CONSTRAINED_TRIANGULATION_FACE_H

