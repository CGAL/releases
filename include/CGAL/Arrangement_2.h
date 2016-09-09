// Copyright (c) 1999  Tel-Aviv University (Israel).
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
// $Source: /CVSROOT/CGAL/Packages/Arrangement/include/CGAL/Arrangement_2.h,v $
// $Revision: 1.33 $ $Date: 2003/09/18 10:19:42 $
// $Name: current_submission $
//
// Author(s)     : Iddo Hanniel, 
//                 Eti Ezra <estere@post.tau.ac.il>,
//                 Shai Hirsch <shaihi@post.tau.ac.il> 
#ifndef CGAL_ARRANGEMENT_2_H
#define CGAL_ARRANGEMENT_2_H

//for now, since the arrangement default ctr is currently with the walk pl.
#include <CGAL/Pm_walk_along_line_point_location.h>

#include <CGAL/Planar_map_2.h>
#include <CGAL/Arr_2_bases.h>
#include <CGAL/In_place_list.h>
//for circulators
#include <CGAL/Arr_iterators.h>
#include <CGAL/IO/Verbose_ostream.h>
#include <CGAL/Pm_with_intersections.h>
#include <CGAL/Planar_map_2/Pm_traits_wrap_2.h>
#include <CGAL/IO/Arr_file_scanner.h>

#include <vector>

CGAL_BEGIN_NAMESPACE

template <class _Dcel, class _Traits,
          class Base_node =
          Arr_base_node<typename _Traits::Curve_2,
                        typename _Traits::X_monotone_curve_2> >
class Arrangement_2 {
public:

  typedef _Dcel                                         Dcel;
  typedef _Traits                                       Traits;
  typedef Pm_traits_wrap_2<Traits>                      Traits_wrap;
  typedef Planar_map_2<Dcel,Traits>                     Planar_map;
  typedef Pm_walk_along_line_point_location<Planar_map> WalkPL;
  typedef Planar_map_with_intersections_2<Planar_map>   Pmwx;
  typedef typename Pmwx::Change_notification            Change_notification;

  typedef Arrangement_2<_Dcel,_Traits,Base_node>        Self;

  typedef typename Traits::Point                        Point_2;
  typedef typename Traits::X_curve                      X_monotone_curve_2;
  typedef typename Traits::Curve                        Curve_2;
   
  typedef typename Planar_map::Halfedge_handle          Pm_halfedge_handle;
  typedef typename Planar_map::Face_handle              Pm_face_handle;

  //for size and stuff
  typedef typename Dcel::Size                           Size;
  typedef typename Dcel::size_type                      size_type;
  typedef typename Dcel::difference_type                difference_type;
  typedef typename Dcel::difference_type                Difference;
  
  typedef typename Dcel::iterator_category              iterator_category;

  // Obsolete, for backward compatability
  typedef Change_notification Pmwx_change_notification; 
  typedef Point_2             Point;
  typedef X_monotone_curve_2  X_curve;
  typedef Curve_2             Curve;

  enum Locate_type {
    VERTEX = Planar_map::VERTEX,
    EDGE = Planar_map::EDGE,
    FACE = Planar_map::FACE,
    UNBOUNDED_VERTEX = Planar_map::UNBOUNDED_VERTEX,
    UNBOUNDED_EDGE = Planar_map::UNBOUNDED_EDGE,
    UNBOUNDED_FACE = Planar_map::UNBOUNDED_FACE
  };

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
  typedef typename In_place_list<Subcurve_node,true>::difference_type 
  Hdifference_type;
  typedef typename In_place_list<Subcurve_node,true>::difference_type 
  HDifference;
  typedef std::bidirectional_iterator_tag          Hiterator_category;

  // typedefs for iterators (for curve nodes, edge_nodes, sub_curve_nodes and 
  // HVF)
  typedef typename In_place_list<Subcurve_node,true>::iterator 
  Subcurve_iterator;
  
  typedef typename In_place_list<Subcurve_node,true>::const_iterator 
  Subcurve_const_iterator;

  typedef _Polyhedron_iterator<
  Subcurve_iterator,
    Curve_node,
    HDifference, Hiterator_category>            Curve_iterator;

  typedef _Polyhedron_const_iterator<
  Subcurve_const_iterator, Subcurve_iterator,
    Curve_node,
    HDifference, Hiterator_category>            Curve_const_iterator;

  typedef _Polyhedron_iterator<
  Subcurve_iterator,
    Edge_node,
    HDifference, Hiterator_category>            Edge_iterator;

  typedef _Polyhedron_const_iterator<
  Subcurve_const_iterator, Subcurve_iterator,
    Edge_node,
    HDifference, Hiterator_category>            Edge_const_iterator;


  //wrappers for planar map iterators

  typedef _Polyhedron_iterator<
    typename Planar_map::Vertex_iterator,
    Vertex,
    Difference, typename Planar_map::iterator_category> Vertex_iterator;

  typedef _Polyhedron_const_iterator<
    typename Planar_map::Vertex_const_iterator, 
    typename Planar_map::Vertex_iterator,
    Vertex,
    Difference, typename Planar_map::iterator_category> Vertex_const_iterator;

  typedef _Polyhedron_iterator<
    typename Planar_map::Halfedge_iterator,
    Halfedge,
    Difference, typename Planar_map::iterator_category> Halfedge_iterator;

  typedef _Polyhedron_const_iterator<
    typename Planar_map::Halfedge_const_iterator, 
    typename Planar_map::Halfedge_iterator,
    Halfedge,
    Difference, typename Planar_map::iterator_category>
  Halfedge_const_iterator;

  typedef _Polyhedron_iterator<
    typename Planar_map::Face_iterator,
    Face,
    Difference, typename Planar_map::iterator_category> Face_iterator;

  typedef _Polyhedron_const_iterator<
    typename Planar_map::Face_const_iterator,
    typename Planar_map::Face_iterator,
    Face,
    Difference, typename Planar_map::iterator_category> Face_const_iterator;


  //the following define the overlap circulators 
  //(might be changed to iterators)

  typedef Arr_overlap_circulator<
    Edge_node,Edge_iterator,Bidirectional_circulator_tag>
  Overlap_circulator;

  typedef Arr_overlap_const_circulator<
    Edge_node,
    Edge_const_iterator,
    Bidirectional_circulator_tag> Overlap_const_circulator;

  //handles
  typedef Vertex_iterator                       Vertex_handle;
  typedef Vertex_const_iterator                 Vertex_const_handle;
  typedef Halfedge_iterator                     Halfedge_handle;
  typedef Halfedge_const_iterator               Halfedge_const_handle;
  typedef Face_iterator                         Face_handle;
  typedef Face_const_iterator                   Face_const_handle;

  typedef _Arr_face_circ<  
    Halfedge,
    Halfedge_iterator,
    Forward_circulator_tag>     Ccb_halfedge_circulator;

  typedef _Arr_face_const_circ<
    Halfedge,
    Halfedge_const_iterator,
    Forward_circulator_tag>     Ccb_halfedge_const_circulator;

  typedef _Arr_vertex_circ<
    Halfedge,
    Halfedge_iterator,
    Forward_circulator_tag>     Halfedge_around_vertex_circulator;
  
  typedef _Arr_vertex_const_circ<
    Halfedge,
    Halfedge_const_iterator,
    Forward_circulator_tag>     Halfedge_around_vertex_const_circulator;

  typedef _Polyhedron_iterator< 
    typename Planar_map::Holes_iterator,
    Ccb_halfedge_circulator,
    Difference, std::bidirectional_iterator_tag>        Holes_iterator;

  typedef _Polyhedron_const_iterator<
    typename Planar_map::Holes_const_iterator, 
    typename Planar_map::Holes_iterator,
    Ccb_halfedge_const_circulator,
    Difference, std::bidirectional_iterator_tag>        Holes_const_iterator;

  //TREE NODES:
  //subcurve_node : Base_node + hides pointers - returns handles/iterators
  //curve_node : sub_curve_node + adds levels
  //edge_node : sub_curve_node + adds halfedges

