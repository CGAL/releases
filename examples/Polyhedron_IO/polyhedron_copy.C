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
// file          : polyhedron_copy.C
// package       : $CGAL_Package: Polyhedron_IO 1.5 (24 Mar 1998) $
// revision      : $Revision: 1.1 $
// revision_date : $Date: 1998/03/01 06:51:10 $
// author(s)     : Lutz Kettner  <kettner@@inf.ethz.ch>
//
// coordinator   : Herve Bronnimann  <Herve.Bronnimann@sophia.inria.fr>
//
// Copies a CGAL_Polyhedron_3 from OFF format to OFF format.
// ============================================================================

#include <CGAL/basic.h>

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <iostream.h>
#include <fstream.h>

#include <CGAL/IO/Verbose_ostream.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Point_3.h>
#include <CGAL/Plane_3.h>
#include <CGAL/Halfedge_data_structure_polyhedron_default_3.h>
#include <CGAL/Polyhedron_default_traits_3.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>

typedef  CGAL_Cartesian<double>                                R;
typedef  CGAL_Polyhedron_default_traits_3<R>                   Traits;
typedef  CGAL_Halfedge_data_structure_polyhedron_default_3<R>  HDS;
typedef  CGAL_Polyhedron_3<Traits,HDS>                         Polyhedron;

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
Switch  noc          = NO_SWITCH;

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
        detectSwitch( noc,    "noc");
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
	cerr << "       copy a CEBaP object (OFF)." << endl;
	cerr << "       -b      binary." << endl;
        cerr << "       -noc    no comments in file." << endl;
	cerr << "       -v      verbose." << endl;
	exit(help_switch == NO_SWITCH);
    }

    CGAL_Verbose_ostream vout( verbose);
    vout << argv[0] << ": verbosity on." << endl;

    const char*  name = "cin";
    istream*     p_in = &cin;
    ifstream     in;
    if ( nParameters > 0) {
	in.open( parameters[ 0]);
	p_in = &in;
	name = parameters[0];
    }
    if ( !*p_in) { 
	cerr << argv[0] << ": error: cannot open file '"<< name
	 << "' for reading." <<endl;
    exit( 1);
    }

    vout << "ifstream(" << name << ") >> CGAL_Polyhedron_3 ..." << endl;
    Polyhedron P;
    (*p_in) >> P;
    vout << "    .... done." << endl;

    if ( !*p_in) { 
	cerr << argv[0] << " read error: while reading file '"<< name << "'." 
	     << endl;
	exit( 1);
    }


    name    = "cout";
    ostream*  p_out = &cout;
    ofstream  out;
    if ( nParameters > 1) {
	out.open( parameters[ 1]);
	p_out = &out;
	name = parameters[1];
    }
    if ( !*p_out) { 
	cerr << argv[0] << ": error: cannot open file '"<< name
	     << "' for writing." <<endl;
    exit( 1);
    }

    if ( binary) {
	vout << "CGAL_set_binary_mode( ofstream(" << name << "))" << endl;
	CGAL_set_binary_mode( *p_out);
    } else if ( noc) {
	vout << "CGAL_set_ascii_mode( ofstream(" << name << "))" << endl;
	CGAL_set_ascii_mode( *p_out);
    } else {
	vout << "CGAL_set_pretty_mode( ofstream(" << name << "))" << endl;
	CGAL_set_pretty_mode( *p_out);
    }

    vout << "ofstream(" << name << ") << CGAL_Polyhedron_3 ..." << endl;
    (*p_out) << P;
    vout << "    .... done." << endl;

    if ( !*p_out) { 
	cerr << argv[0] << " write error: while writing file '"<< name << "'." 
	     << endl;
	exit( 1);
    }


    return 0;
}

// EOF //
