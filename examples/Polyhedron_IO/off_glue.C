// ============================================================================
//
// Copyright (c) 1997 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------------
//
// release       : $CGAL_Revision: $
// release_date  : $CGAL_Date: $
//
// file          : off_glue.C
// package       : $CGAL_Package: Polyhedron_IO 1.9 (10 Jul 1998) $
// revision      : $Revision: 1.1 $
// revision_date : $Date: 1998/03/01 06:51:10 $
// author(s)     : Lutz Kettner  <kettner@@inf.ethz.ch>
//
// coordinator   : Herve Bronnimann  <Herve.Bronnimann@sophia.inria.fr>
//
// Glue vertices of a polyhedron together that have a distance
// less than 'epsilon' to each other.
// ============================================================================

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


/* main */
/* ==== */

#define MaxParameters          2
#define MaxOptionalParameters  2
#define ErrParameters          10000

typedef char Switch;

#define NO_SWITCH    0
#define MINUS_SWITCH 1
#define PLUS_SWITCH  2

Switch  dummy_switch = NO_SWITCH;
Switch  verbose      = NO_SWITCH;
Switch  binary       = NO_SWITCH;
Switch  skel         = NO_SWITCH;
Switch  noc          = NO_SWITCH;
double  epsilon      = 0.0;


/* this macro opens a block, in which the switch is detected */
/* it must be closed with the macro endDetect()              */
#define detectSwitch( var, text) \
    if ( (( argv[i][0] == '/' ) || ( argv[i][0] == '-' ) || \
	  ( argv[i][0] == '+' )) && ( strcmp( text, argv[i]+1) == 0)) { \
	if ( argv[i][0] == '+' ) \
	    var = PLUS_SWITCH; \
	else \
	    var = MINUS_SWITCH;

#define endDetect() \
	if ( nParameters <= MaxParameters ) \
	    continue; \
	else \
	    break; \
    }



/* >main: main function with standard unix parameter input */
/* ------------------------------------------------------- */

main( int argc, char **argv) {
    int i;
    int nParameters = 0;
    char *parameters[ MaxParameters + 1];

    Switch help_switch = NO_SWITCH;

    for (i = 1; i < argc; i++) {

	/* check switches */
	detectSwitch( verbose, "v");
	endDetect();
	detectSwitch( binary, "b");
	endDetect();
	detectSwitch( skel,   "skel");
	endDetect();
	detectSwitch( noc,    "noc");
	endDetect();
	detectSwitch( dummy_switch, "eps");
	    i++;
	    if ( i < argc) {
		epsilon = atof( argv[i]);
		if ( epsilon < 0) {
		    cerr << argv[0] << ": error: epsilon must be greater than "
			    " of equal to zero." << endl;
		    help_switch = MINUS_SWITCH;
		}
	    } else {
		cerr << argv[0] << ": error: -eps need a double parameter." 
		     << endl;
		help_switch = MINUS_SWITCH;
	    }
	endDetect();

	detectSwitch( help_switch, "h");
	endDetect();
	detectSwitch( help_switch, "H");
	endDetect();
	detectSwitch( help_switch, "help");
	endDetect();

	/* else get standard or optional parameters */
	if ( nParameters < MaxParameters ) {
	    parameters[nParameters ++] = argv[i];
	    continue;
	}
	nParameters = ErrParameters;
	break;
    }

    if ((nParameters < MaxParameters - MaxOptionalParameters) ||
	(nParameters > MaxParameters) || (help_switch != NO_SWITCH)) {
	if (help_switch == NO_SWITCH)
	    cerr << "Error: in parameter list" << endl;
	cerr << "Usage: " << argv[0] 
	     << " [<options>] [<infile> [<outfile>]]" << endl;
	cerr << "       glues vertices with distance less than epsilon "
	        "together." << endl;
	cerr << "       -b              binary output (default is ASCII)."
	     << endl;
	cerr << "       -skel           Geomview SKEL format." << endl;
	cerr << "       -noc            no comments in file." << endl;
	cerr << "       -eps <epsilon>  new value for epsilon. Default 0."
	     << endl;
	cerr << "       -v              verbose." << endl;
	exit(help_switch == NO_SWITCH);
    }

    if ( epsilon > 0) {
	cerr << "Sorry, epsilon > 0 not yet supported. Continue "
	        "with epsilon = 0." << endl;
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
    CGAL_File_writer_OFF  writer( binary, noc);
    writer.set_skel( skel);
    writer.header(*p_out, 
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
    writer.footer();
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

