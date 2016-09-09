// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : include/CGAL/Arrangement_2.h
// package       : arr (1.16)
// author(s)     : Iddo Hanniel
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// email         : cgal@cs.uu.nl
//
// ======================================================================
#ifndef ARRANGEMENT_2_H
#define ARRANGEMENT_2_H

//for now, since the arrangement default ctr is currently with the walk pl.
#include <CGAL/Pm_walk_along_line_point_location.h>


//#ifdef BOGI


#ifndef CGAL_PLANAR_MAP_2_H
#include <CGAL/Planar_map_2.h>
#endif

//planar map misc also included

#ifndef ARR_2_BASES_H
#include <CGAL/Arr_2_bases.h>
#endif

#ifndef CGAL_IN_PLACE_LIST_H
#include <CGAL/In_place_list.h>
#endif

#ifndef ARR_ITERATORS_H  
#include <CGAL/Arr_iterators.h> //for circulators
#endif



#include <vector>


CGAL_BEGIN_NAMESPACE

template <class _Dcel, class _Traits, class Base_node>
class Arrangement_2 {
public:

  typedef _Dcel Dcel;
  typedef _Traits Traits;
  typedef Planar_map_traits_wrap<Traits> Traits_wrap;
  typedef Planar_map_2<Dcel,Traits> Planar_map;

  typedef Arrangement_2<_Dcel,_Traits,Base_node> Self;

  typedef typename Traits::Point Point;
  typedef typename Traits::X_curve X_curve;
  typedef typename Traits::Curve Curve;


  //for size and stuff
  typedef typename Dcel::Size            Size;
  typedef typename Dcel::size_type       size_type;
  typedef typename Dcel::difference_type difference_type;
  typedef typename Dcel::difference_type Difference;
  
  typedef typename Dcel::iterator_category      iterator_category;



  //for Action
  //typedef typename Traits::SPLIT_FUNC SPLIT_FUNC;
  

  enum Locate_type { VERTEX=Planar_map::VERTEX,
                     EDGE=Planar_map::EDGE,
                     FACE=Planar_map::FACE,
                     UNBOUNDED_FACE=Planar_map::UNBOUNDED_FACE };

  //forward declerations
  class Subcurve_node;
  class Curve_node;
  class Edge_node;

  class Vertex;
  class Halfedge;
  class Face;


  ///////////////////////////////////////////////////////////////////////
  //          ITERATOR DEFINITIONS

  //for heirarchy tree (H...)
  typedef typename In_place_list<Subcurve_node,true>::size_type   HSize;
  typedef typename In_place_list<Subcurve_node,true>::size_type   Hsize_type;
  typedef typename In_place_list<Subcurve_node,true>::difference_type Hdifference_type;
  typedef typename In_place_list<Subcurve_node,true>::difference_type HDifference;
  typedef std::bidirectional_iterator_tag          Hiterator_category;

  //typedefs for iterators (for curve nodes, edge_nodes, sub_curve_nodes and HVF)
  typedef typename In_place_list<Subcurve_node,true>::iterator 
  Subcurve_iterator;
  
  typedef typename In_place_list<Subcurve_node,true>::const_iterator 
  Subcurve_const_iterator;

  typedef _Polyhedron_iterator<
  Subcurve_iterator,
  Curve_node,
  HDifference, Hiterator_category> Curve_iterator;

  typedef _Polyhedron_const_iterator<
  Subcurve_const_iterator, Subcurve_iterator,
  Curve_node,
  HDifference, Hiterator_category>       Curve_const_iterator;

  typedef _Polyhedron_iterator<
  Subcurve_iterator,
  Edge_node,
  HDifference, Hiterator_category> Edge_iterator;

  typedef _Polyhedron_const_iterator<
  Subcurve_const_iterator, Subcurve_iterator,
  Edge_node,
  HDifference, Hiterator_category>       Edge_const_iterator;


  //wrappers for planar map iterators

  typedef _Polyhedron_iterator<
  typename Planar_map::Vertex_iterator,
  Vertex,
  Difference, typename Planar_map::iterator_category> Vertex_iterator;

  typedef _Polyhedron_const_iterator<
  typename Planar_map::Vertex_const_iterator, typename Planar_map::Vertex_iterator,
  Vertex,
  Difference, typename Planar_map::iterator_category>  Vertex_const_iterator;

  typedef _Polyhedron_iterator<
  typename Planar_map::Halfedge_iterator,
  Halfedge,
  Difference, typename Planar_map::iterator_category> Halfedge_iterator;

  typedef _Polyhedron_const_iterator<
  typename Planar_map::Halfedge_const_iterator, typename Planar_map::Halfedge_iterator,
  Halfedge,
  Difference, typename Planar_map::iterator_category>  Halfedge_const_iterator;

  typedef _Polyhedron_iterator<
  typename Planar_map::Face_iterator,
  Face,
  Difference, typename Planar_map::iterator_category> Face_iterator;

  typedef _Polyhedron_const_iterator<
  typename Planar_map::Face_const_iterator, typename Planar_map::Face_iterator,
  Face,
  Difference, typename Planar_map::iterator_category>  Face_const_iterator;


  //the following define the overlap circulators (might be changed to iterators)
  typedef Arr_overlap_circulator<Edge_node,Edge_iterator,Bidirectional_circulator_tag> Overlap_circulator;
  typedef Arr_overlap_const_circulator<Edge_node,Edge_const_iterator,Bidirectional_circulator_tag> Overlap_const_circulator;

  //handles
  typedef Vertex_iterator Vertex_handle;
  typedef Vertex_const_iterator Vertex_const_handle;
  typedef Halfedge_iterator Halfedge_handle;
  typedef Halfedge_const_iterator Halfedge_const_handle;
  typedef Face_iterator Face_handle;
  typedef Face_const_iterator Face_const_handle;

  typedef _Arr_face_circ<  
  Halfedge,
  Halfedge_iterator,
  Forward_circulator_tag>            Ccb_halfedge_circulator;

  typedef _Arr_face_const_circ<
  Halfedge,
  Halfedge_const_iterator,
  Forward_circulator_tag>       Ccb_halfedge_const_circulator;

  typedef _Arr_vertex_circ<
  Halfedge,
  Halfedge_iterator,
  Forward_circulator_tag>            Halfedge_around_vertex_circulator;
  
  typedef _Arr_vertex_const_circ<
  Halfedge,
  Halfedge_const_iterator,
  Forward_circulator_tag>      Halfedge_around_vertex_const_circulator;

  typedef _Polyhedron_iterator< 
  typename Planar_map::Holes_iterator,
  Ccb_halfedge_circulator,
  Difference, std::bidirectional_iterator_tag>       Holes_iterator;

  typedef _Polyhedron_const_iterator<
  typename Planar_map::Holes_const_iterator, typename Planar_map::Holes_iterator,
  Ccb_halfedge_const_circulator,
  Difference, std::bidirectional_iterator_tag>       Holes_const_iterator;





  //TREE NODES:
  //subcurve_node : Base_node + hides pointers - returns handles/iterators
  //curve_node : sub_curve_node + adds levels
  //edge_node : sub_curve_node + adds halfedges

  ///////////////////////////////////////////////////////////////////////////
  //                         SUBCURVE_NODE
  ///////////////////////////////////////////////////////////////////////////

class Subcurve_node : public  Base_node,
                      public  In_place_list_base<Subcurve_node> 
{
public: 
  friend class Arrangement_2<Dcel,Traits,Base_node>;

  //to enable access of Overlap_iterators into begin_child and past_end_child
  //friend class Overlap_circulator;
  //friend class Overlap_const_circulator;
 
  //the above are not recognized by MSVC, so we use this instead
  friend class Arr_overlap_circulator<Edge_node,Edge_iterator,Bidirectional_circulator_tag>;
  friend class Arr_overlap_const_circulator<Edge_node,Edge_const_iterator,Bidirectional_circulator_tag>;

  Subcurve_node() : ftr(0),begin_child(0),past_end_child(0) {}
  
  virtual ~Subcurve_node() {}

  virtual bool is_edge_node() {return false;}

  Subcurve_iterator parent() { 
    return Subcurve_iterator(ftr); 
  }
  Subcurve_const_iterator parent() const { 
    return Subcurve_const_iterator(ftr);
  }

  Subcurve_iterator children_begin() { 
    return Subcurve_iterator(begin_child); 
  }
  Subcurve_const_iterator children_begin() const { 
    return Subcurve_const_iterator(begin_child);
  }
  
  Subcurve_iterator children_end() { 
    return Subcurve_iterator(past_end_child); 
  }
  Subcurve_const_iterator children_end() const { 
    return Subcurve_const_iterator(past_end_child);
  }

  Curve_iterator curve_node() {
    Subcurve_node* curr=this;
    while (curr->ftr) 
      curr=curr->ftr;
    return Curve_iterator(curr);
  }
  Curve_const_iterator curve_node() const {
    const Subcurve_node* curr=this;
    while (curr->ftr) 
      curr=curr->ftr;
    return Curve_const_iterator(curr);
  }

  Edge_iterator edges_begin() { 
    Subcurve_node* curr=this;
    while (!curr->is_edge_node()) 
      curr=curr->begin_child;
    return Edge_iterator(curr); 
  }
  Edge_const_iterator edges_begin() const {
    const Subcurve_node* curr=this;
    while (!curr->is_edge_node()) 
      curr=curr->begin_child;
    return Edge_const_iterator(curr);
  }

  Edge_iterator edges_end() { 
    Subcurve_node* curr=this;
    while (!curr->is_edge_node())
      curr=curr->past_end_child->prev_link; //curr will never be a past_end_value

    return Edge_iterator(curr->next_link);
  }
  Edge_const_iterator edges_end() const {
    const Subcurve_node* curr=this;
    while (!curr->is_edge_node()) 
      curr=curr->past_end_child->prev_link;
    return Edge_const_iterator(curr->next_link);
  }

  //the set_curve is not protected. how do I protect it? (maybe friend the
  //arrangement and make it protected?)

protected:  

  Subcurve_node* ftr;
  Subcurve_node* begin_child;
  Subcurve_node* past_end_child;
};


