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
// file          : include/CGAL/bops_V2E_rep_out.h
// package       : bops (1.1.2)
// source        : include/CGAL/bops_V2E_rep_out.h
// revision      : $Revision: 1.1.2 $
// revision_date : $Date: Wed Dec  9 13:28:48 MET 1998  $
// author(s)     :             Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

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
