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
// file          : off2off.C
// package       : $CGAL_Package: Polyhedron_IO 1.11 (17 Dec 1998) $
// revision      : $Revision: 1.1 $
// revision_date : $Date: 1998/03/01 06:51:10 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Copies a file in OFF format.
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
#include <CGAL/IO/File_writer_OFF.h>
#include <CGAL/IO/generic_copy_OFF.h>


#define MaxParameters          2
#define MaxOptionalParameters  2
#define ErrParameters          10000

bool  verbose      = false;
bool  binary       = false;
bool  skel         = false;
bool  noc          = false;

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
	cerr << "Usage: " << argv[0] << " [<options>] [<infile> [<outfile>]]"
	     << endl;
	cerr << "       copy an object in OFF." << endl;
	cerr << "       -b      binary (default is ASCII)." << endl;
	cerr << "       -skel   Geomview SKEL format." << endl;
	cerr << "       -noc    no comments in file." << endl;
	cerr << "       -v      verbose." << endl;
	exit( ! help);
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
	     << "' for reading." << endl;
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

    vout << "CGAL_generic_copy_OFF( " << iname << ", " << oname 
	 << (binary ? ", binary" : ", ASCII") << ") ...." << endl;
    CGAL_File_header_OFF  header( binary, noc, skel, verbose);
    CGAL_File_writer_OFF  writer( header);
    CGAL_generic_copy_OFF( *p_in, *p_out, writer);
    vout << "    .... done." << endl;

    if ( !*p_in) { 
	cerr << argv[0] << " read error: while reading file '"
	     << iname << "'." << endl;
	exit( 1);
    }
    if ( !*p_out) { 
	cerr << argv[0] << " write error: while writing file '"
	     << oname << "'." << endl;
	exit( 1);
    }
    return 0;
}

// EOF //
