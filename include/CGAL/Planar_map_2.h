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
// file          : include/CGAL/Planar_map_2.h
// package       : pm (3.07)
// source        : 
// revision      : 
// revision_date : 
// author(s)     : Iddo Hanniel
//                 Eyal Flato
//                 Oren Nechushtan
//
//
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// Chapter       : 
// email         : cgal@cs.uu.nl
//
// ======================================================================
#ifndef CGAL_PLANAR_MAP_2_H
#define CGAL_PLANAR_MAP_2_H

#ifndef CGAL_PLANAR_MAP_MISC_H
#include <CGAL/Planar_map_misc.h>
#endif

#ifndef CGAL_TOPOLOGICAL_MAP_H
#include <CGAL/Topological_map.h>
#endif




#ifndef CGAL_PM_DEFAULT_POINT_LOCATION_H
#include <CGAL/Pm_default_point_location.h>
#endif


CGAL_BEGIN_NAMESPACE

////////////////////////////////////////////////////////////////////////////
//      PLANAR_MAP_2   


template <class _Dcel, class _Traits>
class Planar_map_2 : public Topological_map<_Dcel> {


public:
  typedef _Dcel Dcel;
  typedef _Traits Traits;
  typedef Planar_map_2<Dcel,Traits> Self;
  typedef Planar_map_traits_wrap<Traits> Traits_wrap;
  typedef typename Traits::X_curve X_curve;
  typedef typename Traits::Point Point;
  
  typedef enum{ VERTEX = 1 , EDGE , FACE , UNBOUNDED_FACE } Locate_type ;



  
  Planar_map_2 () :traits(),pl(new Pm_default_point_location<Self>),use_delete_pl(true)
  {
      pl->init(*this,traits);
  }    

  Planar_map_2 (Pm_point_location_base<Self> *pl_ptr) : traits(),pl(pl_ptr),use_delete_pl(false) {
    pl->init(*this,traits);
  }

  
  virtual ~Planar_map_2 () {
    if (use_delete_pl)
      delete pl;
  }
  
  
  
  Halfedge_handle insert_in_face_interior(const typename Traits::X_curve& cv, Face_handle f) 
  {
    Halfedge_handle h = Topological_map<Dcel>::insert_in_face_interior(f);
    h->set_curve(cv);  //should set the curve of the twin as well but for now
    h->twin()->set_curve(cv);
    h->source()->set_point(traits.curve_source(cv));
    h->target()->set_point(traits.curve_target(cv));
    
     //pl->insert(h);  //maybe should be above
     //iddo - for arrangement
     pl->insert(h,cv);

    return h;
  }
  
