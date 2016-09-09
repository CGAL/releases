//  -*- Mode: c++ -*-
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
// file          : include/CGAL/nsquare_intersecting.C
// package       : bops (1.1.2)
// source        : include/CGAL/nsquare_intersecting.C
// revision      : $Revision: 1.1.2 $
// revision_date : $Date: Wed Dec  9 13:28:55 MET 1998  $
// author(s)     :             Carl Van Geem
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

template < class R > 
CGAL_Intersectionresult<R>::CGAL_Intersectionresult() 
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
CGAL_Intersectionresult<R>::CGAL_Intersectionresult (const 
                                        CGAL_Intersectionresult<R> &ires )
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
CGAL_Intersectionresult<R>::CGAL_Intersectionresult (
                           const CGAL_Point_2<R> &iobj,
                           const CGAL_Segment_2<R> &iseg1,
                           const CGAL_Segment_2<R> &iseg2,
                           const bool &i_is_vertex_of_poly1,
                           const bool &i_is_vertex_of_poly2,
                           const bool &i_is_edge_of_poly1,
                           const bool &i_is_edge_of_poly2,
                           const bool &i_is_vertex_vertex_intersection,
                           const bool &i_is_vertex_edge_intersection,
                           const bool &i_is_edge_edge_intersection) 
     {
       _intersection_object = CGAL_make_object(iobj);
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
CGAL_Intersectionresult<R>::CGAL_Intersectionresult (
                           const CGAL_Segment_2<R> &iobj,
                           const CGAL_Segment_2<R> &iseg1,
                           const CGAL_Segment_2<R> &iseg2,
                           const bool &i_is_vertex_of_poly1,
                           const bool &i_is_vertex_of_poly2,
                           const bool &i_is_edge_of_poly1,
                           const bool &i_is_edge_of_poly2,
                           const bool &i_is_vertex_vertex_intersection,
                           const bool &i_is_vertex_edge_intersection,
                           const bool &i_is_edge_edge_intersection) 
     {
       _intersection_object = CGAL_make_object(iobj);
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
CGAL_Intersectionresult<R>& CGAL_Intersectionresult<R>::operator=(
                                 const CGAL_Intersectionresult<R>  &ires)  
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
CGAL_Intersectionresult<R>::~CGAL_Intersectionresult() 
     { 
     }



template < class R > 
CGAL_List_of_intersections<R>::CGAL_List_of_intersections() 
{
}
template < class R > 
CGAL_List_of_intersections<R>::CGAL_List_of_intersections(
                      const CGAL_List_of_intersections<R> &ilist) 
{
       _list_of_intersections = ilist._list_of_intersections;
}
template < class R > 
CGAL_List_of_intersections<R>& CGAL_List_of_intersections<R>::operator=(
                              const CGAL_List_of_intersections<R> &ilist) 
{
       _list_of_intersections = ilist._list_of_intersections;
       return *this;
}
template < class R > 
CGAL_List_of_intersections<R>::~CGAL_List_of_intersections() 
{
}


