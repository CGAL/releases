// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium

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
// file          : include/CGAL/Pm_overlay_for_bops.h
// package       : PmOverlay (2.0.6)
// chapter       : $CGAL_Chapter: Basic / Overlay of Planar Maps for Boolean Operations$
// source        : CGAL/progs/ovl/ovl-for-bops1.3/Pm_overlay_for_bops.h
// revision      : $Revision: 2.0.1$
// revision_date : $14 Dec 1998$
// author(s)     : Petru Pau
//
// coordinator   : RISC Linz (Sabine Stifter)
//
// 
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_PM_OVERLAY_H
#define CGAL_PM_OVERLAY_H

#ifndef CGAL_PREDICATES_ON_POINTS_2
#include <CGAL/predicates_on_points_2.h>
#endif

#ifndef SEGMENT_2_SEGMENT_2_INTERSECTION_H
#include <CGAL/Segment_2_Segment_2_intersection.h>
#endif

#ifndef CGAL_PM_BOPS_DEFAULT_DCEL_H
#include <CGAL/Pm_bops_default_dcel.h>
#endif
 
#ifndef CGAL_PLANAR_MAP_2_H
#include <CGAL/Planar_map_2.h>
#endif

#include <list>
#include <set>

CGAL_BEGIN_NAMESPACE
//#define DEBUG_COLLECT_PORTIONS
//#define DEBUG_INSERT_EDGES
//#define DEBUG_COLORIZE


#define Point_for_pm_bops   _Pfpb_
#define Segment_for_pm_bops _Sfpb_
#define Pm_overlay_for_bops _CGAL__Pofb_

/**************************************************************
********* P O I N T   F O R   B O P S   C L A S S *************
*********                                         *************
******** used to store all the intersection points ************
******** of an edge with edges in the other planar ************
******** map                                       ************
**************************************************************/
template<class T>
class Point_for_pm_bops : public T
{
  // If $p$ is a NORMAL point, no color is assigned;
  // If $p$ is a BEGIN_COMMON point, its color is the color of
  //      the left face of the edge from the other planar map;
  // If $p$ is a END_COMMON point, its color is the color of
  //      the right face of the edge from the other planar map.
public:
  enum Point_type 
  {
    NORMAL_POINT = 0, 
    BEGIN_COMMON = 1, 
    END_COMMON   = 2
  };

  Point_for_pm_bops(T t) : T(t) {
      _color = Pm_ovl_NO_COLOR;
      _type  = NORMAL_POINT;
    }

  Point_for_pm_bops(T p, Point_type t, Pm_ovl_color c) : T(p) {
      _color = c;
      _type  = t;
    }

  Point_type type()  const { return _type; }

  Pm_ovl_color      color() const { return _color; }

  void 	     print() const 
    {
      #ifdef CGAL_HOMOGENOUS_H
       cout << hx() << " " << hy() << " " << hw() ;
      #else // CGAL_CARTESIAN_H
       cout << x()  << " " << y();
      #endif
      switch(_type){
      case NORMAL_POINT: cout << ", normal intersection, ";
	break;
      case BEGIN_COMMON: cout << ", begin common segment, ";
	break;
      case END_COMMON: cout << ", end common segment, ";
      }      
      switch(_color){
      case Pm_ovl_NO_COLOR: cout << "NO_COLOR\n"; 		break;
      case Pm_ovl_RED: cout << "RED\n"; 	   		break;
      case Pm_ovl_BLACK:cout << "BLACK\n";	   		break;
      case Pm_ovl_RED_AND_BLACK: cout << "RED AND BLACK\n"; 	break;
      case Pm_ovl_UNCOLORED: cout << "UNCOLORED! Imagine!\n";
      }
    }
      
private:
  Pm_ovl_color _color;
  Point_type  _type;
};

/*
 *  Comparison between points
 */
template <class I>
struct less_or_under: CGAL_STD::binary_function<I,I, bool>{
  bool operator () (const I& p1, 
		    const I& p2) const
  {
    /*
    if (SMALLER == compare_x(p1,p2)) return true;
    if (LARGER  == compare_x(p1,p2)) return false;
    if (SMALLER == compare_y(p1,p2)) return true;
    if (LARGER  == compare_y(p1,p2)) return false;
    */
    if (p1.x() < p2.x()) return true;
    if (p1.x() > p2.x()) return false;
    if (p1.y() < p2.y()) return true;
    if (p1.y() > p2.y()) return false;
    if (I::NORMAL_POINT == p1.type() &&
	I::BEGIN_COMMON == p2.type()) return true;
    if (I::NORMAL_POINT == p2.type() &&
	I::BEGIN_COMMON == p1.type()) return false;
    if (I::NORMAL_POINT == p2.type() &&
	I::END_COMMON   == p1.type()) return true;
    if (I::NORMAL_POINT == p1.type() &&
	I::END_COMMON   == p2.type()) return false;
    if (I::END_COMMON   == p1.type() &&
	I::BEGIN_COMMON == p2.type()) return true;
    if (I::BEGIN_COMMON == p1.type() &&
	I::END_COMMON   == p2.type()) return false;
    return false;
  }
};



