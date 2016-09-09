/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/


// Source: bops_simple_polygons_2.C 
// Author: Wolfgang Freiseisen
// Last Change by: Carl Van Geem
//                 (CGAL_union on simple polygons added)
 
#ifndef CGAL_BOPS_SIMPLE_POLYGONS_2_C
#define CGAL_BOPS_SIMPLE_POLYGONS_2_C

#ifndef CGAL_INCLUDE_TEMPLATE_CODE
#include<CGAL/bops_simple_polygons_2.h>
#endif

template <class R, class Polygon_Container>
int CGAL_Bops_Simple_Polygons_2< R, Polygon_Container>::
calc_intersection_type(void) const {

  /* intersection types: 
     0 empty
     1 identical
     2 A_subset_of_B
     3 B_subset_of_A
     4 intersection
  */

     CGAL_Bbox_2 a_box= _pgon1.bbox();
     CGAL_Bbox_2 b_box= _pgon2.bbox();

     if( a_box == b_box ) return 1;
     if( !CGAL_do_overlap(a_box, b_box) ) return 0;

     if( b_box.xmin() <= a_box.xmin() && b_box.xmax() >= a_box.xmax() && 
         b_box.ymin() <= a_box.ymin() && b_box.ymax() >= a_box.ymax() )
       return 2;

     if( a_box.xmin() <= b_box.xmin() && a_box.xmax() >= b_box.xmax() && 
         a_box.ymin() <= b_box.ymin() && a_box.ymax() >= b_box.ymax() )
       return 3;

     Polygon_Container::const_iterator it;
     int sum1= 0, n1= _pgon1.size();
     for( it= _pgon1.vertices_begin(); it != _pgon1.vertices_end(); it++)
       sum1 += _pgon2.has_on_bounded_side(*it) ? +1 : -1;

     if( sum1 ==  n1 || sum1 == -n1 ) {
       int sum2= 0, n2= _pgon2.size();
       for( it= _pgon2.vertices_begin(); it != _pgon2.vertices_end(); it++)
         sum2 += _pgon1.has_on_bounded_side(*it) ? +1 : -1;
       if( sum2 ==  n2|| sum2 == -n2) {
         if( sum1 == -n1 && sum2 == -n2 ) // polygons are separated
           // iff no intersections occur, otherwise return 4
           return !_inter_res.size() ? 0 : 4;
         if( sum1 == n1 && sum2 == -n2 ) // A is subset B
           return 2; 
         if( sum1 == -n1 && sum2 == n2 ) // B is subset A
           return 3; 
       }
     }

     return 4; // intersections occur
}



#if 0
// does not work with g++

template <class R, class Polygon_Container>
int CGAL_Bops_Simple_Polygons_2< R, Polygon_Container>::
walk_around(face_iterator face, list<Point_2>& result) const {
  /*
     traverses a face in the DCEL and puts the vertices as points in
     into a list. These points define a polygon.
     Additionally, the visited edges will be marked in the marked-vector.
     The size of the marked-vector should be at least the number of edges
     in the DCEL, i.e. marked.size() >= dcel.number_of_edges
     (The result is always be ordered clockwise.)
  */

  int n= 0;
  vertex_iterator v0, v; 
  edge_iterator e, a= dcel.begin(face);
  mark((*a).index());
  v0= ((*a).F1() == face) ? (*a).V1() : (*a).V2();
  result.push_back(dcel.point(v0)); n++;
  for( e= dcel.next(a,face); e != a; e= dcel.next(e, face) )
  {
    mark((*e).index());
    v= (*e).opposite_vertex( v0 );
    result.push_back(dcel.point(v)); n++;
    v0= v;
  }

  return n;
}

template<class R, class Polygon_Container>
Polygon_2 CGAL_Bops_Simple_Polygons_2 < R > ::
walk_around( face_iterator face ) const {
  /*
     traverses a face in the DCEL and puts the vertices as points in
     into a polygon.
     Additionally, the visited edges will be marked in the marked-vector.
     The size of the marked-vector should be at least the number of edges
     in the DCEL, i.e. marked.size() >= dcel.number_of_edges
   */
  Polygon_2  polygon();

  vertex_iterator v0, v; 
  edge_iterator e, a= dcel.begin(face);
  marked[(*a).index()]= true;
  polygon.append(dcel.point((*a).V1()));
  v0= (*a).V2();
  for( e= dcel.next(a,face); e != a; e= next(e, face) )
  {
    marked[(*e).index()]= true;
    v= (*e).opposite_vertex( v0 );
    polygon.append(dcel.point(v));
    v0= v;
  }

  return polygon;
}
#endif



