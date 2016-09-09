// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// file          : include/CGAL/Pm_walk_along_line_point_location.h
// package       : pm (4.20)
// source        : 
// revision      : 
// revision_date : 
// author(s)     : Oren Nechushtan
//                 Iddo Hanniel
//
//
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// Chapter       : 
// email         : cgal@cs.uu.nl
//
// ======================================================================
#ifndef CGAL_PM_WALK_ALONG_LINE_POINT_LOCATION_H
#define CGAL_PM_WALK_ALONG_LINE_POINT_LOCATION_H

#ifndef CGAL_PM_POINT_LOCATION_BASE_H
#include <CGAL/Pm_point_location_base.h>
#endif

#ifndef CGAL_PLANAR_MAP_MISC_H
#include <CGAL/Planar_map_2/Planar_map_misc.h>
#endif

#ifdef CGAL_PM_DEBUG
#ifndef CGAL_NAIVE_POINT_LOCATION_H
#include <CGAL/Pm_naive_point_location.h>
#endif
#endif

////////////////////////////////////////////////////////
//    WALK_ALONG_LINE STRATEGY
////////////////////////////////////////////////////////

CGAL_BEGIN_NAMESPACE

template <class Planar_map>
class Pm_walk_along_line_point_location : public Pm_point_location_base<Planar_map> {
public:
  typedef typename Planar_map::Traits_wrap Traits_wrap;
  typedef typename Planar_map::Traits Traits;
  typedef typename Traits_wrap::Point Point;
  typedef typename Traits_wrap::X_curve X_curve;
  typedef typename Traits_wrap::Curve_point_status Curve_point_status;
  typedef typename Planar_map::Locate_type Locate_type;
  typedef typename Planar_map::Vertex_handle Vertex_handle;
  typedef typename Planar_map::Halfedge_handle Halfedge_handle;
  typedef typename Planar_map::Face_handle Face_handle;
  typedef typename Planar_map::Ccb_halfedge_circulator Ccb;
  typedef typename Planar_map::Holes_iterator Holes_iterator;
  typedef typename Planar_map::Halfedge_around_vertex_circulator Avc;
  typedef typename Planar_map::Halfedge_iterator Halfedge_iterator;

protected:
  Planar_map* pm;
  Traits_wrap* traits;

public:

  Pm_walk_along_line_point_location() : 
    Pm_point_location_base<Planar_map>(),
    traits(0) {}
  
  void init(Planar_map& pmp, Traits& tr) {
    pm = &pmp;
    traits = (Traits_wrap*)(&tr);
  }

  void insert(Halfedge_handle h
              //additions by iddo for arrangement
              ,const X_curve& cv
              //end additions
              ) {}

  Halfedge_handle locate(const Point& p, Locate_type& lt);

  Halfedge_handle vertical_ray_shoot(const Point& p, Locate_type& lt, bool up);

  void split_edge(const X_curve &cv,
                  Halfedge_handle e1,
                  Halfedge_handle e2
                  //additions by iddo for arrangement
                  ,const X_curve& cv1, const X_curve& cv2
                  //end additions
                  ) {}

  void merge_edge(const X_curve &cv1,
                  const X_curve &cv2,
                  Halfedge_handle e
                  //additions by iddo for arrangement
                  ,const X_curve& cv
                  //end additions
                  ) {}

  void remove_edge(Halfedge_handle e) {}

private:

  /* Simulates a walk along a vertical ray shoot whose shape is determined by 
     'up' and 'including'.
     e is the returned edge 
  */

  void walk_along_line(const Point& p,bool up,bool including,
		       Halfedge_handle& e,Locate_type& lt) const ;