/**************************************************************
******** S E G M E N T   F O R   B O P S   C L A S S **********
*********                                          ************
******** used to store all the segments            ************ 
******** that will be inserted in the overlay      ************
**************************************************************/
template<class T>
class Segment_for_pm_bops : public T
{
  Pm_ovl_color _color;
  Pm_ovl_color _lf_color;
  Pm_ovl_color _rf_color;
public:
  Pm_ovl_color get_color() 	const { return _color; }
  Pm_ovl_color get_lf_color() 	const { return _lf_color; }
  Pm_ovl_color get_rf_color() 	const { return _rf_color; }
  Segment_for_pm_bops(T t, 
		      Pm_ovl_color c, 
		      Pm_ovl_color clf, 
		      Pm_ovl_color crf) : T(t), 
                                   _color(c), 
                                   _lf_color(clf), 
                                   _rf_color(crf) { }
  
  ~Segment_for_pm_bops() { }
};

template <class I>
struct before_or_under: CGAL_STD::binary_function<I&,I&,bool>{
  bool operator () (const I& s1, 
		    const I& s2) const
  {
    if (SMALLER == compare_x(s1.source(),s2.source())) return true;
    if (LARGER  == compare_x(s1.source(),s2.source())) return false;
    if (SMALLER == compare_y(s1.source(),s2.source())) return true;
    if (LARGER  == compare_y(s1.source(),s2.source())) return false;
    if (SMALLER == compare_x(s1.target(),s2.target())) return true;
    if (LARGER  == compare_x(s1.target(),s2.target())) return false;
    if (SMALLER == compare_y(s1.target(),s2.target())) return true;
    return false;
  }
};

/********************************************************************
*************** P M   O V E R L A Y   F O R   B O P S ***************
***************                                       ***************
************** Computes the overlay and associates     **************
************** colors to its components                **************
********************************************************************/
template <class Traits>
class Pm_overlay_for_bops /* : public Traits */
{
public:
  typedef Pm_default_dcel<Traits>		Dcel;
  typedef Planar_map_2<Dcel, Traits > Planar_map;

  typedef Pm_bops_default_dcel<Traits>    bDcel;
  typedef Planar_map_2<bDcel,Traits > Planar_map_for_bops;

  typedef bDcel::Info_vertex Info_vertex;
  typedef bDcel::Info_edge Info_edge;
  typedef bDcel::Info_face Info_face;

  typedef Planar_map::Halfedge_iterator 
    Edge_iterator;
  
  typedef typename Traits::X_curve        Segment;
  typedef typename Traits::Point	  Point;

      
  typedef std::set<Segment_for_pm_bops<Segment>, 
                   before_or_under<Segment> > 
    Segment_container;

  typedef std::set<Point_for_pm_bops<Point>, 
                   less_or_under<Point_for_pm_bops<Point> > > 
    Point_container;

  typedef Planar_map_for_bops::Vertex_iterator 
    Bops_vertex_iterator;
  typedef Planar_map_for_bops::Halfedge_iterator 
    Bops_edge_iterator;
  typedef Planar_map_for_bops::Face_iterator 
    Bops_face_iterator;
  typedef Planar_map_for_bops::Holes_iterator 
    Bops_holes_iterator;
  typedef Planar_map_for_bops::Ccb_halfedge_circulator
    Bops_ccb_halfedge_circulator;

  
  Pm_overlay_for_bops(const Planar_map& pm1, 
			   const Planar_map& pm2,
			         Planar_map_for_bops& pm_out)
    {
      Segment_container l_out;

      Collect_edges(pm1, pm2, l_out);
      Insert_edges(l_out, pm_out);

      Colorize(pm_out);

    }


