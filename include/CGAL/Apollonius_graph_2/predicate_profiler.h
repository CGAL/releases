// Copyright (c) 2003,2006  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Apollonius_graph_2/include/CGAL/Apollonius_graph_2/predicate_profiler.h $
// $Id: predicate_profiler.h 32634 2006-07-19 21:58:48Z mkaravel $
// 
//
// Author(s)     : Menelaos Karavelas <mkaravel@cse.nd.edu>



#ifndef CGAL_APOLLONIUS_GRAPH_2_PREDICATE_PROFILER
#define CGAL_APOLLONIUS_GRAPH_2_PREDICATE_PROFILER 1

#include <CGAL/Apollonius_graph_2/basic.h>

#define AG2_PROFILE_PREDICATES

CGAL_BEGIN_NAMESPACE

CGAL_APOLLONIUS_GRAPH_2_BEGIN_NAMESPACE

class ag2_predicate_profiler
{
public:
  // high level predicates
  static unsigned long side_of_bisector_counter;
  static unsigned long is_trivial_counter;
  static unsigned long infinite_edge_conflict_type_counter;
  static unsigned long finite_edge_conflict_type_counter;

  // subpredicates
  static unsigned long inside_circular_arc_counter;
  static unsigned long distance_from_bitangent_counter;
  static unsigned long shadow_region_type_counter;
  static unsigned long incircle_counter;
  static unsigned long order_on_bisector_counter;

  static void reset() {
    side_of_bisector_counter = 0;
    is_trivial_counter = 0;
    infinite_edge_conflict_type_counter = 0;
    finite_edge_conflict_type_counter = 0;

    inside_circular_arc_counter = 0;
    distance_from_bitangent_counter = 0;
    shadow_region_type_counter = 0;
    incircle_counter = 0;
    order_on_bisector_counter = 0;
  }
};

unsigned long ag2_predicate_profiler::side_of_bisector_counter = 0;
unsigned long ag2_predicate_profiler::is_trivial_counter = 0;
unsigned long ag2_predicate_profiler::infinite_edge_conflict_type_counter = 0;
unsigned long ag2_predicate_profiler::finite_edge_conflict_type_counter = 0;

unsigned long ag2_predicate_profiler::inside_circular_arc_counter = 0;
unsigned long ag2_predicate_profiler::distance_from_bitangent_counter = 0;
unsigned long ag2_predicate_profiler::shadow_region_type_counter = 0;
unsigned long ag2_predicate_profiler::incircle_counter = 0;
unsigned long ag2_predicate_profiler::order_on_bisector_counter = 0;

CGAL_APOLLONIUS_GRAPH_2_END_NAMESPACE

CGAL_END_NAMESPACE

#endif // CGAL_APOLLONIUS_GRAPH_2_PREDICATE_PROFILER
