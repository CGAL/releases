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
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/Delaunay_triangulation_2.h
// package       : Triangulation (4.69)
// source        : $RCSfile: Delaunay_triangulation_2.h,v $
// revision      : $Revision: 1.34 $
// revision_date : $Date: 2000/09/01 11:43:30 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================



#ifndef CGAL_DELAUNAY_TRIANGULATION_2_H
#define CGAL_DELAUNAY_TRIANGULATION_2_H

#include <CGAL/Triangulation_2.h>

CGAL_BEGIN_NAMESPACE

template < class Gt, class Tds>
class Delaunay_triangulation_2 : public Triangulation_2<Gt,Tds>
{
public:
  typedef Gt Geom_traits;
  typedef typename Geom_traits::Point_2       Point;
  typedef typename Geom_traits::Segment_2     Segment;
  typedef typename Geom_traits::Triangle_2    Triangle;
  

  typedef typename Geom_traits::Orientation_2 Orientation_2;
  typedef typename Geom_traits::Compare_x_2   Compare_x;
  typedef typename Geom_traits::Compare_y_2   Compare_y;
  typedef typename Geom_traits::Side_of_oriented_circle_2 
                                              Side_of_oriented_circle;

  
  typedef Triangulation_2<Gt,Tds>                       Triangulation;
  typedef typename Triangulation::Locate_type           Locate_type;
  typedef typename Triangulation::Face_handle           Face_handle;
  typedef typename Triangulation::Vertex_handle         Vertex_handle;
  typedef typename Triangulation::Edge                  Edge;
  typedef typename Triangulation::Edge_circulator       Edge_circulator;
  typedef typename Triangulation::Finite_edges_iterator Finite_edges_iterator;
  typedef typename Triangulation::Finite_faces_iterator Finite_faces_iterator;
  typedef typename Triangulation::Finite_vertices_iterator 
                                                     Finite_vertices_iterator;

  Delaunay_triangulation_2(const Gt& gt = Gt())
  : Triangulation_2<Gt,Tds>(gt) {}
  
  Delaunay_triangulation_2(
	       const Delaunay_triangulation_2<Gt,Tds> &tr)
      : Triangulation_2<Gt,Tds>(tr)
  {   CGAL_triangulation_postcondition( is_valid() );  }
  
// CHECK -QUERY
  bool is_valid(bool verbose = false, int level = 0) const;

  Vertex_handle
  nearest_vertex(const Point& p, Face_handle f= Face_handle()) const;
  
  bool does_conflict(const Point  &p, Face_handle fh) const;
  bool find_conflicts(const Point  &p, 
		      std::list<Face_handle>& conflicts,
		      Face_handle start = Face_handle()) const;
 
  // DUAL
  Point dual (Face_handle f) const;
  Object dual(const Edge &e) const ;
  Object dual(const Edge_circulator& ec) const;
  Object dual(const Finite_edges_iterator& ei) const;
  Point circumcenter(const Point& p0, 
		     const Point& p1, 
		     const Point&   p2) const;
  
  //INSERTION-REMOVAL
  Vertex_handle  insert(const Point  &p, Face_handle start = Face_handle() );
  Vertex_handle insert(const Point& p,
		       Locate_type lt,
		       Face_handle loc, int li );
  Vertex_handle push_back(const Point &p);

  void  remove(Vertex_handle v );
  
  
private:
  void restore_Delaunay(Vertex_handle v);
  void propagating_flip(Face_handle& f,int i);
  void remove_2D(Vertex_handle v );

  Vertex_handle nearest_vertex_2D(const Point& p, Face_handle f) const;
  Vertex_handle nearest_vertex_1D(const Point& p) const;

  void  look_nearest_neighbor(const Point& p,
			      Face_handle f,
			      int i,
			      Vertex_handle& nn) const;