template<class R, class Polygon_Container>
void CGAL_Bops_Simple_Polygons_2_Intersection< R, Polygon_Container > ::
perform(void)
{
  /* performs the intersection algorithm on the colored DCEL */

  /* handle special cases */
  switch( _pgon_intersection_type ) {
    case 0:
      return;
    case 1:
    case 2:
      _result.push_back(CGAL_make_object(_pgon1) );
      return;
    case 3:
      _result.push_back(CGAL_make_object(_pgon2) );
      return;
  }

  CGAL__Dcel_Color search_color(CGAL__RED_AND_BLACK);
  
  /* handle general case */
  list<edge_iterator>::iterator eit;
  list<edge_iterator> elist;

  edge_iterator e;
  vertex_iterator v;
  Polygon_2  pgon;
  bool visit_vertex;

  /* for_all_vertices( vertex v ) */
  for(v= dcel.vertex_begin(); v != dcel.vertex_end(); v++)
    if( (*v).degree() > 2 ) { /* find unmarked edge */
      elist= dcel.get_all_edges( v );

      for( eit= elist.begin(); eit != elist.end(); eit++ ) {
        e=(*eit);
        if( is_unmarked(e) ) {
          mark(e);
          visit_vertex= true;
          if( (*(*e).F1()).color() == search_color ) {
            /* walk around F1 */
            pgon= walk_around((*e).F1());
            _result.push_back(CGAL_make_object(pgon) );
            visit_vertex= false;
          }
          if( (*(*e).F2()).color() == search_color ) {
            /* walk around F2 */
            pgon= walk_around((*e).F2());
            _result.push_back(CGAL_make_object(pgon) );
            visit_vertex= false;
          }
          if(  visit_vertex ) {
            if( (*e).color() == search_color )
	      unmark(e);
            if( (*(*e).V1()).color() != search_color )
              mark( (*e).V1() );
            if( (*(*e).V2()).color() != search_color )
              mark( (*e).V2() );
          }
        }
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
      _result.push_back(CGAL_make_object(*seg) );
      mark( (*e).V1() );
      mark( (*e).V2() );
      delete seg;
    }
  }

  for(v= dcel.vertex_begin(); v != dcel.vertex_end(); v++) {
    if( is_unmarked(v) && (*v).color() == search_color )
       _result.push_back( CGAL_make_object(dcel.point(v)) );
  }
  
  return;
}



template<class R, class Polygon_Container>
void CGAL_Bops_Simple_Polygons_2_Difference< R, Polygon_Container > ::
perform(void)
{
  /* performs the DIFFERENCE algorithm on the colored DCEL */

  Polygon_2  pgon;
  /* handle special cases */
  switch( _pgon_intersection_type ) {
    case 0:
      _result.push_back(CGAL_make_object(_pgon1) );
      return;
    case 1:
    case 2:
      return;
    case 3:
      _result.push_back(CGAL_make_object(_pgon1) );
      _pgon2.reverse_orientation(); // we found a hole
      _result.push_back(CGAL_make_object(_pgon2) );
      return;
  }

  CGAL__Dcel_Color search_color(CGAL__RED);
  
  /* handle general case */
  edge_iterator e;
  vertex_iterator v;
  face_iterator f;

  for(f= dcel.face_begin(); f != dcel.face_end(); f++) {
    if( (*f).color() == search_color ) { /* walk around f */
      pgon= walk_around(f);
      _result.push_back(CGAL_make_object(pgon) );
    }
  }

  Segment_2 *seg;
  for( e= dcel.begin(); e != dcel.end(); e++ ) {
    if( is_unmarked(e)  && (*e).color() == search_color ) {
      seg= new Segment_2( dcel.point((*e).V1()), dcel.point((*e).V2()) );
      _result.push_back(CGAL_make_object(*seg) );
      mark( (*e).V1() );
      mark( (*e).V2() );
      delete seg;
    }
  }

  for(v= dcel.vertex_begin(); v != dcel.vertex_end(); v++) {
    if( is_unmarked(v) && (*v).color() == search_color )
       _result.push_back( CGAL_make_object(dcel.point(v)) );
  }
  
  return;
}


