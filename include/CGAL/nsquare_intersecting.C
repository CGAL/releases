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
// file          : include/CGAL/nsquare_intersecting.C
// package       : bops (2.4)
// source        : include/CGAL/nsquare_intersecting.C
// revision      : $Revision: 1.1.1.1 $
// revision_date : $Date: 1999/10/11 13:50:32 $
// author(s)     : Carl Van Geem
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
// email         : cgal@cs.uu.nl
//
// ======================================================================

CGAL_BEGIN_NAMESPACE

template < class R > 
Intersectionresult<R>::Intersectionresult() 
      {   
        _is_vertex_of_poly1 = false;
        _is_vertex_of_poly2 = false;
        _is_edge_of_poly1 = false;
        _is_edge_of_poly2 = false;
        _is_vertex_vertex_intersection = false;
        _is_vertex_edge_intersection = false;
        _is_edge_edge_intersection = false;
      }

template < class R > 
Intersectionresult<R>::Intersectionresult (const 
                                        Intersectionresult<R> &ires )
     {  
       _intersection_object = ires._intersection_object;
       _segments_poly1 = ires._segments_poly1;
       _segments_poly2 = ires._segments_poly2;
       _is_vertex_of_poly1 = ires._is_vertex_of_poly1;
       _is_vertex_of_poly2 = ires._is_vertex_of_poly2;
       _is_edge_of_poly1 = ires._is_edge_of_poly1;
       _is_edge_of_poly2 = ires._is_edge_of_poly2;
       _is_vertex_vertex_intersection = 
                 ires._is_vertex_vertex_intersection;
       _is_vertex_edge_intersection = ires._is_vertex_edge_intersection;
       _is_edge_edge_intersection = ires._is_edge_edge_intersection;
     }

template < class R > 
Intersectionresult<R>::Intersectionresult (
                           const Point_2<R> &iobj,
                           const Segment_2<R> &iseg1,
                           const Segment_2<R> &iseg2,
                           const bool &i_is_vertex_of_poly1,
                           const bool &i_is_vertex_of_poly2,
                           const bool &i_is_edge_of_poly1,
                           const bool &i_is_edge_of_poly2,
                           const bool &i_is_vertex_vertex_intersection,
                           const bool &i_is_vertex_edge_intersection,
                           const bool &i_is_edge_edge_intersection) 
     {
       _intersection_object = make_object(iobj);
       _segments_poly1.push_back(iseg1);
       _segments_poly2.push_back(iseg2);
       _is_vertex_of_poly1 = i_is_vertex_of_poly1;
       _is_vertex_of_poly2 = i_is_vertex_of_poly2;
       _is_edge_of_poly1 = i_is_edge_of_poly1;
       _is_edge_of_poly2 = i_is_edge_of_poly2;
       _is_vertex_vertex_intersection = i_is_vertex_vertex_intersection;
       _is_vertex_edge_intersection = i_is_vertex_edge_intersection;
       _is_edge_edge_intersection = i_is_edge_edge_intersection;
     }

template < class R > 
Intersectionresult<R>::Intersectionresult (
                           const Segment_2<R> &iobj,
                           const Segment_2<R> &iseg1,
                           const Segment_2<R> &iseg2,
                           const bool &i_is_vertex_of_poly1,
                           const bool &i_is_vertex_of_poly2,
                           const bool &i_is_edge_of_poly1,
                           const bool &i_is_edge_of_poly2,
                           const bool &i_is_vertex_vertex_intersection,
                           const bool &i_is_vertex_edge_intersection,
                           const bool &i_is_edge_edge_intersection) 
     {
       _intersection_object = make_object(iobj);
       _segments_poly1.push_back(iseg1);
       _segments_poly2.push_back(iseg2);
       _is_vertex_of_poly1 = i_is_vertex_of_poly1;
       _is_vertex_of_poly2 = i_is_vertex_of_poly2;
       _is_edge_of_poly1 = i_is_edge_of_poly1;
       _is_edge_of_poly2 = i_is_edge_of_poly2;
       _is_vertex_vertex_intersection = i_is_vertex_vertex_intersection;
       _is_vertex_edge_intersection = i_is_vertex_edge_intersection;
       _is_edge_edge_intersection = i_is_edge_edge_intersection;
     }


template < class R > 
Intersectionresult<R>& Intersectionresult<R>::operator=(
                                 const Intersectionresult<R>  &ires)  
     {
       _intersection_object = ires._intersection_object;
       _segments_poly1 = ires._segments_poly1;
       _segments_poly2 = ires._segments_poly2;
       _is_vertex_of_poly1 = ires._is_vertex_of_poly1;
       _is_vertex_of_poly2 = ires._is_vertex_of_poly2;
       _is_edge_of_poly1 = ires. _is_edge_of_poly1;
       _is_edge_of_poly2 = ires._is_edge_of_poly2;
       _is_vertex_vertex_intersection = ires._is_vertex_vertex_intersection;
       _is_vertex_edge_intersection = ires._is_vertex_edge_intersection;
       _is_edge_edge_intersection = ires._is_edge_edge_intersection;
       return *this;
     }

template < class R > 
Intersectionresult<R>::~Intersectionresult() 
     { 
     }



template < class R > 
List_of_intersections<R>::List_of_intersections() 
{
}
template < class R > 
List_of_intersections<R>::List_of_intersections(
                      const List_of_intersections<R> &ilist) 
{
       _list_of_intersections = ilist._list_of_intersections;
}
template < class R > 
List_of_intersections<R>& List_of_intersections<R>::operator=(
                              const List_of_intersections<R> &ilist) 
{
       _list_of_intersections = ilist._list_of_intersections;
       return *this;
}
template < class R > 
List_of_intersections<R>::~List_of_intersections() 
{
}

CGAL_END_NAMESPACE