  ////////////////////////////////////////////////////////////////////
  //                    EDGE_NODE
  ////////////////////////////////////////////////////////////////////

class Edge_node : public Subcurve_node 
{
public:
  friend class Arrangement_2<Dcel,Traits,Base_node>;

  //need to make them friend of Subcurve_node and not Edge_node
  //friend class Overlap_circulator;
  //friend class Overlap_const_circulator;
  

  Edge_node() : Subcurve_node(), hdg() {
    //the following is needed for the circular overlap list (see the function
    //push_in_edge_list below). if we want to implement a linear list
    //it needs to be removed (begin_child and past_end_child should then be NULL)
    begin_child=this;
    past_end_child=this;
  }

  ~Edge_node() {} //overrides the virtual dtr in Subcurve node

  Halfedge_handle halfedge() {return hdg;}
  Halfedge_const_handle halfedge() const {return hdg;}

  bool is_edge_node() {return true;}

private: //maybe protected
  //  void set_halfedge(Halfedge_const_handle h) {hdg=h;} 
  void set_halfedge(Halfedge_handle h) {hdg=h;} 

private:
  Halfedge_handle hdg;
};


///////////////////////////////////////////////////////////////////////////
//                    CURVE_NODE
///////////////////////////////////////////////////////////////////////////

class Curve_node : public Subcurve_node
{
public:
  friend class Arrangement_2<Dcel,Traits,Base_node>; 

  Curve_node() : Subcurve_node(), levels(), edge_level() {}
  
  ~Curve_node() {} //overrides the virtual dtr in Subcurve_node

  //number of subcurve levels (not including curve level and edge level)
  unsigned int number_of_sc_levels() {
    return levels.size();
  }

  Subcurve_iterator level_begin(unsigned int i) {
    CGAL_precondition(i<number_of_sc_levels());
      return levels[i].begin(); 
  }

  Subcurve_const_iterator level_begin(unsigned int i) const {
    CGAL_precondition(i<number_of_sc_levels());
      return levels[i].begin(); 
  }

  Subcurve_iterator level_end(unsigned int i) {
    CGAL_precondition(i<number_of_sc_levels());
      return levels[i].end(); 
  }

  Subcurve_const_iterator level_end(unsigned int i) const {
    CGAL_precondition(i<number_of_sc_levels());
      return levels[i].end(); 
  }

  //we override the function to make it more efficient when called from Curve_node
  Edge_iterator edges_begin() {
    return edge_level.begin();
  }
  Edge_const_iterator edges_begin() const{
    return edge_level.begin();
  }
  Edge_iterator edges_end() {
    return edge_level.end();
  }
  Edge_const_iterator edges_end() const {
    return edge_level.end();
  }

  
private:
  std::vector<In_place_list<Subcurve_node,true> > levels;
  //level0 is the one beneath the root
  In_place_list<Subcurve_node,true> edge_level;

};
  

//Planar map wrappers
  //halfedge : Pm::Halfedge + hides pointer into iterator (and adds curve node)
  //face : Pm::Face + returns Arr::Halfedge and not Pm::Halfedge etc.
  //Vertex : Pm::Vertex + returns Arr::Halfedge and not Pm::Halfedge etc.

//////////////////////////////////////////////////////////////////////
//                  VERTEX
////////////////////////lanar_map/////////////////////////////////////////////
  class Vertex : public Planar_map::Vertex
  {
  public:
    typedef typename Planar_map::Vertex PmVertex;

    Vertex() : PmVertex()
    {}
    
  
    Vertex(PmVertex *v) : PmVertex(*v) //can also be PmVertex(v)
    {}


    Vertex(PmVertex& v) : PmVertex(v) 
    {}

    bool is_incident_edge(Halfedge_const_handle e) const
    {
#ifndef _MSC_VER
      return (PmVertex::is_incident_edge(e.current_iterator()));
#else
      return ( ((PmVertex*)this)->is_incident_edge(e.current_iterator()));
#endif
    }

    bool is_incident_face(Face_const_handle f) const
    {
#ifndef _MSC_VER
      return (PmVertex::is_incident_face(f.current_iterator()));      
#else
      return ( ((PmVertex*)this)->is_incident_face(f.current_iterator())); 
#endif
    }
    
    /*redundant - use inheritance
    int degree() const
    {
      return PmVertex::degree();
    }*/

    Halfedge_around_vertex_circulator incident_halfedges() 
    {
#ifndef _MSC_VER
      return Halfedge_around_vertex_circulator(Halfedge_handle(PmVertex::incident_halfedges()));
#else
      return Halfedge_around_vertex_circulator(Halfedge_handle( ((PmVertex*)this)->incident_halfedges()));
#endif
    }

    Halfedge_around_vertex_const_circulator incident_halfedges() const 
    {
#ifndef _MSC_VER
		return Halfedge_around_vertex_const_circulator(Halfedge_const_handle(PmVertex::incident_halfedges()));
#else
		return Halfedge_around_vertex_const_circulator(Halfedge_const_handle( ((PmVertex*)(this))->incident_halfedges()));
#endif

    }
    

  };



///////////////////////////////////////////////////////////////////////
//                 HALFEDGE
//////////////////////////////////////////////////////////////////////
  class Halfedge : public Planar_map::Halfedge
  {
  public:
  friend class Arrangement_2<Dcel,Traits,Base_node>; 

    typedef typename Planar_map::Halfedge PmHalfedge;

    Halfedge() : Planar_map::Halfedge()
    {}

    Halfedge( typename Planar_map::Halfedge *e) : Planar_map::Halfedge(*e) {}

    Halfedge(typename Planar_map::Halfedge& e) : Planar_map::Halfedge(e) {}

    Vertex_handle source()
    {
#ifndef _MSC_VER
      return Vertex_handle(PmHalfedge::source()); 
#else
	  return Vertex_handle(((PmHalfedge*)(this))->source()); 
#endif
    }

    Vertex_const_handle source() const
    {
#ifndef _MSC_VER
      return Vertex_const_handle(PmHalfedge::source()); 
#else
      return Vertex_const_handle( ((PmHalfedge*)(this))->source()); 
#endif
    }
    
    Vertex_handle target()	
    {
#ifndef _MSC_VER
      return Vertex_handle(PmHalfedge::target()); 
#else
      return Vertex_handle(((PmHalfedge*)(this))->target()); 
#endif
    }
    Vertex_const_handle target() const	
    {
#ifndef _MSC_VER
      return Vertex_const_handle(PmHalfedge::target());
#else
	  return Vertex_const_handle( ((PmHalfedge*)(this))->target());
#endif
    }
    
    Face_handle face() 
    {
#ifndef _MSC_VER
      return Face_handle(PmHalfedge::face());
#else
	  return Face_handle( ((PmHalfedge*)this)->face());
#endif
    }
    Face_const_handle face() const
    {
#ifndef _MSC_VER
      return Face_const_handle(PmHalfedge::face()); 
#else
	  return Face_const_handle( ((PmHalfedge*)this)->face()); 
#endif
    }
    
    Halfedge_handle twin() 
    {
#ifndef _MSC_VER
      return Halfedge_handle(PmHalfedge::twin()); 
#else
      return Halfedge_handle( ((PmHalfedge*)(this))->twin()); 
#endif
    }
    Halfedge_const_handle twin() const 
    {
#ifndef _MSC_VER
      return Halfedge_const_handle(PmHalfedge::twin());
#else
	  return Halfedge_const_handle( (PmHalfedge*)this)->twin());
#endif
    }
    
    Halfedge_handle next_halfedge() 
    { 
#ifndef _MSC_VER
      return Halfedge_handle(PmHalfedge::next_halfedge() );
#else
      return Halfedge_handle( ((PmHalfedge*)this)->next_halfedge() );
#endif
    }
    Halfedge_const_handle next_halfedge() const 
    { 
#ifndef _MSC_VER
      return Halfedge_const_handle(PmHalfedge::next_halfedge() );
#else
      return Halfedge_const_handle( ((PmHalfedge*)this)->next_halfedge() );
#endif
    }
    
    
    Ccb_halfedge_circulator ccb()
    { 
#ifndef _MSC_VER
      return Ccb_halfedge_circulator(Halfedge_handle(PmHalfedge::ccb())); 
#else
	  return Ccb_halfedge_circulator(Halfedge_handle( ((PmHalfedge*)(this))->ccb())); 
#endif
    }
    Ccb_halfedge_const_circulator ccb() const
    { 
#ifndef _MSC_VER
      return Ccb_halfedge_const_circulator(Halfedge_const_handle(PmHalfedge::ccb()));
#else
	  return Ccb_halfedge_const_circulator(Halfedge_const_handle( ((PmHalfedge*)this)->ccb()));
#endif
    }

     
   Edge_iterator edge_node() {
#ifndef _MSC_VER
	   return Edge_iterator(Subcurve_iterator((Subcurve_node*)PmHalfedge::edge_node()));
#else
	   return Edge_iterator(Subcurve_iterator( (Subcurve_node*)( ((PmHalfedge*)(this))->edge_node()) ) );
#endif
   }
   Edge_const_iterator edge_node() const {
#ifndef _MSC_VER
    return Edge_const_iterator(Subcurve_const_iterator((Subcurve_node*)PmHalfedge::edge_node()));
#else
     return Edge_const_iterator(Subcurve_const_iterator( (const Subcurve_node*)( ((PmHalfedge*)(this))->edge_node()) ) );
#endif
   }
//workaround for MSVC

    //Overlap traversal
    Overlap_circulator overlap_edges() {
      return Overlap_circulator(edge_node());
    }
    Overlap_const_circulator overlap_edges() const {
      return Overlap_const_circulator(edge_node());
    }