  Halfedge_handle insert_from_vertex(const typename Traits::X_curve& cv, Vertex_handle v1, bool source) 
  {
    //find the previous of cv.
    Halfedge_around_vertex_circulator after=v1->incident_halfedges();
    Halfedge_around_vertex_circulator previous=v1->incident_halfedges();
    ++after;
    
    if (after!=previous) {
      while (!(traits.curve_is_between_cw(cv,previous->curve(),after->curve(),v1->point()))) {
        ++after;
        ++previous;
      }
    }
    
    Halfedge_handle h = Topological_map<Dcel>::insert_from_vertex(previous);  
    h->set_curve(cv);  
    h->twin()->set_curve(cv);
    //h is now pointing from v1
    
    if (source)
      h->target()->set_point(traits.curve_target(cv));
    else
      h->target()->set_point(traits.curve_source(cv));
    
     //pl->insert(h);  //maybe should be above
     //iddo - for arrangement
     pl->insert(h,cv);

    return h;
  }
  
  
  Halfedge_handle insert_at_vertices(const typename Traits::X_curve& cv, 
                                     Vertex_handle v1, Vertex_handle v2) 
  {
    Size num_before=number_of_faces();
    
    Halfedge_around_vertex_circulator after=v1->incident_halfedges();
    Halfedge_around_vertex_circulator previous1=v1->incident_halfedges();
    ++after;
    
    if (after!=previous1) {
      while (!(traits.curve_is_between_cw(cv,previous1->curve(),after->curve(),v1->point()))) {
        ++after;
        ++previous1;
      }
    }    
    
    after=v2->incident_halfedges();
    Halfedge_around_vertex_circulator previous2=v2->incident_halfedges();
    ++after;
    
    if (after!=previous2) {
      while (!(traits.curve_is_between_cw(cv,previous2->curve(),after->curve(),v2->point()))) {
        ++after;
        ++previous2;
      }
    }    
    
    
    bool prev1_before_prev2 = prev1_inside_hole(previous1,previous2,cv);
    Halfedge_handle h;
    if (prev1_before_prev2)
      h = Topological_map<Dcel>::insert_at_vertices(previous1,previous2); 
    else
      h = Topological_map<Dcel>::insert_at_vertices(previous2,previous1);
    
    h->set_curve(cv); 
    h->twin()->set_curve(cv);
    
    Size num_after=number_of_faces();
    if (num_after-num_before) { //if additional face was added - move holes
      Face_handle nf = h->face(); //the new face will always be the one pointed at by h
      Face_handle of = h->twin()->face(); //old face
      
      Holes_iterator it=of->holes_begin();
      while (it!=of->holes_end()) {
        //check if the hole is inside new face
        if ( point_is_in((*it)->target()->point(),nf) ) {
          Holes_iterator tmp=it;  //deletion invalidates iterators so... 
          ++it;   //assumes only the erased iterator is invalidated (like stl
          //list) 
					
          move_hole( tmp,of,nf); 
        }
        else
          ++it;
      }
			
    }
		
    if (!prev1_before_prev2) h=h->twin();
    

     //pl->insert(h);
     //iddo - for arrangement
     pl->insert(h,cv);

    return h;
  }   
	
private:
  //a private implementation which defines if previous1 is on an outer ccb of 
  //the new face (returns true) or on an inner ccb (returns false)
  bool prev1_inside_hole(Halfedge_handle previous1,Halfedge_handle previous2,
                         const typename Traits::X_curve& cv) 
  {
    //Defining geometrically wether there is a new face an if there is find
    //if previous1 is on the outside of the new face (send previous1,previous2)
    //or on the inside of the new face (send previous2,previous1)
		
    //the algorithm: 1. go over all the halfedges of the face which will hold 
    //previous1 (since the new face is not constructed yet, 
    //this is modeled by going from previous2->next to previous1 and then
    //over the new curve)
		
    //2. find if the left-most-lower 
    //halfedge  in the path (i.e, the one with the leftmost down target and 
    //is the lowest to the right among the incident edges of this vertex)
    // is directed left (we are on the outside) or right (we are inside )
    //(if not on same ccb then it doesn't matter and return true)
		
    Ccb_halfedge_circulator left_edge(previous2);
    ++left_edge;
    Ccb_halfedge_circulator first(previous2);
    Ccb_halfedge_circulator curr(left_edge);
    
    Ccb_halfedge_circulator last(previous1);
    ++last; //we want the previous1 to be checked as well 
    
    Point left = previous2->target()->point();
    bool b;
    
    do {
      //source
      b=false;
      if (traits.point_is_left( curr->source()->point(),left)) 
        b=true;
      else
        if (traits.point_is_same(curr->source()->point(),left)) {
          if (traits.curve_is_vertical(curr->curve()) &&
              traits.point_is_lower(curr->target()->point(),left) )
            b=true;
          else
            if (traits.curve_compare_at_x_right(curr->curve(),left_edge->curve(),
                                                left)==SMALLER ) 
              b=true;
        }
      
      if (b) {
        left=curr->source()->point();
        left_edge=curr;
      }
      
      //target
      b=false;
      if (traits.point_is_left( curr->target()->point(),left))
        b=true;
      if (traits.point_is_same(curr->target()->point(),left)) {
        if (traits.curve_is_vertical(curr->curve()) &&
            traits.point_is_lower(curr->source()->point(),left) )
          b=true;
        else
          if (traits.curve_compare_at_x_right(curr->curve(),left_edge->curve(),
                                              left)==SMALLER ) 
            b=true;
        
        //we want in the degenerate case to return the halfedge 
        //pointing _at_ the left point 
          else
            if ( (curr)==(left_edge->twin()) )
              b=true;
        
      }
      
      if (b) {
        left=curr->target()->point();
        left_edge=curr;
      }
      
      ++curr;
    } while ( (curr != first) && (curr != last) );
    
    
    //test the new curve against left_edge
    if (traits.point_is_same(traits.curve_target(cv),left)||
        traits.point_is_same(traits.curve_source(cv),left)) {
      if (traits.curve_is_vertical(cv)) {
        return (traits.point_is_lower(previous2->target()->point(),
                                      previous1->target()->point()));
      }
      else
        if (traits.curve_compare_at_x_right(cv,left_edge->curve(),
                                            left)==SMALLER ) {  
          return (traits.point_is_left(previous1->target()->point(),
                                       previous2->target()->point()));
        }
    }
		
    //check if left_edge is from left to right
    if (traits.curve_is_vertical(left_edge->curve())) {
      if (traits.point_is_lower(left_edge->source()->point(),
				left_edge->target()->point()))
        return false;
      else
        return true;
    }
		
    return (traits.point_is_left(left_edge->source()->point(),left_edge->target()->point()));
    
  }
  
  
public:
  Halfedge_handle insert(const typename Traits::X_curve& cv) {
    Point p1=traits.curve_source(cv);
    Point p2=traits.curve_target(cv);
    Locate_type lt1,lt2;
    
    Halfedge_handle h1 = locate(p1,lt1);
    Halfedge_handle h2 = locate(p2,lt2);
    
    if (lt1==VERTEX && lt2==VERTEX) 
      return insert_at_vertices(cv,h1->target(),h2->target()); 
    
    if (lt1==VERTEX && lt2!=VERTEX)
      return insert_from_vertex(cv,h1->target(),true); 
    if (lt1!=VERTEX && lt2==VERTEX)
      return insert_from_vertex(cv,h2->target(),false)->twin();
    
    if (lt1==UNBOUNDED_FACE)
      return insert_in_face_interior(cv,unbounded_face());
    
    if (lt1==FACE)
      return insert_in_face_interior(cv,h1->face());
    
    // makes VC happy
    CGAL_postcondition(false);
    return Halfedge_handle();
		
  }
	
	
  Halfedge_handle split_edge(Halfedge_handle e, const typename Traits::X_curve& c1, const typename Traits::X_curve& c2)
  {
		
    CGAL_precondition(traits.point_is_same(traits.curve_source(c2),
                                           traits.curve_target(c1)));
		
    CGAL_precondition( (traits.point_is_same(traits.curve_source(c1),e->source()->point()) &&
			traits.point_is_same(traits.curve_target(c2),e->target()->point())) ||
			
                       (traits.point_is_same(traits.curve_source(c1),e->target()->point()) &&
			traits.point_is_same(traits.curve_target(c2),e->source()->point())) );
    
    typename Traits::X_curve cv(e->curve());
		
    Halfedge_handle h = Topological_map<Dcel>::split_edge(e);
		
    if (traits.point_is_same(traits.curve_source(c1),h->source()->point())) {
      h->set_curve(c1);
      h->twin()->set_curve(c1);
      h->next_halfedge()->set_curve(c2);
      h->next_halfedge()->twin()->set_curve(c2);
    }
    else {
      h->set_curve(c2);
      h->twin()->set_curve(c2);
      h->next_halfedge()->set_curve(c1);
      h->next_halfedge()->twin()->set_curve(c1);
    }
    
    
    
    h->target()->set_point(traits.curve_target(c1));
    
      
     //pl->split_edge(cv,h,h->next_halfedge());  //update structure in point location
 
     //iddo - for arrangement
    if (traits.point_is_same(traits.curve_source(c1),h->source()->point()))
      pl->split_edge(cv,h,h->next_halfedge(),c1,c2);
    else
      pl->split_edge(cv,h,h->next_halfedge(),c2,c1);
 

    return h;
    
  }
	
  
  Halfedge_handle merge_edge(Halfedge_handle e1, Halfedge_handle e2, 
                             const typename Traits::X_curve& cv) {
    CGAL_precondition( (traits.point_is_same(traits.curve_source(cv),e1->source()->point() )&&
			traits.point_is_same(traits.curve_target(cv),e2->target()->point())) || 
                       (traits.point_is_same(traits.curve_target(cv),e1->source()->point() )&&
			traits.point_is_same(traits.curve_source(cv),e2->target()->point())) );
		
    typename Traits::X_curve c1(e1->curve()), c2(e2->curve());
    
    Halfedge_handle h = Topological_map<Dcel>::merge_edge(e1,e2); 
    h->set_curve(cv);
    h->twin()->set_curve(cv);
    
     //pl->merge_edge(c1,c2,h);
     //iddo - for arrangement
     pl->merge_edge(c1,c2,h,cv);
 

    return h;
  }
	
