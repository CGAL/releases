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
// file          : include/CGAL/IO/Polyhedron_geomview_ostream.h
// package       : Polyhedron_IO (1.11)
// revision      : $Revision: 1.1 $
// revision_date : $Date: 1998/03/03 02:31:42 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Output stream operator for Polyhedrons into Geomview_stream.
//
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

class CGAL_Polyhedron_writer_geomview {
    CGAL_Geomview_stream*  out;
public:
    CGAL_Polyhedron_writer_geomview( CGAL_Geomview_stream& geo) : out(&geo) {}
    void write_header( ostream&, size_t vertices, size_t, size_t facets) {
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
    void write_facet_begin( size_t no) {
	*out << int(no);
    }
    void write_facet_vertex_index( size_t index) {
	*out << int(index);
    }
    void write_facet_end() {
	double r = out->fcr(),
	       g = out->fcg(),
	       b = out->fcb();
	*out << 4 << r << g << b << 1.0;
    }
};


template < class Traits, class HDS >
CGAL_Geomview_stream&
operator<<( CGAL_Geomview_stream &gv,
	    const CGAL_Polyhedron_3<Traits,HDS> &P)
{
    CGAL_Polyhedron_writer_geomview  writer(gv);
    CGAL_generic_print_polyhedron( cerr, P, writer); // note: cerr unused.
    return gv;
}


#endif // CGAL_IO_POLYHEDRON_GEOMVIEW_OSTREAM_H //
// EOF //

