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


// Source: V2E_rep_out.h
// Author: Wolfgang Freiseisen

#ifndef CGAL__V2E_REP_OUT_H
#define CGAL__V2E_REP_OUT_H


#ifdef CGAL__V2E_REP_H
template<class vertex, class edge>
ostream& operator<<( ostream& o,
                     const CGAL__V2E_rep_base_type<vertex, edge>& v2e )
{
  CGAL__V2E_rep_base_type<vertex,edge>::header_const_iterator h_it;
  CGAL__V2E_rep_base_type<vertex,edge>::vertex_const_iterator v_it;

  for( h_it= v2e.header_begin(); h_it != v2e.header_end(); h_it++) {
    v_it= (*h_it).vertex();
    o << "this-index= " << (*v_it).index()
      << " size= " << (*h_it).size() << endl;

    for( v_it= v2e.vertex_begin(h_it); v_it != v2e.vertex_end(v_it);
         v_it= v2e.vertex_next(v_it) ) {
      o << "       "
        << "index= " << (*v_it).index()
        << ", vertex= " << *(*v_it).vertex()
        << ", next= " << (*v_it).next()
        << ", T_vertex= " << (*v_it).vertex()
        << ", T_edge= " << (*v_it).edge()
        << endl;
    }
  }

  o << endl << " LIST" << endl;
  int i= 0;
  for( v_it= v2e.vertex_begin(); v_it != v2e.vertex_end(); v_it++) {
      o << i++ << " | "
        << "index= " << (*v_it).index()
        << ", vertex= " << *((*v_it).vertex())
        << ", next= " << (*v_it).next() 
        << endl;
  }
  return o;
}
#endif

#endif