  ///////////////////////////////////////////////////////////////////////////
  //                         SUBCURVE_NODE
  ///////////////////////////////////////////////////////////////////////////
  class Subcurve_node : public Base_node,
                        public In_place_list_base<Subcurve_node> 
  {
  public: 
    friend class Arrangement_2<Dcel,Traits,Base_node>;

    //to enable access of Overlap_iterators into begin_child and past_end_child
    //friend class Overlap_circulator;
    //friend class Overlap_const_circulator;
 
    //the above are not recognized by MSVC, so we use this instead
    friend class 
    Arr_overlap_circulator<Edge_node,Edge_iterator,
                           Bidirectional_circulator_tag>;
    friend class 
    Arr_overlap_const_circulator<Edge_node,Edge_const_iterator,
                                 Bidirectional_circulator_tag>;

    Subcurve_node(int construct_curve=1) : ftr(0),begin_child(0),
					   past_end_child(0)
    {
      if(construct_curve)
	cv_wrap.x_cv=new X_monotone_curve_2;
    }
  
    virtual ~Subcurve_node() {}

    virtual bool is_edge_node() const { return false; }

    Subcurve_iterator parent() { return Subcurve_iterator(ftr); }

    Subcurve_const_iterator parent() const
    { return Subcurve_const_iterator(ftr); }

    Subcurve_iterator children_begin()
    { return Subcurve_iterator(begin_child); }

    Subcurve_const_iterator children_begin() const
    { return Subcurve_const_iterator(begin_child); }
  
    Subcurve_iterator children_end()
    { return Subcurve_iterator(past_end_child); }

    Subcurve_const_iterator children_end() const
    { return Subcurve_const_iterator(past_end_child); }

    Curve_iterator curve_node()
    {
      Subcurve_node * curr = this;
      while (curr->ftr) 
        curr = curr->ftr;
      return Curve_iterator(curr);
    }

    Curve_const_iterator curve_node() const
    {
      const Subcurve_node * curr = this;
      while (curr->ftr)
        curr = curr->ftr;
      return Curve_const_iterator(curr);
    }

    Edge_iterator edges_begin() { 
      Subcurve_node* curr=this;
      while (!curr->is_edge_node()) 
        curr = curr->begin_child;
      return Edge_iterator(curr); 
    }

    Edge_const_iterator edges_begin() const
    {
      const Subcurve_node * curr = this;
      while (!curr->is_edge_node())
        curr = curr->begin_child;
      return Edge_const_iterator(curr);
    }

    Edge_iterator edges_end()
    { 
      Subcurve_node * curr = this;
      while (!curr->is_edge_node())
        //curr will never be a past_end_value:
        curr = curr->past_end_child->prev_link;
      return Edge_iterator(curr->next_link);
    }

    Edge_const_iterator edges_end() const
    {
      const Subcurve_node * curr = this;
      while (!curr->is_edge_node()) 
        curr=curr->past_end_child->prev_link;
      return Edge_const_iterator(curr->next_link);
    }

    //the set_curve is not protected. how do I protect it? (maybe friend the
    //arrangement and make it protected?)

  protected:  

    Subcurve_node * ftr;
    Subcurve_node * begin_child;
    Subcurve_node * past_end_child;

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

    Edge_node() : Subcurve_node(), hdg()
    {
      //the following is needed for the circular overlap list (see the function
      //push_in_edge_list below). if we want to implement a linear list
      //it needs to be removed (begin_child and past_end_child should then be
      //NULL)
      begin_child = this;
      past_end_child = this;
    }

    ~Edge_node() {} //overrides the virtual dtr in Subcurve node

    Halfedge_handle halfedge() { return hdg; }
    Halfedge_const_handle halfedge() const { return hdg; }

    bool is_edge_node() const { return true; }

  private: //maybe protected
    //  void set_halfedge(Halfedge_const_handle h) {hdg=h;} 
    void set_halfedge(Halfedge_handle h) { hdg = h; } 

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

    Curve_node() : Subcurve_node(0), levels(), edge_level()
    {
      cv_wrap.cv = new Curve_2;
    }
  
    ~Curve_node() {} //overrides the virtual dtr in Subcurve_node

    //number of subcurve levels (not including curve level and edge level)
    unsigned int number_of_sc_levels() const {
      return levels.size();
    }

    Subcurve_iterator level_begin(unsigned int i)
    {
      CGAL_precondition(i<number_of_sc_levels());
      return levels[i].begin(); 
    }

    Subcurve_const_iterator level_begin(unsigned int i) const
    {
      CGAL_precondition(i<number_of_sc_levels());
      return levels[i].begin(); 
    }

    Subcurve_iterator level_end(unsigned int i)
    {
      CGAL_precondition(i<number_of_sc_levels());
      return levels[i].end(); 
    }

    Subcurve_const_iterator level_end(unsigned int i) const
    {
      CGAL_precondition(i<number_of_sc_levels());
      return levels[i].end(); 
    }

    //we override the function to make it more efficient when called from 
    //Curve_node
    Edge_iterator edges_begin() { return edge_level.begin(); }
    Edge_const_iterator edges_begin() const { return edge_level.begin(); }
    Edge_iterator edges_end() { return edge_level.end(); }
    Edge_const_iterator edges_end() const { return edge_level.end(); }

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
  //////////////////////////////////////////////////////////////////////
  class Vertex : public Planar_map::Vertex
  {
  public:
    typedef typename Planar_map::Vertex PmVertex;

    Vertex() : PmVertex() {}

    //can also be PmVertex(v)
    Vertex(PmVertex * v) : PmVertex(*v) {}
    Vertex(PmVertex & v) : PmVertex(v) {}

    bool is_incident_edge(Halfedge_const_handle e) const
    { return (PmVertex::is_incident_edge(e.current_iterator())); }

    bool is_incident_face(Face_const_handle f) const
    { return (PmVertex::is_incident_face(f.current_iterator())); }
    
    /*redundant - use inheritance
      int degree() const
      {
      return PmVertex::degree();
      }*/

    Halfedge_around_vertex_circulator incident_halfedges() 
    {
      return Halfedge_around_vertex_circulator
        (Halfedge_handle(PmVertex::incident_halfedges()));
    }

    Halfedge_around_vertex_const_circulator incident_halfedges() const 
    {
      return Halfedge_around_vertex_const_circulator
        (Halfedge_const_handle(PmVertex::incident_halfedges()));
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

    Halfedge() : Planar_map::Halfedge() {}

    Halfedge(typename Planar_map::Halfedge *e) : Planar_map::Halfedge(*e) {}
    Halfedge(typename Planar_map::Halfedge& e) : Planar_map::Halfedge(e) {}

    Vertex_handle source()
    { return Vertex_handle(PmHalfedge::source()); }
    Vertex_const_handle source() const
    { return Vertex_const_handle(PmHalfedge::source()); }
    
    Vertex_handle target()
    { return Vertex_handle(PmHalfedge::target()); }
    Vertex_const_handle target() const
    { return Vertex_const_handle(PmHalfedge::target()); }
    
    Face_handle face() 
    { return Face_handle(PmHalfedge::face()); }
    Face_const_handle face() const
    { return Face_const_handle(PmHalfedge::face()); }
    
    Halfedge_handle twin() 
    { return Halfedge_handle(PmHalfedge::twin()); }
    Halfedge_const_handle twin() const 
    { return Halfedge_const_handle(PmHalfedge::twin()); }
    
    Halfedge_handle next_halfedge() 
    { return Halfedge_handle(PmHalfedge::next_halfedge()); }
    Halfedge_const_handle next_halfedge() const 
    { return Halfedge_const_handle(PmHalfedge::next_halfedge()); }
    
    Ccb_halfedge_circulator ccb()
    { return Ccb_halfedge_circulator(Halfedge_handle(PmHalfedge::ccb())); }

    Ccb_halfedge_const_circulator ccb() const
    { 
      return Ccb_halfedge_const_circulator
        (Halfedge_const_handle(PmHalfedge::ccb()));
    }
  
    Edge_iterator edge_node()
    {
      return Edge_iterator
        (Subcurve_iterator
         (static_cast<Subcurve_node*>(PmHalfedge::edge_node())));
    }

    Edge_const_iterator edge_node() const
    {
      return Edge_const_iterator
        (Subcurve_const_iterator
         (static_cast<const Subcurve_node*>(PmHalfedge::edge_node())));
    }

    //Overlap traversal
    Overlap_circulator overlap_edges()
    { return Overlap_circulator(edge_node()); }

    Overlap_const_circulator overlap_edges() const
    { return Overlap_const_circulator(edge_node()); }


    //the curve and set curve functions in the base classes 
    //will be required to be blank. maybe thats a problem with
    //other functions of the pm that we use here (check it out)
    //is there a better solution ?

protected: //(private?)
    void set_edge_node(Edge_node* b) {PmHalfedge::set_edge_node(b);}
     
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
    typedef typename Arrangement_2<_Dcel,_Traits,Base_node>::Holes_iterator 
    Holes_iterator; 
    typedef typename
    Arrangement_2<_Dcel,_Traits,Base_node>::Holes_const_iterator 
    Holes_const_iterator; 
#endif

    Face() : PmFace() {}
    
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
    { return Holes_iterator(PmFace::holes_begin()); }

    Holes_const_iterator holes_begin() const
    { return Holes_const_iterator(PmFace::holes_begin()); }
    
    Holes_iterator holes_end()
    { return Holes_iterator(PmFace::holes_end()); }

    Holes_const_iterator holes_end() const 
    { return Holes_const_iterator(PmFace::holes_end()); }

    bool is_halfedge_on_inner_ccb(Halfedge_const_handle e) const
    { return PmFace::is_halfedge_on_inner_ccb(e.current_iterator()); }
    
    bool is_halfedge_on_outer_ccb(Halfedge_const_handle e) const
    { return PmFace::is_halfedge_on_outer_ccb(e.current_iterator()); }
      
    //redundant - use inheritance
    /*
    bool does_outer_ccb_exist() const
    {
    return PmFace::does_outer_ccb_exist();
    }*/
    
    Halfedge_handle halfedge_on_outer_ccb() 
    {
      typename Planar_map::Halfedge_handle pmh =
        PmFace::halfedge_on_outer_ccb();
      return Halfedge_handle(pmh);
    }

    Halfedge_const_handle halfedge_on_outer_ccb() const 
    {
      typename Planar_map::Halfedge_const_handle pmh =
        PmFace::halfedge_on_outer_ccb();
      return Halfedge_const_handle(pmh); 
    }

    Ccb_halfedge_circulator outer_ccb() 
    { return (halfedge_on_outer_ccb())->ccb(); }

    Ccb_halfedge_const_circulator outer_ccb() const
    { return (halfedge_on_outer_ccb())->ccb(); }
  };

  //////////////////////////////////////////////////////////
  //                  ARRANGEMENT 2
  ///////////////////////////////////////////////////////////
  
public:

  //in future need to arrange for the pl to be an Arr_pl, 
  //and public for the arrangement
  /*
  //for the first public release we use the default ctr below (with walk pl) -
  //currently it is faster
  Arrangement_2(const Traits& tr=Traits()) : traits(tr), pm(tr), 
  //do_update(true) {
  last_updated=curve_node_end();  
  }
  */

  //default ctr with the walk as default point location
  Arrangement_2() : pm(Traits(), new WalkPL), do_update(true)
  { 
    //new Traits_wrap(tr)
    last_updated=curve_node_end();  
    use_delete_pl=true; //a bool flag for dtr
    traits = (Traits_wrap *)(&pm.get_traits());
    use_delete_traits = false;
  }

  Arrangement_2(const Traits& tr, Pm_point_location_base<Planar_map> * pl_ptr)
    : pm(Traits(), pl_ptr), do_update(true) 
  { 
    last_updated=curve_node_end();  
    use_delete_pl = false; //a bool flag for dtr
    traits = (Traits_wrap *)(&pm.get_traits());
    use_delete_traits = false;
  }

  Arrangement_2(Pm_point_location_base<Planar_map> * pl_ptr) 
    : pm(pl_ptr), do_update(true) 
  {
    last_updated = curve_node_end();  

    use_delete_pl=false;
    traits = (Traits_wrap *)(&pm.get_traits());
    use_delete_traits = false;
  }

  /*! Copy constructor.
   */
  Arrangement_2(const Self & arr) : pm(arr.pm), do_update(true) 
  {
    last_updated = curve_node_end();  
  
    use_delete_pl = false; //a bool flag for dtr

    // these traits is the newly allocated traits for pm.
    traits = (Traits_wrap *)(&pm.get_traits());
    use_delete_traits = false;

    copy_hierarchy_tree(arr);
  }

  /*
    Arrangement_2(Traits_wrap * tr_ptr, Pm_point_location_base<Self> * pl_ptr) 
      : pm(tr_ptr, pl_ptr, NULL), do_update(true)
    {
      last_updated=curve_node_end();  
      traits = (Traits_wrap *)(&pm.get_traits());
      use_delete_pl = false;
      use_delete_traits = false;
    }
  */

  /*! Destructor
   * need to delete the walk
   */
  ~Arrangement_2()
  {
    if (use_delete_pl)
      //casting away the constness before deletion :
      delete(const_cast<Pm_point_location_base<Planar_map>*> 
             (pm.get_point_location())); 
    if (use_delete_traits)
      delete traits;
  }

  Self & operator=(const Self & arr)
  {
    pm = arr.pm;
    copy_hierarchy_tree(arr);
    return *this;
  }

/////////////////////////////////////////////////////////////////////////////
//                  Reading Arrangement functions. 
////////////////////////////////////////////////////////////////////////////
  bool read (std::istream & in)
  {
    clear();
    Arr_file_scanner<Self>  scanner(in);
    return scan_arr(scanner);
  }

  template <class Scanner>
  bool read (std::istream & in, Scanner & scanner)
  {
    clear(); 
    return scan_arr(scanner);
  }

  Traits & get_traits(){return * traits;}
  const Traits & get_traits() const {return * traits;}
  const Pmwx & get_planar_map() const {return pm;}

public:

  Curve_iterator curve_node_begin()
  { return Curve_iterator(curve_list.begin()); }
  Curve_const_iterator curve_node_begin() const
  { return Curve_const_iterator(curve_list.begin()); }

  Curve_iterator curve_node_end()
  { return Curve_iterator(curve_list.end()); }
  Curve_const_iterator curve_node_end() const
  { return Curve_const_iterator(curve_list.end()); }

  Halfedge_iterator halfedges_begin()
  { return Halfedge_iterator(pm.halfedges_begin()); }
  Halfedge_const_iterator halfedges_begin() const
  { return Halfedge_const_iterator(pm.halfedges_begin()); }
  Halfedge_iterator halfedges_end()
  { return Halfedge_iterator(pm.halfedges_end()); }
  Halfedge_const_iterator halfedges_end() const
  { return Halfedge_const_iterator(pm.halfedges_end()); }

  Vertex_iterator vertices_begin()
  { return Vertex_iterator(pm.vertices_begin()); }
  Vertex_const_iterator vertices_begin() const
  { return Vertex_const_iterator(pm.vertices_begin()); }
  Vertex_iterator vertices_end()
  { return Vertex_iterator(pm.vertices_end()); }
  Vertex_const_iterator vertices_end() const
  { return Vertex_const_iterator(pm.vertices_end()); }

  Face_iterator faces_begin()
  { return Face_iterator(pm.faces_begin()); }
  Face_const_iterator faces_begin() const
  { return Face_const_iterator(pm.faces_begin()); }
  Face_iterator faces_end()
  { return Face_iterator(pm.faces_end()); }
  Face_const_iterator faces_end() const
  { return Face_const_iterator(pm.faces_end()); }

  Size number_of_faces() const { return pm.number_of_faces(); }

  //counts every halfedge (i.e always even)
  Size number_of_halfedges() const { return pm.number_of_halfedges(); }
  Size number_of_vertices() const { return pm.number_of_vertices(); }
  Size number_of_curve_nodes() const { return curve_list.size(); }
  
  Face_handle unbounded_face() { return Face_handle(pm.unbounded_face()); }
  Face_const_handle unbounded_face() const
  { return Face_const_handle(pm.unbounded_face()); }

  //checks validity of planar map and arrangement's hierarchy tree structures
  bool is_valid(bool verbose = false) const
  {
    CGAL::Verbose_ostream verr(verbose);
    //std::ostream& verr = std::cerr;
    bool valid = true;
  
    verr << std::endl;
    verr << "CGAL::Arrangment_2<Decl, Traits, Base_Node>::";
    verr << "is_valid( true ):" << std::endl;
  
    // Planar Map Check
    verr << "a) planar_map check... " << std::endl;
    if (pm.is_valid())
      verr << "passed." << std::endl;
    else
      valid = false;
  
    // Check each Curve Hierarchy tree
    Curve_const_iterator    cit;
    Edge_const_iterator     eit;
    Subcurve_const_iterator sit, child_it, parent_it;
  
    unsigned curve_counter = 1;
    bool
      curve_node_curve_node          = true,
      curve_node_is_edge_node        = true,
      curve_node_null_parent         = true,
      curve_node_children_parent     = true,
      curve_node_children_curve_node = true,
      edge_is_edge_node              = true,
      edge_node_curve_node           = true,
      subcurve_is_edge_node          = true,
      subcurve_curve_node            = true,
      subcurve_edges_curve_node      = true,
      subcurve_edges_parent          = true,
      level_structure_ok             = true,
      not_curve_node, 
      circ_curve_is_next_curve       = true,
      circ_curve_is_halfedge_curve   = true,
      edge_curve_is_halfedge_curve   = true;
  
    verr << "b) hierarchy tree check:" << std::endl;
    // for each curve tree
    for (cit = curve_node_begin(); cit != curve_node_end(); 
         cit++, curve_counter++) {
    
      // check curve node properties
      // ---------------------------
    
      // is_edge_node() should return false for a Curve_node
      curve_node_is_edge_node &= (cit->is_edge_node() == false);
    
      // curve_node() should point at this current curve
      curve_node_curve_node &= (cit->curve_node() == cit);
    
      // parent() should return NULL
      curve_node_null_parent &= (cit->parent() == NULL);
    
      // children's parent should equal this curve node
      sit = cit->children_begin();
      for (;sit != cit->children_end(); sit++)
      {
        curve_node_children_curve_node &= (sit->curve_node() == cit);

        //parent() always returns Subcurve_iterator while cit is of type
        // Curve_iterator. to check that a child's parent indeed points at cit
        // I use the following combined test
        curve_node_children_parent &= (sit->parent()->parent() == NULL &&
                                       sit->parent()->curve_node() == cit);  
      }
    
      // check edges properties
      // ----------------------
      eit = cit->edges_begin();
      for (;eit != cit->edges_end(); eit++) {
        // is_edge_node() should return true for an edge node 
        edge_is_edge_node &= (eit->is_edge_node() == true);
        // edged mutual reference check
        edge_node_curve_node &= eit->curve_node() == cit;
        
        // checking the vaildity of overlappings.
        Overlap_const_circulator ovlp_circ = eit->halfedge()->overlap_edges();
        
        edge_curve_is_halfedge_curve &= 
          (traits->curve_equal(eit->x_curve(), eit->halfedge()->curve()));

        do {
          Overlap_const_circulator next = ovlp_circ;
          ++next;
          
          circ_curve_is_next_curve &= 
            traits->curve_equal(ovlp_circ->x_curve(), next->x_curve());
          circ_curve_is_halfedge_curve &= 
            (traits->curve_equal(ovlp_circ->x_curve(),
                                   eit->halfedge()->curve()));
          
        } while (++ovlp_circ != eit->halfedge()->overlap_edges());
      }
    
      // check subcurves properties
      // --------------------------
      int i, levels;
      levels = cit->number_of_sc_levels();
      if (levels > 0) {
        for (i = 0; i < levels; i++) {
          sit = cit->level_begin(i);
          // check that level i is indeed i deep in this tree
          // go up to curve node i times, expect not too find parent
          // not too soon, not too late
          int j;
          for (j = i, not_curve_node = true, parent_it = sit;
               j >= 0 && not_curve_node;
               j--, parent_it = parent_it->parent())
          {
            // parent found too soon?
            if (parent_it->parent() == NULL) not_curve_node = false;
          }
          level_structure_ok &= not_curve_node;

          // parent found too late :
          level_structure_ok &= (parent_it->parent()==NULL); 
          // for each subcurve in level i
          for (;sit != cit->level_end(i) ; sit++) {
            // is_edge_node() should return false for a Subcurve_node
            subcurve_is_edge_node &= (sit->is_edge_node() == false);
                
            // subcurve - curve check 
            subcurve_curve_node &= (sit->curve_node() == cit);

            // subcurve - edge check 
            eit = sit->edges_begin();
            for (;eit != sit->edges_end(); eit++) {
              // ADD CHECK TO PARENT() !!
              subcurve_edges_curve_node &= eit->curve_node() == cit;
            }

            child_it = sit->children_begin();
            for (;child_it != sit->children_end(); child_it++) {
              // ADD CHECK TO PARENT() !!
              subcurve_edges_parent &= (child_it->parent() == sit);
            }
          } // for (;sit != ...
        } // for (i = 0 ...
      } // if
    }
    verr << std::endl;
    verr << "let cn denote the root Curve_node of the ";
    verr << "arrangement hierarchy tree," << std::endl;
    verr << "    sn denote a Subcurve_node in that tree," << std::endl;
    verr << "and en denote an Edge_node in that tree." << std::endl;
    verr << "(&x stands for an iterator that points at x)" << std::endl;
  
    verr << std::endl;
    verr << "Curve checks:" << std::endl;
    verr <<
      "for all cn : cn.is_edge_node() == false                        ---";
    verr << (curve_node_is_edge_node ? "PASS" : "FAIL") << std::endl;
  
    verr <<
      "for all cn : cn.curve_node() == &cn                            ---";
    verr << (curve_node_curve_node ? "PASS" : "FAIL") << std::endl;
  
    verr <<
      "for all cn : cn.parent() == NULL                               ---";
    verr << (curve_node_null_parent ? "PASS" : "FAIL") << std::endl;
  
    verr <<
      "for all children ch of cn : ch.curve_node_node() == &cn        ---";
    verr << (curve_node_children_curve_node ? "PASS" : "FAIL") << std::endl;

    verr <<
      "for all children ch of cn : ch.parent() is indeed cn           ---";
    verr << (curve_node_children_parent ? "PASS" : "FAIL") << std::endl;

    verr <<
      "level i is indeed i deep in tree                               ---";
    verr << (level_structure_ok ? "PASS" : "FAIL") << std::endl;

    verr << std::endl;
    verr << "Subcurve checks:" << std::endl;
    verr <<
      "for all sn : sn.is_edge_node() == false                        ---";
    verr << (subcurve_is_edge_node ? "PASS" : "FAIL") << std::endl;
  
    verr <<
      "for all sn : sn->curve_node() == &cn                           ---";
    verr << (subcurve_curve_node ? "PASS" : "FAIL") << std::endl;
  
    verr <<
      "for all en in an sn subtree: en->curve_node() == &cn           ---";
    verr << (subcurve_edges_curve_node ? "PASS" : "FAIL") << std::endl;

    verr <<
      "for each child ch of sn : ch->parent() == &sn                  ---";
    verr << (subcurve_edges_curve_node ? "PASS" : "FAIL") << std::endl;
  
    verr << std::endl;
    verr << "Edge checks:" << std::endl;
    verr <<
      "for all en : en.is_edge_node() == true                          ---";
    verr << (edge_is_edge_node ? "PASS" : "FAIL") << std::endl;
  
    verr <<
      "for all en : en->curve_node() == &cn                            ---";
    verr << (edge_node_curve_node ? "PASS" : "FAIL") << std::endl;
    
    verr <<
      "for all en : en->curve() == en->halfedge()->curve()             ---";
    verr << (edge_curve_is_halfedge_curve  ? "PASS" : "FAIL") << std::endl;
  
    verr <<
      "for all en : all overlapping circulators have the same curve    ---";
    verr << (circ_curve_is_next_curve ? "PASS" : "FAIL") << std::endl;

    verr <<
      "for all en : all circulators curves == en->halfedge()->curve()  ---";
    verr << (circ_curve_is_halfedge_curve ? "PASS" : "FAIL") << std::endl;


    valid =
      valid                          &
      curve_node_curve_node          &
      curve_node_is_edge_node        &
      curve_node_null_parent         &
      curve_node_children_parent     &
      curve_node_children_curve_node &
      edge_is_edge_node              &
      edge_node_curve_node           &
      subcurve_is_edge_node          &
      subcurve_curve_node            &
      subcurve_edges_curve_node      &
      subcurve_edges_parent          &
      level_structure_ok             &
      edge_curve_is_halfedge_curve   &
      circ_curve_is_next_curve       & 
      circ_curve_is_halfedge_curve;
  
    // Final Result
    verr << std::endl;
    if (valid)
      verr << " object is valid! " << std::endl;
    else
      verr << "object is INVALID!" << std::endl;
    verr <<   "------------------" << std::endl;

    return valid;
  }

  ///////////////////////////////////////////////////////////////////
  //               INSERTION FUNCTIONS
  Curve_iterator insert_from_vertex(const Curve_2       & cv, 
                                  Vertex_handle         src,
                                  Change_notification * en = NULL)
  {
    CGAL_precondition(traits->point_equal(src->point(), 
                                            traits->curve_source(cv)));

    CGAL_precondition(!traits->point_equal(traits->curve_source(cv),
                                             traits->curve_target(cv)) ||
                      !traits->is_x_monotone(cv));

    //either add Arr to pm as friend class or make public functions
    Curve_node* cn= new Curve_node;
    cn->set_curve(cv);
  
    if (!traits->is_x_monotone(cv)) {
      //get an x_monotone sub_curve list and push it in.
      cn->levels.push_back(In_place_list<Subcurve_node,true>());

      //cut cv into x_monotone curves and insert them into l
      std::list<CGAL_TYPENAME_MSVC_NULL Traits::X_curve> x_list;
      traits->curve_make_x_monotone(cv, std::back_inserter(x_list));

      typename std::list<CGAL_TYPENAME_MSVC_NULL Traits::X_curve>::iterator 
        lit=x_list.begin();
      for (; lit!=x_list.end(); ++lit) {
        Subcurve_node* scn=new Subcurve_node;
        scn->ftr=cn;
        scn->set_x_monotone_curve(*lit);
      
        cn->levels[0].push_back(*scn);
      }
      cn->begin_child=&(*(cn->levels[0].begin()));
      cn->past_end_child=&(*(cn->levels[0].end()));

      //so far - inserted subcurve level, we insert the edge level only if
      // we are in update mode.
      if (do_update) {
        Vertex_handle curr_v = src;
        Subcurve_iterator scit=cn->levels[0].begin();
        In_place_list<Subcurve_node,true> edge_list;    
        for (; scit!=cn->levels[0].end(); ++scit) {
          Arr_hierarchy_ops aho(this, edge_list, &(*scit), en);
          Halfedge_handle h = pm.insert_from_vertex
            (scit->curve(), curr_v.current_iterator(), &aho);
          curr_v = h->target();          // vertex for next insertion
          scit->begin_child=&(*(edge_list.begin()));
          //add edge_list at end of edge_level :
          cn->edge_level.splice(cn->edge_level.end(),edge_list); 
        }
      
        scit=cn->levels[0].begin();
        Subcurve_iterator aux=scit; ++aux;
        for (; aux!=cn->levels[0].end(); ++scit,++aux) { 
          scit->past_end_child=&(*(aux->begin_child));
        }
        //the last past_end_child :
        scit->past_end_child=&(*(cn->edge_level.end())); 

      } //if (do_update)
    }

    else { //insert x_curve directly - sub_curve vector is empty

      if (do_update) { //insertion of edge level only if in update mode
        Arr_hierarchy_ops aho(this, cn->edge_level, cn, en);
        pm.insert_from_vertex(cv, src.current_iterator(), &aho);
        cn->past_end_child=&(*(cn->edge_level.end()));
        cn->begin_child=&(*(cn->edge_level.begin()));
      }
    }
  
    Curve_iterator ci=curve_list.insert(curve_list.end(),*cn);
    if (do_update)
      last_updated=ci;

    return ci;
  }

  Curve_iterator insert(const Curve_2 & cv, Change_notification * en = NULL) 
  {
    //either add Arr to pm as friend class or make public functions
    Curve_node* cn= new Curve_node;
    cn->set_curve(cv);
  
    //get an x_monotone sub_curve list and push it in.
    cn->levels.push_back(In_place_list<Subcurve_node,true>());

    //cut cv into x_monotone curves and insert them into l
    std::list<CGAL_TYPENAME_MSVC_NULL Traits::X_curve> x_list;
    traits->curve_make_x_monotone(cv, std::back_inserter(x_list));

    typename std::list<CGAL_TYPENAME_MSVC_NULL Traits::X_curve>::iterator 
      lit=x_list.begin();
    for (; lit!=x_list.end(); ++lit) {
      Subcurve_node* scn=new Subcurve_node;
      scn->ftr=cn;
      scn->set_x_monotone_curve(*lit);
      
      cn->levels[0].push_back(*scn);
    }
    cn->begin_child=&(*(cn->levels[0].begin()));
    cn->past_end_child=&(*(cn->levels[0].end()));

    //so far - inserted subcurve level, we insert the edge level only if
    // we are in update mode.
    if (do_update) {
      Vertex_handle curr_v;
      Halfedge_handle h;
      bool first_insert(true);
      Subcurve_iterator scit=cn->levels[0].begin();
      In_place_list<Subcurve_node,true> edge_list;    
      for (; scit!=cn->levels[0].end(); ++scit) {
	Arr_hierarchy_ops aho(this, edge_list, &(*scit), en);
	if (first_insert) {
	  typename Planar_map::Vertex_handle src, tgt;
	  h = pm.insert_intersecting_xcurve(scit->x_curve(), src, tgt, false, &aho);
	  first_insert = false;
	}
	else {
	  typename Planar_map::Vertex_handle src(curr_v.current_iterator()), tgt;
	  h = pm.insert_intersecting_xcurve(scit->x_curve(), src, tgt, true, &aho);
	}
	curr_v = h->target();       // vertex for next insertion
	scit->begin_child=&(*(edge_list.begin()));
	//add edge_list at end of edge_level :
	cn->edge_level.splice(cn->edge_level.end(),edge_list); 
      }
      
      scit=cn->levels[0].begin();
      Subcurve_iterator aux=scit; ++aux;
      for (; aux!=cn->levels[0].end(); ++scit,++aux) { 
	scit->past_end_child=&(*(aux->begin_child));
      }
      //the last past_end_child :
      scit->past_end_child=&(*(cn->edge_level.end())); 

    } //if (do_update)
  
    Curve_iterator ci=curve_list.insert(curve_list.end(),*cn);
    if (do_update)
      last_updated=ci;

    return ci;
  }

  /////////////////////////////////////////////////////////////////////
  //   insertion with user defined intersection functions

  template <class F_iterator>
  Curve_iterator insert(const Curve_2         & cv,
                        F_iterator            F_begin,
                        F_iterator            F_end,
                        Change_notification * en = NULL) 
  {
    if (F_begin==F_end)
      return insert(cv); //if list is empty return regular insert function

    Curve_node* cn= new Curve_node;
    cn->set_curve(cv);
    typename std::vector<In_place_list<Subcurve_node,true> >::size_type sz=0;

    //distance(F_begin,F_end,sz); 
    //find size of vector of in place lists 
    //(currently not all STL distance is implemented same - 
    //so I implement it myself); 
    F_iterator first=F_begin;
    while(first++!=F_end) ++sz; 

    //! the following line is _crucial_ to avoid unreferencing 
    //of the lists afterwards
    cn->levels.reserve(sz); 

    //step 1: insert the first level of subcurves (level 0)
    cn->levels.push_back(In_place_list<Subcurve_node,true>());

    //cut cv into curves and insert them into l
    std::list<Curve_2> c_list;

    (*(*F_begin))(cv,c_list); 
    ++F_begin;
  
    typename std::list<Curve_2>::iterator lit=c_list.begin();
    for (; lit!=c_list.end(); ++lit) {
      Subcurve_node* scn=new Subcurve_node;
      scn->ftr=cn;
      scn->set_x_monotone_curve(*lit);
      cn->levels[0].push_back(*scn);
    }
    cn->begin_child=&(*(cn->levels[0].begin()));
    cn->past_end_child=&(*(cn->levels[0].end()));
  
    //step 2: insert the rest of the levels of subcurves 
    //(until no more split functions)
    int i=1; //current level  
    for (; F_begin!=F_end ; ++F_begin, ++i ) {
      cn->levels.push_back(In_place_list<Subcurve_node,true>());
      Subcurve_iterator scit=cn->levels[i-1].begin();
      for (; scit!=cn->levels[i-1].end(); ++scit) {
        //cut cv into curves and insert them into l
        std::list<Curve_2> c_list;
        (*(*F_begin))(scit->x_curve(),c_list);  //split the curve

        Subcurve_iterator aux=cn->levels[i].end();
        if (!cn->levels[i].empty()) {
          --aux;
        }

        typename std::list<Curve_2>::iterator lit=c_list.begin();
        for (; lit!=c_list.end(); ++lit) {
          Subcurve_node* scno=new Subcurve_node;
          scno->ftr=&(*scit); 
          scno->set_x_monotone_curve(*lit);
          cn->levels[i].push_back(*scno); 
        }
      
        if (!cn->levels[i].empty()) {
          ++aux;
        }

        //the begin_child is the one directly after the last one of before.:
        scit->begin_child=&(*aux); 
      }

      (cn->levels[i-1].begin())->begin_child=&(*(cn->levels[i].begin())); 
      //the begin child of the first - now all begin children are well defined

      //defining the past end child pointer of level[i-1]
      scit=cn->levels[i-1].begin();
      Subcurve_iterator aux=scit; ++aux;
      for (; aux!=cn->levels[i-1].end(); ++scit,++aux) { 
        scit->past_end_child=&(*(aux->begin_child));
      }
      //the last past_end_child
      scit->past_end_child=&(*(cn->levels[i].end()));
    }
    //ALL the subcurve levels are now inserted.

    //step 3: insert the edge level.
    if (do_update) { 
      Subcurve_iterator scit=cn->levels[i-1].begin();
      In_place_list<Subcurve_node,true> edge_list;    
      for (; scit!=cn->levels[i-1].end(); ++scit) {
        Arr_hierarchy_ops aho(this, edge_list, &(*scit), en);
        pm.insert(scit->x_curve(), &aho);

        scit->begin_child=&(*(edge_list.begin()));
        //add edge_list at end of edge_level :
        cn->edge_level.splice(cn->edge_level.end(),edge_list); 
      }
    
      scit=cn->levels[i-1].begin();
      Subcurve_iterator aux=scit; ++aux;
      for (; aux!=cn->levels[i-1].end(); ++scit,++aux) { 
        scit->past_end_child=&(*(aux->begin_child));
      }

      //the last past_end_child :    
      scit->past_end_child=&(*(cn->edge_level.end())); 
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
  void handle_split_edge(Pm_halfedge_handle orig_edge, 
                         Pm_halfedge_handle new_edge,
                         const typename Traits::X_curve& c1,
                         const typename Traits::X_curve& c2)
  {
    Halfedge_handle e = orig_edge;
    Edge_iterator eit=e->edge_node();
    Curve_iterator cit=eit->curve_node();

    Edge_node* en=new Edge_node;
    //!! bug fix (two weeks of debugging)
    en->ftr=eit->ftr;

    if (traits->point_equal(traits->curve_source(c1), 
                              orig_edge->source()->point()))
    {
      en->set_x_monotone_curve(c2);
      orig_edge->edge_node()->set_x_monotone_curve(c1);
    }
    else {
      en->set_x_monotone_curve(c1);
      orig_edge->edge_node()->set_x_monotone_curve(c2);
    }

    //insert en after eit in the edge_node list
    ++eit;
    (cit->edge_level).insert(eit.current_iterator(),*en);
        
    en->set_halfedge(Halfedge_handle(new_edge));
    
    new_edge->set_edge_node(en);
    new_edge->twin()->set_edge_node(en);
        
    //deal with overlapping edges of eit (if there were any)
    if (((Edge_node*)(orig_edge->edge_node()))->begin_child != 
        (Subcurve_node*)&(*(orig_edge->edge_node()))) 
    {
      //eit has overlapping edges (it doesn't point to itself)
      //split all overlapping edge_nodes and create the circular list of 
      //the edges corresponding to the new edge

      Overlap_circulator occ= (Halfedge_handle(orig_edge))->overlap_edges();
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

        eit->set_x_monotone_curve(orig_edge->curve());
        nen->set_x_monotone_curve(new_edge->curve());
      
        //insert en before/after eit in the edge_node list
        if (eit->halfedge()== Halfedge_handle(orig_edge->twin())) { 
          //eit is directed opposite orig_edge->edge_node()
          //we take advantage of our knowledge of the pm 
          //split function to know this
          nen->set_halfedge(Halfedge_handle(new_edge->twin()));
          //en will be inserted before eit
        }
        else {
          nen->set_halfedge(Halfedge_handle(new_edge));
          ++eit; //en should be inserted after eit
        }

        //insertion into the in_place edge list
        (cit->edge_level).insert(eit.current_iterator(),*nen);
      } while (++occ != (Halfedge_handle(orig_edge))->overlap_edges());
    }
  }

  Halfedge_handle split_edge(Halfedge_handle e, 
                             const typename Traits::X_curve& c1,
                             const typename Traits::X_curve& c2)
  {
    Edge_iterator eit=e->edge_node();
    Curve_iterator cit=eit->curve_node();
    //find the representative halfedge of the edge node 
    //(the one with the same direction as the curve)
    Halfedge_handle e_rep=eit->halfedge(); 

    typename Planar_map::Halfedge_handle 
      pmh=pm.split_edge(e_rep.current_iterator(),c1,c2);
    handle_split_edge(pmh, pmh->next_halfedge(), c1, c2);
    return Halfedge_handle(pmh);
  }

  ////////////////////////////
  //LOCATE
  ////////////////////////////
  Halfedge_handle locate(const typename Traits::Point_2& p,Locate_type& lt)
  {
    typename Planar_map::Locate_type pmlt;
    typename Planar_map::Halfedge_handle pmh=pm.locate(p,pmlt);
  
    switch(pmlt) {
     case Planar_map::VERTEX :
      //workaround since MSVC does not approve the automatic cast here :
      lt=static_cast<Locate_type>(VERTEX); 
      break;
     case Planar_map::EDGE :
      lt=static_cast<Locate_type>(EDGE); 
      break;
     case Planar_map::FACE :
      lt=static_cast<Locate_type>(FACE); 
      break;
     case Planar_map::UNBOUNDED_VERTEX :
      lt=static_cast<Locate_type>(UNBOUNDED_VERTEX); 
      break;
     case Planar_map::UNBOUNDED_EDGE :
      lt=static_cast<Locate_type>(UNBOUNDED_EDGE); 
      break;
     case Planar_map::UNBOUNDED_FACE :
      lt=static_cast<Locate_type>(UNBOUNDED_FACE); 
      break;
    }    

    return Halfedge_handle(pmh);
  }

  Halfedge_const_handle locate(const typename Traits::Point_2& p,
                               Locate_type& lt) const
  {
    typename Planar_map::Locate_type pmlt;
    typename Planar_map::Halfedge_const_handle pmh=pm.locate(p,pmlt);

    switch(pmlt) {
     case Planar_map::VERTEX :
      //workaround since MSVC does not approve the automatic cast here
      lt = static_cast<Locate_type>(VERTEX);
      break;
     case Planar_map::EDGE :
      lt = static_cast<Locate_type>(EDGE);
      break;
     case Planar_map::FACE :
      lt = static_cast<Locate_type>(FACE);
      break;
     case Planar_map::UNBOUNDED_VERTEX :
      lt = static_cast<Locate_type>(UNBOUNDED_VERTEX);
      break;
     case Planar_map::UNBOUNDED_EDGE :
      lt = static_cast<Locate_type>(UNBOUNDED_EDGE);
      break;
     case Planar_map::UNBOUNDED_FACE :
      lt = static_cast<Locate_type>(UNBOUNDED_FACE);
      break;
    } 

    return Halfedge_const_handle(pmh);
  }

  //////////////////////////////////////////////////////
  //     VERTICAL RAY SHOOT
  //////////////////////////////////////////////////////
  Halfedge_handle vertical_ray_shoot(const typename Traits::Point_2& p,
                                     Locate_type& lt, bool up)
  {
    typename Planar_map::Locate_type pmlt;
    typename Planar_map::Halfedge_handle pmh=pm.vertical_ray_shoot(p,pmlt,up);
    switch(pmlt) {
     case Planar_map::VERTEX :
      //workaround since MSVC does not approve the automatic cast here :
      lt = static_cast<Locate_type>(VERTEX);
      break;
     case Planar_map::EDGE :
      lt = static_cast<Locate_type>(EDGE);
      break;
     case Planar_map::FACE :
      lt = static_cast<Locate_type>(FACE);
      break;
     case Planar_map::UNBOUNDED_VERTEX :
      lt = static_cast<Locate_type>(UNBOUNDED_VERTEX);
      break;
     case Planar_map::UNBOUNDED_EDGE :
      lt = static_cast<Locate_type>(UNBOUNDED_EDGE);
      break;
     case Planar_map::UNBOUNDED_FACE :
      lt = static_cast<Locate_type>(UNBOUNDED_FACE);
      break;
    }    

    return Halfedge_handle(pmh);
  }

  Halfedge_const_handle vertical_ray_shoot(const typename Traits::Point_2& p,
                                           Locate_type& lt) const
  {
    typename Planar_map::Locate_type pmlt;
    typename Planar_map::Halfedge_const_handle pmh =
      pm.vertical_ray_shoot(p,pmlt);

    switch(pmlt) {
     case Planar_map::VERTEX :
      //workaround since MSVC does not approve the automatic cast here :
      lt = static_cast<Locate_type>(VERTEX);
      break;
     case Planar_map::EDGE :
      lt = static_cast<Locate_type>(EDGE);
      break;
     case Planar_map::FACE :
      lt = static_cast<Locate_type>(FACE);
      break;
     case Planar_map::UNBOUNDED_VERTEX :
      lt = static_cast<Locate_type>(UNBOUNDED_VERTEX);
      break;
     case Planar_map::UNBOUNDED_EDGE :
      lt = static_cast<Locate_type>(UNBOUNDED_EDGE);
      break;
     case Planar_map::UNBOUNDED_FACE :
      lt = static_cast<Locate_type>(UNBOUNDED_FACE);
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
    typename std::vector<In_place_list<Subcurve_node,true> >::iterator 
      vit=(cit->levels).begin();
    for (; vit!=(cit->levels).end(); ++vit)  
      (*vit).destroy();  //deletes subcurve lists
  
    curve_list.erase(&(*cit)); //deletes from curve list
  }

  ///////////////////////////////////////////////////////////////
  //            CLEAR
  ///////////////////////////////////////////////////////////////
  void clear()
  {
    pm.clear();

    for (Curve_iterator cv_iter = curve_node_begin(); 
         cv_iter != curve_node_end(); 
         cv_iter++){

      // destroying all subcurves levels.
      for (unsigned int i = 0; i < cv_iter->number_of_sc_levels(); i++)
        cv_iter->levels[i].destroy();
    
      // destroying edge node level.
      cv_iter->edge_level.destroy();
    }
  
    curve_list.destroy();
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
      for (; last_updated!=curve_node_end(); ++last_updated) {
        
        unsigned int num=last_updated->number_of_sc_levels();
        if (num>0) {
          In_place_list<Subcurve_node,true> edge_list;        
          Subcurve_iterator scit=last_updated->level_begin(num - 1);
          for (; scit!=last_updated->level_end(num - 1); ++scit) {
            Arr_hierarchy_ops aho(this, edge_list, &(*scit));
            pm.insert(scit->x_curve(), &aho);
            scit->begin_child=&(*(edge_list.begin()));
            //add edge_list at end of edge_level :
            last_updated->edge_level.splice(last_updated->edge_level.end(),
                                            edge_list); 
          }        
          scit=last_updated->level_begin(num - 1);
          Subcurve_iterator aux=scit; ++aux;
          for (; aux!=last_updated->level_end(num-1); ++scit,++aux) { 
            scit->past_end_child=&(*(aux->begin_child));
          }
          //the last past_end_child :
          scit->past_end_child=&(*(last_updated->edge_level.end())); 
        }
        else { //num==0, no subcurve level, insert Curve directly.
          Arr_hierarchy_ops aho(this, 
                                last_updated->edge_level, 
                                &(*last_updated));
          pm.insert(last_updated->x_curve(), &aho);
          last_updated->past_end_child=&(*(last_updated->edge_level.end()));
          last_updated->begin_child=&(*(last_updated->edge_level.begin()));
        }
      } 
      
      //now last_update==curve_node_end() - take the one before
      --last_updated;
    }
  }

  // object given as a parameter to insert function of pmwx
  // such that insert will not know about curve hirarchy
  class Arr_hierarchy_ops : public Change_notification
  {
  public:
    typedef Self Arr;
    Arr_hierarchy_ops(Arr *arr_,
                      In_place_list<Subcurve_node,true>& edge_list_,
                      Subcurve_node* ftr_,
                      Change_notification *user_notifier_ = NULL ) : 
      arr(arr_), edge_list(edge_list_), ftr(ftr_),
      user_notifier(user_notifier_)
    {}

    void add_edge(const typename Traits::X_curve& cv, 
                  Pm_halfedge_handle e, 
                  bool original_direction, bool overlap=false)
    {
      arr->push_in_edge_list(cv, e, ftr, edge_list, original_direction,
                             overlap);
      if (user_notifier != NULL)
        user_notifier->add_edge(cv, e, original_direction, overlap);
    }

    void split_edge(Pm_halfedge_handle orig_edge, 
                    Pm_halfedge_handle new_edge,
                    const typename Traits::X_curve& c1,
                    const typename Traits::X_curve& c2)
    {
      arr->handle_split_edge(orig_edge, new_edge, c1, c2);
      if (user_notifier != NULL)
        user_notifier->split_edge(orig_edge, new_edge, c1, c2);
    }

    void split_face(Pm_face_handle orig_face, Pm_face_handle new_face)
    {
      if (user_notifier != NULL)
        user_notifier->split_face(orig_face, new_face);
    }

    void add_hole(Pm_face_handle in_face, Pm_halfedge_handle new_hole)
    {
      if (user_notifier != NULL)
        user_notifier->add_hole(in_face, new_hole);
    }

    // return in support_cv the suuporting curve of edge. 
    // if not avilable returns false
    const typename Traits::X_curve &edge_support_curve(Pm_halfedge_handle edge)
    {
      Halfedge_handle arr_handle = edge;
      return arr_handle->edge_node()->parent()->x_curve();
    }

    bool have_support_curve() { return true; }

    Arr *arr;
    In_place_list<Subcurve_node,true> &edge_list;
    Subcurve_node* ftr;
    Change_notification *user_notifier;
  };

  friend class Arr_hierarchy_ops;

  // Pushes the curve cv corresponding to halfedge e to the edge_node_list
  // push_back if original_direction
  // push_front otherwise - will be called from insert after
  // inserting cv into the pm and getting e
  //
  // *** Edge_node class:
  // Edge_node holds a curve that is used also as the curve of its
  // associated halfedge.  There are two halfedges (an halfedge and its
  // twin) which point to the Edge_node.  The Edge_node contains a
  // handle to one of these halfedges of which has the same orientation
  // as the curve the Edge_node holds.  Edge_node also contains two
  // pointers named begin_child and past_end_child which are two
  // pointers in a circulat list of all overlapping curves on the
  // specific edge.
  //
  // *** Historical comment (Eti and Eyal, January 2002)
  // original_direction was a boolean flag indicating whether cv and
  // ftr->curve() have the same orientation.  Pm_with_intersections
  // calculated this value and passed it through the add_edge
  // function of the notifier However, this value was miscalculated
  // and had an error value. As a result, we do not use
  // original_direction. Instead we compare the directions of cv and
  // ftr->curve().
  //
  void push_in_edge_list(const typename Traits::X_curve& cv,
                         Pm_halfedge_handle phe,
                         Subcurve_node* ftr,
                         In_place_list<Subcurve_node,true>& edge_list,
                         bool /* original_direction */,
                         bool overlap=false)
  {
    Halfedge_handle e = phe;
    Edge_node* en=new Edge_node;
    en->ftr=ftr;

    // The following condition replaces the original functionality
    // of original_direction, as described in the histroial comment above.
    // The original condition: if (original_direction) 
    if (traits->compare_xy(traits->curve_source(ftr->x_curve()), 
                           traits->curve_target(ftr->x_curve())) ==
        traits->compare_xy(traits->curve_source(cv), 
                           traits->curve_target(cv)))
      en->set_x_monotone_curve(cv);
    else 
      en->set_x_monotone_curve(traits->curve_opposite(cv));
  
    // DEALING WITH OVERLAP:
    // We use the 2 redundant pointers - begin_child and past_end_child
    // to create a circular linked list of overlapping edges (for the
    // same halfedge)
  
    // 2 options: circular bidircetionsl list(bi-circulator) , 
    //            or linear single directional list (forward iterator),
    //            bidirectional iterator can't be implemented because we can't
    //            have a sentinel for the past_the_end value.
  
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
    
    if (traits->point_equal(e->target()->point(),
                              traits->curve_target(en->x_curve())))
      en->set_halfedge(Halfedge_handle(e));
    else
      en->set_halfedge(Halfedge_handle(e->twin())); 

    edge_list.push_back(*en);
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
  Subcurve_iterator replace(Subcurve_iterator          sc,
                            const std::list<Curve_2> & cv_list, 
                            F_iterator                 F_begin,
                            F_iterator                 F_end)
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
    std::vector<CGAL_TYPENAME_MSVC_NULL 
      In_place_list<Subcurve_node,true>::iterator > level_begin;
    std::vector<CGAL_TYPENAME_MSVC_NULL 
      In_place_list<Subcurve_node,true>::iterator > level_end;
    
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
    
    //will hold the new subtree
    std::vector<In_place_list<Subcurve_node,true> > levels; 
    typename std::vector<In_place_list<Subcurve_node,true> >::size_type sz=0;
    //distance(F_begin,F_end,sz); //find size of vector of in place lists 
    //(currently not all STL distance is implemented same - 
    //so I implement it myself); 
    F_iterator first=F_begin;
    while(first++!=F_end) ++sz; 
    
    //!to avoid unreferencing of the lists afterwards 
    //(sz+1) because the first is also inserted into the vector
    levels.reserve(sz+1); 
    levels.push_back(In_place_list<Subcurve_node,true>() );
    
    typename std::list<Curve_2>::const_iterator 
      lit=cv_list.begin();
    for (; lit!=cv_list.end(); ++lit) {
      Subcurve_node* scn=new Subcurve_node;
      scn->ftr=cn;
      scn->set_x_monotone_curve(*lit);
      levels[0].push_back(*scn);
    }
    
    //step 2: insert the rest of the levels of subcurves (until no more 
    //split functions)
    
    int i=1; //current level  
    for (; F_begin!=F_end ; ++F_begin, ++i ) {
      levels.push_back(In_place_list<Subcurve_node,true>());
      Subcurve_iterator scit=levels[i-1].begin();
      for (; scit!=levels[i-1].end(); ++scit) {
        //cut cv into curves and insert them into l
        std::list<Curve_2> c_list;
        (*(*F_begin))(scit->curve(),c_list);  //split the curve
        Subcurve_iterator aux=levels[i].end();
        --aux;
        //aux keeps the last place we inserted before the coming insertion
        
        typename std::list<Curve_2>::iterator
          lit=c_list.begin();
        for (; lit!=c_list.end(); ++lit) {
          Subcurve_node* scn=new Subcurve_node;
          scn->ftr=&(*scit); 
          scn->set_x_monotone_curve(*lit);
          
          levels[i].push_back(*scn); 
        }  
        
        ++aux;
        scit->begin_child=&(*aux);
      }
      
      //the begin child of the first - now all begin children are well defined
      (levels[i-1].begin())->begin_child=&(*(levels[i].begin())); 
      
      //defining the past end child pointer of level[i-1]
      scit=levels[i-1].begin();
      Subcurve_iterator aux=scit; ++aux;
      for (; aux!=levels[i-1].end(); ++scit,++aux) { 
        scit->past_end_child=&(*(aux->begin_child));
      }
      
    }
    //ALL the subcurve levels are now inserted.
    
    //step 3: insert the edge level.
    
    //first remove edges from pm then insert.
    
    //assumes there will always be a pointer ctr for Edge_iterator
    Edge_iterator start_edges(begin_edge), end_edges(past_end_edge);
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
        //std::cout << "cc->face=" << &(*cc->face()) << " unbounded=" 
        //<< &(*unbounded_face()) << std::endl;
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
      Arr_hierarchy_ops aho(this, el, &(*scit));
      pm.insert(scit->curve(), &aho);
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
    
    //number of levels in the new subtree is the same as in the old one  :
    CGAL_assertion((unsigned int)i==level_begin.size()); 
    
    Subcurve_node* return_value = &(*levels[0].begin());
    
    //step 4.1: replacing level[0]
    
    //erasing the first node and replacing it with the new
    
    //if sc was a first child then make the new one a first child :
    if (sc==cn->children_begin()) {
      cn->begin_child=&(*levels[0].begin());
      
      //if cn is not a curve_node, need to update previous past-end-child :
      if (cn->ftr!=0) { 
        Subcurve_iterator prev_cn=cn; --prev_cn;
        prev_cn->past_end_child=&(*levels[0].begin());
      }
    }
    
    (root->levels[level_number]).erase(level_begin[0],level_end[0]);
    level_begin[0] = level_end[0]; --level_begin[0]; //keeping the one before 
    
    //insert the new level[0] into its place : 
    (root->levels[level_number]).splice(level_end[0],levels[0]); 
    
    //step 4.2: replacing the rest of the subcurve_levels
    //erasing the subcurve levels and replacing them with the new
    int k;
    for (k=1; k<i; ++k) {
      //erasure of old 
      (root->levels[k+level_number]).erase(level_begin[k],level_end[k]);
      
      level_begin[k] = level_end[k]; --level_begin[k]; //keeping the one before
      //for later use
      
      //define the past-end-child of the node before the inserted in 
      //previous level

      //maybe need to check before I do this if the node before 
      //(level_begin[k-1]) is not past-end of levels[k-1]
      level_begin[k-1]->past_end_child=&(*(levels[k].begin()));
      
      //insert the new level[k] into its place 
      (root->levels[level_number+k]).splice(level_end[k],levels[k]); 
      
      //define the past-end-child of last node inserted in the previous level
      Subcurve_iterator prev_last=level_end[k-1];
      --prev_last;
      prev_last->past_end_child=&(*(level_end[k])); 
      
    }
    
    //step 4.3: replacing the edge_level
    //do the same for the edge_level
    root->edge_level.erase(begin_edge,past_end_edge);
    
    //define the past-end-child of node before the inserted in previous level
    (level_begin[k-1])->past_end_child=&(*(edge_list.begin()));
    
    //define the past-end-child of the last node inserted in the previous level
    Subcurve_iterator prev_last=level_end[k-1];
    --prev_last;
    //prev_last->past_end_child=&(*(edge_level_end)); 
    prev_last->past_end_child=&(*(past_end_edge)); 
    
    //insert the new level[k] into its place   
    (root->edge_level).splice(past_end_edge,edge_list); 
    
    return Subcurve_iterator(return_value);
  }
  
  ///////////////////////////////////////////////////////////////////////////
  //                 Scanning Arrangement.
  ///////////////////////////////////////////////////////////////////////// 
private:
  void copy_hierarchy_tree(const Self& arr)
  {
    typedef std::map<const void*, void*> ConnectMap;
    typedef std::map<void*, Halfedge_iterator> Pointer_halfedge_Map;
    
    // mapping all halfedges pointers of the two arrangements.
    ConnectMap  cross_halfedges;
    Halfedge_iterator h_iter1;
    Halfedge_const_iterator h_iter2;
    // we need this for overlapping edge nodes which share pointers to
    // edge nodes on different hirarchies trees.
    ConnectMap  all_edges_map; 
    
    // assuming that the two containers are in the SAME order.
    for (h_iter1 = halfedges_begin(), h_iter2 = arr.halfedges_begin(); 
         h_iter1 != halfedges_end() && h_iter2 != arr.halfedges_end(); 
         ++h_iter1, ++h_iter2)
      cross_halfedges.insert(ConnectMap::value_type((const void*) &(*h_iter2), 
                                                    (void*) &(*h_iter1)));
    
    // mapping the arrangement halfedges pointers to halfedges handles.
    Pointer_halfedge_Map  current_halfedges_pointers;
    for (h_iter1 = halfedges_begin(); h_iter1 != halfedges_end(); ++h_iter1)
    {
      current_halfedges_pointers.insert
        (Pointer_halfedge_Map::value_type((void*) &(*h_iter1), h_iter1));
    }
    
    // for each curve node
    Curve_const_iterator cv_iter;
    for (cv_iter = arr.curve_list.begin(); 
         cv_iter != arr.curve_list.end(); 
         ++cv_iter)
    {
      // first creating the curve node.
      Curve_node* cn = new Curve_node;
      cn->assign(*cv_iter);
      
      // creating subcurve nodes.
      ConnectMap  scn_map;
      unsigned int i;
      // for each level
      for (i = 0; i < cv_iter->levels.size(); ++i)
      {
        // the current level to be created
        In_place_list<Subcurve_node,true> level; 
        // for each subcurve node
        Subcurve_const_iterator scv_iter;
        for (scv_iter = cv_iter->levels[i].begin(); 
             scv_iter !=  cv_iter->levels[i].end(); ++scv_iter){
          Subcurve_node* scn = new Subcurve_node;
          
          scn->assign(*scv_iter);
          
          level.push_back(*scn);
        }
        // inserting the i'th level to current curve node.
        cn->levels.push_back(level);
        
        // copy the original items in cn->levels[i] - otherwise makes a
        // copy.  Notice that the vector of levels is NOT in place and
        // hence mapping the scn pointers instead of the original values
        // will cause a bug!.
        Subcurve_iterator new_scv_iter;
        for (scv_iter = cv_iter->levels[i].begin(), 
               new_scv_iter = cn->levels[i].begin(); 
             scv_iter != cv_iter->levels[i].end() && 
               new_scv_iter != cn->levels[i].end(); 
             ++scv_iter, ++new_scv_iter)
        {
          scn_map.insert(ConnectMap::value_type((const void*)&(*scv_iter), 
                                                (void*) &(*new_scv_iter)));
        }
        
        // Notice that arrangement uses the pointers of end() at each
        // level, instead of the expected NULL pointer.
        scn_map.insert(ConnectMap::value_type
                       ((const void*) cv_iter->levels[i].end().operator->(), 
                        (void*) (cn->levels[i].end().operator->()) ));
      }
      
      // creating edge nodes mapping, we use it (in spite we have
      // all_edge_nodes) for efficientcy.
      ConnectMap  edge_map;
      ConnectMap  halfedge_edge_map;
      Edge_const_iterator edge_iter;
      for (edge_iter = cv_iter->edge_level.begin(); 
           edge_iter != cv_iter->edge_level.end(); ++edge_iter){
        Edge_node* en = new Edge_node;
        
        en->assign(*edge_iter);
        
        halfedge_edge_map.insert
          (ConnectMap::value_type((const void*) &(*edge_iter), 
                                  (void*) &*(edge_iter->halfedge()) ));
        cn->edge_level.push_back(*en);
      }
      
      Edge_iterator new_edge_iter;
      for (edge_iter = cv_iter->edge_level.begin(), 
             new_edge_iter = cn->edge_level.begin(); 
           edge_iter != cv_iter->edge_level.end() && 
             new_edge_iter != cn->edge_level.end(); 
           ++edge_iter, ++new_edge_iter)
      {
        edge_map.insert(ConnectMap::value_type((const void*) &(*edge_iter), 
                                               (void*) &(*new_edge_iter)));
        all_edges_map.insert(ConnectMap::value_type
                             ((const void*) &(*edge_iter),
                              (void*) &(*new_edge_iter)));
      }
      
      edge_map.insert(ConnectMap::value_type
                      ((const void*) cv_iter->edge_level.end().operator->(), 
                       (void*) (cn->edge_level.end().operator->()) ));
      all_edges_map.insert(ConnectMap::value_type
                           ((const void*)cv_iter->
                            edge_level.end().operator->(),
                            (void*) (cn->edge_level.end().operator->()) ));
      
      // updating all edge nodes vector - we need this for overlapping
      // edge nodes which share pointers to edge nodes on different
      // hirarchies trees. 
      
      // updating pointers between sub curve nodes.
      for (i = 0; i < cv_iter->levels.size(); ++i) {
        Subcurve_const_iterator scv_iter;
        Subcurve_iterator new_scv_iter;
        for (scv_iter = cv_iter->levels[i].begin(), 
               new_scv_iter = cn->levels[i].begin(); 
             scv_iter != cv_iter->levels[i].end() && 
               new_scv_iter != cn->levels[i].end(); 
             ++scv_iter, ++new_scv_iter)
        {
          Subcurve_node* scn = &*new_scv_iter;
          // if it's the first level, than the father pointer is to the
          // curve node cn;
          if (i == 0)
            scn->ftr = cn;
          else {
            Subcurve_node* scn_ftr = 
              (Subcurve_node*)
              (scn_map.find((const void*) &*(scv_iter->ftr))->second);
            scn->ftr = scn_ftr;
          }
          
          // if the level is not the last one.
          if (i+1 < cv_iter->levels.size()) {
            Subcurve_node* scn_begin_child = 
              (Subcurve_node*)(scn_map.find
                               ((const void*) scv_iter->begin_child)->second);
            scn->begin_child = scn_begin_child;
            
            // pay attention to the fact that the past_end_child can be end().
            Subcurve_node* scn_past_end_child = 
              (Subcurve_node*)
              (scn_map.find((const void*) scv_iter->past_end_child)->second);
            scn->past_end_child = scn_past_end_child;
          }
          else {
            // last level - the next level is the edge node.
            Edge_node* scn_begin_child = 
              (Edge_node*)
              (edge_map.find((const void*) scv_iter->begin_child)->second);
            scn->begin_child = scn_begin_child;

            // pay attention to the fact that the past_end_child can be end()
            Edge_node* scn_past_end_child = 
              (Edge_node*)
              (edge_map.find((const void*) scv_iter->past_end_child)->second);
            scn->past_end_child = scn_past_end_child;
          }
        }
      }
    
      // updating the father pointer of edge node.
      new_edge_iter = cn->edge_level.begin();
      edge_iter = cv_iter->edge_level.begin();
      for (edge_iter = cv_iter->edge_level.begin(), 
             new_edge_iter = cn->edge_level.begin(); 
           edge_iter != cv_iter->edge_level.end() && 
             new_edge_iter != cn->edge_level.end(); 
           ++edge_iter, ++new_edge_iter)
      {
        Edge_node* en = &*new_edge_iter;
        
        if (cn->levels.size() == 0)
          en->ftr = cn;
        else
          en->ftr = (Subcurve_node*)
            (scn_map.find((const void*) edge_iter->ftr)->second);
      }
      
      // updating cn begin and end children pointers.
      if (cn->levels.size()) {
        cn->begin_child = &(*(cn->levels[0].begin()));
        cn->past_end_child = &(*(cn->levels[0].end()));
      }
      else {
        cn->begin_child = &(*(cn->edge_level.begin()));
        cn->past_end_child = &(*(cn->edge_level.end()));
      }
      cn->ftr = 0;
      curve_list.push_back(*cn);
    }
  
    // running on both curve lists and upfdating edge node pointers.
    // Notice that when updating edge node childrens we need all edge
    // nodes to be defined since when there are overlappings edge nodes
    // will points to other edge nodes on different curve lists.
    Curve_iterator new_cv_iter;
    for (cv_iter = arr.curve_list.begin(), new_cv_iter = curve_list.begin(); 
         cv_iter != arr.curve_list.end() && new_cv_iter != curve_list.end(); 
         ++cv_iter, ++new_cv_iter){
    
      Edge_iterator new_edge_iter = new_cv_iter->edge_level.begin();
      Edge_const_iterator edge_iter = cv_iter->edge_level.begin();
      for (edge_iter = cv_iter->edge_level.begin(), 
             new_edge_iter = new_cv_iter->edge_level.begin(); 
           edge_iter != cv_iter->edge_level.end() && 
             new_edge_iter != new_cv_iter->edge_level.end(); 
           ++edge_iter, ++new_edge_iter)
      {
        Edge_node* en = &*new_edge_iter;
      
        Edge_node* en_begin_child = 
          (Edge_node*)
          (all_edges_map.find
           ((const void*) &*(edge_iter->begin_child))->second);
        en->begin_child = en_begin_child;
      
        Edge_node* en_past_end_child = 
          (Edge_node*)
          (all_edges_map.find
           ((const void*) &*(edge_iter->past_end_child))->second); 
        en->past_end_child = en_past_end_child;

        Halfedge* hp = 
          (Halfedge*)
          (cross_halfedges.find(&*(edge_iter->halfedge() ))->second);
        Halfedge_handle curr_h = current_halfedges_pointers.find(hp)->second;

        curr_h->set_edge_node(en);
        curr_h->twin()->set_edge_node(en);

        // notice the fact that curr_h is in the direction of en->curve(), 
        // since cross_halfedges maps the halfedge pointers 1-1. 
        en->hdg = curr_h;
      }
    }
  }

  template <class Scanner>
  bool scan_arr (Scanner& scanner) 
  {
    typedef typename Dcel::Vertex                         D_vertex;
    typedef typename Dcel::Halfedge                       D_halfedge;
    typedef typename Dcel::Face                           D_face;

    typedef typename  Dcel::Vertex_iterator          D_vetrex_iterator;
    typedef typename  Dcel::Vertex_const_iterator    D_vetrex_const_iterator;
    typedef typename  Dcel::Halfedge_iterator        D_halfedge_iterator;
    typedef typename  Dcel::Halfedge_const_iterator  D_halfedge_const_iterator;
    typedef typename  Dcel::Face_iterator            D_face_iterator;
    typedef typename  Dcel::Face_const_iterator      D_face_const_iterator;

    typedef std::pair<std::size_t, std::size_t>      Index_pair;

    // keeping a vector of halfedges (to access them easily by their indices)
    std::vector<Halfedge_handle> halfedges_vec;
  
    if (!scanner.in())
      return false;

    if (!pm.read(scanner.in(), scanner)) {
      std::cerr << "can't read planar map"<<std::endl;
      scanner.in().clear(std::ios::badbit);
      clear();
      return false;
    }

    for (Halfedge_iterator h_iter = halfedges_begin(); 
         h_iter != halfedges_end(); 
         ++h_iter)
      halfedges_vec.push_back(h_iter);

    std::list<std::list<Index_pair> > en_ovlp_child_indices_all_lists;

    std::size_t number_of_curves;
    scanner.scan_index(number_of_curves);
    if (!scanner.in()) {
      std::cerr << "can't read number of curves"<<std::endl;
      scanner.in().clear(std::ios::badbit);
      clear();
      return false;
    }

    unsigned int i;
    for (i = 0; i < number_of_curves; i++) {
      Curve_node* cn = new Curve_node;
      scanner.scan_Curve_node(cn);

      if (!scanner.in()) {
        std::cerr << "can't read curve node"<<std::endl;
        scanner.in().clear(std::ios::badbit);
        clear();
        return false;
      }

      // reading subcurve node levels.
      std::size_t number_of_levels;
      scanner.scan_index(number_of_levels);
      if (!scanner.in()){
        std::cerr << "can't read number of levels"<<std::endl;
        scanner.in().clear(std::ios::badbit);
        clear();
        return false;
      }

      std::vector<std::vector<std::size_t> > begin_child_indices_table, 
        end_child_indices_table;
      //std::vector<std::vector<Subcurve_node*> > scn_table;
    
      unsigned int j;
      for (j = 0; j < number_of_levels; j++) {
        // reading level j.
      
        std::size_t   number_of_subcurves;
        scanner.scan_index(number_of_subcurves);
        if (!scanner.in()) {
          std::cerr << "can't read number of subcurves"<<std::endl;
          scanner.in().clear(std::ios::badbit);
          clear();
          return false;
        }

        In_place_list<Subcurve_node, true>  scn_list;

        std::vector<std::size_t> begin_child_indices_vec,
          end_child_indices_vec;
        //std::vector<Subcurve_node* > scn_vec;

        for (unsigned int k = 0; k < number_of_subcurves; k++) {
          std::size_t   begin_child_index, end_child_index;
        
          scanner.scan_index(begin_child_index);
          if (! scanner.in()){
            std::cerr << "can't read begin child index"<<std::endl;
            scanner.in().clear(std::ios::badbit);
            clear();
            return false;
          }
          scanner.scan_index(end_child_index);
          if (! scanner.in()) {
            std::cerr << "can't read past end child index"<<std::endl;
            scanner.in().clear(std::ios::badbit);
            clear();
            return false;
          }
          
          begin_child_indices_vec.push_back(begin_child_index);
          end_child_indices_vec.push_back(end_child_index);
          
          Subcurve_node* scn = new Subcurve_node;
          
          scanner.scan_Subcurve_node(scn);
          if (! scanner.in()){
            std::cerr << "can't read subcurve node"<<std::endl;
            scanner.in().clear(std::ios::badbit);
            clear();
            return false;
          }
          
          scn->ftr = cn;
          
          scn_list.push_back(*scn);

          // update the tmp vector for finding scn pointers according indices.
          //scn_vec.push_back(scn);  
        } 
        
        begin_child_indices_table.push_back(begin_child_indices_vec);
        end_child_indices_table.push_back(end_child_indices_vec);
        
        (cn->levels).push_back(scn_list);
      }
      
      // now scanning edge nodes.
      std::size_t     number_of_edge_nodes;
      scanner.scan_index(number_of_edge_nodes);
      if (! scanner.in()){
        std::cerr << "can't read numberof edge nodes"<<std::endl;
        scanner.in().clear(std::ios::badbit);
        clear();
        return false;
      }
      
      std::list<Index_pair>  en_ovlp_child_indices_list;
      
      for (j = 0; j < number_of_edge_nodes; j++) {
        //std::vector<Index_pair>  en_ovlp_child_indices_vec;
        Edge_node* en = new Edge_node;
        std::size_t   halfedge_index;
        std::size_t   cn_ovlp_index, en_ovlp_index;
        
        // scanning the past to end child of edge node 
        // (this pointer indicates the overlapping edge nodes).
        scanner.scan_index(cn_ovlp_index);
        if (! scanner.in()){
          std::cerr << "can't read begin overlapping index"<<std::endl;
          scanner.in().clear(std::ios::badbit);
          clear();
          return false;
        }
     
        scanner.scan_index(en_ovlp_index);
        if (! scanner.in()) {
          std::cerr << "can't read past end overlapping index"<<std::endl;
          scanner.in().clear(std::ios::badbit);
          clear();
          return false;
        }
      
        en_ovlp_child_indices_list.push_back(Index_pair(cn_ovlp_index, 
                                                        en_ovlp_index));
 
        scanner.scan_index(halfedge_index);
        if (! scanner.in()) {
          std::cerr << "can't read halfedge index"<<std::endl;
          scanner.in().clear(std::ios::badbit);
          clear();
          return false;
        }
      
        scanner.scan_Edge_node(en);
        if (! scanner.in()) {
          std::cerr << "can't read edge node"<<std::endl;
          scanner.in().clear(std::ios::badbit);
          clear();
          return false;
        }

        // update the halfedge field.
        en->hdg = halfedges_vec[halfedge_index];
        en->ftr = cn;

        // update the pointer in halfedge and its twin to edge_nodes.
        halfedges_vec[halfedge_index]->set_edge_node(en);
        halfedges_vec[halfedge_index]->twin()->set_edge_node(en);

        // updating cn list.
        cn->edge_level.push_back(*en);  
      }
    
      en_ovlp_child_indices_all_lists.push_back(en_ovlp_child_indices_list);

      // updating cn begin and end children pointers.
      if (number_of_levels){
        cn->begin_child = &(*(cn->levels[0].begin()));
        cn->past_end_child = &(*(cn->levels[0].end()));
      }
      else {
        cn->begin_child = cn->edge_level.begin().operator->();
        cn->past_end_child = cn->edge_level.end().operator->();
      }
    
      // now updating begin and past end children pointers of each 
      // subcurve node and also its pointer to its father.
      for (j = 0; j < number_of_levels; j++) {
        unsigned int k = 0, l = 0, m = 0;
        Subcurve_iterator  scn_child_iter;
        Edge_iterator en_child_iter = cn->edges_begin();
 
        if (j+1 < number_of_levels)  // else - we use the en_child_iter.
          scn_child_iter = cn->level_begin(j+1);

        for (Subcurve_iterator scn_iter = cn->level_begin(j); 
             scn_iter != cn->level_end(j); 
             scn_iter++, k++){
          if (j+1 < number_of_levels){ // not including the last one.
            std::size_t begin_child_index = begin_child_indices_table[j][k];
          
            for (;
                 l < begin_child_index &&
                   scn_child_iter != cn->level_end(j+1);
                 scn_child_iter++, l++);
            scn_iter->begin_child = &(*scn_child_iter);
            
            std::size_t past_end_child_index = end_child_indices_table[j][k];
            // running the pointer and also updating father field.
            for (;
                 l < past_end_child_index && 
                   scn_child_iter != cn->level_end(j+1);
                 scn_child_iter++, l++){
              scn_child_iter->ftr = scn_iter.operator->();
            }
            
            scn_iter->past_end_child = &(*scn_child_iter);
          }
          else {
            //the last one should point to the edge nodes.
            std::size_t begin_child_index = begin_child_indices_table[j][k];
          
            for(;
                m < begin_child_index && en_child_iter != cn->edges_end();
                en_child_iter++, m++) ;
            scn_iter->begin_child = &(*en_child_iter);

            std::size_t past_end_child_index = end_child_indices_table[j][k];
            // running the pointer and also updating father field.
            for(;
                m < past_end_child_index && en_child_iter != cn->edges_end();
                en_child_iter++, m++){
              en_child_iter->ftr = scn_iter.operator->();
            }
            scn_iter->past_end_child = &(*en_child_iter);
          }
        }
      }
      curve_list.push_back(*cn);
    }

    // now updating edge node childs, which indicates overlapping edge nodes.
    Curve_iterator cn_iter = curve_node_begin();
    std::list <std::list<Index_pair> >::iterator 
      all_lists_iter = en_ovlp_child_indices_all_lists.begin();

    for (;
         all_lists_iter != en_ovlp_child_indices_all_lists.end() && 
           cn_iter != curve_node_end();
         all_lists_iter++, cn_iter++){
    
      Edge_iterator en_iter = cn_iter->edges_begin();
      for (std::list<Index_pair>::iterator list_iter =
             (*all_lists_iter).begin();
           list_iter !=  (*all_lists_iter).end() && 
             en_iter != cn_iter->edges_end(); 
           list_iter++, en_iter++) {
        std::size_t cn_ovlp_index = list_iter->first;
        std::size_t en_ovlp_index = list_iter->second;
      
        unsigned int j;
        Curve_iterator tmp_cn_iter;
        for (tmp_cn_iter = curve_node_begin(), j = 0;
             tmp_cn_iter != curve_node_end() && j < cn_ovlp_index;
             tmp_cn_iter++, j++);
        // now tmp_cn_iter is the cn_ovlp_index'th curve node.
        Edge_iterator tmp_en_iter;
        for (tmp_en_iter = tmp_cn_iter->edges_begin(), j = 0;
             tmp_en_iter != tmp_cn_iter->edges_end() && j < en_ovlp_index; 
             tmp_en_iter++, j++);
        // now tmp_en_iter is the en_ovlp_index'th edge node.

        en_iter->past_end_child = tmp_en_iter.operator->();
      }
    }
 
    return true;
  }

///////////////////////////////////////////////////////////////////////////
private:
  bool use_delete_pl;
  bool use_delete_traits;

protected:

  //debug
  //public:

  Traits_wrap *traits;

  Pmwx pm;

  In_place_list<Subcurve_node,true> curve_list;


  //for UPDATE mode
  bool do_update;
  Curve_iterator last_updated;

  /*
  //debug
  public:
  friend ::std::ostream& operator<<(::std::ostream& o,
  const Curve_iterator& cn) {
  o << "Curve_node: " << cn->curve() << std::endl;
  for (unsigned int i=0; i<cn->number_of_sc_levels(); ++i) {

  o << "Level" << i << ": ";
  for (Subcurve_iterator scit=cn->level_begin(i); 
  scit!=cn->level_end(i); ++scit) {
  o << scit->curve() << " , " ;
  }
  o << std::endl;
    
  }

  o <<"Edge level: ";
  for (Edge_iterator eit=cn->edges_begin(); eit!=cn->edges_end();
  ++eit) {
  o << eit->curve() << " , " ;
  }
  o << std::endl;

  return o;
  }
  */
};

CGAL_END_NAMESPACE

#endif
