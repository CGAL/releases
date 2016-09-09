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
// file          : terr_trian.C
// package       : $CGAL_Package: Polyhedron_IO 1.11 (17 Dec 1998) $
// revision      : $Revision: 1.3 $
// revision_date : $Date: 1998/04/01 20:17:57 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Delaunay Triangulation of a set of 3D points in the xy-plane. 
// (Terrain triangulation)
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

#ifdef CGAL_USE_LEDA
#include <CGAL/leda_rational.h>
#endif
#include <CGAL/Cartesian.h>
#include <CGAL/Point_3.h>
#include <CGAL/IO/Verbose_ostream.h>
#include <CGAL/IO/File_scanner_OFF.h>
#include <CGAL/IO/File_writer_OFF.h>
#include <CGAL/Triangulation_short_names_2.h>
#include <CGAL/Triangulation_euclidean_traits_xy_3.h>
#include <CGAL/Triangulation_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include "triangulation_print_OFF.h"

template <class R>
struct  Indexed_point: public CGAL_Point_3<R> {
    int*  index;
    Indexed_point()                                      {}
    Indexed_point( Point_3 p) : CGAL_Point_3<R>(p)       {}
    Indexed_point( double x, double y, double z, int* i) 
        : CGAL_Point_3<R>(x,y,z), index(i)               {}
};

#ifdef CGAL_USE_LEDA
typedef  CGAL_Cartesian<leda_rational>                R;
#else
typedef  CGAL_Cartesian<double>                       R;
#endif
typedef  CGAL_Point_3<R>                              Point_3;
typedef  Indexed_point<R>                             IPoint;
typedef  CGAL_Triangulation_euclidean_traits_xy_3<R>  Gtraits;

struct Gt : public Gtraits {
    typedef IPoint Point;
};

typedef  CGAL_Triangulation_vertex_base_2<Gt> Vb;
typedef  CGAL_Triangulation_face_base_2<Gt>  Fb;

typedef  CGAL_Triangulation_default_data_structure_2<Gt,Vb,Fb> Tds;
typedef  CGAL_Triangulation_2<Gt,Tds>                 Triangulation;
typedef  CGAL_Delaunay_triangulation_2<Gt,Tds>        Delaunay_triangulation;

#define MaxParameters          2
#define MaxOptionalParameters  2
#define ErrParameters          10000

bool  verbose      = false;
bool  binary       = false;
bool  noc          = false;
bool  delaunay     = false;
bool  incr         = false;

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
	else if ( strcmp( "-delaunay", argv[i]) == 0)
	    delaunay = true;
	else if ( strcmp( "-incr", argv[i]) == 0)
	    incr = true;
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
	cerr << "       Terrain triangulation in the xy-plane." << endl;
	cerr << "       -delaunay  Delaunay triangulation (default)." << endl;
	cerr << "       -incr      Incremental insertion (no flips)." << endl;
	cerr << "       -b         binary output (default is ASCII)." << endl;
	cerr << "       -noc       no comments in file." << endl;
	cerr << "       -v         verbose." << endl;
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
	cerr << argv[0] << ": error: cannot open file '" << iname
	 << "' for reading." <<endl;
	exit( 1);
    }

    CGAL_File_scanner_OFF scanner( * p_in, true);
    if ( !*p_in)
	exit( 1);

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

    // index array.
    int* indices = new int[ scanner.size_of_vertices()];
    for ( int k = 0; k < scanner.size_of_vertices(); k++)
	indices[k] = -1;

    if ( delaunay || ! incr) {
	Delaunay_triangulation triang;
	vout << "Scanning and triangulating ..." << endl;
	for ( int j = 0; j < scanner.size_of_vertices(); j++) {
	    double x, y, z;
	    scanner.scan_vertex( x, y, z);
	    IPoint p( x, y, z, indices + j);
	    triang.insert( p);
	}
	vout << "    .... done." << endl;
	vout << "write_triangulation( " << oname 
	     << (binary ? ", binary" : ", ASCII") << ") ...." << endl;
	CGAL_triangulation_print_OFF( *p_out, triang, binary, noc, verbose);
	vout << "    .... done." << endl;
    } else {
        Triangulation triang;
	vout << "Scanning and triangulating ..." << endl;
	for ( int j = 0; j < scanner.size_of_vertices(); j++) {
	    double x, y, z;
	    scanner.scan_vertex( x, y, z);
	    IPoint p( x, y, z, indices + j);
	    triang.insert( p);
	}
	vout << "    .... done." << endl;
	vout << "write_triangulation( " << oname 
	     << (binary ? ", binary" : ", ASCII") << ") ...." << endl;
	CGAL_triangulation_print_OFF( *p_out, triang, binary, noc, verbose);
	vout << "    .... done." << endl;
    }
    if ( !*p_in) { 
	cerr << argv[0] << " read error: while reading file '"<< iname << "'." 
	     << endl;
	exit( 1);
    }
    if ( !*p_out) { 
	cerr << argv[0] << " write error: while writing file '"<< oname << "'." 
	     << endl;
	exit( 1);
    }
    delete[] indices;
    return 0;
}

// EOF //
