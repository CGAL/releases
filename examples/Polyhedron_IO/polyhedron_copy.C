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
// file          : polyhedron_copy.C
// package       : $CGAL_Package: Polyhedron_IO 1.11 (17 Dec 1998) $
// revision      : $Revision: 1.1 $
// revision_date : $Date: 1998/03/01 06:51:10 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Copies a CGAL_Polyhedron_3 from OFF format to OFF format.
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

#define MaxParameters          2
#define MaxOptionalParameters  2
#define ErrParameters          10000

bool  verbose   = false;
bool  binary    = false;
bool  noc       = false;

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
	cerr << "Usage: " << argv[0] << " [<options>] [<infile>]" << endl;
	cerr << "       copy a polyhedron in OFF." << endl;
	cerr << "       -b      binary." << endl;
        cerr << "       -noc    no comments in file." << endl;
	cerr << "       -v      verbose." << endl;
	exit( ! help);
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
