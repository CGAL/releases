// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

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
// file          : include/CGAL/partition_approx_convex_2.h
// package       : Partition_2 (1.38)
// chapter       : Planar Polygon Partitioning
//
// revision      : $Revision: 1.10 $
// revision_date : $Date: 2002/01/17 11:20:34 $
//
// author(s)     : Susan Hert
//
// coordinator   : MPI (Susan Hert)
//
// implementation: Approximately optimal convex partitioning of polygon
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_PARTITION_APPROX_CONVEX_H
#define CGAL_PARTITION_APPROX_CONVEX_H

#include <CGAL/Constrained_triangulation_2.h>
#include <CGAL/Triangulation_indirect_traits_2.h>
#include <CGAL/Turn_reverser.h>
#include <CGAL/Partitioned_polygon_2.h>
#include <CGAL/IO/Tee_for_output_iterator.h>
#include <CGAL/Partition_traits_2.h>
#include <CGAL/partition_is_valid_2.h>
#include <CGAL/partition_assertions.h>
#include <utility>
#include <iterator>

namespace CGAL {

template< class Point_2, class Traits >
bool partition_appx_cvx_is_edge_through_interior(const Point_2& before_s, 
                                                 const Point_2& source,
                                                 const Point_2& after_s, 
                                                 const Point_2& target,
                                                 const Traits& traits )
{
   // determine if the edge goes through the interior of the polygon or not
   typedef typename Traits::Leftturn_2   Leftturn_2;
   Leftturn_2 left_turn = traits.leftturn_2_object();
   Turn_reverser<Point_2, Leftturn_2> right_turn(left_turn);
   if (right_turn(before_s, source, after_s)) // concave angle
   {
     if (right_turn(before_s, source, target) &&
         right_turn(target, source, after_s))
       return false;
   }
   else // left turn or straight
     if (right_turn(before_s, source, target) ||
         right_turn(target, source, after_s))
       return false;
   return true;
}


// e_circ is a circulator for the edges incident to the point referred to by
// v_ref, which is a circualtor around the vertices of the original polygon
template <class Edge_circulator, class Circulator, class Triangulation, 
          class Traits>
bool partition_appx_cvx_cuts_nonconvex_angle( Edge_circulator e_circ, 
                                              Circulator v_ref,
                                              const Triangulation& triangles, 
                                              const Traits& traits)
{
   typedef typename Triangulation::Segment        Segment_2;

#ifdef CGAL_PARTITION_APPROX_CONVEX_DEBUG
   Segment_2 edge = triangles.segment((*e_circ).first, (*e_circ).second);
   std::cout << "edge: " << *edge.source() << " " << *edge.target()
             << std::endl;
#endif

   typename Triangulation::Point next_ccw_pt_ref, prev_ccw_pt_ref;

   // the next and previous edges in the ccw ordering of edges around v_ref
   Edge_circulator next_e = e_circ; next_e++;
   Edge_circulator prev_e = e_circ; prev_e--;

   // find the first edge before this one that has been included in the
   // partition polygon (and is thus marked as constrained in triangulation)
   while (prev_e != e_circ && (triangles.is_infinite(*prev_e) ||
           !(*prev_e).first->is_constrained((*prev_e).second)))
      prev_e--;
 
   Segment_2  next_edge = triangles.segment((*next_e).first,(*next_e).second);
   Segment_2  prev_edge = triangles.segment((*prev_e).first,(*prev_e).second);
#ifdef CGAL_PARTITION_APPROX_CONVEX_DEBUG
   std::cout << "next_edge: " << *next_edge.source() << " " 
             << *next_edge.target() <<std::endl;
   std::cout << "prev_edge: " << *prev_edge.source() << " " 
             << *prev_edge.target() <<std::endl;
#endif
   // find which endpoint is shared by the two edges
   if (next_edge.source() == v_ref)
      next_ccw_pt_ref = next_edge.target();
   else
      next_ccw_pt_ref = next_edge.source();
   if (prev_edge.source() == v_ref)
      prev_ccw_pt_ref = prev_edge.target();
   else
      prev_ccw_pt_ref = prev_edge.source();

#ifdef CGAL_PARTITION_APPROX_CONVEX_DEBUG
   std::cout << "partition_appx_cvx_cuts_nonconvex_angle: next_ccw_pt " 
             << *next_ccw_pt_ref << " v_ref " << *v_ref << " prev_ccw_pt_ref " 
             << *prev_ccw_pt_ref << std::endl;
#endif

   typedef typename Traits::Leftturn_2    Leftturn_2;
   typedef typename Traits::Point_2     Point_2;
   Leftturn_2 left_turn = traits.leftturn_2_object();
   Turn_reverser<Point_2, Leftturn_2>  right_turn(left_turn);
   return right_turn(*next_ccw_pt_ref, *v_ref, *prev_ccw_pt_ref); 
}


template<class InputIterator, class Traits, class OutputIterator>
OutputIterator partition_approx_convex_2(InputIterator first, 
                                         InputIterator beyond,
                                         OutputIterator result,
                                         const Traits& traits) 
{
   if (first == beyond) return result;

   typedef Partitioned_polygon_2< Traits >             P_Polygon_2;
   typedef typename P_Polygon_2::iterator              I;
   typedef Circulator_from_iterator<I>                 Circulator;
   typedef Triangulation_indirect_traits_2<Circulator, Traits>  
                                                       Gt;
   typedef Triangulation_vertex_base_2<Gt>             Vb;
   typedef Constrained_triangulation_face_base_2<Gt>   Fb;
   typedef Triangulation_default_data_structure_2<Gt, Vb, Fb>   
                                                       Tds;
   typedef Constrained_triangulation_2<Gt, Tds>        Constrained_tri_2;
   typedef typename Constrained_tri_2::Edge_iterator   Edge_iterator;
   typedef typename Constrained_tri_2::Edge_circulator Edge_circulator;
   typedef typename Constrained_tri_2::Vertex_iterator Tri_vertex_iterator;
   typedef typename Constrained_tri_2::Vertex_handle   Vertex_handle;
   typedef typename Gt::Segment_2                      Segment_2;

   P_Polygon_2 polygon(first, beyond);

   CGAL_partition_precondition(
    orientation_2(polygon.begin(), polygon.end(), traits) == COUNTERCLOCKWISE);

   Circulator first_c(polygon.begin(), polygon.end(), polygon.begin());
   Circulator c(polygon.begin(), polygon.end());
   Circulator next(polygon.begin(), polygon.end());

   Constrained_tri_2 triangles;
   
   do 
   {
       next = c; next++;
       triangles.insert(c, next);
   } while (++c != first_c);

   Segment_2 edge;
   Circulator source, target, before_s, after_s;

#ifdef CGAL_PARTITION_APPROX_CONVEX_DEBUG
   std::cout << "Inserting diagonals: " << std::endl;
#endif

   Edge_circulator e_circ, first_e;
   Tri_vertex_iterator v_it;


   for (v_it = triangles.vertices_begin(); v_it != triangles.vertices_end(); 
        v_it++)
   {
       first_e = triangles.incident_edges(Vertex_handle(v_it));
       // find the constrained edge attached to this vertex that is first
       // when going CW from the first edge returned above.  
       while (triangles.is_infinite(*first_e) ||  
              !(*first_e).first->is_constrained((*first_e).second)) 
       {
          first_e--;
       }
       e_circ = first_e;
       do 
       {
          if ((*e_circ).first->is_constrained((*e_circ).second))
          {
             edge = triangles.segment((*e_circ).first, (*e_circ).second);
#ifdef CGAL_PARTITION_APPROX_CONVEX_DEBUG
             std::cout << "edge " <<  *edge.source() << " " << *edge.target() 
                       << " is constrained " << std::endl;
#endif
          }  
          else 
          {
             if (!triangles.is_infinite(*e_circ)) 
             {
                edge = triangles.segment((*e_circ).first, (*e_circ).second);
                source = edge.source();
                target = edge.target();
                before_s = source; before_s--;
                after_s = source; after_s++;
#ifdef CGAL_PARTITION_APPROX_CONVEX_DEBUG
                std::cout << "considering " << *source << " " << *target 
                          << "...";
#endif
                if (partition_appx_cvx_is_edge_through_interior(*before_s, 
                                *source, *after_s, *target, traits)) 
                {
                   if (partition_appx_cvx_cuts_nonconvex_angle(e_circ, 
                                 (*v_it).point(), triangles, traits)) 
                   {
#ifdef CGAL_PARTITION_APPROX_CONVEX_DEBUG
                      std::cout << "inserting" << std::endl;
#endif
                      polygon.insert_diagonal(source, target);
                      triangles.insert(source, target);
                   }
#ifdef CGAL_PARTITION_APPROX_CONVEX_DEBUG
                   else 
                      std::cout << "doesn't cut reflex angle" << std::endl;
#endif
                }
#ifdef CGAL_PARTITION_APPROX_CONVEX_DEBUG
                else 
                   std::cout << "not an edge through the interior" 
                             << std::endl;
#endif
             }
#ifdef CGAL_PARTITION_APPROX_CONVEX_DEBUG
             std::cout << "edge is infinite " << std::endl;
#endif
          }
       } while (++e_circ != first_e);
   }

#if defined(CGAL_PARTITION_NO_POSTCONDITIONS) || \
    defined(CGAL_NO_POSTCONDITIONS)  || defined(NDEBUG)
   OutputIterator res(result);
#else
   typedef typename Traits::Polygon_2                  Polygon_2;
   Tee_for_output_iterator<OutputIterator, Polygon_2>  res(result);
#endif // no postconditions

   polygon.partition(res, 0);
   CGAL_partition_postcondition(
       convex_partition_is_valid_2(polygon.begin(), polygon.end(),
                                   res.output_so_far_begin(), 
                                   res.output_so_far_end(), traits));

#if defined(CGAL_PARTITION_NO_POSTCONDITIONS) || \
    defined(CGAL_NO_POSTCONDITIONS)  || defined(NDEBUG)
   return res;
#else
   return res.to_output_iterator();
#endif // no postconditions
}

template <class InputIterator, class OutputIterator>
inline
OutputIterator partition_approx_convex_2(InputIterator first, 
                                         InputIterator beyond,
                                         OutputIterator result)
{
   typedef typename std::iterator_traits<InputIterator>::value_type Point_2;
   typedef typename Kernel_traits<Point_2>::Kernel K;
   return partition_approx_convex_2(first, beyond, result,  
                                    Partition_traits_2<K>());
}

}

#endif // CGAL_PARTITION_APPROX_CONVEX_H
