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
// file          : include/CGAL/IO/Polyhedron_geomview_ostream.h
// package       : Polyhedron_IO (3.11)
// chapter       : Support Library
//
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2001/12/17 12:40:57 $
//
// author(s)     : Lutz Kettner
// coordinator   : INRIA, Sophia Antipolis
//
// Output stream operator for Polyhedrons into Geomview_stream.
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_IO_POLYHEDRON_GEOMVIEW_OSTREAM_H
#define CGAL_IO_POLYHEDRON_GEOMVIEW_OSTREAM_H 1

#include <CGAL/IO/Geomview_stream.h>
#include <CGAL/IO/generic_print_polyhedron.h>
#include <CGAL/Polyhedron_3.h>

CGAL_BEGIN_NAMESPACE

class Polyhedron_writer_geomview {
    Geomview_stream*  out;
public:
    Polyhedron_writer_geomview( Geomview_stream& geo) : out(&geo) {}
    void write_header( std::ostream&, 
                       std::size_t vertices, 
                       std::size_t, 
                       std::size_t facets) {
        // ignore ostream. Output goes to Geomview_stream.
        // Print header.
        out->set_ascii_mode();
        *out << "(geometry " << out->get_new_id("polyhedron")
             << " {appearance {}{ ";
        out->set_binary_mode();
        *out << "OFF BINARY\n"  << int(vertices) << int(facets) << 0 ;
    }
    void write_footer() {
        *out << "}})";
        out->set_ascii_mode();
    }
    void write_vertex( const double& x, const double& y, const double& z) {
        *out << x << y << z;
    }
    void write_facet_header() {}
    void write_facet_begin( std::size_t no) { *out << int(no); }
    void write_facet_vertex_index( std::size_t index) { *out << int(index); }
    void write_facet_end() {
        double r = out->fcr(),
               g = out->fcg(),
               b = out->fcb();
        *out << 4 << r << g << b << 1.0;
    }
};


#ifdef CGAL_USE_POLYHEDRON_DESIGN_ONE
template < class Traits, class HDS >
Geomview_stream&
operator<<( Geomview_stream &gv, const Polyhedron_3<Traits,HDS> &P) {
#else // CGAL_USE_POLYHEDRON_DESIGN_ONE //
template < class Traits,
           class Items,
#ifndef CGAL_CFG_NO_TMPL_IN_TMPL_PARAM
           template < class T, class I, class A>
#endif
           class HDS, class Alloc>
Geomview_stream&
operator<<( Geomview_stream &gv,
            const Polyhedron_3<Traits,Items,HDS,Alloc> &P) {
#endif // CGAL_USE_POLYHEDRON_DESIGN_ONE //
    Polyhedron_writer_geomview  writer(gv);
    generic_print_polyhedron( std::cerr, P, writer); // note: cerr not used.
    return gv;
}

CGAL_END_NAMESPACE

#endif // CGAL_IO_POLYHEDRON_GEOMVIEW_OSTREAM_H //
// EOF //

