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
// file          : off_transform.C
// package       : $CGAL_Package: Polyhedron_IO 1.9 (10 Jul 1998) $
// revision      : $Revision: 1.1 $
// revision_date : $Date: 1998/03/01 06:51:10 $
// author(s)     : Lutz Kettner  <kettner@@inf.ethz.ch>
//
// coordinator   : Herve Bronnimann  <Herve.Bronnimann@sophia.inria.fr>
//
// Applies translation and scaling to an OFF object.
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
#include <CGAL/IO/scan_points_OFF.h>
#include <CGAL/IO/File_writer_OFF.h>

typedef  CGAL_Vector_3< CGAL_Cartesian<float> >       Vector;
typedef  CGAL_Point_3< CGAL_Cartesian<float> >        Point;


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

double  transx       =  0.0;
double  transy       =  0.0;
double  transz       =  0.0;
double  scale        =  1.0;


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
	detectSwitch( dummy_switch, "scale");
	    i++;
	    if ( i < argc) {
		scale = atof( argv[i]);
	    } else {
		cerr << argv[0] << ": error: -scale needs a double parameter." 
		     << endl;
		help_switch = MINUS_SWITCH;
	    }
	endDetect();
	detectSwitch( dummy_switch, "trans");
	    i++;
	    if ( i+2 < argc) {
		transx = atof( argv[i]);
		i++;
		transy = atof( argv[i]);
		i++;
		transz = atof( argv[i]);
	    } else {
		cerr << argv[0] << ": error: -trans needs three double "
		        "parameters." << endl;
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
	cerr << "Usage: " << argv[0] << " [<options>] [<infile> [<outfile>]]"
	     << endl;
	cerr << "       transforms coordinate values of an OFF object." 
	     << endl;
	cerr << "       -trans <x> <y> <y>    translation." << endl;
	cerr << "       -scale <s>            uniform scaling." << endl;
	cerr << "       -b                    binary (default is ASCII)."
	     << endl;
	cerr << "       -skel                 Geomview SKEL format." << endl;
	cerr << "       -noc                  no comments in file." << endl;
	cerr << "       -v                    verbose." << endl;
	exit(help_switch == NO_SWITCH);
    }

    CGAL_Verbose_ostream verr( verbose);
    verr << argv[0] << ": verbosity on." << endl;

    const char*  name = "cin";
    istream*     p_in = &cin;
    ifstream     in;
    if ( nParameters > 0) {
	in.open( parameters[ 0]);
	p_in = &in;
	name = parameters[0];
    }
    if ( ! * p_in) { 
	cerr << argv[0] << ": error: cannot open file '"<< name
	 << "' for reading." <<endl;
	exit( 1);
    }

    verr << "CGAL_scan_points_OFF( " << name << ") ...." << endl;
    CGAL_File_scanner_OFF scanner( * p_in);
    if ( ! * p_in) {
	cerr << argv[0] << ": error: file '"<< name
	 << "' is not in OFF format." << endl;
	abort();
    }
    size_t  n = scanner.size_of_vertices();

    verr << "CGAL_File_writer_OFF( ..." << endl;
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

    scanner.file_info().normalized_to_sphere = false;
    CGAL_File_writer_OFF  writer( scanner.file_info(), binary, noc, skel);
    writer.header( * p_out, 
		   scanner.size_of_vertices(),
		   scanner.file_info().n_halfedges(),
		   scanner.size_of_facets());

    Vector v( transx, transy, transz);
    for ( int k = 0; k < scanner.size_of_vertices(); ++k) {
	double x, y, z;
	scanner.scan_vertex( x, y, z);
	Point q( x, y, z);
	q = q + v;
	q = CGAL_ORIGIN + ( (q - CGAL_ORIGIN) * scale );
	scanner.skip_to_next_vertex( k);
	writer.write_vertex( q.x(), q.y(), q.z());
    }	
    verr << "    .... done." << n << " points read." << endl;

    if ( ! *p_in) { 
	cerr << argv[0] << " read error: while reading file '"<< name << "'." 
	     << endl;
	exit( 1);
    }

    writer.write_facet_header();
    * p_out << endl;
    char c;
    while ( (*p_in).get(c))
	* p_out << c;

    return 0;
}

// EOF //