    //the curve and set curve functions in the base classes 
    //will be required to be blank. maybe thats a problem with
    //other functions of the pm that we use here (check it out)
    //is there a better solution ?

  protected: //(private?)
#ifndef _MSC_VER
      void set_edge_node(Edge_node* b) {PmHalfedge::set_edge_node(b);}
#else 
	  void set_edge_node(Edge_node* b) { ((PmHalfedge*)(this))->set_edge_node(b);}
#endif
     
  private:  
    //disallow this function - allowed only for an Edge_node
    //this overloading works for egcs, if doesn't work for other
    //compilers then this will be the only version .
      void set_edge_node(Base_node* b) {PmHalfedge::set_edge_node(b);}
    
    };


///////////////////////////////////////////////////////////////////
//                   FACE
//////////////////////////////////////////////////////////////////

  class Face : public Planar_map::Face
  {
  public:

    typedef typename Planar_map::Face PmFace;

#ifndef _MSC_VER
    // the following two typedefs are needed for compilation on irix64 (CC7.30)
    typedef Arrangement_2<_Dcel,_Traits,Base_node>::Holes_iterator 
      Holes_iterator; 
    typedef Arrangement_2<_Dcel,_Traits,Base_node>::Holes_const_iterator 
      Holes_const_iterator; 
#endif

    Face() : PmFace()
    {}
    
    Face(PmFace *f) : PmFace(*f) {}

    Face(PmFace& f) : PmFace(f) {} 


    /* redundant - use inheritance 
    bool is_unbounded() const  
    {
      // face is not bounded iff it has no outer boundary
      return (dface::halfedge() == NULL);
    }
    */

    Holes_iterator holes_begin() 
    {
#ifndef _MSC_VER
	  return Holes_iterator( PmFace::holes_begin());
#else
	  return Holes_iterator( ((PmFace*)(this))->holes_begin());
#endif
    }
    Holes_const_iterator holes_begin() const
    {
#ifndef _MSC_VER
      return Holes_const_iterator(PmFace::holes_begin());
#else
	  return Holes_const_iterator( ((PmFace*)this)->holes_begin());
#endif
    }
    
    Holes_iterator holes_end() 
    {
#ifndef _MSC_VER
	  return Holes_iterator(PmFace::holes_end());
#else
	  return Holes_iterator(((PmFace*)(this))->holes_end());
#endif
    }
    Holes_const_iterator holes_end() const 
    {
#ifndef _MSC_VER
      return Holes_const_iterator(PmFace::holes_end());
#else
	  return Holes_const_iterator( ((PmFace*)this)->holes_end());
#endif
    }

    bool is_halfedge_on_inner_ccb(Halfedge_const_handle e) const
    {
#ifndef _MSC_VER
      return PmFace::is_halfedge_on_inner_ccb(e.current_iterator());
#else
      return ((PmFace*)this)->is_halfedge_on_inner_ccb(e.current_iterator());
#endif
    }
    
    bool is_halfedge_on_outer_ccb(Halfedge_const_handle e) const
    {
#ifndef _MSC_VER
	    return PmFace::is_halfedge_on_outer_ccb(e.current_iterator());
#else
	    return ((PmFace*)this)->is_halfedge_on_outer_ccb(e.current_iterator());
#endif
    }
      
    //redundant - use inheritance
    /*
      bool does_outer_ccb_exist() const
      {
      return PmFace::does_outer_ccb_exist();
      }*/
    
    Halfedge_handle halfedge_on_outer_ccb() 
    {
#ifndef _MSC_VER	
      typename Planar_map::Halfedge_handle pmh=PmFace::halfedge_on_outer_ccb();
#else
	  //workaround for MSVC, it doesn't accept the above 
		typename Planar_map::Halfedge_handle pmh= ((typename Planar_map::Face*)(this))->halfedge_on_outer_ccb();
#endif
		return Halfedge_handle(pmh);
    }

    Halfedge_const_handle halfedge_on_outer_ccb() const 
    {
#ifndef _MSC_VER	
      typename Planar_map::Halfedge_const_handle pmh=PmFace::halfedge_on_outer_ccb();
#else
	  //workaround for MSVC, it doesn't accept the above 
		typename Planar_map::Halfedge_const_handle pmh= ((const typename Planar_map::Face*)(this))->halfedge_on_outer_ccb();
#endif
      return Halfedge_const_handle(pmh); 
    }

    Ccb_halfedge_circulator outer_ccb() 
    {
      return (halfedge_on_outer_ccb())->ccb();
    }
    Ccb_halfedge_const_circulator outer_ccb() const
    {
      return (halfedge_on_outer_ccb())->ccb();
    }

  };





//////////////////////////////////////////////////////////
//                  ARRANGEMENT 2
///////////////////////////////////////////////////////////

  
public:

//in future need to arrange for the pl to be an Arr_pl, and public for the arrangement
/*
//for the first public release we use the default ctr below (with walk pl) -
//currently it is faster
Arrangement_2(const Traits& tr=Traits()) : traits(tr), pm(tr), do_update(true) {
    last_updated=curve_node_end();  
}
*/

//default ctr with the walk as default point location
Arrangement_2(const Traits& tr=Traits()) : traits(tr), pm(new Pm_walk_along_line_point_location<Planar_map>,tr), do_update(true) {
  last_updated=curve_node_end();  
  need_del=true; //a bool flag for dtr
}

~Arrangement_2() { //dtr needs to delete the walk
  if (need_del)
    delete((Pm_point_location_base<Planar_map>*)(pm.point_location())); //casting away the constness before deletion
}
 
private:
bool need_del; //for the dtr
public:

Arrangement_2(Pm_point_location_base<Planar_map> *pl, const Traits& tr=Traits()) : traits(tr), pm(pl,tr), do_update(true) {
    last_updated=curve_node_end();  
    need_del=false;
}
  

Curve_iterator curve_node_begin() {
  return Curve_iterator(curve_list.begin());
}
Curve_const_iterator curve_node_begin() const {
  return Curve_const_iterator(curve_list.begin());
}

Curve_iterator curve_node_end() {
  return Curve_iterator(curve_list.end());
}
Curve_const_iterator curve_node_end() const {
  return Curve_const_iterator(curve_list.end());
}

Halfedge_iterator halfedges_begin() {
  return Halfedge_iterator(pm.halfedges_begin());
}
Halfedge_const_iterator halfedges_begin() const {
  return Halfedge_const_iterator(pm.halfedges_begin());
}
Halfedge_iterator halfedges_end() {
  return Halfedge_iterator(pm.halfedges_end());
}
Halfedge_const_iterator halfedges_end() const {
  return Halfedge_const_iterator(pm.halfedges_end());
}


Vertex_iterator vertices_begin() {
  return Vertex_iterator(pm.vertices_begin());
}
Vertex_const_iterator vertices_begin() const {
  return Vertex_const_iterator(pm.vertices_begin());
}
Vertex_iterator vertices_end() {
  return Vertex_iterator(pm.vertices_end());
}
Vertex_const_iterator vertices_end() const {
  return Vertex_const_iterator(pm.vertices_end());
}


Face_iterator faces_begin() {
  return Face_iterator(pm.faces_begin());
}
Face_const_iterator faces_begin() const {
  return Face_const_iterator(pm.faces_begin());
}
Face_iterator faces_end() {
  return Face_iterator(pm.faces_end());
}
Face_const_iterator faces_end() const {
  return Face_const_iterator(pm.faces_end());
}


Size number_of_faces() const
{
  return pm.number_of_faces();
}


//counts every halfedge (i.e always even)
Size number_of_halfedges() const
{
  return pm.number_of_halfedges();
}

Size number_of_vertices() const
{
  return pm.number_of_vertices();
}

Face_handle unbounded_face() {return Face_handle(pm.unbounded_face());}
Face_const_handle unbounded_face() const {return Face_const_handle(pm.unbounded_face());}


///////////////////////////////////////////////////////////////////
//               INSERTION FUNCTIONS

Curve_iterator insert(const typename Traits::Curve& cv) 
{
  //either add Arr to pm as friend class or make public functions
  Curve_node* cn= new Curve_node;
  cn->set_curve(cv);
  
  if (!traits.is_x_monotone(cv)) {
    //get an x_monotone sub_curve list and push it in.
    cn->levels.push_back(In_place_list<Subcurve_node,true>());

    //cut cv into x_monotone curves and insert them into l
    std::list<CGAL_TYPENAME_MSVC_NULL Traits::X_curve> x_list;
    traits.make_x_monotone(cv,x_list);

    typename std::list<CGAL_TYPENAME_MSVC_NULL Traits::X_curve>::iterator lit=x_list.begin();
    for (; lit!=x_list.end(); ++lit) {
      Subcurve_node* scn=new Subcurve_node;
      scn->ftr=cn;
      scn->set_curve(*lit);
      
      cn->levels[0].push_back(*scn);
 
    }  
    cn->begin_child=&(*(cn->levels[0].begin()));
    cn->past_end_child=&(*(cn->levels[0].end()));


    //so far - inserted subcurve level, we insert the edge level only if
    // we are in update mode.
    if (do_update) {

      Subcurve_iterator scit=cn->levels[0].begin();
      In_place_list<Subcurve_node,true> edge_list;    
      for (; scit!=cn->levels[0].end(); ++scit) {
        insert_x_curve(scit->curve(), edge_list , &(*scit));
        scit->begin_child=&(*(edge_list.begin()));
        cn->edge_level.splice(cn->edge_level.end(),edge_list); //add edge_list at end of edge_level
      }
      
      scit=cn->levels[0].begin();
      Subcurve_iterator aux=scit; ++aux;
      for (; aux!=cn->levels[0].end(); ++scit,++aux) { 
        scit->past_end_child=&(*(aux->begin_child));
      }
      scit->past_end_child=&(*(cn->edge_level.end())); //the last past_end_child

    } //if (do_update)


  }

  else { //insert x_curve directly - sub_curve vector is empty

    if (do_update) { //insertion of edge level only if in update mode
      insert_x_curve(cv, cn->edge_level, cn);
      cn->past_end_child=&(*(cn->edge_level.end()));
      cn->begin_child=&(*(cn->edge_level.begin()));
    }

  }
  
  Curve_iterator ci=curve_list.insert(curve_list.end(),*cn);
  if (do_update)
    last_updated=ci;

  return ci;

}

