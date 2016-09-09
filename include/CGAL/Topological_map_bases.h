// Copyright (c) 1997  Tel-Aviv University (Israel).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source: /CVSROOT/CGAL/Packages/Planar_map/include/CGAL/Topological_map_bases.h,v $
// $Revision: 1.2 $ $Date: 2003/09/18 10:24:38 $
// $Name: current_submission $
//
// Author(s)     : Iddo Hanniel <hanniel@math.tau.ac.il>
#ifndef  CGAL_TOPOLOGICAL_MAP_BASES_H
#define  CGAL_TOPOLOGICAL_MAP_BASES_H

#ifndef CGAL_PM_BASIC_H
#include <CGAL/basic.h>
#endif

#include <list>

CGAL_BEGIN_NAMESPACE


//template <class Pt>
class Tpm_vertex_base {
 protected:
    void* hdg;
public:
    Tpm_vertex_base() {}

    void*       halfedge()               {return hdg;}
    const void* halfedge() const         {return hdg;}
    void        set_halfedge( void* h)   { hdg = h;}
    // an incident halfedge of 'v'

};

class Tpm_halfedge_base {
public:

  Tpm_halfedge_base() {}

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


class Tpm_face_base {
public:
  typedef std::list<void*> Holes_container; 
  
  typedef Holes_container::iterator Holes_iterator; 
  typedef Holes_container::const_iterator Holes_const_iterator;


  Tpm_face_base() : holes() {};

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


CGAL_END_NAMESPACE

#else   
#error  Header file .h included twice
#endif  

















