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
// file          : iv2off.C
// package       : $CGAL_Package: Polyhedron_IO 1.9 (10 Jul 1998) $
// revision      : $Revision: 1.1 $
// revision_date : $Date: 1998/03/01 06:51:10 $
// author(s)     : Lutz Kettner  <kettner@@inf.ethz.ch>
//
// coordinator   : Herve Bronnimann  <Herve.Bronnimann@sophia.inria.fr>
//
// Converts Geometry Information in Inventor files (*.iv) into OFF format. 
// The scanner triggers on Coordinate3, IndexedFaceSet, and IndexedLineSet
// keywords. It does not recognize transformations nor groups.
// ============================================================================

#include <CGAL/basic.h>

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <iostream.h>
#include <fstream.h>
#include <list.h>

#include <CGAL/Cartesian.h>
#include <CGAL/Point_3.h>
#include <CGAL/IO/Verbose_ostream.h>
#include <CGAL/IO/File_writer_OFF.h>

typedef  CGAL_Point_3< CGAL_Cartesian<float> >   Point;
typedef  list<Point>                             Point_list;
typedef  list<int>                               Facet;
typedef  list<Facet>                             Facet_list;


/* Command line parameter */
/* ====================== */

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
Switch  block        = NO_SWITCH;
int     n_block      = 0;


/* Global data describing the object */
/* ================================= */
Point_list  points;
Facet_list  facets;


/* iv File Scanner        */
/* ====================== */
void iv_file_scanner( istream& in) {
    int     offset    = 0;    // offset for the Index....Set
    char    c;                // one read character (comment, vertex, or facet)
    char    str[2000];        // temporal storage for rest of identifier
    int     blocks    = 0;    // Number of blocks found.

    CGAL_Verbose_ostream vout( verbose);
    in >> str;
    while( in) {
        if ( strcmp( str, "label") == 0) {
	    in >> str;
	    vout << "Label " << str << " found." << endl;
	    in >> str;
	}
        if ( strcmp( str, "Coordinate3") == 0) {
	    in >> c;
	    if ( c == '{') {
	        in >> str;
		if ( strcmp( str, "point") == 0) {
		    vout << "\"Coordinate3 { point\" block found." << endl;
		    blocks ++;
		    if ( ! block || n_block == blocks) {
			if ( block)
			    vout << "    this block is read." << endl;
			// point coordinate list starts here
			offset = points.size();
			in >> c;
			CGAL_assertion( c == '[');
			in >> c;
			while ( in && ( c != ']')) {
			    in.putback( c);
			    Point p;
			    in >> p;
			    points.push_back( p);
			    in >> c;  // comma or ']' or digit
			    if ( c == ',')
				in >> c;   // ignoring commas
			}
			vout << "    " << points.size() - offset 
			     << " point coordinates read." << endl;
		    }
		}
	    }
	}
	if ( block && n_block != blocks) {
	    in >> str;
	    continue;
	}

        if ( strcmp( str, "IndexedFaceSet") == 0) {
	    in >> c;
	    if ( c == '{') {
	        in >> str;
		if ( strcmp( str, "coordIndex") == 0) {
		    vout << "\"IndexedFaceSet { coordIndex\" block found." 
			 << endl;
		    // indices start here
		    int face_offset = facets.size();
		    in >> c;
		    CGAL_assertion( c == '[');
		    facets.push_back( Facet());
		    Facet* facet = &facets.back();
		    in >> c;
		    while ( in && ( c != ']')) {
			in.putback( c);
			int index;
		        in >> index;
			if ( index >= 0) {
			    facet->push_back( index + offset);
			} else {
			    facets.push_back( Facet());
			    facet = &facets.back();
			}
			in >> c;  // comma or ']' or digit
			if ( c == ',')
			    in >> c;   // ignoring commas
		    }
		    facets.pop_back();
		    vout << "    " << facets.size() - face_offset 
			 << " facets read." << endl;
		}
	    }
	}
        if ( strcmp( str, "IndexedLineSet") == 0) {
	    in >> c;
	    if ( c == '{') {
	        in >> str;
		if ( strcmp( str, "coordIndex") == 0) {
		    vout << "\"IndexedLineSet { coordIndex\" block found." 
			 << endl;
		    // indices start here
		    int face_offset = facets.size();
		    in >> c;
		    CGAL_assertion( c == '[');
		    facets.push_back( Facet());
		    Facet* facet = &facets.back();
		    in >> c;
		    while ( in && ( c != ']')) {
			in.putback( c);
			int index;
		        in >> index;
			if ( index >= 0) {
			    facet->push_back( index + offset);
			} else {
			    facets.push_back( Facet());
			    facet = &facets.back();
			}
			in >> c;  // comma or ']' or digit
			if ( c == ',')
			    in >> c;   // ignoring commas
		    }
		    facets.pop_back();
		    vout << "    " << facets.size() - face_offset 
			 << " polylines read." << endl;
		}
	    }
	}
	in >> str;
    }
    vout << endl;
    vout << "Total number of vertices: " << points.size() << endl;
    vout << "Total number of faces   : " << facets.size() << endl;
    vout << "Total number of blocks  : " << blocks << endl << endl;
}