/////////////////////////////////////////////////////////////////////
//   insertion with user defined intersection functions

template <class F_iterator>
Curve_iterator insert(const typename Traits::Curve& cv,
                      F_iterator F_begin,
                      F_iterator F_end) 
{
  if (F_begin==F_end)
    return insert(cv); //if list is empty return the regular insert function

  Curve_node* cn= new Curve_node;
  cn->set_curve(cv);
  typename std::vector<In_place_list<Subcurve_node,true> >::size_type sz=0;

  //distance(F_begin,F_end,sz); //find size of vector of in place lists (currently not all STL distance is implemented same - so I implement it myself); 
  F_iterator first=F_begin;
  while(first++!=F_end) ++sz; 

  //! the following line is _crucial_ to avoid unreferencing of the lists afterwards
  cn->levels.reserve(sz); 

  //step 1: insert the first level of subcurves (level 0)
  cn->levels.push_back(In_place_list<Subcurve_node,true>());

  //cut cv into curves and insert them into l
  std::list<Curve> c_list;
  //std::list<CGAL_TYPENAME_MSVC_NULL Traits::Curve> c_list;

  (*(*F_begin))(cv,c_list); 
  ++F_begin;
  
  typename std::list<Curve>::iterator lit=c_list.begin();
  for (; lit!=c_list.end(); ++lit) {
    Subcurve_node* scn=new Subcurve_node;
    scn->ftr=cn;
    scn->set_curve(*lit);
    cn->levels[0].push_back(*scn);
  }  
  cn->begin_child=&(*(cn->levels[0].begin()));
  cn->past_end_child=&(*(cn->levels[0].end()));
  

  //step 2: insert the rest of the levels of subcurves (until no more split functions)
  int i=1; //current level  
  for (; F_begin!=F_end ; ++F_begin, ++i ) {
    cn->levels.push_back(In_place_list<Subcurve_node,true>());
    Subcurve_iterator scit=cn->levels[i-1].begin();
    for (; scit!=cn->levels[i-1].end(); ++scit) {
      //cut cv into curves and insert them into l
		std::list<Curve> c_list;
      (*(*F_begin))(scit->curve(),c_list);  //split the curve

      Subcurve_iterator aux=cn->levels[i].end();
      if (!cn->levels[i].empty()) {
      --aux; 
      }

      typename std::list<Curve>::iterator lit=c_list.begin();
      for (; lit!=c_list.end(); ++lit) {
        Subcurve_node* scno=new Subcurve_node;
        scno->ftr=&(*scit); 
        scno->set_curve(*lit);
        cn->levels[i].push_back(*scno); 
      }
      
      if (!cn->levels[i].empty()) {
        ++aux;
      }

      scit->begin_child=&(*aux); //the begin_child is the one directly after the last one of before.
    }

    (cn->levels[i-1].begin())->begin_child=&(*(cn->levels[i].begin())); 
    //the begin child of the first - now all begin children are well defined

    //defining the past end child pointer of level[i-1]
    scit=cn->levels[i-1].begin();
    Subcurve_iterator aux=scit; ++aux;
    for (; aux!=cn->levels[i-1].end(); ++scit,++aux) { 
      scit->past_end_child=&(*(aux->begin_child));
    }
    scit->past_end_child=&(*(cn->levels[i].end())); //the last past_end_child

  }
  //ALL the subcurve levels are now inserted.

  //step 3: insert the edge level.
  if (do_update) { 
    Subcurve_iterator scit=cn->levels[i-1].begin();
    In_place_list<Subcurve_node,true> edge_list;    
    for (; scit!=cn->levels[i-1].end(); ++scit) {
      insert_x_curve(scit->curve(), edge_list , &(*scit));
      //debug
      //cout << (*this);
      //(*Wp).clear();
      //(*Wp) << (*this);
      //(*Wp).read_mouse();

      scit->begin_child=&(*(edge_list.begin()));
      cn->edge_level.splice(cn->edge_level.end(),edge_list); //add edge_list at end of edge_level
    }
    
    scit=cn->levels[i-1].begin();
    Subcurve_iterator aux=scit; ++aux;
    for (; aux!=cn->levels[i-1].end(); ++scit,++aux) { 
      scit->past_end_child=&(*(aux->begin_child));
    }
    scit->past_end_child=&(*(cn->edge_level.end())); //the last past_end_child
    
  } //if (do_update)

  //insert in curve list and return
  Curve_iterator ci=curve_list.insert(curve_list.end(),*cn);
    
  if (do_update)
    last_updated=ci;
  return ci;

}

///////////////////////////////////////////////////////////////
//    SPLIT EDGE

//add a new edge_node after e->edge_node(), split the edge in the pm,
//update the curves and halfedge pointers in the nodes and halfedges
Halfedge_handle split_edge(Halfedge_handle e, 
                           const typename Traits::X_curve& c1,
                           const typename Traits::X_curve& c2)
{
  Edge_iterator eit=e->edge_node();
  Curve_iterator cit=eit->curve_node();
  Halfedge_handle e_rep=eit->halfedge(); //find the representative halfedge of the edge node (the one with the same direction as the curve)

  typename Traits::X_curve cv=eit->curve();
  typename Planar_map::Halfedge_handle pmh=pm.split_edge(e_rep.current_iterator(),c1,c2);

  Edge_node* en=new Edge_node;
   //!! bug fix (two weeks of debugging)
   en->ftr=eit->ftr;
  

  if (traits.point_is_same(traits.curve_source(cv),traits.curve_source(c1))) {
    en->set_curve(c2);
    pmh->edge_node()->set_curve(c1);
  }
  else { //c2 is before c1
    en->set_curve(c1);
    pmh->edge_node()->set_curve(c2);
  }

  //insert en after eit in the edge_node list
  ++eit;
  (cit->edge_level).insert(eit.current_iterator(),*en);

  en->set_halfedge(Halfedge_handle(pmh->next_halfedge()));

  pmh->next_halfedge()->set_edge_node(en);
  pmh->next_halfedge()->twin()->set_edge_node(en);

  //deal with overlapping edges of eit (if there were any)
  if ( ((Edge_node*)(pmh->edge_node()))->begin_child != (Subcurve_node*)&(*(pmh->edge_node()))) {
    //eit has overlapping edges (it doesn't point to itself)
    //split all overlapping edge_nodes and create the circular list of the edges corresponding to the new edge

    Overlap_circulator occ= (Halfedge_handle(pmh))->overlap_edges();
    ++occ; //we have already dealt with the first edge
    do {
      //add a new edge before/after edge_iterator(occ);
      //set its curve,ftr,begin_child,past_end_child,halfedge
      eit=occ;
      cit=eit->curve_node();
      Edge_node* nen=new Edge_node;
      nen->ftr=eit->ftr;
      //insert nen into circular list before en
      nen->begin_child=en->begin_child;
      nen->past_end_child=en;
      en->begin_child->past_end_child=nen;
      en->begin_child=nen;

      /*
      if (traits.point_is_same(traits.curve_source(eit->curve()),traits.curve_source(c1))) {
        nen->set_curve(c2);
        eit->set_curve(c1);
      }
      else { //c2 is before c1
        nen->set_curve(c1);
        eit->set_curve(c2);
      }
      */
      eit->set_curve(pmh->curve());
      nen->set_curve(pmh->next_halfedge()->curve());

      //insert en before/after eit in the edge_node list
      if (eit->halfedge()== Halfedge_handle(pmh->twin())) { 
        //eit is directed opposite pmh->edge_node()
        //we take advantage of our knowledge of the pm split function to know this
        nen->set_halfedge(Halfedge_handle(pmh->next_halfedge()->twin()));
        //en will be inserted before eit
      }
      else {
        nen->set_halfedge(Halfedge_handle(pmh->next_halfedge()));
        ++eit; //en should be inserted after eit
      }

      //insertion into the in_place edge list
      (cit->edge_level).insert(eit.current_iterator(),*nen);
    } while (++occ != (Halfedge_handle(pmh))->overlap_edges());
  }
  
  return Halfedge_handle(pmh);
}

////////////////////////////
//LOCATE
////////////////////////////
Halfedge_handle locate(const typename Traits::Point& p,Locate_type& lt)
{
  typename Planar_map::Locate_type pmlt;
  typename Planar_map::Halfedge_handle pmh=pm.locate(p,pmlt);
  
  switch(pmlt) {
  case Planar_map::VERTEX :
    lt=static_cast<Locate_type>(VERTEX); //workaround since MSVC does not approve the automatic cast here
    break;
  case Planar_map::EDGE :
    lt=static_cast<Locate_type>(EDGE); //workaround since MSVC does not approve the automatic cast here
    break;
  case Planar_map::FACE :
    lt=static_cast<Locate_type>(FACE); //workaround since MSVC does not approve the automatic cast here
    break;
  case Planar_map::UNBOUNDED_FACE :
    lt=static_cast<Locate_type>(UNBOUNDED_FACE); //workaround since MSVC does not approve the automatic cast here
    break;
  }    

return Halfedge_handle(pmh);
}

Halfedge_const_handle locate(const typename Traits::Point& p,Locate_type& lt) const
{
  typename Planar_map::Locate_type pmlt;
  typename Planar_map::Halfedge_const_handle pmh=pm.locate(p,pmlt);

  switch(pmlt) {
  case Planar_map::VERTEX :
    lt=static_cast<Locate_type>(VERTEX);//workaround since MSVC does not approve the automatic cast here
    break;
  case Planar_map::EDGE :
    lt=static_cast<Locate_type>(EDGE);//workaround since MSVC does not approve the automatic cast here
    break;
  case Planar_map::FACE :
    lt=static_cast<Locate_type>(FACE);//workaround since MSVC does not approve the automatic cast here
    break;
  case Planar_map::UNBOUNDED_FACE :
    lt=static_cast<Locate_type>(UNBOUNDED_FACE);//workaround since MSVC does not approve the automatic cast here
    break;
  } 

  return Halfedge_const_handle(pmh);
}