  /*
    find the first halfedge pointing to p, when going clockwise
    if up==true - start from 6 oclock, else start from 12 oclock
    precondition:    e points to p
    postcondition:   returned value points to p
  */
  Halfedge_handle find_vertex_representation(Halfedge_handle e,const Point& p,
					     bool up) const


//find the first halfedge pointing at v, when going clockwise
//if highest==true - start from 12 oclock, else start from 6 oclock
{

#ifdef CGAL_PM_DEBUG

  CGAL_precondition(traits->point_is_same(e->target()->point(),p));

#endif

  Avc first = e,curr=first;
  ++curr;
  if (up)
    while(curr!=first)
      {
	if (traits->curve_compare_at_x_from_bottom(curr->curve(),e->curve(),p)
	    ==SMALLER) 
	  {
	    e=curr;
	    break;// this can't be improved
	  }
	++curr;
      }
  else
    while(curr!=first)
      {
	if (traits->curve_compare_at_x_from_top(curr->curve(),e->curve(),p)
	    ==SMALLER) 
	  {
	    e=curr;
	    break;// this can't be improved
	  }
	++curr;
      }

#ifdef CGAL_PM_DEBUG

  CGAL_postcondition(e!=pm->halfedges_end());
  CGAL_postcondition(traits->point_is_same(e->target()->point(),p));

#endif

  return e;

}


  /*
    Finds the closest halfedge on a ccb along a vertical ray shoot.
    The bools 'up' and 'including' set the vertical ray shoot's shape.
    The return value is true iff such an halfedge exists.
    Locate type is 
      UNBOUNDED_FACE if point is outside ccb
      FACE if inside
      EDGE of on edge-boundary
      VERTEX if on vertex-boundary.
   */
  bool find_closest(const Point& p,const Ccb& c,
		    bool up,bool including,
		    Halfedge_handle& e,Locate_type& lt) const;

#ifdef CGAL_PM_DEBUG

  void debug() {}

  void debug(const Halfedge_handle& e) const
    {
      {
	if (e!=pm->halfedges_end()) 
	  std::cerr << "(" << e->source()->point() << "," 
		    << e->target()->point() << ")" << std::flush;
	else std::cerr << "(oo)";
      }
    }

#endif

};

///////////////IMPLEMENTATION ////////////////////////////////////////

/*
 Point p -  the source of the vertical ray shoot
 bool up -  true if the ray shoot is upwards, otherwise false (downwards)
 bool including - true if the ray includes its source, false otherwise

 The intersection of the vertical ray shoot is represented using:
 Locate_type lt - the type of the intersection
 Halfedge_handle e - an halfedge representing the intersection depending on
{
 lt == point, ( a vertex in the planar map )
      find the first halfedge pointing at p, when going clockwise if 
      highest==true - start from 12 oclock, else start from 6 oclock 
      DEBUG: highest = up or !up ???
 lt == curve, ( an halfedge in the planar map )
      DEBUG: ?
 lt == face, ( a face in the planar map )
      DEBUG: ?
 lt == unbounded face, ( an unbounded face in the planar map)
      DEBUG: ?
}

*/


template <class Planar_map>
void Pm_walk_along_line_point_location<Planar_map>::walk_along_line(
						 const Point& p,
						 bool up,
						 bool including, 
					      // bool type,
						 Halfedge_handle& e,
						 Locate_type& lt) const 
{
  bool type = including;
  Face_handle f=(type || lt!=Planar_map::VERTEX) ? e->face() : 
    e->twin()->face()    ,last;
  do
    {
      last=f;
      /*
        
          x
         /
        x
        
        p

        A situation where CGAL_assertion(f!=pm->unbounded_face()) doesn't hold.
     */

#ifdef CGAL_PM_WALK_DEBUG

      std::cerr << "\n pre find_closest(" << p << ", , " << up 
		<< "," << including << ",(" << e->source()->point() 
		<< "," << e->target()->point()  << ")," << lt << ");";
#endif

        if (f!=pm->unbounded_face()) 
          {

#ifdef CGAL_PM_DEBUG

      bool found = 

#endif
        
        find_closest(p,f->outer_ccb(),up,including,e,lt);

#ifdef CGAL_PM_DEBUG
      
      CGAL_assertion(found);
      
#endif
          }
      
        f=(type || lt!=Planar_map::VERTEX) ? e->face() : e->twin()->face();
    }
  while((type == (lt==Planar_map::UNBOUNDED_FACE)) && last!=f);
}

