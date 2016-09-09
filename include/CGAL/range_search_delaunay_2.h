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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/range_search_delaunay_2.h
// package       : Point_set_2 (2.3.2)
// revision      : 2.3.2
// revision_date : 11 April 2002 
// author(s)     : Matthias Baesken
//
// coordinator   : Matthias Baesken, Trier  (<baesken>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_RANGE_SEARCH_DELAUNAY_2_H
#define CGAL_RANGE_SEARCH_DELAUNAY_2_H

#include <CGAL/basic.h>
#include <CGAL/Unique_hash_map.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/nearest_neighbor_delaunay_2.h>
#include <list>
#include <queue>
#include <map>
#include <stack>
#include <cmath>

CGAL_BEGIN_NAMESPACE

// was 
// std::map<typename Dt::Vertex *,int, std::less<typename Dt::Vertex *> >

template<class Dt,class Circle,class OutputIterator,class MAP_TYPE>
void dfs(const Dt& delau, 
         MAP_TYPE& mark, 
         typename Dt::Vertex_handle v, 
	 const Circle& C, 
	 OutputIterator res,
	 bool first_vertex)
{
    typedef typename Dt::Geom_traits               Gt;
    typedef typename Dt::Vertex                    Vertex;
    typedef typename Dt::Vertex_circulator         Vertex_circulator;
    typedef typename Dt::Vertex_handle             Vertex_handle;
    typedef typename Gt::Bounded_side_2            Bounded_side_2;

    Bounded_side_2  test;
    
    if (! first_vertex) *res = v;
    
    //mark_vertex v
    mark[v] = true;
    
    // get incident vertices of v ...
    Vertex_circulator vc = delau.incident_vertices(v);
    Vertex_circulator start =vc;
     
    Vertex_handle act;
     
    // go through the vertices ...
    do {
       act = vc->handle();
 
       if (! delau.is_infinite(act)) {
	 // test, if act is marked ...
         bool is_marked = mark[act];     
       
         if ((! is_marked) && !( test(C,act->point()) == ON_UNBOUNDED_SIDE) ) 
           dfs(delau, mark, act, C, res, false);       
       }             
       vc++;
    } while (vc != start);     
}


// second dfs uses test - predicate function object ...

template<class Dt,class Circle,class OutputIterator,class MAP_TYPE,class Pred>
bool dfs(const Dt& delau, 
         MAP_TYPE& mark, 
         typename Dt::Vertex_handle v, 
	 const Circle& C, 
	 OutputIterator res,
	 bool first_vertex,
	 bool return_if_predicate_succeded,
	 Pred& pred)
{
    typedef typename Dt::Geom_traits               Gt;
    typedef typename Dt::Vertex                    Vertex;
    typedef typename Dt::Vertex_circulator         Vertex_circulator;
    typedef typename Dt::Vertex_handle             Vertex_handle;
    typedef typename Gt::Bounded_side_2            Bounded_side_2;

    Bounded_side_2  test;
    
    if (! first_vertex) {
      if (pred(v->point())) {
         *res = v;
	 
	 if (return_if_predicate_succeded) return true;
      }
    }
    
    //mark_vertex v
    mark[v] = true;
    
    // get incident vertices of v ...
    Vertex_circulator vc = delau.incident_vertices(v);
    Vertex_circulator start =vc;
     
    Vertex_handle act;
     
    // go through the vertices ...
    do {
       act = vc->handle();
 
       if (! delau.is_infinite(act)) {
	 // test, if act is marked ...
         bool is_marked = mark[act];    
       
         if ((! is_marked) && !( test(C,act->point()) == ON_UNBOUNDED_SIDE) ) 
           if (dfs(delau, mark, act, C, res, false, return_if_predicate_succeded, pred)) return true;       
       }             
       vc++;
    } while (vc != start);   
    
    return false;  
}


template<class Dt,class Circle,class OutputIterator,class MAP_TYPE,class Pred>
void dfs_using_predicate(const Dt& delau, 
         MAP_TYPE& mark, 
         typename Dt::Vertex_handle v, 
	 const Circle& C, 
	 OutputIterator res,
	 bool first_vertex,
	 bool return_if_predicate_succeded,
	 Pred& pred)
{
  bool val = dfs(delau, mark, v, C, res, first_vertex, return_if_predicate_succeded, pred);
  pred.set_result(val);
}

// circular range search ...