  void Insert_edges(const Segment_container& all_segs, 
		    Planar_map_for_bops& pm)
  {
      Segment_container::const_iterator s_i;
      Planar_map_for_bops::Halfedge_iterator 	 new_edge;
      
      for (s_i=all_segs.begin(); s_i!=all_segs.end(); s_i++){

	new_edge = (Planar_map_for_bops::Halfedge_iterator)
	  pm.insert(Segment((*s_i).source(), (*s_i).target()));
	if ((*new_edge).source()->point() == (*s_i).source()){
	     Info_edge ie;
	     ie.map_color  = (*s_i).get_color() ;
	     ie.edge_color = (*s_i).get_color();
	     ie.left_face_color =  (*s_i).get_lf_color();
	  (*new_edge).set_info(ie);	
	     ie.left_face_color =  (*s_i).get_rf_color();
	  (*new_edge).twin()->set_info(ie);
	}
	else
	  if ((*new_edge).target()->point() == (*s_i).source()){
	     Info_edge ie;
	     ie.map_color  = (*s_i).get_color() ;
	     ie.edge_color = (*s_i).get_color();
	     ie.left_face_color =  (*s_i).get_rf_color();
	  (*new_edge).set_info( ie);	
	     ie.left_face_color =  (*s_i).get_lf_color();
	  (*new_edge).twin()->set_info(ie);
         }
      }
      return;
    }

