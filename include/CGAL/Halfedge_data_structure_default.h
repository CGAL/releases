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
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/Halfedge_data_structure_default.h
// package       : Halfedge_DS (2.8)
// chapter       : $CGAL_Chapter: Halfedge Data Structures $
// source        : hds.fw
// revision      : $Revision: 1.3 $
// revision_date : $Date: 1999/04/07 19:29:14 $
// author(s)     : Lutz Kettner
//
// coordinator   : MPI Saarbruecken (Stefan Schirra)
//
// Halfedge Data Structure Default Implementation for CGAL.
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_HALFEDGE_DATA_STRUCTURE_DEFAULT_H
#define CGAL_HALFEDGE_DATA_STRUCTURE_DEFAULT_H 1
#ifndef CGAL_HALFEDGE_DATA_STRUCTURE_BASES_H
#include <CGAL/Halfedge_data_structure_bases.h>
#endif

#ifndef CGAL_HALFEDGE_DATA_STRUCTURE_USING_LIST_H
#include <CGAL/Halfedge_data_structure_using_list.h>
#endif

CGAL_BEGIN_NAMESPACE

template <class Pt>
class Halfedge_data_structure_default
    : public Halfedge_data_structure_using_list<
          Vertex_max_base<Pt>, Halfedge_max_base, Facet_max_base> {
public:  // CREATION
    typedef typename   Halfedge_data_structure_using_list<
        Vertex_max_base<Pt>, Halfedge_max_base, Facet_max_base>::Size Size;
    Halfedge_data_structure_default() {}
    Halfedge_data_structure_default( Size v, Size h, Size f)
    : Halfedge_data_structure_using_list<
        Vertex_max_base<Pt>, Halfedge_max_base, Facet_max_base> (v,h,f) {}
};

CGAL_END_NAMESPACE
#endif // CGAL_HALFEDGE_DATA_STRUCTURE_DEFAULT_H //
// EOF //