//////////////////////////////////////////////////////
//     VERTICAL RAY SHOOT
//////////////////////////////////////////////////////
Halfedge_handle vertical_ray_shoot(const typename Traits::Point& p,Locate_type& lt, bool up)
{
  typename Planar_map::Locate_type pmlt;
  typename Planar_map::Halfedge_handle pmh=pm.vertical_ray_shoot(p,pmlt,up);
  switch(pmlt) {
  case Planar_map::VERTEX :
    lt=static_cast<Locate_type>(VERTEX);
    break;
  case Planar_map::EDGE :
    lt=static_cast<Locate_type>(EDGE);
    break;
  case Planar_map::FACE :
    lt=static_cast<Locate_type>(FACE);
    break;
  case Planar_map::UNBOUNDED_FACE :
    lt=static_cast<Locate_type>(UNBOUNDED_FACE);
    break;
  }    

return Halfedge_handle(pmh);
}

Halfedge_const_handle vertical_ray_shoot(const typename Traits::Point& p,Locate_type& lt) const
{
  typename Planar_map::Locate_type pmlt;
  typename Planar_map::Halfedge_const_handle pmh=pm.vertical_ray_shoot(p,pmlt);

  switch(pmlt) {
  case Planar_map::VERTEX :
    lt=static_cast<Locate_type>(VERTEX);
    break;
  case Planar_map::EDGE :
    lt=static_cast<Locate_type>(EDGE);
    break;
  case Planar_map::FACE :
    lt=static_cast<Locate_type>(FACE);
    break;
  case Planar_map::UNBOUNDED_FACE :
    lt=static_cast<Locate_type>(UNBOUNDED_FACE);
    break;
  }   

  return Halfedge_const_handle(pmh);
}


///////////////////////////////////////////////////////////////
// REMOVE CURVE
/////////////////////////////////////////////////////////////
//removes the curve ,its heirarchy tree, and the edges in the pm
void remove_curve(Curve_iterator cit)
{
  Edge_iterator eit=cit->edges_begin();
  for (; eit!=cit->edges_end(); ++eit) {
    if (eit->begin_child == &(*eit)) { //no overlap
      pm.remove_edge((eit->halfedge()).current_iterator()); //deletes edges
    }
    else { //eit overlaps - don't remove the halfedges from planar map
      eit->begin_child->past_end_child=eit->past_end_child;
      eit->past_end_child->begin_child=eit->begin_child;
      
      //set the edge_node ptr of halfedges to something that is not deleted
      eit->halfedge()->set_edge_node(eit->begin_child); 
      eit->halfedge()->twin()->set_edge_node(eit->begin_child); 
    }
  }
  typename std::vector<In_place_list<Subcurve_node,true> >::iterator vit=(cit->levels).begin();
  for (; vit!=(cit->levels).end(); ++vit)  
    (*vit).destroy();  //deletes subcurve lists
  
  curve_list.erase(&(*cit)); //deletes from curve list
}

///////////////////////////////////////////////////////////////
//            UPDATE
///////////////////////////////////////////////////////////////
void set_update(bool u) {
  do_update=u;
  if (u) {
    //go from last_updated to curve_node_end(), and insert x_curves
    if (last_updated!=curve_node_end()) //for the very first update
      ++last_updated;
    else
      last_updated=curve_node_begin();
    for ( ; last_updated!=curve_node_end(); ++last_updated) {
      
      unsigned int num=last_updated->number_of_sc_levels();
      if (num>0) {
        In_place_list<Subcurve_node,true> edge_list;        
        Subcurve_iterator scit=last_updated->level_begin(num - 1);
        for (; scit!=last_updated->level_end(num - 1); ++scit) {
          insert_x_curve(scit->curve(), edge_list , &(*scit));
          scit->begin_child=&(*(edge_list.begin()));
          last_updated->edge_level.splice(last_updated->edge_level.end(),edge_list); //add edge_list at end of edge_level
        }        
        scit=last_updated->level_begin(num - 1);
        Subcurve_iterator aux=scit; ++aux;
        for (; aux!=last_updated->level_end(num-1); ++scit,++aux) { 
          scit->past_end_child=&(*(aux->begin_child));
        }
        scit->past_end_child=&(*(last_updated->edge_level.end())); //the last past_end_child
      }
      else { //num==0, no subcurve level, insert Curve directly.
        insert_x_curve(last_updated->curve(), last_updated->edge_level,
                       &(*last_updated));
        last_updated->past_end_child=&(*(last_updated->edge_level.end()));
        last_updated->begin_child=&(*(last_updated->edge_level.begin()));
      }
    } 
    
    //now last_update==curve_node_end() - take the one before
    --last_updated;
  }
}

///////////////////////////////////////////////////////////////
//               INSERTION OF X_CURVE
///////////////////////////////////////////////////////////////

