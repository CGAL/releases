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
// file          : include/CGAL/Pm_with_intersections.h
// package       : Arrangement (2.52)
// author(s)     : Eyal flato
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_PLANAR_MAP_WITH_INTERSECTIONS_H
#define CGAL_PLANAR_MAP_WITH_INTERSECTIONS_H

#ifndef CGAL_PLANAR_MAP_2_H
#include <CGAL/Planar_map_2.h>
#endif // CGAL_PLANAR_MAP_2_H
#ifndef CGAL_PM_WITH_INTERSECTIONS_MISC_H
#include <CGAL/Pm_with_intersections_misc.h>
#endif // CGAL_PM_WITH_INTERSECTIONS_MISC_H
#ifndef CGAL_PM_WALK_ALONG_LINE_POINT_LOCATION_H
#include <CGAL/Pm_walk_along_line_point_location.h>
#endif // CGAL_PM_WALK_ALONG_LINE_POINT_LOCATION_H

#include <CGAL/Planar_map_2/Pm_change_notification.h>

#ifndef CGAL_PM_COUNT_OPERATIONS_TIMES
#define CGAL_PM_START_OP(x) 
#define CGAL_PM_END_OP(x)  
#define CGAL_DEFINE_COUNT_OP_TIMES_OBJECT
#endif

CGAL_BEGIN_NAMESPACE

template<class Planar_map_>
class Planar_map_with_intersections_2 : public Planar_map_
{
public:
  typedef Planar_map_                                       Planar_map;
  typedef Planar_map_with_intersections_2<Planar_map>       Self;
  typedef typename Planar_map::Traits                       Traits;
  typedef typename Planar_map::Traits_wrap                  Pm_traits_wrap;
  typedef Planar_map_with_intersections_traits_wrap<Traits> Pmwx_traits_wrap;
  typedef typename Planar_map::Halfedge_handle              Halfedge_handle;
  typedef typename Planar_map::Vertex_handle                Vertex_handle;
  typedef typename Planar_map::Face_handle                  Face_handle;
  typedef typename Traits::X_curve                          X_curve_2;
  typedef typename Traits::Curve                            Curve_2;
  typedef typename Traits::Point                            Point_2;
  typedef typename Planar_map::Change_notification      Change_notification;

  typedef typename Planar_map::Halfedge_iterator            Halfedge_iterator;
    
  // Obsolete, for backward compatability
  typedef Point_2                               Point;
  typedef X_curve_2                             X_curve;
  typedef Curve_2                               Curve;
  typedef Change_notification                   Pmwx_change_notification;

  CGAL_DEFINE_COUNT_OP_TIMES_OBJECT

  // Constructors
  // ------------
  
  Planar_map_with_intersections_2() 
    : Planar_map(new Pmwx_traits_wrap,
                 new Pm_walk_along_line_point_location<Planar_map>, NULL),
      pmwx_use_delete_traits(true), 
      pmwx_use_delete_pl(true)
  { 
    pmwx_traits = (Pmwx_traits_wrap*)traits;
  }    
        
  Planar_map_with_intersections_2(Pm_point_location_base<Planar_map> *pl_ptr) 
    : Planar_map(new Pmwx_traits_wrap, pl_ptr, NULL),
      pmwx_use_delete_traits(true), 
      pmwx_use_delete_pl(false)
  {
    pmwx_traits = (Pmwx_traits_wrap*)traits;
  }

  Planar_map_with_intersections_2(const Traits& tr_, 
                                  Pm_point_location_base<Planar_map> *pl_ptr) 
    : Planar_map(new Pmwx_traits_wrap(tr_), pl_ptr, NULL),
      pmwx_use_delete_traits(true), 
      pmwx_use_delete_pl(false)
  {
    pmwx_traits = (Pmwx_traits_wrap*)traits;
  }

  Planar_map_with_intersections_2(Pmwx_traits_wrap *tr_ptr,
                                  Pm_point_location_base<Planar_map> *pl_ptr) 
    : Planar_map(tr_ptr, pl_ptr, NULL),
      pmwx_use_delete_traits(false), 
      pmwx_use_delete_pl(false)
  {
    pmwx_traits = (Pmwx_traits_wrap*)traits;
  }

  // Copy Constructor
  // ----------------
  Planar_map_with_intersections_2(const Self & rhs);

  // Destructor
  //-----------

  ~Planar_map_with_intersections_2();
        
  // Operations
  // ----------

  const X_curve_2& curve(Halfedge_handle he, Change_notification *en )
  { 
    if( en == NULL ) 
      return he->curve();
    if( !en->have_support_curve() ) 
      return he->curve();
    return en->edge_support_curve( he ); 
  }

