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
// $Source: /CVSROOT/CGAL/Packages/Planar_map/include/CGAL/Pm_simple_point_location.h,v $
// $Revision: 1.13 $ $Date: 2003/09/18 10:24:36 $
// $Name: current_submission $
//
// Author(s)     : Eyal Flato <flato@math.tau.ac.il>

#ifndef CGAL_PM_SIMPLE_POINT_LOCATION_H
#define CGAL_PM_SIMPLE_POINT_LOCATION_H

#include <CGAL/Pm_point_location_base.h>
#include <CGAL/Planar_map_2/Pm_traits_wrap_2.h>

#include <list>

CGAL_BEGIN_NAMESPACE

template <class Planar_map_>
class Pm_simple_point_location : public Pm_point_location_base<Planar_map_> {

public:
  typedef Planar_map_                          Planar_map;
  typedef typename Planar_map::Traits          Traits;
  typedef Pm_point_location_base<Planar_map>   Base;
  typedef Pm_simple_point_location<Planar_map> Self;
  typedef typename Planar_map::Traits_wrap     Traits_wrap;
  typedef typename Planar_map::Locate_type     Locate_type;
  typedef typename Planar_map::Face_handle     Face_handle;
  typedef typename Planar_map::Ccb_halfedge_circulator 
                                               Ccb_halfedge_circulator;
  typedef typename Planar_map::Halfedge_handle Halfedge_handle;
  typedef typename Planar_map::Halfedge_iterator  Halfedge_iterator;
  typedef typename Planar_map::Halfedge           Halfedge;
  typedef typename Planar_map::Vertex_handle      Vertex_handle;
  typedef typename Traits::Point                  Point;
  typedef typename Traits::X_curve                X_curve;
  typedef Pm_bounding_box_base<Planar_map>        Bounding_box;
  typedef typename Base::Halfedge_handle_iterator Halfedge_handle_iterator;
  typedef typename Base::Token                    Token;
  typedef std::list<Halfedge_handle>              Halfedges_list;
	
public:	
  Pm_simple_point_location() : 
    Pm_point_location_base<Planar_map>(),
    traits(0) {}
	
  Pm_simple_point_location(Planar_map* _pm,Traits_wrap* _traits) : 
    Pm_point_location_base<Planar_map>(),traits(_traits),pm(_pm) {}
	
  void init(Planar_map& pmp, Traits& tr) 
  {
    pm = &pmp;
    traits = (Traits_wrap*)(&tr);
  }
	
  void insert(Halfedge_handle, const X_curve &) 
  {
  }
	
  void find_relevant_halfedges(const Point& p, Halfedges_list &relevant) const
  {
    // find whether p is on a halfedge
    typename Planar_map::Halfedge_iterator hit;
    for (hit = pm->halfedges_begin(); hit != pm->halfedges_end(); ++hit) 
      {
	if (traits->point_in_x_range(hit->curve(),p)) 
	  {
	    relevant.push_back(hit);
	  }
      }
		
  }

  Halfedge_handle locate(const Point& p, Locate_type& lt) const
  {
    // find whether p is on a vertex
    typename Planar_map::Vertex_iterator vit;
    for (vit=pm->vertices_begin(); vit!=pm->vertices_end(); ++vit) 
      {
	if (traits->point_equal(p,vit->point()) ) 
	  {
	    lt = Planar_map::VERTEX; 
	    Halfedge_handle h(vit->incident_halfedges());	
	    return h;
	  }
      }
		
    Halfedges_list relevant_halfedges;
    find_relevant_halfedges(p, relevant_halfedges);

    // find whether p is on a halfedge
    typename Halfedges_list::const_iterator hit;
    for (hit=relevant_halfedges.begin(); hit!=relevant_halfedges.end(); ++hit) 
      {
	if (traits->point_in_x_range((*hit)->curve(),p) &&
	    traits->curve_compare_y_at_x(p, (*hit)->curve()) == EQUAL) 
	  {
	    lt = Planar_map::EDGE; 
	    return *hit;
	  }
      }
		
    lt = Planar_map::UNBOUNDED_FACE;
    Locate_type temp;
    Halfedge_handle h;

    h = vertical_ray_shoot(p, temp, true, relevant_halfedges);
		
    if( temp != Planar_map::UNBOUNDED_FACE ) 
      {
	if (temp == Planar_map::VERTEX) {  
                       //since h points at the vertex and is the first 
	  h=h->twin(); //halfedge after the ray clockwise! then the  face
	               //is to its _right_ (maybe the specs will change in 
	               //the future) 
	}        
			
	if ( !(h->face()->is_unbounded()) ) 
	  lt=Planar_map::FACE;
	return h;
      }
    else //==the vertical ray shoot returned the halfedges_end() iterator.
      {
	if (pm->unbounded_face()->holes_begin() == 
	    pm->unbounded_face()->holes_end() ) //an empty map
	  return h; //return halfedges_end()
	else {
	  //- returns a halfedge on an inner ccb of the unbounded face
	  typename Planar_map::Holes_iterator hot = 
	    pm->unbounded_face()->holes_begin();
	  return (*hot);
	}
      }
  }
	