  void propagate_conflicts(const Point &p, 
			   Face_handle fh, 
			   int i,
			   std::list<Face_handle>& conflicts) const;

public:
  template < class Stream>
  Stream& draw_dual(Stream & ps)
    {
      Finite_edges_iterator eit= finite_edges_begin();
      for (; eit != finite_edges_end(); ++eit) {
	Object o = dual(eit);
	typename Geom_traits::Line_2  l;
	typename Geom_traits::Ray_2   r;
	Segment s;
	if (CGAL::assign(s,o)) ps << s;
	if (CGAL::assign(r,o)) ps << r;
	if (CGAL::assign(l,o)) ps << l;
      }
      return ps;
    }

  template < class InputIterator >
  int
  insert(InputIterator first, InputIterator last)
    {
      int n = number_of_vertices();
      while(first != last){
	insert(*first);
	++first;
      }
      return number_of_vertices() - n;
    }

};

template < class Gt, class Tds >
inline bool
Delaunay_triangulation_2<Gt,Tds>::
does_conflict(const Point  &p, Face_handle fh) const
{
  return (side_of_oriented_circle(fh,p) == ON_POSITIVE_SIDE);
}

template < class Gt, class Tds >
bool
Delaunay_triangulation_2<Gt,Tds>::
find_conflicts(const Point  &p, 
	       std::list<Face_handle>& conflicts,
	       Face_handle start)  const
{
  int li;
  Locate_type lt;
  Face_handle fh = locate(p,lt,li, start);
  switch(lt) {
  case OUTSIDE_AFFINE_HULL:
  case VERTEX:
    return false;
  case FACE:
  case EDGE:
  case OUTSIDE_CONVEX_HULL:
    conflicts.push_back(fh);
    propagate_conflicts(p,fh,0,conflicts);
    propagate_conflicts(p,fh,1,conflicts);
    propagate_conflicts(p,fh,2,conflicts);
    return true;    
  }
  CGAL_triangulation_assertion(false);
  return false;
}

template < class Gt, class Tds >
void 
Delaunay_triangulation_2<Gt,Tds>::
propagate_conflicts(const Point &p, 
		    Face_handle fh, 
		    int i,
		    std::list<Face_handle>& conflicts) const
{
  Face_handle fn = fh->neighbor(i);
  if (! does_conflict(p,fn)) return;
  conflicts.push_back(fn);
  int j = fn->index(fh);
  propagate_conflicts(p,fn,cw(j),conflicts);
  propagate_conflicts(p,fn,ccw(j),conflicts);
  return;
}

template < class Gt, class Tds >
bool
Delaunay_triangulation_2<Gt,Tds>::
is_valid(bool verbose, int level) const
{
  bool result = Triangulation_2<Gt,Tds>::is_valid(verbose, level);

  for( Finite_faces_iterator it = finite_faces_begin(); 
       it != finite_faces_end() ; it++) {
    for(int i=0; i<3; i++) {
      if ( ! is_infinite( it->mirror_vertex(i))) {
	result = result &&  ON_POSITIVE_SIDE != 
	  side_of_oriented_circle( it, it->mirror_vertex(i)->point());
      }
      CGAL_triangulation_assertion( result );
    }
  }
  return result;
}

template < class Gt, class Tds >
Delaunay_triangulation_2<Gt,Tds>::Vertex_handle
Delaunay_triangulation_2<Gt,Tds>:: 
nearest_vertex(const Point  &p, Face_handle f) const
{
  switch (dimension()) {
  case 0:
    if (number_of_vertices() == 0) return NULL;
    if (number_of_vertices() == 1) return finite_vertex();
    //break;
  case 1:
    return nearest_vertex_1D(p);
    //break;      
  case 2:
    return nearest_vertex_2D(p,f);
    //break;
  }
  return NULL;
}
  