  // finds the intersection of <cv> directed <direction_right> with the
  // halfedge <he>. The returned intersections is based on the intersection
  // of the supporting curves (if they exist).
  bool 
  directed_nearest_intersection_with_halfedge(
                                              const X_curve_2 &cv,
                                              const X_curve_2 &orig_cv,
                                              Halfedge_handle he,
                                              const Point_2 &ref_point,
                                              bool direction_right,
                                              Point_2 &xp1,
                                              Point_2 &xp2,
                                              Change_notification *en)
  {
    bool intersection_exists;
    if (direction_right)
      intersection_exists =
        pmwx_traits->do_intersect_to_right(cv, he->curve(), ref_point);
    else
      intersection_exists = 
        pmwx_traits->do_intersect_to_left(cv, he->curve(), ref_point);

    if ( ! intersection_exists)
      return false;

    if (direction_right)
      intersection_exists = pmwx_traits->nearest_intersection_to_right
        ( orig_cv, curve(he, en), ref_point, xp1, xp2);
    else
      intersection_exists = pmwx_traits->nearest_intersection_to_left
        ( orig_cv, curve(he, en), ref_point, xp1, xp2);

    CGAL_assertion (intersection_exists);
                
    // check for an intersection on the real curves. assume there is none.
    intersection_exists = false;

    // since we are checking on the parent, we should make sure that the 
    // intersection point is on the halfedge_cv and not only on the parent.
    // do not worry: we will get the same intersection point for the correct
    // halfedge_cv as well, and therefore we can throw it away if it's 
    // not on halfedge_cv
    // no need to check for cv because the checked side of it is not 
    // in the arrangement yet so there is no possibility for an 
    // intersection point not on cv.

    // the intersection is only one point
    const X_curve_2 &he_cv = he->curve();
    if (traits->point_is_same(xp1, xp2)) {
      if (traits->curve_get_point_status(he_cv, xp1) == Traits::ON_CURVE) {
        intersection_exists = true;
      }
    }
    else { // there is an overlap
      bool swap_done( false);
      if ( ! pmwx_traits->point_is_left_low(xp1, xp2))
      {
        pmwx_traits->points_swap(xp1, xp2);
        swap_done = true;
      }

      Point_2 left_point = traits->point_leftlow_most
        ( traits->curve_source(he_cv), traits->curve_target(he_cv));
      Point_2 right_point = traits->point_righttop_most
        ( traits->curve_source(he_cv), traits->curve_target(he_cv));
  
      if ( traits->point_is_left_low( xp1, left_point)) {
        xp1 = left_point;
      }
      if ( traits->point_is_left_low( right_point, xp2)) {
        xp2 = right_point;
      }
      if (traits->point_is_left_low( xp1, xp2)) {
        intersection_exists = true;
      }
      if ( swap_done)
        pmwx_traits->points_swap(xp1, xp2);
    }

    return intersection_exists;
  }


