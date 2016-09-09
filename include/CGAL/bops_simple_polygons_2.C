// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/bops_simple_polygons_2.C
// author(s)     :            Wolfgang Freiseisen 
//
// email         : cgal@cs.uu.nl
//
// ============================================================================

#ifndef CGAL_BOPS_SIMPLE_POLYGONS_2_C
#define CGAL_BOPS_SIMPLE_POLYGONS_2_C

#ifndef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#include<CGAL/bops_simple_polygons_2.h>
#endif

template <class I>
//CGAL_Bops_Simple_Polygons_2<I>::Intersection_type 
int
CGAL_Bops_Simple_Polygons_2<I>::calc_intersection_type(int) const {
     typename I::Bbox a_box= I::get_Bbox(_pgon1);
     typename I::Bbox b_box= I::get_Bbox(_pgon2);

     if( a_box == b_box ) {
       if( _pgon1 == _pgon2 ) return is_identical;
     }
     if( !I::do_overlap(a_box, b_box) ) return is_empty;

     if( I::box_is_contained_in_box( a_box, b_box) )
       return A_is_subset_of_B;
     if( I::box_is_contained_in_box( b_box, a_box) )
       return B_is_subset_of_A;

     typename Polygon_Container::const_iterator it;
     int sum1= 0, n1= _pgon1.size();
     for( it= _pgon1.vertices_begin(); it != _pgon1.vertices_end(); it++)
       sum1 += I::has_on_bounded_side(_pgon2, *it) ? +1 : -1;

     if( sum1 ==  n1 || sum1 == -n1 ) {
       int sum2= 0, n2= _pgon2.size();
       for( it= _pgon2.vertices_begin(); it != _pgon2.vertices_end(); it++)
         sum2 += I::has_on_bounded_side(_pgon1,*it) ? +1 : -1;
       if( sum2 ==  n2|| sum2 == -n2) {
         if( sum1 == -n1 && sum2 == -n2 ) // polygons are separated
           // iff no intersections occur, otherwise return 4
           return !_inter_res.size() ? is_empty : is_intersection;
         if( sum1 == n1 && sum2 == -n2 ) // A is subset B
           return A_is_subset_of_B; 
         if( sum1 == -n1 && sum2 == n2 ) // B is subset A
           return B_is_subset_of_A; 
       }
     }

     return is_intersection; // intersections occur
}



template<class I>
void CGAL_Bops_Simple_Polygons_2_Intersection<I> ::
perform(void)
{
  /* performs the intersection algorithm on the colored DCEL */

  /* handle special cases */
  switch( _pgon_intersection_type ) {
    case is_empty:
      return;
    case is_identical:
    case A_is_subset_of_B:
      _result.push_back(I::Make_object(_pgon1) );
      return;
    case B_is_subset_of_A:
      _result.push_back(I::Make_object(_pgon2) );
      return;
    case is_intersection:
      break;
  }

  CGAL__Dcel_Color search_color(CGAL__RED_AND_BLACK);
  
  /* handle general case */
  list<edge_iterator> elist;

  edge_iterator e;
  vertex_iterator v;
  Polygon_2  pgon;

  face_iterator f;

  for(f= dcel.face_begin(); f != dcel.face_end(); f++) {
    if( (*f).color() == search_color ) { /* walk around f */
      pgon= walk_around(f);
      _result.push_back(I::Make_object(pgon) );
    }
  }

  /* Now we have found all possible polygons.
     Last but not least we have to search for edges and vertices, which
     have both colors, i.e. they are part of the intersection result.
  */

  
  Segment_2 *seg;
  for( e= dcel.begin(); e != dcel.end(); e++ ) { /* for_all_edges( edge e ) */
    if( is_unmarked(e)  && (*e).color() == search_color ) {
      seg= new Segment_2( dcel.point((*e).V1()), dcel.point((*e).V2()) );
      _result.push_back(I::Make_object(*seg) );
      mark( (*e).V1() );
      mark( (*e).V2() );
      delete seg;
    }
  }

  for(v= dcel.vertex_begin(); v != dcel.vertex_end(); v++) {
    if( is_unmarked(v) && (*v).color() == search_color )
       _result.push_back( I::Make_object(dcel.point(v)) );
  }
  
  return;
}