template<class Dt, class Circle, class OutputIterator>
OutputIterator range_search(Dt& delau, 
                            const Circle& C, 
			    OutputIterator res)
{ 
  typedef typename Dt::Geom_traits                    Gt;
  typedef typename Dt::Point                          Point;
  typedef typename Dt::Vertex_handle                  Vertex_handle;
  typedef typename Dt::Vertex                         Vertex;
  typedef typename Dt::Vertex_iterator                Vertex_iterator;
  typedef typename Gt::Bounded_side_2                 Bounded_side_2;
  typedef typename Gt::Construct_center_2             Construct_center_2;

  Bounded_side_2  test;

  if (delau.number_of_vertices() == 0) return res;
  if (delau.number_of_vertices() == 1) 
  { 
       // get the one vertex ...
       Vertex_iterator vit = delau.finite_vertices_begin();
       Vertex v = (*vit);
       Point p = v.point();
       
       if (! (test(C, p) == ON_UNBOUNDED_SIDE)){
        *res= v.handle(); res++;
       }
       return res;
   }  
     
   // normal case ...
   Point p = Construct_center_2()(C);
   Vertex_handle v = lookup(delau, p);  
   bool new_v = false;     

   // we have to insert the center ...
   if ( v == NULL )
   { 
       new_v = true;
       v = delau.insert(p); 
   }
     
   //std::map<Vertex*,int, std::less<Vertex*> > mark;
   Unique_hash_map<Vertex_handle, bool> mark;
     
   dfs(delau,mark,v,C,res,new_v);
     
   if (new_v)
   { 
     delau.remove(v);
   }    
   
   return res;        
}
   
   
// triangular range search ...   

template<class Dt, class OutputIterator>
OutputIterator range_search(Dt& delau, 
                            const typename Dt::Point& a, 
			    const typename Dt::Point& b, 
                            const typename Dt::Point& c,
			    OutputIterator res)
{
  typedef typename Dt::Geom_traits                    Gt;
  typedef typename Dt::Point                          Point;
  typedef typename Gt::Circle_2                       Circle;
  typedef typename Dt::Vertex_handle                  Vertex_handle;
  typedef typename Gt::Orientation_2                  Orientation_2;
  typedef typename Gt::Construct_circle_2             Construct_circle_2;
  
  Orientation_2 test_ori;
   
  int orient = (int)(test_ori(a,b,c));
  Circle C = Construct_circle_2()(a,b,c);
  std::list<Vertex_handle> L;
  range_search(delau, C, std::back_inserter(L));
      
  typename std::list<Vertex_handle>::const_iterator it = L.begin();
      
  for(;it != L.end();it++)
  { Point p = (*it)->point();
    if ( ((int)(test_ori(a,b,p))) == - orient ||
         ((int)(test_ori(b,c,p))) == - orient ||
         ((int)(test_ori(c,a,p))) == - orient ) { }     
    else { *res = *it; res++; }
  }
  return res;     
}


// rectangular range search ....

template<class Dt,class OutputIterator>
OutputIterator range_search(Dt& delau, 
                            const typename Dt::Point& a1, 
			    const typename Dt::Point& b1, 
                            const typename Dt::Point& c1,
			    const typename Dt::Point& d1,
			    OutputIterator res)
// a1 upper left, b1 lower left , c1 lower right
{
  typedef typename Dt::Geom_traits                    Gt;
  typedef typename Dt::Point                          Point;
  typedef typename Gt::Circle_2                       Circle;
  typedef typename Dt::Vertex_handle                  Vertex_handle;
  typedef typename Gt::Orientation_2                  Orientation_2;
  typedef typename Gt::Construct_circle_2             Construct_circle_2;
  
  Point a=a1,b=b1,c=c1,d=d1;
    
  if (Orientation_2()(a,b,c) == RIGHTTURN) 
  { Point tmp = b;
    b = d;
    d = tmp;
  }
   
  Circle C = Construct_circle_2()(a,b,c);
     
  std::list<Vertex_handle> L;
  range_search(delau, C, std::back_inserter(L));
  typename std::list<Vertex_handle>::const_iterator it = L.begin();     

  for(;it != L.end();it++)
  { Point p = (*it)->point();
    if ( Orientation_2()(a,b,p) == RIGHTTURN || Orientation_2()(b,c,p) == RIGHTTURN ||
         Orientation_2()(c,d,p) == RIGHTTURN || Orientation_2()(d,a,p) == RIGHTTURN )  { }
    else { *res = *it; res++; }
  }
  return res;     
}


// ------------------------------------------------------------------------------------------------
// new range search variants using test function object ...

// circular range search ...