  Halfedge_handle locate(const Point& p, Locate_type& lt)
  {
    ((Bounding_box*)get_bounding_box())->insert(p);
    Halfedge_handle h=((cPLp)this)->locate(p,lt);
    if (!((Bounding_box*)get_bounding_box())->locate(p,lt,h))
      h=((cPLp)this)->locate(p,lt);
    return h;
  }

  Halfedge_handle vertical_ray_shoot(const Point& p, Locate_type& lt, 
				     bool up) const
  {
    Halfedges_list relevant_halfedges;
    find_relevant_halfedges(p, relevant_halfedges);
    return vertical_ray_shoot(p, lt, up, relevant_halfedges);
  }
	
  Halfedge_handle vertical_ray_shoot(const Point& p, Locate_type& lt, bool up,
				     const Halfedges_list &relevant_halfedges)
  const
  {
		
    typename Planar_map::Halfedge_iterator it, eit, closest_edge;
    bool first = false;
    Comparison_result point_above_under, res;
    Comparison_result curve_above_under;
    bool              in_x_range;
		
    it = pm->halfedges_begin();
    eit = pm->halfedges_end();
    closest_edge = eit;
    lt = Planar_map::EDGE;
		
    // set the flags for comparison acording to the ray 
    // direction (up/down)
    if (up) 
    {
      point_above_under = SMALLER;
      curve_above_under = LARGER;
    } 
    else 
    {
      point_above_under = LARGER;
      curve_above_under = SMALLER;
    }

    typename Halfedges_list::const_iterator rel_it;
    for (rel_it = relevant_halfedges.begin(); 
	 rel_it != relevant_halfedges.end();) 
      {
	it = *rel_it;

	in_x_range = traits->point_in_x_range(it->curve(), p);
	if (in_x_range)
	  res = traits->curve_compare_y_at_x(p, it->curve());

	if (in_x_range && (res == point_above_under)) 
        {
          if (!first) 
          {
            closest_edge = it;
            first = true;
          } 
          else 
          {
            if (traits->curves_compare_y_at_x(closest_edge->curve(),
                                              it->curve(), p) == 
                curve_above_under) 
            {
              closest_edge = it;
            }
          }
        }
	if (in_x_range && res == EQUAL  && 
	    traits->curve_is_vertical(it->curve()))
        {
          // The vertical ray shoot is not including p itself,
          // thus we are interested only in vertical curves that
          // extend upwards
          // In this case the Locate type is always EDGE
          // Remark: This treatment was originally written in the walk PL.
          if (up && 
              traits->point_is_right_top(traits->curve_righttop_most
					 (it->curve()), p) ||
              ! up &&
              traits->point_is_left_low(traits->curve_leftlow_most
					(it->curve()), p))
            /*
              x       x
              |       |
              p=x  or  p
              |
              x
            */
          {
            lt = Planar_map::EDGE;
            if (up==traits->point_is_left_low(it->target()->point(),
                                              it->source()->point()))
              return it;
            else 
              return it->twin();
          }
        }
	++rel_it;
	++rel_it;
      }
		
    // if we didn't find any edge above p then it is the empty face
    if (!first) {
      lt=Planar_map::UNBOUNDED_FACE;
      Halfedge_handle h=pm->halfedges_end();
      return h; //==NULL
    }
    // if the closest point is a vertex then find the first clockwise 
    // edge from the vertical segment
    typename Planar_map::Vertex_handle v = pm->vertices_end();
    bool maybe_vertical=false; // BUG fix (Oren)
    if ( traits->point_equal_x(closest_edge->target()->point(), p) ) 
      {
	v = closest_edge->target();
	maybe_vertical=true; // BUG fix (Oren)
      }
		
    if ( traits->point_equal_x( closest_edge->source()->point(), p) ) 
      {
	if (!maybe_vertical || 
	    traits->point_is_right_top(closest_edge->target()->point(),
				       closest_edge->source()->point())==up) 
                                    // BUG fix (Oren)
	  v = closest_edge->source();
				/*
				  special care for the vertical cases:
				
				  x             p
				  |
				  x     and     x
				  |
				  p             x
				*/
      }
		
		
    //if (closest_is_vertex)
    if (v != pm->vertices_end()) 
      {
	lt=Planar_map::VERTEX;
	if (up)    
	  closest_edge = find_lowest(v,traits, false);  
	else
	  closest_edge = find_lowest(v,traits, true);
      }
		
    Halfedge_handle h;	
    if (lt==Planar_map::VERTEX)
      {
	h=closest_edge;
      }
    else if (up) 
      {
	// return the edge that is going from right to left
	// such that p is to the left of this edge
			
	if ( traits->point_is_right( closest_edge->source()->point(),
				     closest_edge->target()->point()) )
	  {
	    h=closest_edge;  //source is right of the target
	  }
	else
	  h=closest_edge->twin();
      } 
    else 
      {
	if ( traits->point_is_left( closest_edge->source()->point(),
				    closest_edge->target()->point()) )
	  h=closest_edge;
	else
	  h=closest_edge->twin();
      }
    return h;
  }

