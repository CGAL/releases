// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/IO/print_OFF.h
// package       : Polyhedron_IO (3.9)
// chapter       : $CGAL_Chapter: Support Library ... $
// source        : polyhedron_io.fw
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2001/07/02 20:58:55 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Print a Polyhedron_3 in object file format (OFF)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_IO_PRINT_OFF_H
#define CGAL_IO_PRINT_OFF_H 1

#include <CGAL/basic.h>
#include <CGAL/IO/File_writer_OFF.h>
#include <CGAL/IO/generic_print_polyhedron.h>
#include <CGAL/Polyhedron_3.h>
#include <iostream>

CGAL_BEGIN_NAMESPACE

#ifdef CGAL_USE_POLYHEDRON_DESIGN_ONE
template <class Traits, class HDS>
void
print_OFF( std::ostream& out,
           const Polyhedron_3<Traits,HDS>& P,
           bool verbose = false) {
#else // CGAL_USE_POLYHEDRON_DESIGN_ONE //
template < class Traits,
           class Items,
#ifndef CGAL_CFG_NO_TMPL_IN_TMPL_PARAM
           template < class T, class I, class A>
#endif
           class HDS, class Alloc>
void
print_OFF( std::ostream& out,
           const Polyhedron_3<Traits,Items,HDS,Alloc>& P,
           bool verbose = false) {
#endif // CGAL_USE_POLYHEDRON_DESIGN_ONE //
    File_writer_OFF  writer( verbose);
    writer.header().set_binary( is_binary( out));
    writer.header().set_no_comments( ! is_pretty( out));
    writer.header().set_polyhedral_surface( true);
    writer.header().set_halfedges( P.size_of_halfedges());
    generic_print_polyhedron( out, P, writer);
}

#ifdef CGAL_USE_POLYHEDRON_DESIGN_ONE
template <class Traits, class HDS>
void
print_OFF( std::ostream& out,
           const Polyhedron_3<Traits,HDS>& P,
           const File_header_OFF& header) {
#else // CGAL_USE_POLYHEDRON_DESIGN_ONE //
template < class Traits,
           class Items,
#ifndef CGAL_CFG_NO_TMPL_IN_TMPL_PARAM
           template < class T, class I, class A>
#endif
           class HDS, class Alloc>
void
print_OFF( std::ostream& out,
           const Polyhedron_3<Traits,Items,HDS,Alloc>& P,
           const File_header_OFF& header) {
#endif // CGAL_USE_POLYHEDRON_DESIGN_ONE //
    File_writer_OFF  writer( header);
    writer.header().set_polyhedral_surface( true);
    writer.header().set_halfedges( P.size_of_halfedges());
    generic_print_polyhedron( out, P, writer);
}

CGAL_END_NAMESPACE
#endif // CGAL_IO_PRINT_OFF_H //
// EOF //
