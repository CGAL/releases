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


// Source: dcel_base.C
// Author: Wolfgang Freiseisen
 

#ifndef CGAL__DCEL_BASE_C
#define CGAL__DCEL_BASE_C

#ifndef CGAL_INCLUDE_TEMPLATE_CODE
#include <CGAL/bops_dcel_base.h>
#endif

#include <CGAL/bops_V2E_rep.h>


/*
typedef CGAL__V2E_rep_base_type<CGAL__Dcel_vertex,CGAL__Dcel_edge>
        V2E_rep_base_dcel;
*/

  void CGAL__Dcel_base ::
  construct_vertex_cycles( V2E_rep_base_dcel& v2e) {
    /* construction of vertex cycles */
    /* preconditions:
                vertex list _v_list is initialized: 
                edge   list _e_list is initialized: V1, V2
                vertex-to-edge representation is initialized and sorted
    */

    V2E_rep_base_dcel::header_iterator v1;
    V2E_rep_base_dcel::vertex_iterator v2, v2_begin;

    nc_vertex_iterator vtex;
    nc_edge_iterator e;
    CGAL__Dcel_edge_id  u;

    /* for all vertices v1 */
    for( v1= v2e.header_begin(); v1 != v2e.header_end(); v1++) {
      vtex= (nc_vertex_iterator)(*(*v1).vertex()).vertex();
      (*vtex)._degree= (*v1).size();

      /* for all vertices v2 in "v1-list" */
      v2_begin= v2e.vertex_begin(v1);
      (*vtex)._header= (*v2_begin).edge();
      for( v2= v2_begin; v2 != v2e.vertex_end(v2); v2= v2e.vertex_next(v2) )
      { /* edge [v1,v2] */
        e= (nc_edge_iterator)(*v2).edge();
        u= (*e).V1()==vtex ? EDGE_1 : EDGE_2;
        (*e).P(u)= (*v2e.vertex_next(v2)).edge(); 
      }
      (*e).P(u)= (*v2_begin).edge(); /* closing the circle */
      
    }
    return;
  }


  void CGAL__Dcel_base ::
  construct_face_cycles( void ) {
    /* construction of face cycles */
    /* preconditions:
          face list _f_list is not initialized, it will be cleared and filled
          edge list _e_list is initialized: V1, V2, P1, P2
    */

    int m= number_of_edges();
    nc_edge_iterator a= _e_list.begin();

    /* create face-list */
    int f= 2 + m - number_of_vertices();
    _f_list.erase(_f_list.begin(), _f_list.end());
    _f_list.reserve(f+1);
    for(int i= 0; i < f; i++)
      _f_list.push_back( CGAL__Dcel_face_type(i) ); 
    
    nc_face_iterator s= _f_list.begin();; 
    int k= 1; /* edge-counter */
  
    CGAL__Dcel_edge_id   u;

    while ( k<= 2*m ) {
      if( (*a).F1() != NULL && (*a).F2() != NULL )
        /* if F1(a) and F2(a) are set, then take next edge a */
        a++;
      else { /* at least one of F1(a) or F2(a) is not initialized */
        /* which face is not initialized ? -> u */
        u= (*a).F1() == NULL ? FACE_1 : FACE_2;

        /* initialize face and its header */
        k++;
        (*a).F(u)= s;
        (*s).header()= a;

        /* get the corresponding vertex */
        vertex_iterator c= (*a).V(u);
      
        /* initialize all unset faces by face s and vertex c */
        nc_edge_iterator e= a;
        for( e= (nc_edge_iterator)(*e).P(u); e != a; e= (nc_edge_iterator)(*e).P(u) ) {
          u= (*e).V1() == c  ? VERTEX_2 : VERTEX_1;
          /* initialize face Fu(e) */
          k++;
          (*e).F(u)= s;
          c= (*e).V(u); /* set (new) vertex */
        }
        s++;
      }
    } /* while */

    return;
  }

  
#endif /* CGAL__DCEL_C */