  void Colorize(Planar_map_for_bops& pm)
    {
      
      std::list<Bops_face_iterator> face_list;

      Bops_face_iterator 	fi;
      Bops_vertex_iterator 	vi;
      
      Info_face this_face_color = Pm_ovl_UNCOLORED;
      Info_edge ie;
      Info_vertex iv;
      
      for(fi=pm.faces_begin(); fi!=pm.faces_end(); ++fi)
	(*fi).set_info(this_face_color);

      this_face_color = Pm_ovl_NO_COLOR;

      for(vi=pm.vertices_begin(); vi!=pm.vertices_end(); ++vi)
	(*vi).set_info(this_face_color);
      
      pm.unbounded_face()->set_info(this_face_color);

      Bops_holes_iterator hi=pm.unbounded_face()->holes_begin();
      if (hi==pm.unbounded_face()->holes_end()) return;

      Bops_ccb_halfedge_circulator 	ccb_i = *hi;
      Bops_edge_iterator		he = (Bops_edge_iterator)(*ccb_i).twin();
      Bops_face_iterator       		f  = (Bops_face_iterator)(*he).face();
      Bops_edge_iterator   		he_next = (Bops_edge_iterator)(*he).next_halfedge();
      Bops_vertex_iterator      	v;
      
      (*f).set_info((*he).info().left_face_color);

      do{
	ie.edge_color     = (Pm_ovl_color)((int)(*he_next).info().edge_color |
					(int)(*he).info().left_face_color);
        ie.map_color      = (*he_next).info().map_color;
        ie.left_face_color= (*he_next).info().left_face_color;  

	(*he_next).set_info(ie);
        ie.left_face_color= (*he_next).twin()->info().left_face_color;
	(*he_next).twin()->set_info(ie);

	v = (Bops_vertex_iterator)(*he_next).source();
	iv = (Pm_ovl_color)((int)ie.edge_color | (int) (*v).info());
	(*v).set_info(iv);
	
	if (!(*he_next).twin()->face()->is_unbounded()){
	  Pm_ovl_color tmp_color = Pm_ovl_NO_COLOR;
	  (*he_next).twin()->face()->set_info(tmp_color);
          face_list.push_back((Bops_face_iterator)(*he_next).twin()->face());
	}
	
	he_next = (*he_next).next_halfedge();
      } while (he_next!=he);
  
      while (face_list.size()>0){
	f = face_list.front();
	face_list.pop_front();

	this_face_color = Pm_ovl_NO_COLOR;
//	f.set_info(this_face_color);

	he = (Bops_edge_iterator)(*f).halfedge_on_outer_ccb();
		
	Bops_edge_iterator he_next = he;

	Pm_ovl_color this_face_color = Pm_ovl_NO_COLOR;
	Pm_ovl_color max_face_color  = Pm_ovl_NO_COLOR;

	bool has_both_colors = false;
	Pm_ovl_color neighbor_to_unbounded = Pm_ovl_NO_COLOR;
	bool twins_face_changed = false;
	bool edge_adjacent_to_unbounded_face 	= false;
	
	// int nr_colors = 0;
	
	Bops_edge_iterator he_neigh;

	#ifdef DEBUG_COLORIZE
	  cout << "Another face\n";
	#endif
 
	do{
	  if ((*he_next).info().left_face_color == Pm_ovl_RED_AND_BLACK){
	    this_face_color = Pm_ovl_RED_AND_BLACK;
	    has_both_colors = true;
	  }
	  else{
	    if ((*he_next).twin()->face()->info() == Pm_ovl_NO_COLOR){
	      this_face_color = (*he_next).info().left_face_color;
	    }
	    else {
	      if ((*he_next).info().left_face_color == Pm_ovl_NO_COLOR){
		he_neigh = he_next;
		edge_adjacent_to_unbounded_face = true;
	      }
	      else {
		if ((*he_next).info().edge_color != (*he_next).info().map_color){
		  if ((*he_next).info().edge_color != (Pm_ovl_color)3)
		    CGAL_kernel_assertion_msg(false, "Modified edge color != 3");
		  this_face_color = (Pm_ovl_color)3;
		  twins_face_changed = true;
		}
	      }
	    }
	  }

	  #ifdef DEBUG_COLORIZE
 	    cout << (*he_next) << " -- " << (int)(*he_next).info().left_face_color << endl;
	  #endif

	  max_face_color = (Pm_ovl_color)((int)(*he_next).info().left_face_color | 
				   (int)max_face_color);
	  he_next = (Bops_edge_iterator)(*he_next).next_halfedge();
	} while (he_next!=he);
	
	
	if (has_both_colors || (max_face_color == Pm_ovl_RED_AND_BLACK)){
	  this_face_color = Pm_ovl_RED_AND_BLACK;
	  (*f).set_info(this_face_color);  
	}
	else
	  if (neighbor_to_unbounded != Pm_ovl_NO_COLOR){
	    (*f).set_info(neighbor_to_unbounded);  
	  }
	  else
	    if (edge_adjacent_to_unbounded_face){
	      if (max_face_color == 3)
		CGAL_kernel_assertion_msg(false, 
		     "Red_and_black face external to a map!");
	      (*f).set_info(max_face_color);
	    }
	  else
	    if (twins_face_changed) {
	      this_face_color = Pm_ovl_RED_AND_BLACK;
	      (*f).set_info(this_face_color);
	    }
	    else
	      (*f).set_info(max_face_color);
	
	do{
	  ie.edge_color     = (Pm_ovl_color)((int)(*he_next).info().edge_color | 
				      (int)(*f).info());
	  ie.map_color      = (*he_next).info().map_color;
	  ie.left_face_color= (*he_next).info().left_face_color; 
	  
	  (*he_next).set_info(ie);

	  ie.left_face_color= (*he_next).twin()->info().left_face_color;
	  (*he_next).twin()->set_info(ie);

	  v = (Bops_vertex_iterator)(*he_next).source();
	  iv = (Pm_ovl_color)((int)ie.edge_color | (int) (*v).info());
	  (*v).set_info(iv);
	  
	  if ((*he_next).twin()->face()->info() == Pm_ovl_UNCOLORED){
	    Pm_ovl_color tmp_color = Pm_ovl_NO_COLOR;
	    (*he_next).twin()->face()->set_info(tmp_color);
	    face_list.push_back((Bops_face_iterator)(*he_next).twin()->face());
	  }
	  
	  he_next = (*he_next).next_halfedge();
          
	} while (he_next!=he);
      }


      return;
    }


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
//            S T A R T I N G    F R O M    H E R E                 //
//    these functions can be replaced with a faster version         //
//             eventually using the fast intersection               //
//                  of a set of segments                            //
//------------------------------------------------------------------//
  void Collect_edges(const Planar_map& pm1,
		     const Planar_map& pm2,
		           Segment_container& all_segs)
    {

      Planar_map::Halfedge_const_iterator e_i;
      Point p1, p2;
      Pm_ovl_color e_color;
      Pm_ovl_color lf_color;
      Pm_ovl_color rf_color;
      
      // Intersect each edge of pm1 with pm2
      for(e_i=pm1.halfedges_begin(); e_i!=pm1.halfedges_end(); ++e_i){
        Point_container o;
	p1 = (*e_i).source()->point();
	p2 = (*e_i).target()->point();

	if (SMALLER == compare_x(p1,p2) ||
            x_equal(p1,p2) &&
            SMALLER == compare_y(p1, p2)) {
	  if ((*e_i).face()->is_unbounded()) 
	    lf_color=Pm_ovl_NO_COLOR;
	  else
	    lf_color=Pm_ovl_RED;
	  if ((*e_i).twin()->face()->is_unbounded()) 
	    rf_color=Pm_ovl_NO_COLOR;
	  else
	    rf_color=Pm_ovl_RED;
	  e_color = Pm_ovl_RED;	  

	  Intersect_segment_planar_map(Segment(p1, p2), Pm_ovl_RED, pm2, o);
	  Collect_portions(p1, p2, e_color, lf_color, rf_color, o, all_segs);
	}
      }
      
      // Intersect each edge of pm2 with pm1
      for(e_i=pm2.halfedges_begin(); e_i!=pm2.halfedges_end(); ++e_i){
        Point_container o;
        p1 = (*e_i).source()->point();
	p2 = (*e_i).target()->point();

	if (SMALLER == compare_x(p1,p2) ||
            x_equal(p1,p2) &&
            SMALLER == compare_y(p1, p2)) {
	  if ((*e_i).face()->is_unbounded()) 
	    lf_color=Pm_ovl_NO_COLOR;
	  else
	    lf_color=Pm_ovl_BLACK;
	  if ((*e_i).twin()->face()->is_unbounded()) 
	    rf_color=Pm_ovl_NO_COLOR;
	  else
	    rf_color=Pm_ovl_BLACK;
	  e_color = Pm_ovl_BLACK;
	  
	  Intersect_segment_planar_map(Segment(p1, p2), Pm_ovl_BLACK, pm1, o);
	  Collect_portions(p1, p2, e_color, lf_color, rf_color, o, all_segs);
	}
     }

     return;
    }
       