  // input: cv.source is on vh
  // is_overlap is true if cv overlaps prev_halfedge around vh.
  void find_face_of_curve_around_vertex(
                                        const X_curve_2 &cv, 
                                        const X_curve_2 &orig_cv, 
                                        const Vertex_handle &vh,
                                        Halfedge_handle &prev_halfedge,
                                        Point_2& overlap_end_pt,
                                        bool &is_overlap,
                                        Change_notification *en)
  {
    CGAL_PM_START_OP(1);
     
    typename Planar_map::Halfedge_around_vertex_circulator next, prev, start, 
                                                           last_next_checked;
    X_curve_2 xcv;
    Point_2 xp1, xp2;
    Point_2 start_point;
    bool direction_right = pmwx_traits->point_is_left_low
      (pmwx_traits->curve_source(cv), pmwx_traits->curve_target(cv));
    bool b;
                
    start_point = pmwx_traits->curve_source(cv);
        
        last_next_checked = halfedges_end();        
    start = vh->incident_halfedges();
    prev = start;
    next = prev;
    ++next;
    do {
      if ((last_next_checked != prev) && 
          (traits->curves_overlap( cv, prev->curve()))) {
        // cv overlapps prev->curve()
        b = directed_nearest_intersection_with_halfedge
          (cv, orig_cv, prev, start_point, direction_right, xp1, xp2, en);
        // Verify that there is indeed an intersection
        CGAL_assertion( b );
        // Verify that there is indeed an overlap
        CGAL_assertion( !pmwx_traits->point_is_same(xp1, xp2));

        // the overlapping part might not start from the source 
        // vertex (in polyline for example), so if this is the case, 
        // we ignore the overlap. 
        if ( (pmwx_traits->point_is_same(xp1, 
                                         pmwx_traits->curve_source(cv))) ||
             (pmwx_traits->point_is_same(xp2, 
                                         pmwx_traits->curve_source(cv))) )
        {
          if ( traits->point_is_same( vh->point(), xp1)) {
            overlap_end_pt = xp2;
          }
          else {
            CGAL_assertion(  traits->point_is_same( vh->point(), xp2));
            overlap_end_pt = xp1;
          }
          
          prev_halfedge = prev;
          is_overlap = true;
          CGAL_PM_END_OP(1);
          return;
        }
      }

          // Same check as above is done now to next->curve() to prevent
          // unexpected behavior of is_between_cw when one of the curves
          // overlaps at vh.
          // last_next_checked is set to next so if the test fails
          // (namely, there is no overlap at vh) then it will not 
          // be executed again at the next loop when prev will be this 
          // next. this is for efficiency only.
      if (traits->curves_overlap( cv, next->curve())) {
    last_next_checked = next;
        // cv overlapps next->curve()
        b = directed_nearest_intersection_with_halfedge
          (cv, orig_cv, next, start_point, direction_right, xp1, xp2, en);
        // Verify that there is indeed an intersection
        CGAL_assertion( b );
        // Verify that there is indeed an overlap
        CGAL_assertion( !pmwx_traits->point_is_same(xp1, xp2));

        // the overlapping part might not start from the source 
        // vertex (in polyline for example), so if this is the case, 
        // we ignore the overlap. 
        if ( (pmwx_traits->point_is_same(xp1, 
                                         pmwx_traits->curve_source(cv))) ||
             (pmwx_traits->point_is_same(xp2, 
                                         pmwx_traits->curve_source(cv))) )
        {
          if ( traits->point_is_same( vh->point(), xp1)) {
            overlap_end_pt = xp2;
          }
          else {
            CGAL_assertion(  traits->point_is_same( vh->point(), xp2));
            overlap_end_pt = xp1;
          }
          
          prev_halfedge = next;
          is_overlap = true;
          CGAL_PM_END_OP(1);
          return;
        }
      }
  
          /////////***** Eyal end
      // The following remarked test is not fully correct
          // since there can be an overlap that does not start at vh
          // but elsewhere on cv (e.g., polylines).
          // this condition is redundant if curve_is_between_cw does
          // not return true when overlap occurs, but it is needed
          // since it is not a defined behaviour (in specs).
      //// if (!traits->curves_overlap( cv, next->curve())) ----
      
      if (next != prev) 
          {
          if (( pmwx_traits->curve_is_between_cw
                        (cv, prev->curve(), next->curve(), vh->point()) ))
                                        {
                  prev_halfedge = prev;
                  is_overlap = false;
                  CGAL_PM_END_OP(1);
                  return;
                                        }
          }
      ++next;
      ++prev;
    } while (prev != start);
                
    // assuming no overlapping occurs, the only situation in 
    // which we reached this line is when there is only one 
    // edge from vh
    CGAL_assertion(next == prev);
    prev_halfedge = prev;
    is_overlap = false;
    CGAL_PM_END_OP(1)
      return;
  }
        
        
  // finds the first intersection in the direction cv.source --> cv.target
  // in <face>.
  // return false if no intersection is found and tru otherwise.
  // the returned <intersection> is the intersection curve of 
  // <cv> and <face>'s boundary.
  // returned <halfedge> is the halfedge on whic the intersection occurs,
  // in case of intersection-point halfedge->source will contain this point
  bool find_first_intersection_in_face(
                                       const Face_handle &face,
                                       const X_curve_2 &cv,
                                       const X_curve_2 &orig_cv, 
                                       Halfedge_handle &halfedge,
                                       Point_2 &best_xpnt1,
                                       Point_2 &best_xpnt2,
                                       Change_notification *en)
  {
    CGAL_PM_START_OP(2)
      Halfedge_handle best_halfedge_x;
    typename Planar_map::Ccb_halfedge_circulator che, che_beg;
    Point_2 start_point, best_point, xpnt;
    Point_2 xp1, xp2;
    bool b, better_xcv;
    bool intersection_exist = false;
    bool direction_right = pmwx_traits->point_is_left_low
      (pmwx_traits->curve_source(cv), pmwx_traits->curve_target(cv));
    
    start_point = pmwx_traits->curve_source(cv);
    best_point = pmwx_traits->curve_target(cv);
    
    if (!face->is_unbounded())
    {
      che = face->outer_ccb();
      che_beg = che;
      do
      {
        b = directed_nearest_intersection_with_halfedge
          (cv, orig_cv, che, start_point, direction_right, xp1, xp2, en);
        if (b)
        {
          // direct xp1-xp2 to be like cv
          if (direction_right)
          {
            if (!pmwx_traits->point_is_left_low(xp1, xp2))
              pmwx_traits->points_swap(xp1, xp2);
          }
          else
          {
            if (!pmwx_traits->point_is_right_top(xp1, xp2))
              pmwx_traits->points_swap(xp1, xp2);
          }
          
          xpnt = xp1;
          if (direction_right)
            better_xcv = 
              pmwx_traits->point_is_left_low(xpnt, best_point);
          else
            better_xcv = 
              pmwx_traits->point_is_right_top(xpnt, best_point);
          if (better_xcv || (!intersection_exist)) // xcv is better
          {
            best_halfedge_x = che;
            best_point = xpnt;
            best_xpnt1 = xp1;
            best_xpnt2 = xp2;
            intersection_exist = true;
          }
        }
        ++che;
      } while (che != che_beg);
    }
    
    typename Planar_map::Holes_iterator holes;
    for (holes = face->holes_begin(); holes != face->holes_end(); holes++)
    {
      che = *holes;
      che_beg = che;
      do
      {
        b = directed_nearest_intersection_with_halfedge
          (cv, orig_cv, che, start_point, direction_right, xp1, xp2, en);
        if (b)
        {
          // direct xp1-xp2 to be like cv
          if (direction_right)
          {
            if (!pmwx_traits->point_is_left_low(xp1, xp2))
              pmwx_traits->points_swap(xp1, xp2);
          }
          else
          {
            if (!pmwx_traits->point_is_right_top(xp1, xp2))
              pmwx_traits->points_swap(xp1, xp2);
          }
          
          xpnt = xp1;
          if (direction_right)
            better_xcv =
              pmwx_traits->point_is_left_low(xpnt, best_point);
          else
            better_xcv = 
              pmwx_traits->point_is_right_top(xpnt, best_point);
          if (better_xcv || (!intersection_exist)) // xcv is better
          {
            best_halfedge_x = che;
            best_point = xpnt;
            best_xpnt1 = xp1;
            best_xpnt2 = xp2;
            intersection_exist = true;
          }
        }
        ++che;
      } while (che != che_beg);
    }
    
    
    halfedge = best_halfedge_x;
    
    CGAL_PM_END_OP(2)
      return intersection_exist;
  }

  
  void get_vertex_of_point_on_halfedge
  ( const Point_2 &point,                     
    Halfedge_handle halfedge,
    Vertex_handle &vertex_of_point, 
    // in case of split it is easy to compute:
    Halfedge_handle &vertex_of_point_prev_halfedge,
    // true if vertex_of_point_prev_halfedge is set :
    bool &vertex_of_point_prev_halfedge_set,
    Change_notification *en)
  {
    CGAL_PM_START_OP(3)
      if (pmwx_traits->point_is_same(point, halfedge->source()->point()))
      {
        vertex_of_point = halfedge->source();
        vertex_of_point_prev_halfedge_set = false;
      }
      else if (pmwx_traits->point_is_same(point, halfedge->target()->point()))
      {
        vertex_of_point = halfedge->target();
        vertex_of_point_prev_halfedge_set = false;
      }
      else
      {  // intersection in the interior - split
        X_curve_2 split1, split2;
        Halfedge_handle he_split;
        if (pmwx_traits->point_is_same
            (halfedge->source()->point(), 
             pmwx_traits->curve_source(halfedge->curve())) )
        {
          pmwx_traits->directed_curve_split(halfedge->curve(), 
                                            halfedge->source()->point(), 
                                            point, split1, split2);
          he_split = Planar_map::split_edge(halfedge, split1, split2);
          if (en != NULL) 
            en->split_edge(he_split, he_split->next_halfedge(), 
                           split1, split2);
                            
          vertex_of_point = he_split->target();
          vertex_of_point_prev_halfedge = 
            he_split->next_halfedge()->twin();
          vertex_of_point_prev_halfedge_set = true;
        }
        else
        {
          Halfedge_handle twin_halfedge = halfedge->twin();
          pmwx_traits->directed_curve_split
            (twin_halfedge->curve(), twin_halfedge->source()->point(), 
             point, split1, split2);
          he_split = Planar_map::split_edge(twin_halfedge, split1, split2);
          if (en != NULL) en->split_edge(he_split, 
                                         he_split->next_halfedge(), 
                                         split1, split2);
                            
          // change he_split to be on the current face becase we spliited 
          // the twin_halfedge and not halfedge - this is to be 
          // consistent with 
          // the arrangement code that is based on the fact the the 
          // splitted halfedge
          // is the one that is directed like the curve
          he_split = he_split->next_halfedge()->twin();
          vertex_of_point = he_split->target();
          vertex_of_point_prev_halfedge = 
            he_split->next_halfedge()->twin();
          vertex_of_point_prev_halfedge_set = true;
        }
      }
                
    // in order to enable polyline overlap
    // (a little ugly solution. should be made nicer) : 
    vertex_of_point_prev_halfedge_set = false; 
    CGAL_PM_END_OP(3)
      }

 
  // insert the first part of cv into the face source_face 
  // returning: 
  //   1. inserted edge
  //   2. remaining curve (the part that was not inserted)
  //   3. remaining curve source vertex 
  int insert_intersecting_xcurve_in_face_interior
  ( const X_curve_2 &cv,                     // inserted curve
    const X_curve_2 &orig_cv, 
    Face_handle source_face,
    Halfedge_handle &inserted_halfedge,
    bool &remaining_curve_trivial,
    X_curve_2 &remaining_curve,
    Vertex_handle &remaining_curve_source_vertex, 
    // in case of split it is easy to compute :
    Halfedge_handle &remaining_curve_prev_halfedge,
    // true if remaining_curve_face is set :
    bool &remaining_curve_prev_halfedge_set,  
    Change_notification *en)
  {
    CGAL_PM_START_OP(4)
      remaining_curve_trivial = false;
    //std::cout << "iisifi " 
    // << "insert_intersecting_xcurve_in_face_interior: " << cv << std::endl;
    Halfedge_handle intersection_he;
    Point_2 xpnt1, xpnt2;
                
    if ( find_first_intersection_in_face(
                                         source_face,
                                         cv,
                                         orig_cv,
                                         intersection_he,
                                         xpnt1, 
                                         xpnt2,
                                         en) )
    {
      Point_2 insert_point;
      X_curve_2 cv_first_part;
      bool direction_right = 
        pmwx_traits->point_is_left_low(pmwx_traits->curve_source(cv),
                                       pmwx_traits->curve_target(cv));
                        
      if (direction_right)
        insert_point = pmwx_traits->point_leftlow_most(xpnt1, xpnt2);
      else
        insert_point = pmwx_traits->point_righttop_most(xpnt1, xpnt2);
                        
      CGAL_assertion(!pmwx_traits->point_is_same
                     (pmwx_traits->curve_source(cv), insert_point));

      remaining_curve_trivial = 
        pmwx_traits->point_is_same(pmwx_traits->curve_target(cv), 
                                   insert_point);
      if (remaining_curve_trivial)
        cv_first_part = cv;
      else
        pmwx_traits->directed_curve_split(cv, pmwx_traits->curve_source(cv), 
                                          insert_point, cv_first_part, 
                                          remaining_curve);

                        
#ifdef CGAL_PM_WITH_INTERSECTIONS_PRINT_DEBUG
      std::cout << "cv " << cv << std::endl;
      std::cout << "xpnt1 " << xpnt1 << std::endl;
      std::cout << "xpnt2 " << xpnt2 << std::endl;
      std::cout << "insert_point " << insert_point << std::endl;
      std::cout << "cv_first_part " << cv_first_part << std::endl;
      std::cout << "remaining_curve " << remaining_curve << std::endl;
      std::cout << "intersection_he->curve() " 
                << intersection_he->curve() << std::endl;
      //                        std::cout << " " << << std::endl;
#endif                        
      get_vertex_of_point_on_halfedge(
                                      insert_point,
                                      intersection_he,
                                      remaining_curve_source_vertex,
                                      remaining_curve_prev_halfedge,
                                      remaining_curve_prev_halfedge_set, 
                                      en);

      inserted_halfedge =
        Planar_map::insert_from_vertex(cv_first_part, 
                                       remaining_curve_source_vertex);
      if (en != NULL) en->add_edge(cv_first_part, inserted_halfedge,
                                   false, false);
      CGAL_PM_END_OP(4)
        return 1;
    }
    else
    {
      inserted_halfedge = 
        Planar_map::insert_in_face_interior(cv, source_face);
      if (en != NULL)
      {
        en->add_edge(cv, inserted_halfedge, true, false);
        en->add_hole(source_face, inserted_halfedge);
      }
      //std::cout << "iisifi inserted_halfedge " 
      // << inserted_halfedge->source()->point() <<
      //  " ----> " << inserted_halfedge->target()->point() << std::endl;
      if (pmwx_traits->point_is_same(inserted_halfedge->source()->point(), 
                                     pmwx_traits->curve_source(cv)))
        remaining_curve_source_vertex = inserted_halfedge->target();
      else
        remaining_curve_source_vertex = inserted_halfedge->source();
      remaining_curve_trivial = true;
      remaining_curve_prev_halfedge_set = false;
      CGAL_PM_END_OP(4)
        return 1;
    }
  }


