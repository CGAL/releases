// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// file          : include/CGAL/Arr_2_bases.h
// package       : Arrangement (2.18)
// author(s)     : Iddo Hanniel 
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_ARR_2_BASES_H
#define CGAL_ARR_2_BASES_H

#include <list>

CGAL_BEGIN_NAMESPACE

template <class Pt>
class Arr_2_vertex_base {
 protected:
  void* hdg;
  Pt    pt;
public:
  typedef Pt           Point;

  Arr_2_vertex_base() {}

  void*       halfedge()               {return hdg;}
  const void* halfedge() const         {return hdg;}
  void        set_halfedge( void* h)   { hdg = h;}
  // an incident halfedge pointing at `v'.

  //    Point&       point()       { return pt;}
  const Point& point() const { return pt;}
  void set_point(const Point& p) {
    pt=p;
  }

};

template <class Base_node>
class Arr_2_halfedge_base {
public:
  typedef typename Base_node::Curve Curve;

  Arr_2_halfedge_base() : bn(0) {}

  void*       opposite()       { return opp;}
  const void* opposite() const { return opp;}

  void*       next()           { return nxt;}
  const void* next() const     { return nxt;}
  // the next halfedge along the face.
  
  void  set_opposite( void* h)  { opp = h;}

  void  set_next( void* h)      { nxt = h;}
  

  //    void*       prev()       { return prv;}
  //  const void* prev() const { return prv;}


  void*       vertex()       { return v;}
  const void* vertex() const { return v;}
  
  void*       face()       { return f;}
  const void* face() const { return f;}
  // the face to the left.

  void  set_vertex( void* _v)     { v = _v;}

  void  set_face( void* _f)      { f = _f;}


  //for debug only !!
  //const Curve&       curve() const  { return cv;}
  //void set_curve(const Curve& c) {cv=c;}

  //WATCH OUT:
  //we make the curve and set_curve empty so the pm can find them but not
  //use them , the curves are set in the halfedge via the edge_node!!

  
  const Curve& curve() const { 
    return bn->curve();
  }
//  void set_curve(const Curve& cv) {bn->set_curve(cv);}
//the setting of the curve is done only in the arrangement level
  void set_curve(const Curve& cv) {}
    

  Base_node* edge_node() {return bn;} //will become private in the arrangement
  const Base_node* edge_node() const {return bn;} 
  void set_edge_node(Base_node* b) {bn=b;}

protected:

  void* opp;
  void* nxt;
  
  void* v; 
  void* f; //face
  
  Base_node* bn;

  //debug
  //Curve cv;

};


class Arr_2_face_base {
public:
  typedef std::list<void*> Holes_container; 
  
  typedef Holes_container::iterator Holes_iterator; 
  typedef Holes_container::const_iterator Holes_const_iterator;


  Arr_2_face_base() : holes() {};

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

  
  //this is not documented but needed for a private project
  Holes_container::size_type number_of_holes() const { return holes.size();}

protected:
  void* hdg;
  Holes_container holes ;


};


template <class _Curve>
class Arr_base_node {
public:
  typedef _Curve Curve;

  Arr_base_node() {}
  virtual ~Arr_base_node() {}

  const Curve& curve() const {return cv;}
  void set_curve(const Curve& c) {cv=c;}

protected: 
  Curve cv;
};

CGAL_END_NAMESPACE

#endif