template <class Planar_map>
bool Pm_walk_along_line_point_location<Planar_map>::find_closest(
	     const Point& p,
	     const Ccb& c,
	     bool up,bool including, // bool type,
	     Halfedge_handle& e,
	     Locate_type& lt) const
{
  bool type = including; // for possible future implementation
  bool intersection = e!=pm->halfedges_end(); 
  // used to answer is it known that ray shoot intersects curves?
  bool inside = false; // used to calculate if point is inside ccb
  Ccb curr=c;
  do
    {
      const X_curve& cv=curr->curve(),&ecv=e->curve();
      const Point& p1=traits->curve_source(cv),&p2 = traits->curve_target(cv);
      Curve_point_status s = traits->curve_get_point_status(cv, p);
      if ( s == (up ? Traits::UNDER_CURVE : Traits::ABOVE_CURVE)
// && !traits->curve_is_vertical(cv)
	) 
        /* cv is a non vertical curve intersecting the vertical ray shoot 
               x
             / 
           x |     ( for a vertical ray shoot upwards )
             |
             p

        The vertical case is excluded for lexicographically the curve is not intersecting with the ray:

           x        |  x
           |        | /
           x   =>   |x 
           |        |
           p        p
        */

	{
	  if (traits->point_is_left_low(p,p1)!=traits->point_is_left_low(p,p2))
	    {
	      inside = !inside; // count parity of curves intersecting ray in their interior
	    }
	  if (!intersection || 
	      traits->curve_compare_at_x(ecv, cv , p) == (up ? LARGER : SMALLER)
	      )
	    {
              // orient e leftlow
              if ( up == traits->point_is_left_low(
						   curr->target()->point(),
						   curr->source()->point())
		   ) 
                e = curr ;
              else
                e = curr->twin();
              if (!type)
                if (!traits->curve_is_vertical(cv))
                  {
                    if (traits->point_is_same_x(e->source()->point(),p)) 
		      { e=e->twin(); lt=Planar_map::VERTEX;}
                    else if (traits->point_is_same_x(e->target()->point(),p)) 
		      { lt=Planar_map::VERTEX;}
                    else lt=Planar_map::EDGE;
                  }
                else // for p is within e'th x range
                  lt=Planar_map::VERTEX;
              intersection = true;
	    }
	  else if (e!=curr && e!=curr->twin() && 
		   traits->curve_compare_at_x(ecv, cv , p) == EQUAL)
	    /* first intersection point of ray and curve is an end point like

	                   x x
	   x--x---x        |/ 
	      |            x
	      |            |
	      p       or   p

	    */
	    {
	      Point q = traits->curve_source(cv);
	      if (q!=traits->curve_source(ecv) &&
		  q!=traits->curve_target(ecv))
	      q=traits->curve_target(cv);
	      if ((up ? traits->curve_compare_at_x_from_bottom(ecv,cv,q) :
		  traits->curve_compare_at_x_from_top(ecv,cv,q)) == LARGER)
                if (type != (traits->point_is_same(curr->target()->point(),q))) 
                  e = curr;
                else
                  e= curr->twin();
              if (!type) lt=Planar_map::VERTEX; 
	      // lt should be already Planar_map::VERTEX
            }

#ifdef CGAL_PM_DEBUG

	  else
	    {
	      CGAL_assertion(
			 traits->curve_compare_at_x(ecv, cv , p) == 
			 (!up ? LARGER : SMALLER) ||
			 e==curr || e==curr->twin()
	      );
	    }

#endif // CGAL_PM_DEBUG

        }
      else if ( s == Traits::ON_CURVE )
	{
	  if (!including)
	  /* The vertical ray shoot is not including p itself,
	     thus we are interested only in vertical curves that
	     extend upwards
	     Remark:
	     The Locate type is always EDGE
	  */
	    {
	      if (traits->curve_is_vertical(cv) && traits->point_is_higher(traits->curve_highest(cv),p))

		/*
		  x       x
		  |       |
		 p=x  or  p
		          |
			  x
		*/

		{
		  lt = Planar_map::EDGE;
		  if (up==traits->point_is_left_low(curr->target()->point(),curr->source()->point()))
                    e = curr;
                  else 
                    e = curr->twin();

#ifdef CGAL_PM_WALK_DEBUG

                  std::cerr << "\n find_closest(" 
			    << p << ", , " << up << "," << including 
			    << ",(" << "," << e->target()->point() 
			    << ")," << lt << ");";

#endif

		  return true;
		}
	    }
	  else // including
	    {

	      // p is in interior of curr->curve();
	      if ( !traits->point_is_same(p,traits->curve_source(cv)) && 
		   !traits->point_is_same(p,traits->curve_target(cv)))
		{
		  lt = Planar_map::EDGE;
		  if (up==traits->point_is_left_low(curr->target()->point(),curr->source()->point()))
                    e = curr;
                  else 
                    e = curr->twin();
		}
	      else // end point
		{
		  lt = Planar_map::VERTEX;

#ifdef CGAL_PM_DEBUG
		  
		  CGAL_assertion(curr!=pm->halfedges_end());

#endif
                  if (traits->point_is_same(curr->target()->point(),p))
                    e = find_vertex_representation(curr,p,up);	
                  else
                    e = find_vertex_representation(curr->twin(),p,up);

#ifdef CGAL_PM_DEBUG

		  CGAL_assertion(traits->point_is_same(e->target()->point(),p));

#endif

		}

#ifdef CGAL_PM_WALK_DEBUG

              std::cerr << "\n find_closest(" 
			<< p << ", , " << up << "," << including 
			<< ",(" << e->source()->point() 
			<< "," << e->target()->point()  
			<< ")," << lt 
			<< ");";

#endif

	      return true;
	    }
	}
      ++curr;
    }
  while (curr!=c);

  if (!intersection) {
    lt=Planar_map::UNBOUNDED_FACE;
    return false;
  }
  if (type) lt = (inside ? Planar_map::FACE : Planar_map::UNBOUNDED_FACE);

#ifdef CGAL_PM_WALK_DEBUG

  std::cerr << "\n find_closest(" << p << ", , " << up << "," << including 
	    << ",(" << e->source()->point() << "," << e->target()->point()  
	    << ")," << lt << ");";

#endif

  return true;
}