  // source_prev_halfedge->face() is the face we are working on
  // source_prev_halfedge->target() is the vertex on whice cv's source is
  // assuming cv does not overlap an edge from source_prev_halfedge->target()
  // insert the first part of cv into face where cv's source is on the 
  // boundary of face
  // returning: 
  //   1. inserted edge
  //   2. remaining curve (the part that was not inserted)
  //   3. remaining curve source vertex 
  int insert_intersecting_xcurve_from_boundary_of_face
  (const X_curve_2 &cv,                     // inserted curve
   const X_curve_2 &orig_cv, 
   Halfedge_handle source_prev_halfedge,
   Halfedge_handle &inserted_halfedge,
   bool &remaining_curve_trivial,
   X_curve_2 &remaining_curve,
   Vertex_handle &remaining_curve_source_vertex, 
   // in case of split it is easy to compute :
   Halfedge_handle &remaining_curve_prev_halfedge, 
   // true if remaining_curve_face is set :
   bool &remaining_curve_prev_halfedge_set,  
   Change_notification *en)
  {
    CGAL_PM_START_OP(5)
      remaining_curve_trivial = false;
    //std::cout << "iifbof " 
    // << "insert_intersecting_xcurve_from_boundary_of_face: " 
    // << cv << std::endl;
    //std::cout << "iifbof " 
    // << "         source_prev_halfedge: " 
    // << source_prev_halfedge->source()->point() <<
    //   " ----> " << source_prev_halfedge->target()->point() << std::endl;
    Halfedge_handle intersection_he;
    Point_2 xpnt1, xpnt2;
    Face_handle orig_face = source_prev_halfedge->face();
                
    if ( find_first_intersection_in_face(
                                         source_prev_halfedge->face(),
                                         cv,
                                         orig_cv,
                                         intersection_he,
                                         xpnt1,
                                         xpnt2,
                                         en) )
    {
      Point_2 insert_point;
      X_curve_2 cv_first_part;

      // keep the source vertex. We can't rely on 
      // source_prev_halfedge->target() because it might be changed if 
      // source_prev_halfedge is intersected by the new curve
      Vertex_handle source_vertex(source_prev_halfedge->target());

      bool direction_right = 
        pmwx_traits->point_is_left_low(pmwx_traits->curve_source(cv), 
                                       pmwx_traits->curve_target(cv));
                        
      if (direction_right)
        insert_point = pmwx_traits->point_leftlow_most(xpnt1, xpnt2);
      else
        insert_point = pmwx_traits->point_righttop_most(xpnt1, xpnt2);
                        
      CGAL_assertion(!pmwx_traits->point_is_same
                     (pmwx_traits->curve_source(cv), insert_point));

      remaining_curve_trivial = 
        pmwx_traits->point_is_same(pmwx_traits->curve_target(cv), 
                                   insert_point);
      if (remaining_curve_trivial)
        cv_first_part = cv;
      else
        pmwx_traits->directed_curve_split(cv, pmwx_traits->curve_source(cv), 
                                          insert_point, cv_first_part, 
                                          remaining_curve);
                        
      get_vertex_of_point_on_halfedge(
                                      insert_point,
                                      intersection_he,
                                      remaining_curve_source_vertex,
                                      remaining_curve_prev_halfedge,
                                      remaining_curve_prev_halfedge_set,
                                      en);
                        
      //std::cout << "iifbob " << "insert_at_vertices: " << 
      //  cv_first_part << 
      //  "   vx1: "<< source_prev_halfedge->target()->point() <<
      //  "   prev_src: "<< source_prev_halfedge->source()->point() <<
      //  "   vx2: "<< remaining_curve_source_vertex->point() << std::endl;
#ifdef CGAL_PM_WITH_INTERSECTIONS_PRINT_DEBUG
      std::cout << "cv " << cv << std::endl;
      std::cout << "xpnt1 " << xpnt1 << std::endl;
      std::cout << "xpnt2 " << xpnt2 << std::endl;
      std::cout << "insert_point " << insert_point << std::endl;
      std::cout << "cv_first_part " << cv_first_part << std::endl;
      std::cout << "remaining_curve " << remaining_curve << std::endl;
      std::cout << "intersection_he->curve() " 
                << intersection_he->curve() << std::endl;
      //                        std::cout << " " << << std::endl;
#endif                        
      inserted_halfedge = 
        Planar_map::insert_at_vertices(cv_first_part, source_vertex, 
                                       remaining_curve_source_vertex);
      if (en != NULL) 
      {
        en->add_edge(cv_first_part, inserted_halfedge, true, false);
        if (inserted_halfedge->face() == orig_face)
          en->split_face(inserted_halfedge->face(), 
                         inserted_halfedge->twin()->face());
        else
          en->split_face(inserted_halfedge->twin()->face(), 
                         inserted_halfedge->face());
      }
      CGAL_PM_END_OP(5)
        return 1;
    }
    else
    {
      inserted_halfedge = 
        Planar_map::insert_from_vertex(cv, source_prev_halfedge->target()); 
      if (en != NULL) 
        en->add_edge(cv, inserted_halfedge,true, false);
      if (pmwx_traits->point_is_same(inserted_halfedge->source()->point(), 
                                     pmwx_traits->curve_source(cv)))
        remaining_curve_source_vertex = inserted_halfedge->target();
      else
        remaining_curve_source_vertex = inserted_halfedge->source();
      remaining_curve_trivial = true;
      remaining_curve_prev_halfedge_set = false;
      CGAL_PM_END_OP(5)
        return 1;
    }
  }

        
  Halfedge_handle 
  insert_intersecting_xcurve(
                             // inserted curve:
                             const X_curve_2 &cv_,               
                             Vertex_handle &source_vertex,
                             // to be set by the function :  
                             Vertex_handle &target_vertex, 
                             bool source_vertex_valid,
                             Change_notification *en = NULL)
  {
    CGAL_PM_START_OP(6)
      //if a vertex on which an endpoint of cv_ is known then set cv to 
      //have this endpoint as it's source
                
      // at the end source_vertex and target_vertex will contain the
      // end-vertices of cv
      int count = 0;
    Vertex_handle curr_vertex = source_vertex;
    X_curve_2 cv = cv_; 
    X_curve_2 orig_cv = cv;
    X_curve_2 split1, split2;
    Point_2 overlap_end_pt;
    Halfedge_handle inserted_he, prev_halfedge, he_split, last_edge;
    bool is_overlap;
    bool next_face_valid = false;
    bool remaining_curve_trivial = false; 

    if (!source_vertex_valid)
    {
#ifdef CGAL_PM_WITH_INTERSECTIONS_PRINT_DEBUG
      std::cout << "!";
#endif 
      typename Planar_map::Locate_type lt;
      Halfedge_handle he;
      //-- locate pmwx_traits->curve_source(cv)
      CGAL_PM_START_OP(7)
        he = locate(pmwx_traits->curve_source(cv), lt);
      CGAL_PM_END_OP(7)
                        
        if (lt == Planar_map::VERTEX)
        { //-- if on vertex --> source_vertex and curr_vertex
          source_vertex = he->target();
          curr_vertex = source_vertex;
        }
        else if (lt == Planar_map::EDGE)
        { //-- if on edge - split edge --> source_vertex and curr_vertex
          if (pmwx_traits->point_is_same
              (he->source()->point(), 
               pmwx_traits->curve_source(he->curve())) )
          {
            pmwx_traits->directed_curve_split
              (he->curve(), he->source()->point(),
               pmwx_traits->curve_source(cv), split1, split2);
            he_split = Planar_map::split_edge(he, split1, split2);
            if (en != NULL) en->split_edge(he_split, 
                                           he_split->next_halfedge(), 
                                           split1, split2);
          }
          else
          {
            Halfedge_handle twin_he = he->twin();
            pmwx_traits->directed_curve_split
              (twin_he->curve(), twin_he->source()->point(),
               pmwx_traits->curve_source(cv), split1, split2);
            he_split = Planar_map::split_edge(twin_he, split1, split2);
            if (en != NULL) 
              en->split_edge(he_split, he_split->next_halfedge(), 
                             split1, split2);
          }
          source_vertex = he_split->target();
          curr_vertex = source_vertex;
        } 
        else //Planar_map::UNBOUNDED_FACE or Planar_map::FACE
        { //-- if in face interior === special treatment ===
          Face_handle face;
          if (lt == Planar_map::UNBOUNDED_FACE)
            face = unbounded_face();
          else
            face = he->face();
          // insert_intersecting_xcurve_in_face_interior(curr_vertex)
          X_curve_2 remaining_curve; 
          insert_intersecting_xcurve_in_face_interior
            ( cv, 
              orig_cv,
              face,
              inserted_he,
              remaining_curve_trivial,
              remaining_curve,    
              curr_vertex,  
              prev_halfedge,
              next_face_valid,
              en);
          if (!remaining_curve_trivial)
            cv = remaining_curve;
          last_edge = inserted_he;
          target_vertex = curr_vertex; // temporary - can be changed later
          if (inserted_he->source() == curr_vertex)
            source_vertex = inserted_he->target();
          else
            source_vertex = inserted_he->source();
          //inserted_edges.push_back(inserted_he);
          count++;
        }
                        
      // by now: curr_vertex and source_vertex are set
      source_vertex_valid = true;
    }
                
    while (!remaining_curve_trivial)
    {
#ifdef CGAL_PM_WITH_INTERSECTIONS_PRINT_DEBUG
      std::cout << "@";
#endif
      if (!next_face_valid)
      { 
#ifdef CGAL_PM_WITH_INTERSECTIONS_PRINT_DEBUG
        std::cout << "#";
#endif
        //-- locate cv around curr_vertex
        //std::cout << "iis " << " ---- curr_vertex: " 
        //<< curr_vertex->point() << std::endl;
        find_face_of_curve_around_vertex(
                                         cv, 
                                         orig_cv,
                                         curr_vertex,
                                         prev_halfedge,
                                         overlap_end_pt,
                                         is_overlap,
                                         en);
        //std::cout << "iis " << " ---- prev_halfedge: " 
        //<< prev_halfedge->source()->point() <<
        //   "  ---->  " << prev_halfedge->target()->point() << std::endl;
        if (is_overlap)
        { // if overlaps an edge from curr_vertex 
#ifdef CGAL_PM_WITH_INTERSECTIONS_PRINT_DEBUG
          std::cout << "$";
#endif
          // rem: prev_halfedge->target == curr_vertex
          if ( pmwx_traits->point_is_same
               (prev_halfedge->source()->point(),        overlap_end_pt) )
          { // whole edge is overlapped, proceed to its other end
#ifdef CGAL_PM_WITH_INTERSECTIONS_PRINT_DEBUG
            std::cout << "%";
#endif
            if (en != NULL) 
              en->add_edge(prev_halfedge->curve(), prev_halfedge,
                           false, true);
            last_edge = prev_halfedge;
            // update cv
                        
            CGAL_assertion(pmwx_traits->point_is_same
                           (pmwx_traits->curve_source(cv), 
                            curr_vertex->point()));
            remaining_curve_trivial = pmwx_traits->point_is_same
              ( pmwx_traits->curve_target(cv), 
                prev_halfedge->source()->point());
            if (!remaining_curve_trivial)
            {
              pmwx_traits->directed_curve_split
                (cv, curr_vertex->point(), 
                 prev_halfedge->source()->point(), split1, split2);
              cv = split2;
            }
            curr_vertex = prev_halfedge->source();
            count++;
          }
          else
          { 
            // otherwise - split prev_halfedge and let curr_vertex 
            //be the splitting point
#ifdef CGAL_PM_WITH_INTERSECTIONS_PRINT_DEBUG
            std::cout << "^";
#endif
            if (pmwx_traits->point_is_same
                (prev_halfedge->twin()->source()->point(), 
                 pmwx_traits->curve_source
                 (prev_halfedge->twin()->curve())) )
            {
              pmwx_traits->directed_curve_split
                (prev_halfedge->curve(), curr_vertex->point(), 
                 overlap_end_pt, split1, split2);
                                
              // split prev_halfedge->twin() so that the splitted 
              // edge 
              // source will be the same as split1's source
              he_split = 
                Planar_map::split_edge(prev_halfedge->twin(), 
                                       split1, split2);
              if (en != NULL) 
                en->split_edge(he_split, he_split->next_halfedge(), 
                               split1, split2);
              if (en != NULL) en->add_edge(he_split->curve(), 
                                           he_split, true, true);
              last_edge = he_split;
                            
              // update cv
              remaining_curve_trivial = pmwx_traits->point_is_same
                ( pmwx_traits->curve_target(cv), 
                  he_split->target()->point());
              if (!remaining_curve_trivial)
              {
                pmwx_traits->directed_curve_split
                  (cv, pmwx_traits->curve_source(cv), 
                   he_split->target()->point(), split1, split2);
                cv = split2;
              }
              curr_vertex = he_split->target();
            }
            else
            {
              pmwx_traits->directed_curve_split
                (prev_halfedge->twin()->curve(), 
                 pmwx_traits->curve_source
                 (prev_halfedge->twin()->curve()),
                 overlap_end_pt, split1, split2);
                        
              // split prev_halfedge->twin() so that the splitted
              //  edge 
              // source will be the same as split1's source
              he_split = Planar_map::split_edge
                (prev_halfedge, split1, split2);
              if (en != NULL)
                en->split_edge(he_split, 
                               he_split->next_halfedge(), 
                               split1, split2);
              if (en != NULL) 
                en->add_edge
                  (he_split->next_halfedge()->twin()->curve(),
                   he_split->next_halfedge()->twin(), true, true);
              last_edge = he_split->next_halfedge()->twin();

              // update cv
              remaining_curve_trivial = pmwx_traits->point_is_same
                ( pmwx_traits->curve_target(cv), 
                  he_split->next_halfedge()->twin()->
                  target()->point());
              if (!remaining_curve_trivial)
              {
                pmwx_traits->directed_curve_split
                  (cv, pmwx_traits->curve_source(cv), 
                   he_split->next_halfedge()->twin()->
                   target()->point(), split1, split2);
                cv = split2;
              }
              curr_vertex = 
                he_split->next_halfedge()->twin()->target();

            }
            count++;
          }
                                        
          target_vertex = curr_vertex; // temporary -can be changed later
          next_face_valid = false; 
          continue;
        }
        // if not overlap then in face
        next_face_valid = true;
      }
                        
      // now - we are sure that cv is in the interior of
      // prev_halfedge->face (does not overlaps an halfedge around 
      // curr_vertex)
                        
#ifdef CGAL_PM_WITH_INTERSECTIONS_PRINT_DEBUG
      std::cout << "&";
#endif
      X_curve_2 remaining_curve;
      insert_intersecting_xcurve_from_boundary_of_face
        ( cv,
          orig_cv,
          prev_halfedge,
          inserted_he,
          remaining_curve_trivial,
          remaining_curve,
          curr_vertex,
          prev_halfedge,
          next_face_valid,
          en);
      if (!remaining_curve_trivial)
        cv = remaining_curve;
      last_edge = inserted_he;

      count++;
                        
      target_vertex = curr_vertex; // temporary - can be changed later
    }

    if (!pmwx_traits->point_is_same(last_edge->target()->point(), 
                                    pmwx_traits->curve_target(cv_)))
      last_edge = last_edge->twin();
    CGAL_PM_END_OP(6)
      return last_edge; 
  }