template < class Gt, class Tds >
Delaunay_triangulation_2<Gt,Tds>::Vertex_handle
Delaunay_triangulation_2<Gt,Tds>:: 
nearest_vertex_2D(const Point& p, Face_handle f) const
{
  CGAL_triangulation_precondition(dimension() == 2);
    if (f== Face_handle()) f = locate(p);
  else
    CGAL_triangulation_precondition(oriented_side(f,p)!=ON_NEGATIVE_SIDE);

  typename Geom_traits::Less_distance_to_point_2 
    closer = geom_traits().less_distance_to_point_2_object(p);
  Vertex_handle nn =  !is_infinite(f->vertex(0)) ? f->vertex(0):f->vertex(1);
  if ( !is_infinite(f->vertex(1))  && 
       closer(f->vertex(1)->point(), nn->point())) nn=f->vertex(1);
  if ( !is_infinite(f->vertex(2))  &&
       closer(f->vertex(2)->point(), nn->point())) nn=f->vertex(2);
 
  look_nearest_neighbor(p,f,0,nn);
  look_nearest_neighbor(p,f,1,nn);
  look_nearest_neighbor(p,f,2,nn);
  return nn;
}

template < class Gt, class Tds >
Delaunay_triangulation_2<Gt,Tds>::Vertex_handle
Delaunay_triangulation_2<Gt,Tds>:: 
nearest_vertex_1D(const Point& p) const
{
  typename Geom_traits::Less_distance_to_point_2 
    closer=geom_traits().less_distance_to_point_2_object(p);
  
  Vertex_handle nn;
  
  Finite_vertices_iterator vit=finite_vertices_begin();
  nn = vit->handle();
  for ( ; vit != finite_vertices_end(); ++vit){
    if (closer(vit->point(), nn->point()) ) nn=vit->handle();
  } 
  return nn;
}
  
template < class Gt, class Tds >
void
Delaunay_triangulation_2<Gt,Tds>::
look_nearest_neighbor(const Point& p,
                      Face_handle f,
		      int i,
		      Vertex_handle& nn) const
{
  Face_handle  ni=f->neighbor(i);
  if ( ON_POSITIVE_SIDE != side_of_oriented_circle(ni,p) ) return;

  typename Geom_traits::Less_distance_to_point_2 
    closer=geom_traits().less_distance_to_point_2_object(p);
  i = ni->index(f);
  if ( !is_infinite(ni->vertex(i)) &&
       closer(ni->vertex(i)->point(), nn->point()) )  nn=ni->vertex(i);
    
  // recursive exploration of triangles whose circumcircle contains p
  look_nearest_neighbor(p, ni, ccw(i), nn);
  look_nearest_neighbor(p, ni, cw(i), nn);
} 

//DUALITY
template<class Gt, class Tds>
inline
Delaunay_triangulation_2<Gt,Tds>::Point
Delaunay_triangulation_2<Gt,Tds>::
dual (Face_handle f) const
{
  CGAL_triangulation_precondition (dimension()==2);
  return circumcenter(f->vertex(0)->point(),
		      f->vertex(1)->point(),
		      f->vertex(2)->point());
}

template<class Gt, class Tds>
inline
Delaunay_triangulation_2<Gt,Tds>::Point
Delaunay_triangulation_2<Gt,Tds>::
circumcenter (const Point& p0, const Point& p1, const Point&  p2) const
{
  return 
    geom_traits().construct_circumcenter_2_object()(p0,p1,p2);
}

  
template < class Gt, class Tds >
Object
Delaunay_triangulation_2<Gt,Tds>::
dual(const Edge &e) const
{
  typedef typename Geom_traits::Line_2        Line;
  typedef typename Geom_traits::Ray_2         Ray;
  typedef typename Geom_traits::Direction_2   Direction;

  CGAL_triangulation_precondition (!is_infinite(e));
  if( dimension()== 1 ){
    Point p = (e.first)->vertex(cw(e.second))->point();
    Point q = (e.first)->vertex(ccw(e.second))->point();
    Line l  = geom_traits().construct_bisector_2_object()(p,q);
    return Object(new Wrapper< Line >(l));
  }
		    
  // dimension==2
  if( (!is_infinite(e.first)) &&
      (!is_infinite(e.first->neighbor(e.second))) ) {
    Segment s = geom_traits().construct_segment_2_object()
                          (dual(e.first),dual(e.first->neighbor(e.second)));
    return Object(new Wrapper< Segment >(s));
  } 
  // one of the adjacent face is infinite
  Face_handle f; int i;
  if (is_infinite(e.first)) {
    f=e.first->neighbor(e.second); f->has_neighbor(e.first,i);
  } 
  else {
    f=e.first; i=e.second;
  }
  Point p = f->vertex(cw(i))->point();
  Point q = f->vertex(ccw(i))->point();
  Line l = geom_traits().construct_bisector_2_object()(p,q);
  Direction d = geom_traits().construct_direction_of_line_2_object()(l);
  Ray r = geom_traits().construct_ray_2_object()(dual(f), d);
  return Object(new Wrapper< Ray >(r));
}
  