//if unbounded face - returns NULL or some edge on unbounded face 
//if its a vertex returns a halfedge pointing _at_ it
template <class Planar_map>
typename Pm_walk_along_line_point_location<Planar_map>::Halfedge_handle
Pm_walk_along_line_point_location<Planar_map>::locate(
							   const Point& p, 
							   Locate_type& lt)
{
  Face_handle f=pm->unbounded_face(),last=pm->faces_end();  
  // invariant: p always lies in f's interior or holes

  Halfedge_handle e=pm->halfedges_end(); // closest halfedge so far
  lt = Planar_map::UNBOUNDED_FACE;
  while(f!=last) // stop at innermost level
    {
      last = f;
      Holes_iterator it=f->holes_begin(),end=f->holes_end();
      while(it!=end && last==f)     // handle holes
	{
	  if (find_closest(p,*it,true,true,e,lt))
	      	switch (lt)
		{
		case Planar_map::UNBOUNDED_FACE:
		  break;
		case Planar_map::FACE:
		  walk_along_line(p,true,true,e,lt);
		  switch(lt)
		    {
		    case Planar_map::VERTEX:
		      
#ifdef CGAL_PM_DEBUG

		      CGAL_assertion(
				  traits->point_is_same(e->target()->point(),p)
				);

#endif
		      
		    case Planar_map::EDGE:
		      return e;
		    case Planar_map::FACE:
		      f=e->face();
		      break;
		    default:
		      CGAL_assertion(lt==Planar_map::FACE||
				     lt==Planar_map::EDGE||
				     lt==Planar_map::VERTEX);
		      break;
		    }
		  break;
		case Planar_map::VERTEX:
		  
#ifdef CGAL_PM_DEBUG

		      CGAL_assertion(traits->point_is_same(e->target()->point(),p));

#endif
		  
		case Planar_map::EDGE:
		  return e;
		default:
		  CGAL_assertion(lt==Planar_map::UNBOUNDED_FACE||
				 lt==Planar_map::FACE||lt==Planar_map::EDGE||
				 lt==Planar_map::VERTEX);
		}
	  ++it;
	}
    }
  if (lt==Planar_map::UNBOUNDED_FACE && f!=pm->unbounded_face()) 
    lt=Planar_map::FACE;
  if (e==pm->halfedges_end() && pm->number_of_halfedges()>0) 
    //    {
      return Halfedge_handle(*(pm->unbounded_face()->holes_begin()));
  
  return e;
}


