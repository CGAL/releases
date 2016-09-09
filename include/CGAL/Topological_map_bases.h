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
// file          : include/CGAL/Topological_map_bases.h
// package       : pm (2.052)
// source        : 
// revision      : 
// revision_date : 
// author(s)     : Iddo Hanniel
//
//
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// Chapter       : 
//
// email         : cgal@cs.uu.nl
//
// ======================================================================
#include <list.h>

#ifndef CGAL_PM_CONFIG_H
#include <CGAL/Pm_config.h>
#endif

//template <class Pt>
class CGAL_Tpm_vertex_base {
 protected:
    void* hdg;
public:
    CGAL_Tpm_vertex_base() {}

    void*       halfedge()               {return hdg;}
    const void* halfedge() const         {return hdg;}
    void        set_halfedge( void* h)   { hdg = h;}
    // an incident halfedge of 'v'

};

class CGAL_Tpm_halfedge_base {
public:

  CGAL_Tpm_halfedge_base() {}

  void*       opposite()       { return opp;}
  const void* opposite() const { return opp;}

  void*       next()           { return nxt;}
  const void* next() const     { return nxt;}
  // the next halfedge along the face.
  
  void  set_opposite( void* h)  { opp = h;}

  void  set_next( void* h)      { nxt = h;}
  
  //will probably be in a max base in the future
  //    void*       prev()       { return prv;}
  //  const void* prev() const { return prv;}

  void*       vartex()       { return v;}
  const void* vertex() const { return v;}
  
  void*       face()       { return f;}
  const void* face() const { return f;}
  // the face to the left.

  void  set_vertex( void* _v)     { v = _v;}

  void  set_face( void* _f)      { f = _f;}

protected:

  void* opp;
  void* nxt;
  
  void* v; 
  void* f; //face
  
};


class CGAL_Tpm_face_base {
public:
  typedef list<void*> Holes_container; 
  
  typedef Holes_container::iterator Holes_iterator; 
  typedef Holes_container::const_iterator Holes_const_iterator;


  CGAL_Tpm_face_base() : holes() {};

  void* halfedge() { return hdg;}
  const void* halfedge() const { return hdg;}

  void set_halfedge(void* h) {hdg=h;}

  //mine

  Holes_iterator  holes_begin() {return holes.begin();}
  Holes_iterator  holes_end() {return holes.end();}

  
  Holes_const_iterator  holes_begin() const {return holes.begin();}
  Holes_const_iterator  holes_end() const {return holes.end();}
  

  void add_hole(void* halfedge_ptr)
  {

    holes.push_back(halfedge_ptr);

  }


  void erase_hole(Holes_iterator hit) {
    holes.erase(hit);
  }
  void erase_holes(Holes_iterator first, Holes_iterator last) {
    holes.erase(first,last);
  }

  

private:
  void* hdg;
  Holes_container holes ;


};




















