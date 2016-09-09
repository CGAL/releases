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
// file          : include/CGAL/Pm_default_dcel.h
// package       : pm (2.052)
// source        : 
// revision      : 
// revision_date : 
// author(s)     : Iddo Hanniel
//                 Oren Nechushtan
//
//
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// Chapter       : 
//
// email         : cgal@cs.uu.nl
//
// ======================================================================
#ifndef CGAL_PM_DEFAULT_DCEL_H
#define CGAL_PM_DEFAULT_DCEL_H 1

#ifndef CGAL_PM_CONFIG_H
#include <CGAL/Pm_config.h>
#endif

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif

#include <list.h>


#ifndef CGAL_IN_PLACE_LIST_H
#include <CGAL/In_place_list.h>
#endif

//needed for holes iterator
#ifndef CGAL_PLANAR_MAP_MISC_H
#include <CGAL/Planar_map_misc.h>
#endif


template <class Pt>
class CGAL_Pm_vertex_base {
protected:
  void* hdg;
  Pt    pt;
public:
  typedef Pt           Point;
  
  CGAL_Pm_vertex_base() {}
  CGAL_Pm_vertex_base( const Pt& p) : pt(p) {}
  
  void*       halfedge()               {return hdg;}
  const void* halfedge() const         {return hdg;}
  void        set_halfedge( void* h)   { hdg = h;}
  // an incident halfedge pointing at `v'.
  
  Point&       point()       { return pt;}
  const Point& point() const { return pt;}
  
  void set_point(const Point& p) {pt=p;}
};



template <class X_curve>
class CGAL_Pm_halfedge_base {
public:
  typedef X_curve Curve;

  CGAL_Pm_halfedge_base() {}

  CGAL_Pm_halfedge_base(const X_curve& c) : cv(c) {}

  void*       opposite()       { return opp;}
  const void* opposite() const { return opp;}

  void*       next()           { return nxt;}
  const void* next() const     { return nxt;}
  // the next halfedge along the face.
  
  void  set_opposite( void* h)  { opp = h;}

  void  set_next( void* h)      { nxt = h;}
  
  void*       vertex()       { return v;}
  const void* vertex() const { return v;}
  
  void*       face()       { return f;}
  const void* face() const { return f;}
  // the face to the left.

  void  set_vertex( void* _v)     { v = _v;}

  void  set_face( void* _f)      { f = _f;}


  Curve&       curve()       { return cv;}
  const Curve& curve() const { return cv;}

  void set_curve(const X_curve& c) {cv=c;}

protected:
  void* opp;
  void* nxt;
  
  void* v; //target
  void* f; //face
  
  X_curve cv;

};


class CGAL_Pm_face_base {
public:
  typedef list<void*> Holes_container; 
  
  typedef Holes_container::iterator Holes_iterator; 

  typedef Holes_container::const_iterator Holes_const_iterator;


  CGAL_Pm_face_base() : holes() {};

  void* halfedge() { return hdg;}
  const void* halfedge() const { return hdg;}