  Face_handle remove_edge(Halfedge_handle e) {
    pl->remove_edge(e);
		
    //if a new hole can be created define geometrically the 
    //halfedge (e or e->twin) that points at the new hole.
    //if the leftmost point in the path e...e->twin
    //is left of the leftmost point in the path e->twin ... e
    //then e->twin  points at the hole created.
		
    if (e->face() == e->twin()->face() ) {
      Ccb_halfedge_circulator ccb_e=e->ccb() ;
      Ccb_halfedge_circulator ccb_t=e->twin()->ccb();
      
      Point e_left=e->target()->point();
      Point t_left=ccb_t->target()->point();
			
      //find the leftmost point in the path from e to its twin
      Ccb_halfedge_circulator aux=ccb_e;
      do {
        if (traits.compare_x(aux->target()->point(),e_left)==SMALLER) {
          e_left=aux->target()->point();
        }
      } while (++aux!=ccb_t);
			
      //find the leftmost point in the path from the twin to e
      aux=ccb_t;
      do {
        if (traits.compare_x(aux->target()->point(),t_left)==SMALLER) {
          t_left=aux->target()->point();
        }        
      } while (++aux!=ccb_e);
			
      //compare the two left points
      if (traits.compare_x(t_left,e_left) == SMALLER) //e points at hole 
        return Topological_map<Dcel>::remove_edge(e);
      else
        return Topological_map<Dcel>::remove_edge(e->twin());
			
    }
    else {
      
      return Topological_map<Dcel>::remove_edge(e);
    }
		
  }
	
	
  Halfedge_handle vertical_ray_shoot(const typename Traits::Point& p,
                                     Locate_type &lt, bool up)
  {
    return pl->vertical_ray_shoot(p,lt,up);
  }
	
  
  Halfedge_const_handle vertical_ray_shoot(const typename Traits::Point& p,
                                           Locate_type &lt, bool up) const
  {
    return pl->vertical_ray_shoot(p,lt,up);
  }
	
	
	
