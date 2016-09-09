// ============================================================================
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
// file          : examples/Polyhedron_IO/triangulation_print_OFF.h
// package       : $CGAL_Package: Polyhedron_IO 2.11 (04 Feb 2000) $
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2001/06/29 06:24:56 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Print a Triangulation<Traits> with 3d points in object file format (OFF).
// email         : contact@cgal.org
// www           : http://www.cgal.org
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
    std::map<const Vertex*,std::size_t, std::less<const Vertex*> > mapping;
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