  void set_halfedge(void* h) {hdg=h;}

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





template <class V, class H, class F> class CGAL__Pm_Vertex;
template <class V, class H, class F> class CGAL__Pm_Halfedge;
template <class V, class H, class F> class CGAL__Pm_Face;

template <class V, class H, class F>
class CGAL__Pm_Vertex
    : public  V,
      public  CGAL_In_place_list_base< CGAL__Pm_Vertex<V,H,F> >
{
public:
  typedef V                              Base;
  typedef CGAL__Pm_Vertex<V,H,F>    Vertex;
  typedef CGAL__Pm_Halfedge<V,H,F>  Halfedge;
  typedef CGAL__Pm_Face<V,H,F>     Face;

  CGAL__Pm_Vertex() {}
  //    CGAL__Pm_Vertex( const Point& p) : V(p) {}

  Halfedge*       halfedge()       {return (Halfedge*)(V::halfedge());}
  const Halfedge* halfedge() const {return (const Halfedge*)(V::halfedge());}
  void            set_halfedge( Halfedge* h) { V::set_halfedge(h);}

  /* irrelevant
#if _MSC_VER>=1100
public:
#else
protected:
#endif
  //forbid copy constructor and assignment (only derived classes can use them)
  CGAL__Pm_Vertex( const CGAL__Pm_Vertex&);
  CGAL__Pm_Vertex& operator=(const CGAL__Pm_Vertex&);
  */

};

template <class V, class H, class F>
class CGAL__Pm_Halfedge
  : public  H,
    public  CGAL_In_place_list_base< CGAL__Pm_Halfedge<V,H,F> >
{
public:
  typedef H                              Base;
  typedef CGAL__Pm_Vertex<V,H,F>    Vertex;
  typedef CGAL__Pm_Halfedge<V,H,F>  Halfedge;
  typedef CGAL__Pm_Face<V,H,F>     Face;

  CGAL__Pm_Halfedge() : H() {}  
  //CGAL__Pm_Halfedge( const Curve& c) : H(c) {}

  Halfedge*       opposite()       {return (Halfedge*)(H::opposite());}
  
  Halfedge*       next()           {return (Halfedge*)(H::next());}
  //in the future will probably be implemented in a max base
  //    const Halfedge* prev()     const {return (const Halfedge*)(H::prev());}

  Vertex*         vertex()         {return (Vertex*)(H::vertex());}

  Face*          face()          {return (Face*)(H::face());}
  
  const Halfedge* opposite() const {return (const Halfedge*)(H::opposite());}

  const Halfedge* next()     const {return (const Halfedge*)(H::next());}
  //in the future will probably be implemented in a max base
  //    const Halfedge* prev()     const {return (const Halfedge*)(H::prev());}

  const Vertex*   vertex()   const {return (const Vertex*)(H::vertex());}

  const Face*    face()    const {return (const Face*)(H::face());}
  
  void  set_next( Halfedge* h)     { H::set_next(h);}

  void  set_vertex( Vertex* ve)    { H::set_vertex(ve);}

  void  set_face( Face* face)   { H::set_face(face);}
  
private:
  void  set_opposite( void* h)     { H::set_opposite(h);}

  /*
#if _MSC_VER>=1100
public:
#else
protected:
#endif
  //forbid copy constructor and assignment (only derived classes can use them)
  
  CGAL__Pm_Halfedge( const CGAL__Pm_Halfedge&);
  CGAL__Pm_Halfedge& operator=(const CGAL__Pm_Halfedge&);
  */  

};


template <class V, class H, class F>
class CGAL__Pm_Face
    : public  F,
      public  CGAL_In_place_list_base< CGAL__Pm_Face<V,H,F> >
{
public:
  typedef F                              Base;
  typedef CGAL__Pm_Vertex<V,H,F>    Vertex;
  typedef CGAL__Pm_Halfedge<V,H,F>  Halfedge;
  typedef CGAL__Pm_Face<V,H,F>     Face;

  CGAL__Pm_Face() {}  
  
  Halfedge*       halfedge()       {return (Halfedge*)(F::halfedge());}
  const Halfedge* halfedge() const {return (const Halfedge*)(F::halfedge());}
  void            set_halfedge( Halfedge* h) { F::set_halfedge(h);}


  typedef CGAL__Polyhedron_iterator< typename F::Holes_iterator, 
    Halfedge*, 
#if	_MSC_VER>=1100
    typename F::Holes_iterator::distance_type,
#else
    typename F::Holes_iterator::difference_type, 
#endif
    typename F::Holes_iterator::iterator_category>       Holes_iterator;

  typedef CGAL__Polyhedron_const_iterator<
  typename F::Holes_const_iterator, 
  typename F::Holes_iterator,
  const Halfedge*,
#if _MSC_VER>=1100
  typename F::Holes_const_iterator::distance_type, 
#else
  typename F::Holes_const_iterator::difference_type, 
#endif
  typename F::Holes_const_iterator::iterator_category>       Holes_const_iterator;

  void add_hole(Halfedge* h) { F::add_hole(h); }
  void erase_hole(Holes_iterator hit) {F::erase_hole(hit.current_iterator());}
  void erase_holes(Holes_iterator first, Holes_iterator last) {F::erase_holes(first.current_iterator(), last.current_iterator());}


  Holes_iterator holes_begin() {return F::holes_begin();}
  Holes_iterator holes_end() {return F::holes_end();}

  Holes_const_iterator holes_begin() const {return F::holes_begin();}
  Holes_const_iterator holes_end() const {return F::holes_end();}
  
  /*
#if _MSC_VER>=1100
public:
#else
protected:
#endif
  //forbid copy constructor and assignment (only derived classes can use them)
  CGAL__Pm_Face( const CGAL__Pm_Face&);
  CGAL__Pm_Face& operator=(const CGAL__Pm_Face&);
  */

};


// A Dcel Class Using Lists
// ----------------------------------
//

template < class V, class H, class F>
class CGAL_Pm_dcel {
public:
  typedef CGAL_Pm_dcel<V,H,F>   Self;
  typedef CGAL__Pm_Vertex<V,H,F>         Vertex;
  typedef CGAL__Pm_Halfedge<V,H,F>       Halfedge;
  typedef CGAL__Pm_Face<V,H,F>          Face;
  
protected:
  // Three managed in-place lists for the elements. 
  typedef CGAL_In_place_list<Vertex,true>      Vertex_list;
  typedef CGAL_In_place_list<Halfedge,true>    Halfedge_list;
  typedef CGAL_In_place_list<Face,true>       Face_list;
public:
  typedef typename Halfedge_list::size_type   Size;
  typedef typename Halfedge_list::size_type   size_type;
  typedef typename Halfedge_list::difference_type difference_type;
  typedef typename Halfedge_list::difference_type Difference;
  typedef bidirectional_iterator_tag          iterator_category;

protected:
    Vertex_list    vertices;
    Halfedge_list  halfedges;
    Face_list     faces;

public:

  typedef bidirectional_iterator_tag          iterator_category;

