// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/Triangulation_ds_face_2.h
// package       : Triangulation (3.17)
// source   : $Source: /u/alcor/0/prisme_util/CGAL/Local/cvsroot/Triangulation/include/CGAL/Triangulation_ds_face_2.h,v $CVSROOT/Triangulation/include/CGAL/Triangulation_ds_face_2.h,v $
// revision      : $Revision: 1.10.1.9 $
// revision_date : $Date: 1999/04/30 14:09:25 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_DS_FACE_2_H
#define CGAL_TRIANGULATION_DS_FACE_2_H

#include <CGAL/Triangulation_short_names_2.h>

CGAL_BEGIN_NAMESPACE 

template <class Vb, class Fb >
class  Triangulation_ds_vertex_2 ;


template < class Vb, class Fb >
class  Triangulation_ds_face_2
  : public Fb
{
public:
  //typedef typename Fb::Triangle Triangle;
  typedef Triangulation_ds_vertex_2<Vb,Fb> Vertex;
  typedef Triangulation_ds_face_2<Vb,Fb> Face;

  // creators
  Triangulation_ds_face_2()
    : Fb()
  {}
    
  Triangulation_ds_face_2(Vertex* v0, Vertex* v1, Vertex* v2)
    :  Fb(v0,v1,v2)
  {}
    
  Triangulation_ds_face_2(Vertex* v0, Vertex* v1, Vertex* v2,
				Face* n0, Face* n1, Face* n2)
    :  Fb(v0,v1,v2,n0,n1,n2)
  {}


  //setting
  inline 
  void set_vertex(int i, Vertex* v)
  {
    Fb::set_vertex(i,v);
  }
    
    
  inline 
   void set_neighbor(int i, Face* n)
  {
    Fb::set_neighbor(i,n);
  }

  inline
  void set_vertices() 
  {
    Fb::set_vertices();
  }
      
  inline 
  void set_vertices(Vertex* v0,
		    Vertex* v1,
		    Vertex* v2)
  {
    Fb::set_vertices(v0,v1,v2);
   }
    
  inline
  void set_neighbors() 
  {
    Fb::set_neighbors();
  }
     
  inline
  void set_neighbors(Face* n0,
		     Face* n1,
		     Face* n2)
  {
    Fb::set_neighbors(n0,n1,n2);
  }

  //Vertex Access Member Functions
  Vertex* vertex(int i) const
  {
    return( (Vertex*) (Fb::vertex(i)));
  } 

 inline
   bool has_vertex(const Vertex* v) const
  {
    //Triangulation_ds_vertex_2<Vb,Fb>* w=v;
    return (Fb::has_vertex(v));
  }
    
    
  inline 
  bool has_vertex(const Vertex* v, int& i) const
  {
    return (Fb::has_vertex(v,i));
  }
    
  inline 
  int index(const Vertex* v) const
  {
    return(Fb::vertex_index(v));
  }

  // Neighbors Access Functions
  inline 
  Face* neighbor(int i) const
  {
    return ((Face*) Fb::neighbor(i));
  }
    
  inline 
  bool has_neighbor(const Face* n) const
  {
    return (Fb::has_neighbor(n));
  }
    
    
  inline 
  bool has_neighbor(const Face* n, int& i) const
  {
    return (Fb::has_neighbor(n,i));
  }
    
    
  inline 
  int index(const Face* n) const
  {
    return(Fb::face_index(n));
  }
    

  //Additionnal Operations

  //the following function has been moved to the tds class
//   void insert_in_face(Vertex*& v)

//   void insert_in_edge(const Vertex* v, int i)

//   bool insert_outside(const Vertex* v, int i)
//   bool remove(Vertex* v)

//   void flip(int i)


   bool is_valid(bool verbose = false, int level = 0) const
  {
    bool result = Fb::is_valid();
    for(int i = 0; i < 3; i++) {
      Face* n = neighbor(i);
            
      // The following seems natural, but it may fail if the faces
      // this and n are neighbors on two edges (1-dim triangulation,
      // with infinite faces
      // int ni = n->index(this);

      //  int ni = cw(n->index(vertex(cw(i))));
      // CGAL_triangulation_assertion( this == n->neighbor(ni) );
      // result = result && (vertex(cw(i)) == n->vertex(ccw(ni)));
      // result = result && (vertex(ccw(i)) == n->vertex(cw(ni)));

      int in;
      if (! n->has_vertex(vertex(cw(i)),in )) return false;
      in = cw(in); 
      result = result && ( this == n->neighbor(in) );
      result = result && (vertex(ccw(i)) == n->vertex(cw(in)));

    }
    return result;
  }
   

};

CGAL_END_NAMESPACE

#endif //CGAL_TRIANGULATION_DS_FACE_2_H