void insert_x_curve(const typename Traits::X_curve& c, In_place_list<Subcurve_node,true>& edge_list, Subcurve_node* ftr)
{

  //step 0 :ensure that cv source is left of target
  typename Traits::X_curve cv;
  bool left_to_right=true;

  //debug
  //std::cout << "source=" << traits.curve_source(c).to_point();
  //std::cout << "target=" << traits.curve_target(c).to_point() << endl;
  //std::cout << "left_low(t,s)=" << traits.point_is_left_low(traits.curve_target(c),traits.curve_source(c)) << endl;

  if (traits.point_is_left_low(traits.curve_target(c),traits.curve_source(c)))
    {
      //flip if target is left/ if vertical target is lower
      cv=traits.curve_flip(c);
      left_to_right=false;
    }
  else
    cv=c;
  
  typename Traits::X_curve cvo=cv; //the original curve before intersections

  Locate_type lt;
  Halfedge_handle h=locate(traits.curve_source(cv),lt);

  Vertex_handle srcv,trgtv;
  
  //step 1: case 3: source(cv) is in face - find face, break
  //        case 1: source(cv) is on edge - split edge, find next face
  //        case 2: source(cv) is on vertex - find next face
  Face_handle next_face;

  switch (lt) {
  case EDGE : {
    typename Traits::X_curve cv1=h->curve();
    typename Traits::X_curve tmp1,tmp2;
    traits.curve_split(cv1,tmp1,tmp2, traits.curve_source(cv)); //split curve
    //at splitting point 


    h=split_edge(h, tmp1,tmp2);
    lt=static_cast<Locate_type>(VERTEX); //workaround since MSVC does not approve the automatic cast here
    // - we are now at the state of vertex ! (no need to break)
    /*
    Halfedge_handle h1=split_edge(h, tmp1,tmp2);
    srcv=h1->target();
    //find next face 

    Halfedge_handle h2=h1->next_halfedge()->twin();
    if (h2==h1 ||
        traits.curve_is_between_cw(cv,h1->curve(),h2->curve(),traits.curve_source(cv)))
      next_face=h1->face();
    else
      next_face=h2->face();

    break;
    */

  }

  case VERTEX : {
    srcv=h->target();
    //finding the next face the curve goes through
    Halfedge_around_vertex_circulator strt,circ,circ1=srcv->incident_halfedges();
    strt=circ=circ1;
    ++circ1;

    if (traits.curves_overlap(cv,circ->curve())) {
      //there is an overlap, don't get into the curve_is_between_cw loop.
      next_face=circ->face();
      break;
    }      

    if (circ!=circ1) {
      do {
        //check overlap
        if (traits.curves_overlap(cv,circ1->curve())) {
          //there is an overlap, don't get into the curve_is_between_cw func.
          next_face=circ1->face();
          break;        
        }
        
        if (traits.curve_is_between_cw(cv,circ->curve(),circ1->curve(),traits.curve_source(cv))) {
          next_face=circ->face();
          break;
        }
        ++circ;
        ++circ1;
      } while (circ!=strt);

    }
    else { //only one edge from the vertex (tip)
      next_face=circ->face();
    }
      
    break;
  }    

  case FACE :
    next_face=h->face();
    break;
  case UNBOUNDED_FACE:
    next_face=Face_handle(pm.unbounded_face());
    break;
  

  default:
	  CGAL_assertion(false);

  } //switch(lt)

  typename  Traits::Point p1,p2;
  //maybe do it with some other ctr (Zurich decisions)
  typename Traits::X_curve cv1,cv2;

  Halfedge_handle hh;
  
  while (1) {
    //step 2: finding the closest intersection point, p, with the faces boundary
    //if no intersection exists - insert cv (into arrangement and pm) and break

    //change - to prevent cascaded intersection
    if (!(find_nearest_intersection(cvo,traits.curve_source(cv),next_face,p1,p2,hh)) ) {
      //if (!(find_nearest_intersection(cv,traits.curve_source(cv),next_face,p1,p2,hh)) ) {


      if (lt==FACE || lt==UNBOUNDED_FACE) {
        typename Planar_map::Halfedge_handle e;
        if (left_to_right) {
          e=pm.insert_in_face_interior(cv,next_face.current_iterator());
        }
        else {
          e=pm.insert_in_face_interior(traits.curve_flip(cv),next_face.current_iterator());
        }
        push_in_edge_list(cv,Halfedge_handle(e),ftr,edge_list,left_to_right);
        return;
      }
      else { //source is on a vertex and target inside next_face 
        typename Planar_map::Halfedge_handle e;
        if (left_to_right) {
          e=pm.insert_from_vertex(cv,srcv.current_iterator(),true);
        }
        else {
          e=pm.insert_from_vertex(traits.curve_flip(cv),srcv.current_iterator(),false);
        }

        push_in_edge_list(cv,Halfedge_handle(e),ftr,edge_list,left_to_right);

        return;
      }

    } //if (!find_nearest_intersection...
    

    //DEALING WITH OVERLAP:
    //1. there are 2 kinds of overlap - 
    //   a - p1 == srcv                  p1------p2
    //                                 srcv------------

    //   b - p1 is right of srcv         p1------p2
    //                             srcv--------------------

    //2. we can seperate the cases, we can make a block of steps 3,4,5 for 
    //   overlap/no overlap, or we can deal only with a, and b can be dealt
    //   by splitting at p1 (and in the step after it becomes srcv == case a).
    //3. We take the latter way (easier to implement) , might be changed in future!!

    //step 3: if p1,p2 is on edge - split the edge and find the vertex of p.
    // if p is on a vertex find it

    if (traits.point_is_same(p1, hh->source()->point())) {
      if (traits.point_is_same(p1,p2)) { //no overlap
        trgtv=Vertex_handle(hh->source());
      }
      else { //deal with overlap
        //we need to check first if lt==FACE because in that case srcv doesn't hold a point yet (it is null) - otherwise srcv has a value
        if ( (lt==FACE || lt==UNBOUNDED_FACE) ||
             !traits.point_is_same(p1,srcv->point())) {
          //deal with it as if the curve ends at p1. (the segment (p1,p2) will be dealt with at the next iteration)
          trgtv=Vertex_handle(hh->source());
        }
        else { //p1 == srcv
          if (traits.point_is_same(p2,hh->target()->point())) {
            trgtv=hh->target();
            push_in_edge_list(hh->curve(),Halfedge_handle(hh),ftr,edge_list,left_to_right,true); //insert with overlap
          }
          else { //p2 is inside hh
            typename Traits::X_curve crv=hh->curve();
            typename Traits::X_curve crv1,crv2;
            traits.curve_split(crv,crv1,crv2,p2);
            Halfedge_handle e=split_edge(hh,crv1,crv2);
            trgtv=e->target();
            
            //inserting the curve (crv1/2) that is incident to p1         
            if (traits.point_is_same(traits.curve_source(crv1),p1) ||
                traits.point_is_same(traits.curve_target(crv1),p1)) {
              push_in_edge_list(crv1,Halfedge_handle(e),ftr,edge_list,left_to_right,true); //insert with overlap
            }
            else {
              push_in_edge_list(crv2,Halfedge_handle(e),ftr,edge_list,left_to_right,true); 
            }
            
          }
        }
      }
    }
    else
      if (traits.point_is_same(p1, hh->target()->point())) {
        if (traits.point_is_same(p1,p2)) { //no overlap
          trgtv=Vertex_handle(hh->target());
        }
        else { //deal with overlap
          //see comment above why this condition is here
          if ( (lt==FACE || lt==UNBOUNDED_FACE) ||
               !traits.point_is_same(p1,srcv->point())) {
            //deal with it as if the curve ends at p1. (the segment (p1,p2) will be dealt with at the next iteration)
            trgtv=Vertex_handle(hh->target());
          } 
          else {
            if (traits.point_is_same(p2,hh->source()->point())) {
              trgtv=hh->source();
              push_in_edge_list(hh->curve(),Halfedge_handle(hh),ftr,edge_list,left_to_right,true); //insert with overlap;
            }
            else { //p2 is inside hh
              typename Traits::X_curve crv=hh->curve();
              typename Traits::X_curve crv1,crv2;
              traits.curve_split(crv,crv1,crv2,p2);
              Halfedge_handle e=split_edge(hh,crv1,crv2);
              trgtv=e->target();
              //inserting the curve (crv1/2) that is incident to p1 
              if (traits.point_is_same(traits.curve_source(crv1),p1) ||
                  traits.point_is_same(traits.curve_target(crv1),p1)) {
                push_in_edge_list(crv1,Halfedge_handle(e),ftr,edge_list,left_to_right,true); //insert with overlap
              }
              else {
                push_in_edge_list(crv2,Halfedge_handle(e),ftr,edge_list,left_to_right,true); 
              }
              
            }
            
          }
        }
      }
      else { //p1 is not on a vertex 
        if (traits.point_is_same(p1,p2)) { //no overlap
          typename Traits::X_curve crv=hh->curve();
          //debug
          //std::cout << traits.curve_source(crv).to_point() << " , " ;
          //std::cout << traits.curve_target(crv).to_point() << std::endl ;

          typename Traits::X_curve crv1,crv2;
          //maybe check if it's fromleft to right in order to assure left to right curve ???
          
          traits.curve_split(crv,crv1,crv2,p2);
          trgtv=((split_edge(hh,crv1,crv2))->target());
        }
        else { //deal with overlap
          //will never get here since we took care in the previous step that
          //overlap will take place only when p1 is on a vertex (otherwise we 
          //create a vertex at p1 (split the edge) and in the next iteration 
          //p1 is on a vertex.)
          CGAL_assertion(false);
        }
      }
    
    //step 4: if (p2==cv.target)
    //          insert cv and return. (p2 is the end of cv)
    if (traits.point_is_same(p2,traits.curve_target(cv))) {
      if (lt==FACE || lt==UNBOUNDED_FACE) {
        
        //can't get here if there is an overlap.
        typename Planar_map::Halfedge_handle e;
        if (left_to_right) {
          e=pm.insert_from_vertex(cv,trgtv.current_iterator(),false);
        }
        else {
          e=pm.insert_from_vertex(traits.curve_flip(cv),trgtv.current_iterator(),true);
        }

        push_in_edge_list(cv,Halfedge_handle(e),ftr,edge_list,left_to_right);
        
        
        return;
      }
      else { //cv source is on a vertex or edge (that was split at step 3
        // or at the switch statement) 
        
        if (traits.point_is_same(p1,p2)) { //no overlap
          typename Planar_map::Halfedge_handle e;
          if (left_to_right) {
            e=pm.insert_at_vertices(cv,srcv.current_iterator(),trgtv.current_iterator());
          }
          else {
            e=pm.insert_at_vertices(traits.curve_flip(cv),srcv.current_iterator(),trgtv.current_iterator());
          }

          push_in_edge_list(cv,Halfedge_handle(e),ftr,edge_list,left_to_right);
          
          return;
        }
        
        else {
          //do nothing - it was dealt with
          if (traits.point_is_same(p1,srcv->point())) {
            //wev'e alraedy pushed (p1,p2) into edge list in step 3
            return;
          }
          else {
            //do nothing p2 will be dealt with at next iteration
            //we are still at p1
          }
        }
      }
    }
      
    //step 5: split cv at trgtv->point() into cv1 and cv2 and insert cv1.
    traits.curve_split(cv,cv1,cv2,trgtv->point());
    
    if (lt==FACE || lt==UNBOUNDED_FACE) {
      typename Planar_map::Halfedge_handle e;
      if (left_to_right) {
        e=pm.insert_from_vertex(cv1,trgtv.current_iterator(),false);
      }
      else {
        e=pm.insert_from_vertex(traits.curve_flip(cv1),trgtv.current_iterator(),true);
      }

      push_in_edge_list(cv1,Halfedge_handle(e),ftr,edge_list,left_to_right);
    }
    else {
      
      if (traits.point_is_same(p1,p2)) { //no overlap
        typename Planar_map::Halfedge_handle e;
        if (left_to_right) {
          //debug
          //std::cout << "srcv=" << srcv->point().to_point();
          //std::cout << " trgv=" << trgtv->point().to_point() << std::endl;

          e=pm.insert_at_vertices(cv1,srcv.current_iterator(),trgtv.current_iterator());
        }
        else {
          e=pm.insert_at_vertices(traits.curve_flip(cv1),srcv.current_iterator(),trgtv.current_iterator());
        }

        push_in_edge_list(cv1,Halfedge_handle(e),ftr,edge_list,left_to_right);
      }
      else {//deal with overlap (don't insert into pm)
        if (!traits.point_is_same(p1,srcv->point())) {
          typename Planar_map::Halfedge_handle e;
          if (left_to_right) {
            e=pm.insert_at_vertices(cv1,srcv.current_iterator(),trgtv.current_iterator());
          }
          else {
            e=pm.insert_at_vertices(traits.curve_flip(cv1),srcv.current_iterator(),trgtv.current_iterator());
          }

          push_in_edge_list(cv1,Halfedge_handle(e),ftr,edge_list,left_to_right);
        }            
        
        else { //p1 == srcv->point(), was dealt with at step 3 
          //so do nothing
        }
        
      }
      
    }
    
    //step 6: find next face and goto step 2
    srcv=trgtv;
    cv=cv2;
    
    
    //finding the next face the curve goes through
    Halfedge_around_vertex_circulator strt,circ,circ1= srcv->incident_halfedges();
    strt=circ=circ1;
    ++circ1;
    //check overlaps
    if (traits.curves_overlap(cv,circ->curve())) {
      //there is an overlap, don't get into the curve_is_between_cw loop.
      next_face=circ->face();
    }      
    else {
      
      if (circ!=circ1) {
        do {
          //check overlap
          if (traits.curves_overlap(cv,circ1->curve())) {
            //there is an overlap, don't get into the curve_is_between_cw func.
            next_face=circ1->face();
            break;        
          }
          
          if (traits.curve_is_between_cw(cv,circ->curve(),circ1->curve(),traits.curve_source(cv))) {
            next_face=circ->face();
            break;
          }
          ++circ;
          ++circ1;
        } while (circ!=strt);
      }
      else
        next_face=circ->face();
      
    }
    
    lt= static_cast<Locate_type>(VERTEX); //workaround since MSVC does not approve the automatic cast here
    
  } //while(1)
  
  
}


///////////////////////////////////////////////////////////////////
//           PRIVATE IMPLEMENTATIONS
////////////////////////////////////
private:

//returns true iff there is an intersection strictly to the right of r_pt
//with an edge of the face f (in that case the nearest intersecting halfedge will be heald at hh and the intersection points in p1,p2)

