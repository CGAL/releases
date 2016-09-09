// ============================================================================
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
// file          : off_glue.C
// package       : $CGAL_Package: Polyhedron_IO 1.11 (17 Dec 1998) $
// revision      : $Revision: 1.1 $
// revision_date : $Date: 1998/03/01 06:51:10 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Glue vertices of a polyhedron together that have equal coordinate values.
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#include <CGAL/basic.h>

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <iostream.h>
#include <fstream.h>

#include <CGAL/Cartesian.h>
#include <CGAL/Vector_3.h>
#include <CGAL/Point_3.h>
#include <CGAL/IO/Verbose_ostream.h>
#include <CGAL/IO/File_scanner_OFF.h>
#include <CGAL/IO/File_writer_OFF.h>

#include <vector.h>
#include <algo.h>


typedef  CGAL_Vector_3< CGAL_Cartesian<float> >       Vector;
typedef  CGAL_Point_3< CGAL_Cartesian<float> >        Point;
struct   Vertex {
    Point   point;
    Vector  normal;
    int     index;
};
typedef  vector<Vertex>           Vertex_vector;
typedef  Vertex_vector::iterator  VIterator;

struct   VertexComp {
    bool operator()( const Vertex* v, const Vertex* w) const {
	return ( v->point.x() < w->point.x() ||
	    (v->point.x() == w->point.x() && v->point.y() < w->point.y()) ||
	    (v->point.x() == w->point.x() && (v->point.y() == w->point.y() 
					   && v->point.z() < w->point.z())));
    }
};

#define MaxParameters          2
#define MaxOptionalParameters  2
#define ErrParameters          10000

bool  verbose = false;
bool  binary  = false;
bool  skel    = false;
bool  noc     = false;

