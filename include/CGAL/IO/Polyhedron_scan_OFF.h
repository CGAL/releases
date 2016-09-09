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
// file          : include/CGAL/IO/Polyhedron_scan_OFF.h
// package       : Polyhedron_IO (3.9)
// chapter       : $CGAL_Chapter: Support Library ... $
// source        : polyhedron_io.fw
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2001/07/02 20:58:54 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Scanner for OFF as polyhedral surface builder
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_IO_POLYHEDRON_SCAN_OFF_H
#define CGAL_IO_POLYHEDRON_SCAN_OFF_H 1

#include <CGAL/basic.h>
#include <CGAL/IO/File_header_OFF.h>
#include <CGAL/IO/File_scanner_OFF.h>
#include <CGAL/Modifier_base.h>
#include <CGAL/Polyhedron_incremental_builder_3.h>
#include <CGAL/Polyhedron_3.h>
#include <iostream>
#include <cstddef>

CGAL_BEGIN_NAMESPACE

template < class HDS>
class Polyhedron_scan_OFF :  public Modifier_base<HDS> {
protected:
    std::istream&    m_in;
    File_header_OFF  m_file_header;
public:

    typedef HDS Halfedge_data_structure;

// DEFINITION
//
// Polyhedron_scan_OFF<Traits> is a polyhedral surface builder.
// It scans a polyhedron given in OFF from a stream and appends it
// incrementally using the incremental builder.

    Polyhedron_scan_OFF( std::istream& in, bool verbose = false)
        : m_in(in), m_file_header( verbose) {}

    // Activation
    void operator()( HDS& hds);

    const File_header_OFF&  header() const { return m_file_header; }
};

template < class HDS >
void
Polyhedron_scan_OFF<HDS>:: operator()( HDS& target) {
    File_scanner_OFF scanner( m_in, m_file_header.verbose());
    if ( ! m_in) {
        if ( scanner.verbose()) {
            std::cerr << " " << std::endl;
            std::cerr << "Polyhedron_scan_OFF<HDS>::" << std::endl;
            std::cerr << "operator(): input error: file format is not in "
                         "OFF." << std::endl;
        }
        return;
    }
    m_file_header = scanner;  // Remember file header after return.

    Polyhedron_incremental_builder_3<HDS> B( target, scanner.verbose());
    B.begin_surface( scanner.size_of_vertices(),
                     scanner.size_of_facets(),
                     scanner.size_of_halfedges());

#ifdef CGAL_USE_POLYHEDRON_DESIGN_ONE
    typedef typename HDS::Point Point;
#else // CGAL_USE_POLYHEDRON_DESIGN_ONE //
    typedef typename HDS::Traits     Traits;
    typedef typename Traits::Point_3 Point;
#endif // CGAL_USE_POLYHEDRON_DESIGN_ONE //

    // read in all vertices
    int  i;
    for ( i = 0; i < scanner.size_of_vertices(); i++) {
        Point p;
        file_scan_vertex( scanner, p);
        B.add_vertex( p);
        scanner.skip_to_next_vertex( i);
    }
    if ( ! m_in  || B.error()) {
        B.rollback();
        m_in.clear( std::ios::badbit);
        return;
    }

    // read in all facets
    for ( i = 0; i < scanner.size_of_facets(); i++) {
        B.begin_facet();
        Integer32 no;
        scanner.scan_facet( no, i);
        if( ! m_in || B.error() || no < 3) {
            if ( scanner.verbose()) {
                std::cerr << " " << std::endl;
                std::cerr << "Polyhedron_scan_OFF<Traits>::" << std::endl;
                std::cerr << "operator()(): input error: facet " << i
                     << " has less than 3 vertices." << std::endl;
            }
            B.rollback();
            m_in.clear( std::ios::badbit);
            return;
        }
        for ( int j = 0; j < no; j++) {
            Integer32 index;
            scanner.scan_facet_vertex_index( index, i);
            B.add_vertex_to_facet( index);
        }
        B.end_facet();
        scanner.skip_to_next_facet( i);
    }
    if ( ! m_in  || B.error()) {
        B.rollback();
        m_in.clear( std::ios::badbit);
        return;
    }
    if ( B.check_unconnected_vertices()) {
        if ( ! B.remove_unconnected_vertices()) {
            if ( scanner.verbose()) {
                std::cerr << " " << std::endl;
                std::cerr << "Polyhedron_scan_OFF<Traits>::" << std::endl;
                std::cerr << "operator()(): input error: cannot "
                             "succesfully remove isolated vertices."
                          << std::endl;
            }
            B.rollback();
            m_in.clear( std::ios::badbit);
            return;
        }
    }
    B.end_surface();
}

CGAL_END_NAMESPACE
#endif // CGAL_IO_POLYHEDRON_SCAN_OFF_H //
// EOF //