  Halfedge_handle locate(const typename Traits::Point& p,
                         Locate_type &lt)
  {
    return pl->locate(p,lt);
  }
	
  Halfedge_const_handle locate(const typename Traits::Point& p,
                               Locate_type &lt) const
  {
    return pl->locate(p,lt);
  }
	
	
	
protected:  //private implementation
  //returns true if the point  is inside (in the strict sense) of nf
  //algorithm: count the intersections of a vertical ray shoot - are they odd ?
  //assumes outer ccb exists
  bool point_is_in(const typename Traits::Point& p, Face_const_handle nf) const
  {
    int count = 0;
    
    Ccb_halfedge_const_circulator circ = nf->outer_ccb();
    do {
      ++circ;
    } while ((traits.curve_is_vertical(circ->curve()))&&circ!=nf->outer_ccb());
    if (circ==nf->outer_ccb() && traits.curve_is_vertical(circ->curve()) )
      return false; 
    //if the whole ccb is vertical then the point is out.
    //else advance to a non vertical curve 
		
    Ccb_halfedge_const_circulator last = circ;
    
    
    do {
      if (traits.point_is_same(circ->target()->point(), p)) //point is on outer ccb 
        return false;
      if (!traits.curve_is_vertical(circ->curve())) {
				
        if ( (traits.curve_get_point_status(circ->curve(),p) == 
              Traits::UNDER_CURVE) && 
             !(traits.point_is_same_x(circ->source()->point(),p)) ) {  
          //point is under curve in the range (source,target]
					
          if (traits.point_is_same_x(circ->target()->point(),p)) {
            //p is exactly under a vertex of the ccb - if next is not on the 
            //same side of the vertical line from p as circ is, 
            //we count one more intersection
            
            Ccb_halfedge_const_circulator next=circ;
            ++next;
            if (traits.curve_is_vertical(next->curve())) {
              //advance to non-vertical edge
              while (traits.curve_is_vertical(next->curve())) {
                ++next;
              }
            }
            if ( (traits.point_is_right(circ->source()->point(),p)&&
                  traits.point_is_left(next->target()->point(),p)) ||
                 (traits.point_is_left(circ->source()->point(),p)&&
                  traits.point_is_right(next->target()->point(),p)) ) {
              
              ++count;
            }
          }
          else {
            ++count;
          }
        }
      }
    } while (++circ!=last);
		
    return (count%2 != 0);  //if count is odd return true
    
  }


	
#ifdef CGAL_PM_DEBUG // for private debug use
  
public:
  void debug()
  {
    if (pl) ((Pm_default_point_location<Self>*)pl)->debug();
  }
  
#else
  
protected:
  
#endif
  
  Traits_wrap  traits;
  Pm_point_location_base<Self> *pl;
private:
  bool use_delete_pl;


};


CGAL_END_NAMESPACE


#endif












