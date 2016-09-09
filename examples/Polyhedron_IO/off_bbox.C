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
// file          : off_bbox.C
// package       : $CGAL_Package: Polyhedron_IO 1.5 (24 Mar 1998) $
// revision      : $Revision: 1.1 $
// revision_date : $Date: 1998/03/01 06:51:10 $
// author(s)     : Lutz Kettner  <kettner@@inf.ethz.ch>
//
// coordinator   : Herve Bronnimann  <Herve.Bronnimann@sophia.inria.fr>
//
// computes bbox of an OFF object.
// ============================================================================

#include <CGAL/basic.h>

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <iostream.h>
#include <fstream.h>
#include <float.h>

#include <CGAL/Bbox_3.h>
#include <CGAL/IO/Verbose_ostream.h>
#include <CGAL/IO/scan_points_OFF.h>


/* main */
/* ==== */

#define MaxParameters          1
#define MaxOptionalParameters  1
#define ErrParameters          10000

typedef char Switch;

#define NO_SWITCH    0
#define MINUS_SWITCH 1
#define PLUS_SWITCH  2

Switch  dummy_switch = NO_SWITCH;
Switch  verbose      = NO_SWITCH;
Switch  unitcube     = NO_SWITCH;

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
	detectSwitch( verbose,  "v");
	endDetect();
	detectSwitch( unitcube, "unit");
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
	cerr << "       computes the bbox of the coordinates of an OFF object."
	     << endl;
	cerr << "       -unit     prints transformation to unit cube." << endl;
	cerr << "                 (can be used with 'off_transform')" << endl;
	cerr << "       -v        verbose." << endl;
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

    verr << "CGAL_File_scanner_OFF( " << name << ") ...." << endl;
    CGAL_File_scanner_OFF scanner( * p_in);
    if ( ! * p_in) {
	cerr << argv[0] << ": error: file '"<< name
	 << "' is not in OFF format." << endl;
	abort();
    }
    if ( scanner.size_of_vertices() <= 0) {
	cerr << argv[0] << ": error: file '"<< name
	 << "' has no vertices." << endl;
	abort();
    }
    size_t  n = scanner.size_of_vertices();
    CGAL_Bbox_3 bbox;
    double x, y, z;
    scanner.scan_vertex( x, y, z);
    bbox = CGAL_Bbox_3( x,y,z, x,y,z);
    n--;
    while (n--) {
	scanner.scan_vertex( x, y, z);
	bbox = bbox + CGAL_Bbox_3( x,y,z, x,y,z);
	scanner.skip_to_next_vertex( scanner.size_of_vertices() - n - 1);
    }
    verr << ".... done." << scanner.size_of_vertices() << " points read." 
	 << endl;

    if ( !in) { 
	cerr << argv[0] << " read error: while reading file '"<< name << "'." 
	     << endl;
	exit( 1);
    }
    if ( ! unitcube) {
	cout << bbox.xmin() << "  " << bbox.ymin() << "  " << bbox.zmin() 
	     << '\n';
	cout << bbox.xmax() << "  " << bbox.ymax() << "  " << bbox.zmax() 
	     << endl;
    } else {
	double s = DBL_MAX;
	double d = bbox.xmax() - bbox.xmin();
	if ( d > 0 && 2/d < s)
	    s = 2/d;
        d = bbox.ymax() - bbox.ymin();
	if ( d > 0 && 2/d < s)
	    s = 2/d;
        d = bbox.zmax() - bbox.zmin();
	if ( d > 0 && 2/d < s)
	    s = 2/d;
	if ( s == DBL_MAX)
	    s = 1;
	cout << "-trans  " << (-(bbox.xmin() + bbox.xmax())/2) 
	     << "  "       << (-(bbox.ymin() + bbox.ymax())/2) 
	     << "  "       << (-(bbox.zmin() + bbox.zmax())/2) 
	     << "  -scale  " << s << endl;
    }
    return 0;
}

// EOF //