  Halfedge_handle 
  insert_intersecting_curve(
                            // inserted curve:
                            const Curve_2            & c,
                            Vertex_handle            & source_vertex,
                            // to be set by the function :  
                            Vertex_handle            & target_vertex, 
                            bool                       source_vertex_valid,
                            Change_notification      * en = NULL)
  {
    if (traits->is_x_monotone(c))
    {
      return insert_intersecting_xcurve(c, source_vertex, target_vertex, 
                                        source_vertex_valid, en);
    }
    else
    {
      Vertex_handle         src, tgt;
      Halfedge_handle last_he;
      std::list<CGAL_TYPENAME_MSVC_NULL Traits::X_curve_2> x_list;
      typename std::list<
        CGAL_TYPENAME_MSVC_NULL Traits::X_curve_2>::const_iterator it;
      traits->make_x_monotone(c, x_list);
      src = source_vertex;
      tgt = target_vertex;
      for (it = x_list.begin(); it != x_list.end(); it++)
      {
        if (it == x_list.begin()) 
          last_he = insert_intersecting_xcurve(*it, src, tgt, 
                                               source_vertex_valid, en); 
        else
          last_he = insert_intersecting_xcurve(*it, src, tgt, true, en); 
        src = tgt;
      }
      target_vertex = tgt;
      return last_he;
    }
  }