template < class Gt, class Tds >
inline Object
Delaunay_triangulation_2<Gt,Tds>::  
dual(const Edge_circulator& ec) const
{
  return dual(*ec);
}
  
template < class Gt, class Tds >
inline Object
Delaunay_triangulation_2<Gt,Tds>::
dual(const Finite_edges_iterator& ei) const
{
  return dual(*ei);
}
  
template < class Gt, class Tds >
inline
Delaunay_triangulation_2<Gt,Tds>::Vertex_handle
Delaunay_triangulation_2<Gt,Tds>::
insert(const Point  &p,  Face_handle start)
{
  Locate_type lt;
  int li;
  Face_handle loc = locate (p, lt, li, start);
  return insert(p, lt, loc, li);
}
  
template < class Gt, class Tds >
inline
Delaunay_triangulation_2<Gt,Tds>::Vertex_handle
Delaunay_triangulation_2<Gt,Tds>::
push_back(const Point &p)
{
  return insert(p);
}
  
template < class Gt, class Tds >
inline
Delaunay_triangulation_2<Gt,Tds>::Vertex_handle
Delaunay_triangulation_2<Gt,Tds>::
insert(const Point  &p, Locate_type lt, Face_handle loc, int li)
{
  Vertex_handle v = Triangulation_2<Gt,Tds>::insert(p,lt,loc,li);
  restore_Delaunay(v);
  return(v);
}


template < class Gt, class Tds >
void
Delaunay_triangulation_2<Gt,Tds>::
restore_Delaunay(Vertex_handle v)
{
  if(dimension() <= 1) return;

  Face_handle f=v->face();
  Face_handle next;
  int i;
  Face_handle start(f);
  do {
    i = f->index(v);
    next = f->neighbor(ccw(i));  // turn ccw around v
    propagating_flip(f,i);
    f=next;
  } while(next != start);
  return;
}

template < class Gt, class Tds >
void
Delaunay_triangulation_2<Gt,Tds>::
remove(Vertex_handle v )
{
  CGAL_triangulation_precondition( v != Vertex_handle());
  CGAL_triangulation_precondition( !is_infinite(v));
        
  if ( dimension() <= 1) Triangulation::remove(v);
  else  remove_2D(v);
        
  return;
}

template < class Gt, class Tds >
void
Delaunay_triangulation_2<Gt,Tds>::
propagating_flip(Face_handle& f,int i)
{
  Face_handle n = f->neighbor(i);
      
  if ( ON_POSITIVE_SIDE != 
       side_of_oriented_circle(n,  f->vertex(i)->point()) ) {          
    return;
  }
  flip(f, i);
  propagating_flip(f,i);
  i = n->index(f->vertex(i));
  propagating_flip(n,i);
}

template <class Gt, class Tds >
void
Delaunay_triangulation_2<Gt,Tds>::
remove_2D(Vertex_handle v)
{
  if (test_dim_down(v)) {  _tds.remove_dim_down(&(*v));  }
  else {
    std::list<Edge> hole;
    make_hole(v, hole);
    fill_hole_delaunay(hole);
    delete &(*v);
    set_number_of_vertices(number_of_vertices()-1);
  }
  return;       
}



CGAL_END_NAMESPACE

#endif // CGAL_DELAUNAY_TRIANGULATION_2_H
