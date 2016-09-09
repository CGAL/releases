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
// file          : terr_trian.C
// package       : $CGAL_Package: Polyhedron_IO 1.6 (02 Apr 1998) $
// revision      : $Revision: 1.3 $
// revision_date : $Date: 1998/04/01 20:17:57 $
// author(s)     : Lutz Kettner  <kettner@@inf.ethz.ch>
//
// coordinator   : Herve Bronnimann  <Herve.Bronnimann@sophia.inria.fr>
//
// Delaunay Triangulation of a set of 3D points in the xy-plane. 
// (Terrain triangulation)
// ============================================================================

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
typedef  CGAL_Triangulation_euclidean_traits_xy_3<R>  Triangulation_traits;

struct TTraits : public Triangulation_traits {
    typedef IPoint Point;
    typedef CGAL_Triangulation_vertex<IPoint> Vertex;
    typedef CGAL_Triangulation_face<Vertex>   Face;
    typedef Vertex::Vertex_handle             Vertex_handle;
    typedef Face::Face_handle                 Face_handle;
};

typedef  CGAL_Triangulation_2< TTraits>               Triangulation;
typedef  CGAL_Delaunay_triangulation_2< TTraits>      Delaunay_triangulation;


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
Switch  delaunay     = NO_SWITCH;
Switch  incr         = NO_SWITCH;

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
	detectSwitch( binary,   "b");
	endDetect();
	detectSwitch( noc,      "noc");
	endDetect();
	detectSwitch( delaunay, "delaunay");
	endDetect();
	detectSwitch( delaunay, "incr");
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
	cerr << "       Terrain triangulation in the xy-plane." << endl;
	cerr << "       -delaunay  Delaunay triangulation (default)." << endl;
	cerr << "       -incr      Incremental insertion (no flips)." << endl;
	cerr << "       -b         binary output (default is ASCII)." << endl;
	cerr << "       -noc       no comments in file." << endl;
	cerr << "       -v         verbose." << endl;
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
	CGAL_triangulation_print_OFF( *p_out, triang, binary, noc);
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
	CGAL_triangulation_print_OFF( *p_out, triang, binary, noc);
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