  // return the last inserted halfedge whose target points to the last 
  // point of the inserted xcurve
  Halfedge_handle insert_from_vertex(const Curve_2                & c, 
                                     Vertex_handle                  src, 
                                     Change_notification          * en = NULL)
  {
    CGAL_precondition( ! traits->point_is_same( traits->curve_source(c),
                                                traits->curve_target(c)));
    Vertex_handle tgt;
    return insert_intersecting_curve(c, src, tgt, true, en);
  }

  // return the last inserted halfedge whose target points to the last 
  // point of the inserted xcurve
  Halfedge_handle insert(const Curve_2            & c, 
                         Change_notification      * en = NULL)
  {
    // If curve is x-monotone then its source is different from its target.
    // (which is not true for non x-monotone curves, e.g, triangles.)
    CGAL_precondition( ! traits->is_x_monotone(c) ||
                       ! traits->point_is_same( traits->curve_source( c),
                                                traits->curve_target( c)));
    Vertex_handle src, tgt;
    return insert_intersecting_curve(c, src, tgt, false, en);
  }

  // Non intersecting insert methods:

  //! inserts a given curve into the map.
  Halfedge_handle non_intersecting_insert(const X_curve_2 & cv,
                                          Change_notification * en = NULL)
  { return Planar_map::insert(cv, en); }