template<class I>
void CGAL_Bops_Simple_Polygons_2_Difference<I> :: perform(void)
{
  /* performs the DIFFERENCE algorithm on the colored DCEL */

  Polygon_2  pgon;
  /* handle special cases */
  switch( _pgon_intersection_type ) {
    case is_empty:
      _result.push_back(I::Make_object(_pgon1) );
      return;
    case is_identical:
    case A_is_subset_of_B:
      return;
    case B_is_subset_of_A:
      _result.push_back(I::Make_object(_pgon1) );
      I::reverse_orientation(_pgon2); // we found a hole
      _result.push_back(I::Make_object(_pgon2) );
      return;
    case is_intersection:
      break;
  }

  CGAL__Dcel_Color search_color(CGAL__RED);
  
  /* handle general case */
  edge_iterator e;
  vertex_iterator v;
  face_iterator f;

  for(f= dcel.face_begin(); f != dcel.face_end(); f++) {
    if( (*f).color() == search_color ) { /* walk around f */
      pgon= walk_around(f);
      _result.push_back(I::Make_object(pgon) );
    }
  }

  Segment_2 *seg;
  for( e= dcel.begin(); e != dcel.end(); e++ ) {
    if( is_unmarked(e)  && (*e).color() == search_color ) {
      seg= new Segment_2( dcel.point((*e).V1()), dcel.point((*e).V2()) );
      _result.push_back(I::Make_object(*seg) );
      mark( (*e).V1() );
      mark( (*e).V2() );
      delete seg;
    }
  }

  for(v= dcel.vertex_begin(); v != dcel.vertex_end(); v++) {
    if( is_unmarked(v) && (*v).color() == search_color )
       _result.push_back( I::Make_object(dcel.point(v)) );
  }
  
  return;
}


template<class I>
void CGAL_Bops_Simple_Polygons_2_Union<I> :: perform(void) 
{
  /* performs the UNION algorithm on the colored DCEL */

  /* handle special cases */
  switch( _pgon_intersection_type ) {
  case is_empty: /* empty intersection ==> return both polygons */
      _result.push_back(I::Make_object(_pgon1) );
      _result.push_back(I::Make_object(_pgon2) );
      return;
  case is_identical: /*  pgon1 == pgon2 */
      _result.push_back(I::Make_object(_pgon1) );
      return;
  case A_is_subset_of_B: /* pgon1 subset of pgon2, hence pgon1 is a hole */
      _result.push_back(I::Make_object(_pgon2) );
      I::reverse_orientation(_pgon1); /* we found a hole */
      _result.push_back(I::Make_object(_pgon1) );
      return;
  case B_is_subset_of_A: /* pgon2 subset of pgon1, hence pgon2 is a hole */
      _result.push_back(I::Make_object(_pgon1) );
      I::reverse_orientation(_pgon2); /* we found a hole */
      _result.push_back(I::Make_object(_pgon2) );
      return;
  case is_intersection:
      break;
  }


 typedef typename Polygon_2::Vertex_const_iterator polygon_vertex_iterator;

 polygon_vertex_iterator p1it = _pgon1.left_vertex();
 polygon_vertex_iterator p2it = _pgon2.left_vertex();
 polygon_vertex_iterator pit  = (*p1it).x() < (*p2it).x() ? p1it : p2it ;
 
 /* pt = ... the outmost to the left point of polygons A and B */
 Point_2 pt = *pit;
 vertex_iterator vit = dcel.find(pt);
 /* edgeE = ... the edge starting at vit with largest slope (and 
                                      thus on the outer boundary */
 edge_iterator lit, eit, ait= dcel.begin(vit);
 marked[(*ait).index()]= true;
 Point_2 pt1, pt2, pt3;
 lit = ait;
 for( eit= dcel.next(ait,vit); eit != ait; eit= dcel.next(eit, vit) ) {
    pt1= dcel.point(vit); 
    pt2= dcel.point((*eit).opposite_vertex(vit) ) ;
    pt3= dcel.point((*lit).opposite_vertex(vit) ) ;
    if( is_leftturn(pt1, pt3, pt2) ) lit = eit; 
  }

 /* faceF = ... the face of *lit without color */
 face_iterator faceFit= (*(*lit).F1()).color() == CGAL__UNCOLORED ?
                        (*lit).F1() : (*lit).F2();

 /* get the outer boundary */
 Polygon_2 pgon= walk_around(faceFit,false);
 _result.push_back(I::Make_object(pgon) );


 /* get the holes */
 for( eit= dcel.begin(); eit != dcel.end(); eit++ ) { /*for_all_edges(edge e)*/
    if( marked[(*eit).index()] == false ) {
       if( (*(*eit).F1()).color() ==  CGAL__UNCOLORED ) {
	   pgon = walk_around((*eit).F1(),false);
	   _result.push_back(I::Make_object(pgon) );
         }
       if( (*(*eit).F2()).color() ==  CGAL__UNCOLORED ) {
	   pgon= walk_around((*eit).F2(),false);
	   _result.push_back(I::Make_object(pgon) );
         }
      }
   }

  return;
}

#endif /* CGAL_BOPS_SIMPLE_POLYGONS_2_C */