template< class R, class Polygon_Container >
void CGAL_Bops_Simple_Polygons_2_Union< R, Polygon_Container >::perform(void) 
{
  /* performs the UNION algorithm on the colored DCEL */

  /* handle special cases */
  switch( _pgon_intersection_type ) {
    case 0: // empty intersection ==> return both polygons
      _result.push_back(CGAL_make_object(_pgon1) );
      _result.push_back(CGAL_make_object(_pgon2) );
      return;
    case 1: //  pgon1 == pgon2
      _result.push_back(CGAL_make_object(_pgon1) );
      return;
    case 2: // pgon1 subset of pgon2, hence pgon1 is a hole 
      _result.push_back(CGAL_make_object(_pgon2) );
      _pgon1.reverse_orientation(); // we found a hole
      _result.push_back(CGAL_make_object(_pgon1) );
      return;
    case 3: // pgon2 subset of pgon1, hence pgon2 is a hole 
      _result.push_back(CGAL_make_object(_pgon1) );
      _pgon2.reverse_orientation(); // we found a hole
      _result.push_back(CGAL_make_object(_pgon2) );
      return;
  }

 /* pt = ... the outmost to the left point of polygons A and B */
 Polygon_2::Vertex_const_iterator p1it;
 Polygon_2::Vertex_const_iterator p2it;
 Polygon_2::Vertex_const_iterator pit; 
 Point_2 pt ;
 Point_2 pt1 ;
 Point_2 pt2 ;
 Point_2 pt3 ;
 vertex_iterator vit ;

 p1it = _pgon1.left_vertex();
 p2it = _pgon2.left_vertex();
 pit  = ( (*p1it).x() < (*p2it).x() ) ? p1it : p2it ;
 pt = *pit;
 vit = dcel.find(pt);
 /* edgeE = ... the edge starting at vit with largest slope (and 
                                      thus on the outer boundary */
 edge_iterator lit, eit, ait= dcel.begin(vit);
 marked[(*ait).index()]= true;
 lit = ait;
 for( eit= dcel.next(ait,vit); eit != ait; eit= dcel.next(eit, vit) )
  {
    pt1= dcel.point(vit); 
    pt2= dcel.point((*eit).opposite_vertex(vit) ) ;
    pt3= dcel.point((*lit).opposite_vertex(vit) ) ;

    if ((pt3-pt1).direction() <  (pt2-pt1).direction() ) 
      lit = eit; 
  }

 /* faceF = ... the face of *lit without color */
 face_iterator faceFit;
 if ((*(*lit).F1()).color() == CGAL__UNCOLORED)
   faceFit = (*lit).F1();
 else
   faceFit = (*lit).F2();

 /* the outer boundary */
 Polygon_2 pgon;

 pgon= walk_around(faceFit,false);
 _result.push_back(CGAL_make_object(pgon) );


/* the holes */
	
/* bool found_a_hole = false;	*/
 for( eit= dcel.begin(); eit != dcel.end(); eit++ ) /*for_all_edges(edge e)*/
  {
    if( marked[(*eit).index()] == false ) 
      {
       if( (*(*eit).F1()).color() ==  CGAL__UNCOLORED )
         {
	   pgon = walk_around((*eit).F1(),false);
	   _result.push_back(CGAL_make_object(pgon) );
/*	   found_a_hole = true; */
         }
       if( (*(*eit).F2()).color() ==  CGAL__UNCOLORED )
         {
	   pgon= walk_around((*eit).F2(),false);
	   _result.push_back(CGAL_make_object(pgon) );
/*	   found_a_hole = true;*/
         }
      }
   }

/* if (( _result.size() == 0 ) && (found_a_hole))
            {the result contains two non-intersecting polygons.}*/

 return;
}

#endif /* CGAL_BOPS_SIMPLE_POLYGONS_2_C */