  //! iterates through a given range of curves, inserting the curves into the
  // map.
  template <class X_curve_2_iterator>
  Halfedge_iterator non_intersecting_insert(const X_curve_2_iterator & begin,
                                            const X_curve_2_iterator & end,
                                            Change_notification * en = NULL)
  { return Planar_map::insert(begin, end, en); }

  //! inserts a given curve as a new inner component of a given face.
  Halfedge_handle
  non_intersecting_insert_in_face_interior(const X_curve_2 & cv, 
                                           Face_handle f,
                                           Change_notification * en = NULL)
  { return Planar_map::insert_in_face_interior(cv, f, en); }

  //! inserts a given curve that one of its endpoints is held by the target
  // vertex of a given halfedge into the map.
  Halfedge_handle non_intersecting_insert_from_vertex(const X_curve_2 & cv, 
                                                      Halfedge_handle h,
                                                      Change_notification *
                                                        en = NULL) 
  { return Planar_map::insert_from_vertex(cv, h, en); }

  //! inserts a given curve that both of its endpoints are held by the target
  // vertices of two given halfedges respectively into the map.
  Halfedge_handle non_intersecting_insert_at_vertices(const X_curve_2 & cv, 
                                                      Halfedge_handle h1, 
                                                      Halfedge_handle h2,
                                                      Change_notification *
                                                        en = NULL)
  { return Planar_map::insert_at_vertices(cv, h1, h2, en); } 