  typedef typename Vertex_list::iterator      Vertex_iterator;
  typedef typename Halfedge_list::iterator    Halfedge_iterator;
  typedef typename Face_list::iterator       Face_iterator;
  
  typedef typename Vertex_list::const_iterator    Vertex_const_iterator;
  typedef typename Halfedge_list::const_iterator  Halfedge_const_iterator;
  typedef typename Face_list::const_iterator     Face_const_iterator;
  
  // CREATION

  CGAL_Pm_dcel() {}

#if _MSC_VER>=1100
public:
#else
private:
#endif
  // Forbid copy constructor and assignment (will be implemented later).
  CGAL_Pm_dcel( const Self&) {}
  Self& operator=( const Self&)            { return *this;}
  
public:
  // Access Member Functions
  
  Size size_of_vertices() const  { return vertices.size();}
  Size size_of_halfedges() const { return halfedges.size();}
  Size size_of_faces() const    { return faces.size();}

  Vertex_iterator   vertices_begin()   { return vertices.begin();}
  Vertex_iterator   vertices_end()     { return vertices.end();}
  Halfedge_iterator halfedges_begin()  { return halfedges.begin();}
  Halfedge_iterator halfedges_end()    { return halfedges.end();}
  Face_iterator    faces_begin()     { return faces.begin();}
  Face_iterator    faces_end()       { return faces.end();}
  
  // The constant iterators and circulators.

  Vertex_const_iterator   vertices_begin()  const{ return vertices.begin();}
  Vertex_const_iterator   vertices_end()    const{ return vertices.end();}
  Halfedge_const_iterator halfedges_begin() const{ return halfedges.begin();}
  Halfedge_const_iterator halfedges_end()   const{ return halfedges.end();}
  Face_const_iterator    faces_begin()    const{ return faces.begin();}
  Face_const_iterator    faces_end()      const{ return faces.end();}
  
  // Insertion
  //
  // The following operations just allocate a new element of that type.
  // Halfedges are always allocated in pairs of opposite halfedges. The
  // opposite pointers are automatically set.
  
  Vertex* new_vertex() {
    Vertex* v = new Vertex;
    vertices.push_back( *v);
    return v;
  }
  
  Vertex* new_vertex( const Vertex* w) {
    Vertex* v = new Vertex(*w);
    vertices.push_back( *v);
    return v;
  }
  
  /*
  Vertex* new_vertex( const Point& p) {
    Vertex* v = new Vertex(p);
    vertices.push_back( *v);
    return v;
  }
  */

  Halfedge* new_edge() {
    // creates a new pair of opposite halfedges.
    Halfedge* h = new Halfedge;
    Halfedge* g = new Halfedge;
    h->H::set_opposite(g);
    g->H::set_opposite(h);

    halfedges.push_back( *h);
    halfedges.push_back( *g);
    return h;
  }
  
  Halfedge* new_edge( const Halfedge* he) {
    Halfedge* h = new Halfedge( *he);
    Halfedge* g = new Halfedge(* (he->opposite()));
    h->H::set_opposite(g);
    g->H::set_opposite(h);

    halfedges.push_back( *h);
    halfedges.push_back( *g);
    return h;
  }
  
  /*
    Halfedge* new_edge(const Curve& c) {
    Halfedge* h = new Halfedge(c);
    Halfedge* g = new Halfedge(c);  //maybe change to flip??
    //    h->H::set_twin(g);
    //g->H::set_twin(h);
    h->H::set_opposite(g);
    g->H::set_opposite(h);

    halfedges.push_back( *h);
    halfedges.push_back( *g);
    return h;
  }*/
  
  Face* new_face(){
    Face* f = new Face;
    faces.push_back( *f);
    return f;
  }
  
  Face* new_face( const Face* g) {
    Face* f = new Face(*g);
    faces.push_back( *f);
    return f;
  }
  
  // Removal
  //
  // The following operations erase an element referenced by a pointer.
  // Halfedges are always deallocated in pairs of opposite halfedges. Erase
  // of single elements is optional. The deletion of all is mandatory.

  void delete_vertex( Vertex* v) { vertices.erase(v);}
  
  void delete_edge( Halfedge* h) {
    // deletes the pair of opposite halfedges h.
    Halfedge* g = h->opposite();
    halfedges.erase(h);
    halfedges.erase(g);
  }

  void delete_face( Face* f) { faces.erase(f);}
  
  void delete_all() {
    vertices.destroy();
    halfedges.destroy();
    faces.destroy();
  }
  
};



///////////////////////////////////////////////////////////////
//               DEFAULT DCEL
///////////////////////////////////////////////////////////////

template <class Traits>
class CGAL_Pm_default_dcel
  : public CGAL_Pm_dcel<
CGAL_Pm_vertex_base<typename Traits::Point>,
CGAL_Pm_halfedge_base<typename Traits::X_curve>,
CGAL_Pm_face_base
> 
{
public:  // CREATION
  
  CGAL_Pm_default_dcel() {}
  
};




#endif 
// EOF //