// main function with standard unix commandline arguments
// ------------------------------------------------------
int main( int argc, char **argv) {
    int i;
    int nParameters = 0;
    char *parameters[ MaxParameters + 1];

    bool help = false;

    for (i = 1; i < argc && nParameters <= MaxParameters; i++) {
	// check commandline options
	if ( strcmp( "-v", argv[i]) == 0)
	    verbose = true;
	else if ( strcmp( "-b", argv[i]) == 0)
	    binary = true;
	else if ( strcmp( "-skel", argv[i]) == 0)
	    skel = true;
	else if ( strcmp( "-noc", argv[i]) == 0)
	    noc = true;
	else if ( (strcmp( "-h", argv[i]) == 0) || 
		  (strcmp( "-help", argv[i]) == 0))
	    help = true;
	// else parse mandatory or optional commandline arguments
	else if ( nParameters < MaxParameters ) {
	    parameters[nParameters ++] = argv[i];
	} else 
	    nParameters = ErrParameters;
    }
    if ((nParameters < MaxParameters - MaxOptionalParameters) ||
	(nParameters > MaxParameters) || help) {
	if ( ! help)
	    cerr << "Error: in parameter list" << endl;
	cerr << "Usage: " << argv[0] 
	     << " [<options>] [<infile> [<outfile>]]" << endl;
	cerr << "       glues vertices of equal coordinates together." << endl;
	cerr << "       -b              binary output (default is ASCII)."
	     << endl;
	cerr << "       -skel           Geomview SKEL format." << endl;
	cerr << "       -noc            no comments in file." << endl;
	cerr << "       -v              verbose." << endl;
	exit( ! help);
    }

    CGAL_Verbose_ostream vout( verbose);
    vout << argv[0] << ": verbosity on." << endl;

    const char*  name = "<cin>";
    istream*     p_in = &cin;
    ifstream     in;
    if ( nParameters > 0) {
        in.open( parameters[ 0]);
        p_in = &in;
        name = parameters[0];
    }
    if ( !in) { 
        cerr << argv[0] << ": error: cannot open file '"<< name
         << "' for reading." <<endl;
	exit( 1);
    }

    CGAL_File_scanner_OFF  scanner( * p_in);
    if ( ! (*p_in)) {
	cerr << " " << endl;
	cerr << argv[0] << ": input error: file format is not in OFF." << endl;
	abort();
    }
    Vertex_vector            vertices;
    vector<Vertex*>          sorted_vertices;
    // Avoid any reallocation
    vertices.reserve(        scanner.size_of_vertices());
    sorted_vertices.reserve( scanner.size_of_vertices());

    float x, y, z;
    for ( i = 0; i < scanner.size_of_vertices(); i++) {
	Vertex  vertex;
	scanner.scan_vertex( x, y, z);
	vertex.point = Point( x, y, z);
	//scanner.scan_normal( x, y, z);
	vertex.normal = Vector( x, y, z);
	scanner.skip_to_next_vertex( i);
	vertex.index = -1;
	vertices.push_back( vertex);
	sorted_vertices.push_back( & vertices.back());
    }
    vout << scanner.size_of_vertices() << " vertices read." << endl;

    sort( sorted_vertices.begin(), sorted_vertices.end(), VertexComp());
    int current_index = 0;
    sorted_vertices[0]->index = 0;
    for ( i = 1; i < scanner.size_of_vertices(); i++) {
	if ( sorted_vertices[i]->point != sorted_vertices[i-1]->point)
	    current_index++;
	sorted_vertices[i]->index = current_index;
    }
    current_index++;
    vout << "Merged to " << current_index << " vertices." << endl;


    const char*  oname    = "<cout>";
    ostream*     p_out = &cout;
    ofstream     out;
    if ( nParameters > 1) {
	out.open( parameters[ 1]);
	p_out = &out;
	oname = parameters[1];
    }
    if ( !*p_out) { 
	cerr << argv[0] << ": error: cannot open file '"<< oname
	     << "' for writing." <<endl;
	exit( 1);
    }

    vout << "CGAL_File_writer_OFF( " << (binary ? ", binary" : ", ASCII") 
	 << ") ...." << endl;
    CGAL_File_header_OFF  header( binary, noc, skel, verbose);
    CGAL_File_writer_OFF  writer( header);
    writer.write_header(*p_out, 
			current_index, 
			0, 
			scanner.size_of_facets(), 
			scanner.has_normals());
    vector<Vertex*>::iterator v = sorted_vertices.begin();
    writer.write_vertex((*v)->point.x(), (*v)->point.y(), (*v)->point.z());
    if ( scanner.has_normals()) {
	writer.write_normal((*v)->normal.x(), 
			    (*v)->normal.y(), 
			    (*v)->normal.z());
    }
    ++v;
    for ( ; v != sorted_vertices.end(); ++v) {
	if ( (*v)->index != (*(v-1))->index) {
	    writer.write_vertex( (*v)->point.x(), 
				 (*v)->point.y(), 
				 (*v)->point.z());
	    if ( scanner.has_normals()) {
		writer.write_normal( (*v)->normal.x(), 
				     (*v)->normal.y(), 
				     (*v)->normal.z());
	    }
	}
    }

    // Copy facets and translate vertex indices.
    writer.write_facet_header();
    for ( i = 0; i < scanner.size_of_facets(); i++) {
	int no;  // number of vertices of a facet.
	scanner.scan_facet( no, i);
	writer.write_facet_begin( no);
	for ( int j = 0; j < no; j++) {
	    int index;
	    scanner.scan_facet_vertex_index( index, i);
	    writer.write_facet_vertex_index(  vertices[index].index);
	}
	scanner.skip_to_next_facet( i);
	writer.write_facet_end();
    }
    writer.write_footer();
    vout << "    .... done." << endl;

    if ( ! * p_in) { 
        cerr << argv[0] << " read error: while reading file '"<< name << "'." 
             << endl;
        exit( 1);
    }
    if ( !*p_out) { 
	cerr << argv[0] << " write error: while writing file '"<< oname 
	     << "'."  << endl;
	exit( 1);
    }
    return 0;
}

// EOF //