  //! inserts a given curve that one of its endpoints is held by a given vertex
  // into the map.
  Halfedge_handle non_intersecting_insert_from_vertex(const X_curve_2 & cv, 
                                                      Vertex_handle v1,
                                                      Change_notification *
                                                        en = NULL) 
  { return Planar_map::insert_from_vertex(cv, v1, en); }

  //! inserts a given curve that both of its endpoints are held by two given
  // vertices respectively into the map.
  Halfedge_handle non_intersecting_insert_at_vertices(const X_curve_2 & cv, 
                                                      Vertex_handle v1, 
                                                      Vertex_handle v2,
                                                      Change_notification *
                                                        en = NULL)
  { return Planar_map::insert_at_vertices(cv, v1, v2, en); } 
    
  // Data Members
  // ------------
protected:
  Pmwx_traits_wrap *pmwx_traits;
  bool pmwx_use_delete_traits;
  bool pmwx_use_delete_pl;
};

//-----------------------------------------------------------------------------
template<class Pm>
Planar_map_with_intersections_2<Pm>::
Planar_map_with_intersections_2(const Self & rhs)
  : Planar_map(rhs),
    pmwx_use_delete_traits(false),pmwx_use_delete_pl(false)
{
  pmwx_traits = (Pmwx_traits_wrap*)traits;
}

//-----------------------------------------------------------------------------
template<class Pm>
Planar_map_with_intersections_2<Pm>::~Planar_map_with_intersections_2()
{
  if (pmwx_use_delete_traits){
    delete traits;
  }
  if (pmwx_use_delete_pl){
    delete pl;
  }
}

//-----------------------------------------------------------------------------
CGAL_END_NAMESPACE

#endif