  Halfedge_handle vertical_ray_shoot(const Point& p, Locate_type& lt, bool up)
  {
    /* Make sure the source point is in the bounding box on the output */
    ((Bounding_box*)get_bounding_box())->insert(p);
    Halfedge_handle h=((cPLp)this)->vertical_ray_shoot(p,lt,up);
    /* Apply the bounding box on the output */
    if (!((Bounding_box*)get_bounding_box())->vertical_ray_shoot(p,lt,up,h))
      {
	h=((cPLp)this)->vertical_ray_shoot(p,lt,up);
	CGAL_assertion(lt!=Planar_map::UNBOUNDED_FACE);
      }
    return h;
  }

  void split_edge(const X_curve &,
		  Halfedge_handle, Halfedge_handle,
		  const X_curve &, const X_curve &) 
  {
  }

  void merge_edge(const X_curve &, const X_curve &,
		  Halfedge_handle,
                  const X_curve &) 
  {
  }

  void remove_edge(Halfedge_handle) 
  {
  }

  void remove_edge(const Halfedge_handle_iterator &,
		   const Halfedge_handle_iterator &) 
  {
  }

  void clear() 
  {
  }

  void update(const Halfedge_handle_iterator &,
	      const Halfedge_handle_iterator &,
	      const Token & token)
  { token.rebuild_bounding_box(this); }

public:
  inline const Bounding_box* get_bounding_box() const 
  {return pm->get_bounding_box();}	
  inline const Traits* get_traits() const {return traits;}
	
protected:
  Halfedge_handle find_lowest(Vertex_handle v,Traits_wrap *traits, 
			      bool highest) const
    //find the first halfedge pointing at v, when going clockwise
    //if highest==true - start from 12 oclock, else start from 6 oclock
  {
		
    Halfedge_handle lowest_left = pm->halfedges_end();
    Halfedge_handle lowest_right = pm->halfedges_end();
    Halfedge_handle vertical_up = pm->halfedges_end();
    Halfedge_handle vertical_down = pm->halfedges_end();
		
		
    typename Planar_map::Halfedge_around_vertex_circulator first = 
      v->incident_halfedges();
    typename Planar_map::Halfedge_around_vertex_circulator curr = first;
		
    do {
      if ( traits->point_is_left(curr->source()->point(), v->point())) 
	{
	  if (lowest_left == pm->halfedges_end())
	    lowest_left = curr;
				
	  if (traits->curves_compare_y_at_x_left(curr->curve(),
					      lowest_left->curve(), 
					      v->point())==SMALLER)
	    lowest_left = curr;
	}
			
      if ( traits->point_is_right(curr->source()->point(), 
				  v->point()) ) 
	{
	  if (lowest_right == pm->halfedges_end())
	    lowest_right = curr;
				
	  if (traits->curves_compare_y_at_x_right(curr->curve(),
					       lowest_right->curve(), 
					       v->point())==LARGER
	      )
	    lowest_right = curr;
	}
			
			
			
      if (traits->curve_is_vertical(curr->curve())) {
	if (traits->compare_xy(v->point(),
			       curr->source()->point())==LARGER)
	  //debug
	  //{ std::cout << "vertical up = " << curr->curve() << std::endl;
					
	  vertical_up=curr; 
				
				//}//enddebug
				
	if (traits->compare_xy(v->point(),
			       curr->source()->point())==SMALLER)
	  //debug
	  //{ std::cout << "vertical down = " << curr->curve() << std::endl;
					
	  vertical_down=curr;
				//}//enddebug
				
      }        
			
    } while (++curr != first);
		
		
    /*
      vertical_down  
      |
      v   <- lowest_right      
                    'v'  
      lowest_left->  ^ 
                     |
                     vertical_up
    */
		
    if (!highest) {
      if (lowest_left!= pm->halfedges_end()) 
	return lowest_left;
      else 
	if (vertical_down!= pm->halfedges_end()) 
	  return vertical_down;
	else
	  return lowest_right;
    }
    else { //down
      if (lowest_right!=pm->halfedges_end()) 
	return lowest_right;
      else 
	if (vertical_up!=pm->halfedges_end()) 
	  return vertical_up;
	else
	  return lowest_left;
    }
		
  }
	
#ifdef CGAL_PM_DEBUG
  void debug(){}
#endif
	
protected:
  typedef const Self* cPLp;
	
protected:
  Planar_map* pm;
  Traits_wrap* traits;
};

CGAL_END_NAMESPACE

#endif //CGAL_PM_NAIVE_POINT_LOCATION_H

