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
// file          : include/CGAL/bops_V2E_rep_out.h
// package       : bops (2.4)
// source        : include/CGAL/bops_V2E_rep_out.h
// revision      : $Revision: 1.1.1.1 $
// revision_date : $Date: 1999/10/11 13:50:31 $
// author(s)     : Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL__V2E_REP_OUT_H
#define CGAL__V2E_REP_OUT_H

CGAL_BEGIN_NAMESPACE 

#ifdef CGAL__V2E_REP_H
template<class vertex, class edge>
ostream& operator<<( ostream& o,
                     const _V2E_rep_base_type<vertex, edge>& v2e )
{
  _V2E_rep_base_type<vertex,edge>::header_const_iterator h_it;
  _V2E_rep_base_type<vertex,edge>::vertex_const_iterator v_it;

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

CGAL_END_NAMESPACE

#endif