/* OFF File Writer        */
/* ====================== */
void print_OFF( ostream& out) {
    CGAL_File_writer_OFF  writer( binary, noc);
    writer.set_skel( skel);
    writer.header( out, points.size(), 0, facets.size());
    while( ! points.empty()) {
	writer.write_vertex( points.front().x(),
			     points.front().y(), 
			     points.front().z());
	points.pop_front();
    }
    writer.write_facet_header();
    while( ! facets.empty()) {
	Facet& facet = facets.front();
	writer.write_facet_begin( facet.size());
	while( ! facet.empty()) {
	    writer.write_facet_vertex_index( facet.front());
	    facet.pop_front();
	}
	writer.write_facet_end();
	facets.pop_front();
    }
    writer.footer();
}


/* main */
/* ==== */

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
	detectSwitch( block,    "#");
	    i++;
	    if ( i < argc) {
		n_block = atoi( argv[i]);
		if ( n_block < 0) {
		    cerr << argv[0] << ": error: <i> must be greater than "
			    " zero." << endl;
		    help_switch = MINUS_SWITCH;
		}
	    } else {
		cerr << argv[0] << ": error: -# needs an integer parameter." 
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

	/* else get standard or optional paramters */
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
	cerr << "Usage: " << argv[0] << " [<options>] [<infile>]" << endl;
	cerr << "       converts an Inventor file to OFF." << endl;
	cerr << "       -# <i>  convert only i-th block (i in 1..n)." << endl;
	cerr << "       -b      binary (default is ASCII)." << endl;
	cerr << "       -skel   Geomview SKEL format." << endl;
	cerr << "       -noc    no comments in file." << endl;
	cerr << "       -v      verbose." << endl;
	exit(help_switch == NO_SWITCH);
    }

    CGAL_Verbose_ostream vout( verbose);
    vout << argv[0] << ": verbosity on." << endl;

    const char*  iname = "cin";
    istream*     p_in = &cin;
    ifstream     in;
    if ( nParameters > 0) {
	in.open( parameters[ 0]);
	p_in = &in;
	iname = parameters[0];
    }
    if ( !*p_in) { 
	cerr << argv[0] << ": error: cannot open file '"<< iname
	 << "' for reading." <<endl;
    exit( 1);
    }

    const char*  oname    = "cout";
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

    CGAL_set_ascii_mode(* p_in);
    CGAL_set_ascii_mode(* p_out);

    vout << "Scanning Inventor file `" << iname << "' ....\n--------" << endl;
    iv_file_scanner( *p_in);
    vout << "--------\n    .... done." << endl;

    if ( !*p_in  && !p_in->eof()) { 
	cerr << argv[0] << " read error: while reading file '"<< iname << "'." 
	     << endl;
	exit( 1);
    }

    vout << "print_OFF: `" << iname << "' ...." << endl;
    print_OFF( *p_out);
    vout << "    .... done." << endl;

    if ( !*p_out) { 
	cerr << argv[0] << " write error: while writing file '"<< oname 
	     << "'." << endl;
	exit( 1);
    }

    return 0;
}

// EOF //