//in the future we will move this function to the pl strategy, so that the
//default pl can make use of its trapezoidal map to find it faster!

bool find_nearest_intersection(const typename Traits::X_curve& cv, 
                               const typename Traits::Point& r_pt, 
                               Face_handle f, 
                               typename Traits::Point& p1, 
                               typename Traits::Point& p2, 
                               Halfedge_handle& h) const
{
  Ccb_halfedge_circulator first,ccb_circ;
  bool FindFlag=false;
  p1=traits.point_to_right(traits.curve_target(cv)); //initialize p with a far value 

  typename Traits::Point p_cand1,p_cand2;
  if (f->does_outer_ccb_exist()) {
    ccb_circ=first=f->outer_ccb();
    do {
      if (traits.do_intersect_to_right(cv,ccb_circ->curve(),
                                       r_pt)) {

        //change - to prevent cascaded intersection
        //BUG FIX (Iddo 25/11/99)
        //!! the following lines find the rightmost between the left point of ccb_circ and r_pt.
        // we need to find an intersection right of rightmost - otherwise we
        //can find an intersection point that is not on ccb_circ (since we now
        //compare with the original curve of ccb_circ and not with ccb_circ itself) 
        Point cs=traits.curve_source(ccb_circ->curve());
        Point ct=traits.curve_target(ccb_circ->curve());
        Point cleft=traits.point_is_left_low(cs,ct) ? cs : ct;
        Point rightmost = traits.point_is_left_low(r_pt,cleft) ? cleft : r_pt;

        //the fix below is not enough, we need to take care of the following
        //endcase -- rightmost IS the intersection point (and it is right of r_pt), in this case the
        //intersection predicate won't return it (since it returns strictly to the right intersection point)
        //we deal with it with a special case.
        bool special_case=false;
        if (!(traits.point_is_same(rightmost,r_pt))) {
          if (!traits.curves_overlap(cv,ccb_circ->curve())) { 
            //deal with it only when there is no overlap, otherwise it is taken care of
            if (traits.curve_get_point_status(cv,rightmost)==Traits::ON_CURVE){
              p_cand1=p_cand2=rightmost;
              special_case=true;
            }
          }
        }
        
        if (!special_case) { //avoid calling the predicate if we're at a special case (we might ruin p_cand1/2)
          traits.nearest_intersection_to_right(cv,ccb_circ->edge_node()->parent()->curve(),rightmost,p_cand1,p_cand2);
        }

        //debug
        //Point tmp1,tmp2;
        //traits.nearest_intersection_to_right(cv,ccb_circ->curve(),
        //                                     r_pt,tmp1,tmp2);
        //CGAL_assertion(tmp1==p_cand1);
        //CGAL_assertion(tmp2==p_cand2);

        //traits.nearest_intersection_to_right(cv,ccb_circ->edge_node()->parent()->curve(),
        //                                     r_pt,p_cand1,p_cand2);

        //traits.nearest_intersection_to_right(cv,ccb_circ->curve(),
        //                                     r_pt,p_cand1,p_cand2);

        //OVERLAP: because of continuity and x-mono of cv, if p_cand1 is the nearest, then p_cand2 will be nearer than any other.

        if ( (traits.compare_x(p_cand1,p1)==SMALLER) 
             || ( (traits.compare_x(p_cand1,p1)==EQUAL) &&
                  (traits.compare_y(p_cand1,p1)==SMALLER) ) ) {
          p1=p_cand1;
          p2=p_cand2;
          h=ccb_circ;
          FindFlag=true;
        }
      }
    } while (++ccb_circ!=first) ;
    
  }   //outer ccb
  
  Holes_iterator hit=f->holes_begin();
  Holes_iterator h_end=f->holes_end(); //workaround for MSVC

  //for (; hit!=f->holes_end(); ++hit) {
  for (; hit!=h_end; ++hit) {
    first=ccb_circ=*hit;
    do {
      if (traits.do_intersect_to_right(cv,ccb_circ->curve(),
                                       r_pt)) {

        //change - to prevent cascaded intersection
        //BUG FIX - same as above (Iddo 25/11/99)
        Point cs=traits.curve_source(ccb_circ->curve());
        Point ct=traits.curve_target(ccb_circ->curve());
        Point cleft=traits.point_is_left_low(cs,ct) ? cs : ct;
        Point rightmost = traits.point_is_left_low(r_pt,cleft) ? cleft : r_pt;
        
        //we deal with the special case (see above).
        bool special_case=false;
        if (!(traits.point_is_same(rightmost,r_pt))) {
          if (!traits.curves_overlap(cv,ccb_circ->curve())) { 
            //deal with it only when there is no overlap, otherwise it is taken care of
            if (traits.curve_get_point_status(cv,rightmost)==Traits::ON_CURVE){
              p_cand1=p_cand2=rightmost;
              special_case=true;
            }
          }
        }
 
        if (!special_case) {
          traits.nearest_intersection_to_right(cv,ccb_circ->edge_node()->parent()->curve(),rightmost,p_cand1,p_cand2);
        }

        //debug
        //Point tmp1,tmp2;
        //traits.nearest_intersection_to_right(cv,ccb_circ->curve(),
        //                                     r_pt,tmp1,tmp2);
        //CGAL_assertion(tmp1==p_cand1);
        //CGAL_assertion(tmp2==p_cand2);


        //traits.nearest_intersection_to_right(cv,ccb_circ->edge_node()->parent()->curve(),
        //                                     r_pt,p_cand1,p_cand2);
        //traits.nearest_intersection_to_right(cv,ccb_circ->curve(),
        //                                     r_pt,p_cand1,p_cand2);

        //OVERLAP: because of continuity and x-mono of cv, if p_cand1 is the nearest, then p_cand2 will be nearer than any other.

        if ( (traits.compare_x(p_cand1,p1)==SMALLER)||
             ((traits.compare_x(p_cand1,p1)==EQUAL)&&
              (traits.compare_y(p_cand1,p1)==SMALLER)) ) {

          p1=p_cand1;
          p2=p_cand2;
          h=ccb_circ;
          FindFlag=true;
        }
      }
      ++ccb_circ;
    } while (ccb_circ!=first);
  }

  return FindFlag;

}

////////////////////////////////////////////////////////////////////////
// pushes the curve cv corresponding to halfedge e to the edge_node_list
// push_back if left_to_right
//push_front otherwise - will be called from insert_x_curve after
//inserting cv into the pm and getting e
void push_in_edge_list(const typename Traits::X_curve& cv,
                       Halfedge_handle e,
                       Subcurve_node* ftr,
                       In_place_list<Subcurve_node,true>& edge_list,
                       bool left_to_right,
                       bool overlap=false)
{
  if (left_to_right) {
    Edge_node* en=new Edge_node;
    en->set_curve(cv);
    en->ftr=ftr;
    
    //DEALING WITH OVERLAP:
    //we use the 2 redundant pointers - begin_child and past_end_child to create
    //a circular linked list of overlapping edges (for the same halfedge)

    //2 options: circular bidircetionsl list(bi-circulator) , 
    //           or linear single directional list (forward iterator),
    //           bidirectional iterator can't be implemented because we can't
    //           have a sentinel for the past_the_end value.

    //we implement below a bi-dircetional circular list, when no overlap
    //en points at itself - this implies that the default ctr of the
    //edge node has begin_child and past_end_child initialized to this
    //(whereas if we implement a forward list, it is initialized to NULL).

    if (overlap) {
      //pointer shuffling to insert en into circular list
      //past_end_child == next, begin_child == prev

      Edge_node* aux=&(*e->edge_node());
      en->past_end_child = aux; 
      en->begin_child = aux->begin_child;

      aux->begin_child->past_end_child = en;
      aux->begin_child = en;
    }
    else {
      //initialization of circular list with en - not needed - done in the ctr
      //en->past_end_child=en;
      //en->begin_child=en;
    }

    //the following code should replace the above code if we want a single list
    //if (overlap)
    //  en->past_end_child=&(*e->edge_node());

    e->set_edge_node(en);
    e->twin()->set_edge_node(en);
    
    if (traits.point_is_same(e->target()->point(),traits.curve_target(cv)))
      en->set_halfedge(Halfedge_handle(e));
    else
      en->set_halfedge(Halfedge_handle(e->twin())); 
    edge_list.push_back(*en);
  }
  else {  //right_to_left - we've done a flip at beginning
    Edge_node* en=new Edge_node;
    en->set_curve(traits.curve_flip(cv));
    en->ftr=ftr;

    //DEALING WITH OVERLAP: like above
    if (overlap) {
      //pointer shuffling to insert en into circular list
      //past_end_child == next, begin_child == prev

      Edge_node* aux=&(*e->edge_node());
      en->past_end_child = aux; 
      en->begin_child = aux->begin_child;

      aux->begin_child->past_end_child = en;
      aux->begin_child = en;
    }
    else {
      //initialization of circular list with en - no need done in the ctr
      //en->past_end_child=en;
      //en->begin_child=en;
    }

    //the following code should replace the above code if we want a single list
    //if (overlap)
    //  en->past_end_child=&(*e->edge_node());
    
    e->set_edge_node(en);
    e->twin()->set_edge_node(en);
    
    if (traits.point_is_same(e->source()->point(),traits.curve_target(cv)))
      en->set_halfedge(Halfedge_handle(e));
    else
      en->set_halfedge(Halfedge_handle(e->twin())); 
    edge_list.push_front(*en);
  }   
}

//////////////////////////////////////////////////////////////////////////
// The following function is implemented for the Adaptive arr of Bezier
// curves - a local project that is not (currently) in CGAL.


//debug
//public:
protected: 

//replace the subtree rooted at sc, with the list of curves cv_list
//then continue to subdivide with the rest of the levels.

//assumes sc is not a Curve_node and not an edge_node

