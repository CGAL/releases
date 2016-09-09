// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/IO/Polyhedron_geomview_ostream.h
// package       : Polyhedron_IO (2.5)
// revision      : $Revision: 1.3 $
// revision_date : $Date: 1999/03/09 22:18:32 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Output stream operator for Polyhedrons into Geomview_stream.
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_IO_POLYHEDRON_GEOMVIEW_OSTREAM_H
#define CGAL_IO_POLYHEDRON_GEOMVIEW_OSTREAM_H 1

#ifndef CGAL_IO_GEOMVIEW_STREAM_H
#include <CGAL/IO/Geomview_stream.h>
#endif // CGAL_IO_GEOMVIEW_STREAM_H
#ifndef CGAL_IO_GENERIC_PRINT_POLYHEDRON_H
#include <CGAL/IO/generic_print_polyhedron.h>
#endif // CGAL_IO_GENERIC_PRINT_POLYHEDRON_H
#ifndef CGAL_POLYHEDRON_3_H
#include <CGAL/Polyhedron_3.h>
#endif // CGAL_POLYHEDRON_3

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
        *out << "(geometry polyhedron  {appearance {}{ ";
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


template < class Traits, class HDS >
Geomview_stream&
operator<<( Geomview_stream &gv, const Polyhedron_3<Traits,HDS> &P) {
    Polyhedron_writer_geomview  writer(gv);
    generic_print_polyhedron( std::cerr, P, writer); // note: cerr not used.
    return gv;
}

CGAL_END_NAMESPACE

#endif // CGAL_IO_POLYHEDRON_GEOMVIEW_OSTREAM_H //
// EOF //

