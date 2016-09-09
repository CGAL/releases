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
// file          : off_transform.C
// package       : $CGAL_Package: Polyhedron_IO 1.11 (17 Dec 1998) $
// revision      : $Revision: 1.1 $
// revision_date : $Date: 1998/03/01 06:51:10 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Applies translation and scaling to an OFF object.
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

typedef  CGAL_Vector_3< CGAL_Cartesian<float> >       Vector;
typedef  CGAL_Point_3< CGAL_Cartesian<float> >        Point;

#define MaxParameters          2
#define MaxOptionalParameters  2
#define ErrParameters          10000

bool  verbose      = false;
bool  binary       = false;
bool  skel         = false;
bool  noc          = false;

double  transx       =  0.0;
double  transy       =  0.0;
double  transz       =  0.0;
double  scale        =  1.0;

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
	else if ( strcmp( "-scale", argv[i]) == 0) {
	    i++;
	    if ( i < argc) {
		scale = atof( argv[i]);
	    } else {
		cerr << argv[0] << ": error: -scale needs a double parameter." 
		     << endl;
		help = true;
	    }
	} else if ( strcmp( "-trans", argv[i]) == 0) {
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
		help = true;
	    }
	} else if ( (strcmp( "-h", argv[i]) == 0) || 
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
	cerr << "       transforms coordinate values of an OFF object." 
	     << endl;
	cerr << "       -trans <x> <y> <y>    translation." << endl;
	cerr << "       -scale <s>            uniform scaling." << endl;
	cerr << "       -b                    binary (default is ASCII)."
	     << endl;
	cerr << "       -skel                 Geomview SKEL format." << endl;
	cerr << "       -noc                  no comments in file." << endl;
	cerr << "       -v                    verbose." << endl;
	exit( ! help);
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

    CGAL_File_header_OFF  header( binary, noc, skel, verbose);
    CGAL_File_writer_OFF  writer( header);
    writer.write_header( * p_out, 
			 scanner.size_of_vertices(),
			 scanner.size_of_halfedges(),
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