template <class F_iterator>
Subcurve_iterator replace(Subcurve_iterator sc,
                          const std::list<CGAL_TYPENAME_MSVC_NULL Traits::Curve>& cv_list, 
                          F_iterator F_begin,
                          F_iterator F_end)
{
  Subcurve_node* cn= sc->ftr;

  //define the level we're in and finding the curve_node (the root)
  int level_number=-1;
  Subcurve_node* curr = &(*sc);
  while (curr->ftr) {
    curr=curr->ftr;
    ++level_number;
  }

  Curve_iterator root(curr);

  //step 0: define the past_end levels
  std::vector<CGAL_TYPENAME_MSVC_NULL In_place_list<Subcurve_node,true>::iterator > level_begin;
  std::vector<CGAL_TYPENAME_MSVC_NULL In_place_list<Subcurve_node,true>::iterator > level_end;

  Edge_node* past_end_edge;
  Edge_node* begin_edge;

  Subcurve_iterator begin_aux=sc;
  Subcurve_iterator end_aux=sc;
  ++end_aux;

  level_end.push_back(end_aux); end_aux=(--end_aux)->children_end();
  level_begin.push_back(begin_aux); begin_aux=begin_aux->children_begin();

  while (!begin_aux->is_edge_node()) {
    level_begin.push_back(begin_aux);
    level_end.push_back(end_aux);

    end_aux=(--end_aux)->children_end();
    begin_aux=begin_aux->children_begin();
  }

  past_end_edge = (Edge_node*)(&(*(end_aux))); //use static_cast ?
  begin_edge = (Edge_node*)(&(*begin_aux));

  //step 1: insert the first level of subcurves (the one given in cv_list)
  //do it with vector<inplacelist> and splice at the end

  std::vector<In_place_list<Subcurve_node,true> > levels; //will hold the new subtree
  typename std::vector<In_place_list<Subcurve_node,true> >::size_type sz=0;
  //distance(F_begin,F_end,sz); //find size of vector of in place lists (currently not all STL distance is implemented same - so I implement it myself); 
  F_iterator first=F_begin;
  while(first++!=F_end) ++sz; 
  levels.reserve(sz+1); //!to avoid unreferencing of the lists afterwards (sz+1) because the first is also inserted into the vector

  levels.push_back(In_place_list<Subcurve_node,true>() );
  
  typename std::list<CGAL_TYPENAME_MSVC_NULL Traits::Curve>::const_iterator lit=cv_list.begin();
  for (; lit!=cv_list.end(); ++lit) {
    Subcurve_node* scn=new Subcurve_node;
    scn->ftr=cn;
    scn->set_curve(*lit);
    levels[0].push_back(*scn);
  }

  //step 2: insert the rest of the levels of subcurves (until no more split functions)
  
  int i=1; //current level  
  for (; F_begin!=F_end ; ++F_begin, ++i ) {
    levels.push_back(In_place_list<Subcurve_node,true>());
    Subcurve_iterator scit=levels[i-1].begin();
    for (; scit!=levels[i-1].end(); ++scit) {
      //cut cv into curves and insert them into l
      std::list<CGAL_TYPENAME_MSVC_NULL Traits::Curve> c_list;
      (*(*F_begin))(scit->curve(),c_list);  //split the curve
      Subcurve_iterator aux=levels[i].end();
      --aux; //aux keeps the last place we inserted before the coming insertion

      typename std::list<CGAL_TYPENAME_MSVC_NULL Traits::Curve>::iterator lit=c_list.begin();
      for (; lit!=c_list.end(); ++lit) {
        Subcurve_node* scn=new Subcurve_node;
        scn->ftr=&(*scit); 
        scn->set_curve(*lit);

        levels[i].push_back(*scn); 
      }  
      
      ++aux;
      scit->begin_child=&(*aux);
    }

    (levels[i-1].begin())->begin_child=&(*(levels[i].begin())); //the begin child of the first - now all begin children are well defined

    //defining the past end child pointer of level[i-1]
    scit=levels[i-1].begin();
    Subcurve_iterator aux=scit; ++aux;
    for (; aux!=levels[i-1].end(); ++scit,++aux) { 
      scit->past_end_child=&(*(aux->begin_child));
    }

  }
  //ALL the subcurve levels are now inserted.

  //step 3: insert the edge level.

  //first remove edges from pm then insert_x_curve.
  Edge_iterator start_edges(begin_edge), end_edges(past_end_edge); //assumes there will always be a pointer ctr for Edge_iterator
  while (start_edges!=end_edges) {
    Edge_iterator tmp=start_edges++;
    //pm.remove_edge((tmp->halfedge()).current_iterator());
    //the previous line is replaced by the following to deal with overlaps

    if (tmp->begin_child == &(*tmp)) { //no overlap
      pm.remove_edge((tmp->halfedge()).current_iterator()); //deletes edges

      //debug
      //Ccb_halfedge_circulator cc= *(unbounded_face()->holes_begin());
      //do {
        //debug
      //std::cout << "cc->face=" << &(*cc->face()) << " unbounded=" << &(*unbounded_face()) << std::endl;
      //CGAL_assertion(cc->face()==unbounded_face());
      //++cc;
      //} while (cc != *(unbounded_face()->holes_begin()) );

      //debug
      //Face_handle ff=faces_begin();
      //std::cout << "faces=" << &(*ff); ++ff;
      //std::cout << " " << &(*ff) << std::endl;
      

    }
    else { //tmp overlaps - don't remove the halfedges from planar map
      tmp->begin_child->past_end_child=tmp->past_end_child;
      tmp->past_end_child->begin_child=tmp->begin_child;
      
      //set the edge_node ptr of halfedges to something that is not deleted
      tmp->halfedge()->set_edge_node(tmp->begin_child); 
      tmp->halfedge()->twin()->set_edge_node(tmp->begin_child); 
    }
    
  }
  
  In_place_list<Subcurve_node,true> edge_list;    
  
  Subcurve_iterator scit=levels[i-1].begin();
  Subcurve_iterator aux;
  for (; scit!=levels[i-1].end(); ++scit) {
    In_place_list<Subcurve_node,true> el;    
    
    insert_x_curve(scit->curve(), el , &(*scit));
    scit->begin_child=&(*(el.begin()));
    
    edge_list.splice(edge_list.end(),el); //add el at end of edge_list
    
  } 
  
  scit=levels[i-1].begin();
  
  aux=scit; ++aux;
  for (; aux!=levels[i-1].end(); ++scit,++aux) { 
    scit->past_end_child=&(*(aux->begin_child));
  }

  //step 4: insert the whole subtree back into its place and do the
  //finish on the stitches

  assert((unsigned int)i==level_begin.size()); //number of levels in the new subtree is the same as in the old one 

  Subcurve_node* return_value = &(*levels[0].begin());

  //step 4.1: replacing level[0]

  //erasing the first node and replacing it with the new
  if (sc==cn->children_begin()) { //if sc was a first child then make the new one a first child
    cn->begin_child=&(*levels[0].begin());

    if (cn->ftr!=0) { //if cn is not a curve_node, need to update previous past-end-child
      Subcurve_iterator prev_cn=cn; --prev_cn;
      prev_cn->past_end_child=&(*levels[0].begin());
    }
  }

  (root->levels[level_number]).erase(level_begin[0],level_end[0]);
  level_begin[0] = level_end[0]; --level_begin[0]; //keeping the one before  
  (root->levels[level_number]).splice(level_end[0],levels[0]); //insert the new level[0] into its place 

  //step 4.2: replacing the rest of the subcurve_levels
  //erasing the subcurve levels and replacing them with the new
  int k;
  for (k=1; k<i; ++k) {
    //erasure of old 
    (root->levels[k+level_number]).erase(level_begin[k],level_end[k]);

    level_begin[k] = level_end[k]; --level_begin[k]; //keeping the one before
    //for later use

    //define the past-end-child of the node before the inserted in previous level

    //maybe need to check before I do this if the node before (level_begin[k-1]) is not past-end of levels[k-1]
    level_begin[k-1]->past_end_child=&(*(levels[k].begin()));

    (root->levels[level_number+k]).splice(level_end[k],levels[k]); //insert the new level[k] into its place 

    //define the past-end-child of the last node inserted in the previous level
    Subcurve_iterator prev_last=level_end[k-1];
    --prev_last;
    prev_last->past_end_child=&(*(level_end[k])); 

  }

  //step 4.3: replacing the edge_level
  //do the same for the edge_level
  root->edge_level.erase(begin_edge,past_end_edge);

  //define the past-end-child of the node before the inserted in previous level
  (level_begin[k-1])->past_end_child=&(*(edge_list.begin()));

  //define the past-end-child of the last node inserted in the previous level
  Subcurve_iterator prev_last=level_end[k-1];
  --prev_last;
  //prev_last->past_end_child=&(*(edge_level_end)); 
  prev_last->past_end_child=&(*(past_end_edge)); 
  
  (root->edge_level).splice(past_end_edge,edge_list); //insert the new level[k] into its place   
  
  return Subcurve_iterator(return_value);
}

///////////////////////////////////////////////////////////////////////////
protected:

//debug
//public:

Traits_wrap traits;

Planar_map pm;

In_place_list<Subcurve_node,true> curve_list;


//for UPDATE mode
bool do_update;
Curve_iterator last_updated;

/*
//debug
public:
friend ::std::ostream& operator<<(::std::ostream& o,const Curve_iterator& cn) {
  o << "Curve_node: " << cn->curve() << endl;
  for (unsigned int i=0; i<cn->number_of_sc_levels(); ++i) {

    o << "Level" << i << ": ";
    for (Subcurve_iterator scit=cn->level_begin(i); 
         scit!=cn->level_end(i); ++scit) {
      o << scit->curve() << " , " ;
    }
    o << endl;
    
  }

  o <<"Edge level: ";
  for (Edge_iterator eit=cn->edges_begin(); eit!=cn->edges_end();
       ++eit) {
    o << eit->curve() << " , " ;
  }
  o << endl;

  return o;
}


*/




};

CGAL_END_NAMESPACE

#endif