template <class Planar_map>
Pm_walk_along_line_point_location<Planar_map>::Halfedge_handle
Pm_walk_along_line_point_location<Planar_map>::vertical_ray_shoot(
							      const Point& p, 
							      Locate_type& lt, 
							      bool up) 
{
  Face_handle f=pm->unbounded_face(),last=pm->faces_end();  
  // p always lies in f's interior
  Halfedge_handle e=pm->halfedges_end(); // closest halfedge so far
  lt = Planar_map::UNBOUNDED_FACE;
  while(f!=last) // stop at innermost level
    {
      last = f;
      Holes_iterator it=f->holes_begin(),end=f->holes_end();
      while(it!=end && last==f)     // handle holes
	{
	  if (find_closest(p,*it,up,false,e,lt))
            {
	      	switch (lt)
		{
                case Planar_map::VERTEX:

#ifdef CGAL_PM_DEBUG

		  CGAL_assertion(
				 type && 
			       traits->point_is_same(e->target()->point(),p)|| 
			        !type && 
			       traits->point_is_same_x(e->target()->point(),p)
				 );
		  
#endif

		case Planar_map::EDGE:

#ifdef CGAL_PM_WALK_DEBUG

                  std::cerr << "\nwalk_along_line(" 
			    << p << "," << up << "," << lt << ")";

#endif

		  walk_along_line(p,up,false,e,lt);
		  switch(lt)
		    {
		    case Planar_map::VERTEX:
		      
#ifdef CGAL_PM_DEBUG

		      CGAL_assertion(
			         traits->point_is_same(e->target()->point(),p)
				 );

#endif
                      f=e->twin()->face();
		      break;
		    case Planar_map::EDGE:

#ifdef CGAL_PM_DEBUG

		      CGAL_assertion(
				     up == traits->point_is_left_low(
					       e->target()->point(),
					       e->source()->point()
					       )
				     );

#endif                      
		    case Planar_map::UNBOUNDED_FACE:
		      break;
		    default:
		      CGAL_assertion(
				     lt==Planar_map::UNBOUNDED_FACE||
				     lt==Planar_map::EDGE||
				     lt==Planar_map::VERTEX
				     );
		      break;
		    }
		  break;
		default:
		  CGAL_assertion(lt==Planar_map::EDGE||lt==Planar_map::VERTEX);
		  break;
		}
            }
	  ++it;
	}
    }
  if (e==pm->halfedges_end()) 
      lt=Planar_map::UNBOUNDED_FACE;
	
  /* symmetric diagrams for downward ray shoot
	  x
	  |\
	  | x
	  p    => VERTEX

	  x
	   \
	   |\  => EDGE
	   | x
	   p

	  x        x
	  |        |
	 p=x   or  p   => EDGE
	           |
		   x

	   x
	   |
	   x
	        => VERTEX
	   p
	*/

  return e;
}
  
CGAL_END_NAMESPACE

#endif //PM_WALK_ALONG_LINE_POINT_LOCATION_H

// DEBUG: shoot downwards