  void Intersect_segment_planar_map(const Segment& s, 
				    Pm_ovl_color c,
				    const Planar_map& pm, 
				          Point_container& p_c)
    {
      Planar_map::Halfedge_const_iterator e_i;
      Object o;
      Point p;
      Segment seg;

      for(e_i=pm.halfedges_begin(); e_i!=pm.halfedges_end(); e_i++){
	o=intersection(s, (*e_i).curve());
	if (assign(p, o))
	  p_c.insert(Point_for_pm_bops<Point>(p));
	if (assign(seg,o)){
	  Point p1;
	  Point p2;
	  p1 = seg.source();
	  p2 = seg.target();
	  if (SMALLER == compare_x(p2,p1) ||
	      x_equal(p1,p2) &&
	      SMALLER == compare_y(p2, p1)){
	    Point aux = p1;
	    p1 = p2;
	    p2 = aux;
	  }
	  Pm_ovl_color s_col;
	  if ((*e_i).face()->is_unbounded()) s_col = Pm_ovl_NO_COLOR;
	  else s_col = (Pm_ovl_color)(3-(int)c);
  	  p_c.insert(Point_for_pm_bops<Point>(p1, 
		      Point_for_pm_bops<Point>::BEGIN_COMMON,
		      s_col));

	  if ((*e_i).twin()->face()->is_unbounded()) s_col = Pm_ovl_NO_COLOR;
	  else s_col = (Pm_ovl_color)(3-(int)c);
	  p_c.insert(Point_for_pm_bops<Point>(p2, 
		     Point_for_pm_bops<Point>::END_COMMON,
		     s_col));
	}
      }

      return;
    }
  
  void Collect_portions(const Point& A,
			const Point& B,
			const Pm_ovl_color& c,
			const Pm_ovl_color& lf,
			const Pm_ovl_color& rf,
			      Point_container& o,
			      Segment_container& all_segs)
    {
      Point_container::iterator pc_i;
      Point p1, p2;
      Pm_ovl_color lf_color=lf, 
	    rf_color=rf, 
	    e_color =c;
      
      p1 = A;

      for(pc_i=o.begin(); pc_i!=o.end(); pc_i++)
      {
#ifdef CGAL_CARTESIAN_H
	p2 = Point((*pc_i).x(), (*pc_i).y());
#else
	p2 = Point((*pc_i).hx(), (*pc_i).hy(), (*pc_i).hw());
#endif
	
	if ((*pc_i).type()==Point_for_pm_bops<Point>::NORMAL_POINT){
	  rf_color = rf;
	  lf_color = lf;
	  e_color  = c;
	}
	if ((*pc_i).type()==Point_for_pm_bops<Point>::END_COMMON){
	  rf_color = (Pm_ovl_color)((int)rf_color+(int)(*pc_i).color());
	}
	if (p1 != p2) 
        {
          all_segs.insert(Segment_for_pm_bops<Segment>(Segment(p1, p2),
						       e_color, 
						       lf_color, 
						       rf_color));
	}
	if ((*pc_i).type()==Point_for_pm_bops<Point>::BEGIN_COMMON){
	  lf_color = (Pm_ovl_color)((int)(*pc_i).color()+(int)lf_color);
	  e_color  = (Pm_ovl_color)3;
	}
	p1 = p2;
	
      }

      p2 = B;
      
      rf_color = rf;
      lf_color = lf;
      e_color  = c;
      if (p1 != p2) 
      {
        all_segs.insert(Segment_for_pm_bops<Segment>(Segment(p1, p2),   
						    c, lf, rf));
        p1 = p2;
      }
      return;
    }  
}; 
CGAL_END_NAMESPACE
#endif