template<class Dt, class Circle, class OutputIterator,class Pred>
OutputIterator range_search(Dt& delau, 
                            const Circle& C, 
			    OutputIterator res,
			    Pred& pred,
			    bool return_if_succeded)
{ 
  typedef typename Dt::Geom_traits                    Gt;
  typedef typename Dt::Point                          Point;
  typedef typename Dt::Vertex_handle                  Vertex_handle;
  typedef typename Dt::Vertex                         Vertex;
  typedef typename Dt::Vertex_iterator                Vertex_iterator;
  typedef typename Gt::Bounded_side_2                 Bounded_side_2;
  typedef typename Gt::Construct_center_2             Construct_center_2;

  Bounded_side_2  test;

  if (delau.number_of_vertices() == 0) return res;
  if (delau.number_of_vertices() == 1) 
  { 
       // get the one vertex ...
       Vertex_iterator vit = delau.finite_vertices_begin();
       Vertex v = (*vit);
       Point p = v.point();
       
       if (! (test(C, p) == ON_UNBOUNDED_SIDE)){
        *res= v.handle(); res++;
       }
       
       bool val = pred(p);
       pred.set_result(val);
       
       return res;
   }  
     
   // normal case ...
   Point p = Construct_center_2()(C);
   Vertex_handle v = lookup(delau, p);  
   bool new_v = false;     

   // we have to insert the center ...
   if ( v == NULL )
   { 
       new_v = true;
       v = delau.insert(p); 
   }
     
   //std::map<Vertex*,int, std::less<Vertex*> > mark;
   Unique_hash_map<Vertex_handle, bool> mark;
   
   dfs_using_predicate(delau,mark,v,C,res,new_v, return_if_succeded, pred);
     
   if (new_v)
   { 
     delau.remove(v);
   }    
   
   return res;        
}
   
   
// triangular range search ...   

template<class Dt, class OutputIterator,class Pred>
OutputIterator range_search(Dt& delau, 
                            const typename Dt::Point& a, 
			    const typename Dt::Point& b, 
                            const typename Dt::Point& c,
			    OutputIterator res,
			    Pred& pred,
			    bool return_if_succeded)			    
{
  typedef typename Dt::Geom_traits                    Gt;
  typedef typename Dt::Point                          Point;
  typedef typename Gt::Circle_2                       Circle;
  typedef typename Dt::Vertex_handle                  Vertex_handle;
  typedef typename Gt::Orientation_2                  Orientation_2;
  typedef typename Gt::Construct_circle_2             Construct_circle_2;
  
  Orientation_2 test_ori;
   
  int orient = (int)(test_ori(a,b,c));
  Circle C = Construct_circle_2()(a,b,c);
  std::list<Vertex_handle> L;
  
  range_search(delau, C, std::back_inserter(L), pred, return_if_succeded);
  if (return_if_succeded) return res;
      
  typename std::list<Vertex_handle>::const_iterator it = L.begin();
      
  for(;it != L.end();it++)
  { Point p = (*it)->point();
    if ( ((int)(test_ori(a,b,p))) == - orient ||
         ((int)(test_ori(b,c,p))) == - orient ||
         ((int)(test_ori(c,a,p))) == - orient ) { }     
    else { *res = *it; res++; }
  }
  return res;     
}


// rectangular range search ....

template<class Dt,class OutputIterator,class Pred>
OutputIterator range_search(Dt& delau, 
                            const typename Dt::Point& a1, 
			    const typename Dt::Point& b1, 
                            const typename Dt::Point& c1,
			    const typename Dt::Point& d1,
			    OutputIterator res,
			    Pred& pred,
			    bool return_if_succeded)
// a1 upper left, b1 lower left , c1 lower right
{
  typedef typename Dt::Geom_traits                    Gt;
  typedef typename Dt::Point                          Point;
  typedef typename Gt::Circle_2                       Circle;
  typedef typename Dt::Vertex_handle                  Vertex_handle;
  typedef typename Gt::Orientation_2                  Orientation_2;
  typedef typename Gt::Construct_circle_2             Construct_circle_2;
  
  Point a=a1,b=b1,c=c1,d=d1;
    
  if (Orientation_2()(a,b,c) == RIGHTTURN) 
  { Point tmp = b;
    b = d;
    d = tmp;
  }
   
  Circle C = Construct_circle_2()(a,b,c);
     
  std::list<Vertex_handle> L;
  
  range_search(delau, C, std::back_inserter(L), pred, return_if_succeded);
  if (return_if_succeded) return res;
  
  
  typename std::list<Vertex_handle>::const_iterator it = L.begin();     

  for(;it != L.end();it++)
  { Point p = (*it)->point();
    if ( Orientation_2()(a,b,p) == RIGHTTURN || Orientation_2()(b,c,p) == RIGHTTURN ||
         Orientation_2()(c,d,p) == RIGHTTURN || Orientation_2()(d,a,p) == RIGHTTURN )  { }
    else { *res = *it; res++; }
  }
  return res;     
}



CGAL_END_NAMESPACE

#endif
