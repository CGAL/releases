// ============================================================================
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
// file          : triangulation_print_OFF.h
// package       : $CGAL_Package: Polyhedron_IO 2.5 (29 Apr 1999) $
// revision      : $Revision: 1.5 $
// revision_date : $Date: 1999/03/09 22:18:32 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Print a Triangulation<Traits> with 3d points in object file format (OFF).
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_PRINT_OFF_H
#define CGAL_TRIANGULATION_PRINT_OFF_H 1

#ifndef CGAL_PROTECT_MAP
#include <map>
#define CGAL_PROTECT_MAP
#endif

CGAL_BEGIN_NAMESPACE

template < class Triang >
void
triangulation_print_OFF( std::ostream& out, 
			 const Triang& triang, 
			 bool binary  = false, 
			 bool noc     = false,
			 bool verbose = false) {
    CGAL_precondition( triang.is_valid());
    typedef typename Triang::Vertex           Vertex;
    typedef typename Triang::Vertex_iterator  Vertex_iterator;
    typedef typename Triang::Face_iterator    Face_iterator;
    // Build a map from vertex pointers to vertex indices.
    std::map<const Vertex*,std::size_t, less<const Vertex*> > mapping;
    std::size_t vn = 0;
    Vertex_iterator vi = triang.vertices_begin();
    for ( ; vi != triang.vertices_end(); ++vi) {
	CGAL_assertion( ! triang.is_infinite( vi));
	mapping[ &*vi] = vn;
	vn++;
    }
    CGAL_assertion( vn == std::size_t( triang.number_of_vertices()));

    // Count finite and infinite faces.
    std::size_t fn  = 0;
    Face_iterator fi = triang.faces_begin();
    for ( ; fi != triang.faces_end(); ++fi) {
	CGAL_assertion( ! triang.is_infinite( fi));
	fn++;
    }
    std::size_t fin = triang.number_of_faces() - fn;

    File_header_OFF  header( binary, noc, false, verbose);
    File_writer_OFF  writer( header);
    writer.write_header( out, vn, 3 * fn + fin, fn);

    vi = triang.vertices_begin();
    for ( ; vi != triang.vertices_end(); ++vi) {
	CGAL_assertion( ! triang.is_infinite( vi));
	writer.write_vertex( to_double(vi->point().x()),
			     to_double(vi->point().y()),
			     to_double(vi->point().z()));
    }
    writer.write_facet_header();

    fi = triang.faces_begin();
    while ( fn --) {
	writer.write_facet_begin( 3);
	CGAL_assertion( mapping.find(&*(fi->vertex(0))) != mapping.end());
	CGAL_assertion( mapping.find(&*(fi->vertex(1))) != mapping.end());
	CGAL_assertion( mapping.find(&*(fi->vertex(2))) != mapping.end());
	writer.write_facet_vertex_index( mapping[ &*(fi->vertex(0))]);
	writer.write_facet_vertex_index( mapping[ &*(fi->vertex(1))]);
	writer.write_facet_vertex_index( mapping[ &*(fi->vertex(2))]);
	writer.write_facet_end();
	++fi;
    }
    CGAL_assertion( fi == triang.faces_end());
    writer.write_footer();
}

CGAL_END_NAMESPACE

#endif // CGAL_TRIANGULATION_PRINT_OFF_H //
// EOF //

