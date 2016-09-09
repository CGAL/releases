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
// file          : off2off.C
// package       : $CGAL_Package: Polyhedron_IO 2.5 (29 Apr 1999) $
// revision      : $Revision: 1.3 $
// revision_date : $Date: 1999/03/09 22:18:32 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Copies a file in OFF format.
// email         : cgal@cs.uu.nl
//
// ======================================================================

#include <CGAL/basic.h>

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>

#include <CGAL/IO/Verbose_ostream.h>
#include <CGAL/IO/File_writer_OFF.h>
#include <CGAL/IO/generic_copy_OFF.h>

using namespace std;

bool  verbose      = false;
bool  binary       = false;
bool  skel         = false;
bool  noc          = false;

// main function with standard unix commandline arguments
// ------------------------------------------------------
int main( int argc, char **argv) {
    int n = 0; // number of filenames
    char *filename[2];
    bool help = false;
    for (int i = 1; i < argc; i++) { // check commandline options
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
	else if ( n < 2 ) {
	    filename[ n++] = argv[i];
	} else {
	    ++n;
	    break;
	}
    }
    if ((n > 2) || help) {
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

    CGAL::Verbose_ostream vout( verbose);
    vout << argv[0] << ": verbosity on." << endl;

    const char*  iname = "cin";
    istream*     p_in  = &cin;
    ifstream     in;
    if ( n > 0) {
	in.open( filename[0]);
	p_in = &in;
	iname = filename[0];
    }
    if ( !*p_in) { 
	cerr << argv[0] << ": error: cannot open file '"<< iname
	     << "' for reading." << endl;
	exit( 1);
    }

    const char*  oname = "cout";
    ostream*     p_out = &cout;
    ofstream     out;
    if ( n > 1) {
	out.open( filename[1]);
	p_out = &out;
	oname = filename[1];
    }
    if ( !*p_out) { 
	cerr << argv[0] << ": error: cannot open file '"<< oname
	     << "' for writing." <<endl;
	exit( 1);
    }

    vout << "CGAL::generic_copy_OFF( " << iname << ", " << oname 
	 << (binary ? ", binary" : ", ASCII") << ") ...." << endl;
    CGAL::File_header_OFF  header( binary, noc, skel, verbose);
    CGAL::File_writer_OFF  writer( header);
    CGAL::generic_copy_OFF( *p_in, *p_out, writer);
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
