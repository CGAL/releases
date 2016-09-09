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
// file          : viewpoint2off.C
// package       : $CGAL_Package: Polyhedron_IO 1.9 (10 Jul 1998) $
// revision      : $Revision: 1.1 $
// revision_date : $Date: 1998/03/01 06:51:10 $
// author(s)     : Lutz Kettner  <kettner@@inf.ethz.ch>
//
// coordinator   : Herve Bronnimann  <Herve.Bronnimann@sophia.inria.fr>
//
// Copies from Viewpoint ASCII format into OFF format.
// ============================================================================

#include <CGAL/basic.h>

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <iostream.h>
#include <fstream.h>
#include <strstream.h>
#include <vector.h>

#include <CGAL/Cartesian.h>
#include <CGAL/known_bit_size_integers.h>
#include <CGAL/Point_3.h>
#include <CGAL/IO/Verbose_ostream.h>
#include <CGAL/IO/binary_file_io.h>
#include <CGAL/IO/File_writer_OFF.h>

typedef  CGAL_Cartesian<float>                  R;
typedef  CGAL_Point_3<R>                        Point;
typedef  vector<Point>                          Point_vector;
typedef  vector<int>                            Facet;
typedef  vector<Facet>                          Facet_vector;


/* main */
/* ==== */

#define MaxParameters          3
#define MaxOptionalParameters  2
#define ErrParameters          10000

typedef char Switch;

#define NO_SWITCH    0
#define MINUS_SWITCH 1
#define PLUS_SWITCH  2

Switch  dummy_switch = NO_SWITCH;
Switch  verbose      = NO_SWITCH;
Switch  binary       = NO_SWITCH;
Switch  binary_mesh  = NO_SWITCH;
Switch  ascii_mesh   = NO_SWITCH;
Switch  normals_file = NO_SWITCH;
Switch  no_normals   = NO_SWITCH;

const char* normals_filename = 0;


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
#if CGAL_CFG_INCOMPLETE_TYPE_BUG_5
    Point _work_around_incomplete_type;
#endif  // CGAL_CFG_INCOMPLETE_TYPE_BUG_5
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
	detectSwitch( binary_mesh, "mesh");
	endDetect();
	detectSwitch( ascii_mesh, "ascii");
	endDetect();
	detectSwitch( normals_file, "normals");
	    i++;
	    if ( i < argc) {
		normals_filename = argv[i];
	    } else {
		cerr << argv[0] << ": error: -normals need a filename as "
		     "parameter." << endl;
		help_switch = MINUS_SWITCH;
	    }
	endDetect();
	detectSwitch( no_normals, "no_normals");
	endDetect();

	detectSwitch( help_switch, "h");
	endDetect();
	detectSwitch( help_switch, "H");
	endDetect();
	detectSwitch( help_switch, "help");
	endDetect();

	/* else get standard or optional parameters */
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
	cerr << "Usage: " << argv[0] 
	     << " [<options>] <infile.coo> <infile.ele> [<outfile>]" << endl;
	cerr << "   or: " << argv[0] 
	     << " [<options>] <infile.msh> [<outfile>]" << endl;
	cerr << "       convert an object from Viewpoint formats into OFF." 
	     << endl;
	cerr << "       -b      binary output (default is ASCII)." << endl;
	cerr << "       -mesh   forces input to be read from mesh file." 
	     << endl;
	cerr << "       -ascii  forces input to be read from ascii mesh file." 
	     << endl;
	cerr << "       -normals <filename>   reads normals file (in "
	        "polygon format)." << endl;
	cerr << "       -no_normals           ignore normals." << endl;
	cerr << "       -v      verbose." << endl;
	exit(help_switch == NO_SWITCH);
    }

    CGAL_Verbose_ostream vout( verbose);
    vout << argv[0] << ": verbosity on." << endl;

    ifstream     in( parameters[ 0]);
    if ( ! in) { 
	cerr << argv[0] << ": error: cannot open file '"<< parameters[ 0]
	 << "' for reading." <<endl;
	exit( 1);
    }

    Point_vector  points;
    Point_vector  normals;
    Facet_vector  facets;
    points.reserve(  64000);  // Avoid too much reallocation
    normals.reserve( 64000);
    facets.reserve(  64000);
    float x,y,z;
    char  c,d,e;
    in.get(c);
    if ( c < '0' && c > '9')
	binary_mesh = 1;
    in.putback(c);
    CGAL_Integer32   number;
    if ( ! binary_mesh) {
	in >> number;
	if ( number != 1)
	    ascii_mesh = 1;
    }
    if ( binary_mesh) {
	vout << "Scanning Viewpoint binary mesh data file ..." << endl;
	CGAL__Binary_read_big_endian_integer32( in, number);
	int tmesh = 0;
	while( in) {
	    tmesh ++;
	    for ( int j = 0; j < number; j++) {
		if ( j > 1) {
		    facets.push_back( Facet());
		    Facet& facet = (*(facets.end() - 1));
		    facet.push_back( points.size());
		    if (j & 1) {
			facet.push_back( points.size()-2);
			facet.push_back( points.size()-1);
		    } else {
			facet.push_back( points.size()-1);
			facet.push_back( points.size()-2);
		    }
		}
		// Scan vertex coordinates.
		CGAL__Binary_read_big_endian_float32( in, x);
		CGAL__Binary_read_big_endian_float32( in, y);
		CGAL__Binary_read_big_endian_float32( in, z);
		points.push_back( Point( x, y, z));
	    }
	    for ( int k = 0; k < number; k++) {
		// Scan vertex normal.
		CGAL__Binary_read_big_endian_float32( in, x);
		CGAL__Binary_read_big_endian_float32( in, y);
		CGAL__Binary_read_big_endian_float32( in, z);
		if ( ! no_normals)
		    normals.push_back( Point( x, y, z));
	    }
	    CGAL__Binary_read_big_endian_integer32( in, number);
	}
	in.close();
	vout << points.size() << " vertex coordinates read." << endl;
	vout << facets.size() << " facets read." << endl;
	vout << tmesh << " triangle meshes read." << endl;
    } else if ( ascii_mesh) {
	vout << "Scanning Viewpoint ASCII mesh data file ..." << endl;
	int tmesh = 0;
	while( in) {
	    tmesh ++;
	    for ( int j = 0; j < number; j++) {
		if ( j > 1) {
		    facets.push_back( Facet());
		    Facet& facet = (*(facets.end() - 1));
		    facet.push_back( points.size());
		    if (j & 1) {
			facet.push_back( points.size()-2);
			facet.push_back( points.size()-1);
		    } else {
			facet.push_back( points.size()-1);
			facet.push_back( points.size()-2);
		    }
		}
		// Scan vertex coordinates.
		in >> x >> y >> z;
		points.push_back( Point( x, y, z));
	    }
	    for ( int k = 0; k < number; k++) {
		// Scan vertex normal.
		in >> x >> y >> z;
		if ( ! no_normals)
		    normals.push_back( Point( x, y, z));
	    }
	    in >> number;
	}
	in.close();
	vout << points.size() << " vertex coordinates read." << endl;
	vout << facets.size() << " facets read." << endl;
	vout << tmesh << " triangle meshes read." << endl;
    } else {
	vout << "Scanning Viewpoint polygon data files ..." << endl;
	vout << "    ... start with coordinates file ..." << endl;
	if ( nParameters < 2) {
	    cerr << argv[0] << ": error: two input filenames needed." << endl;
	    exit( 1);
	}
	while( in) {
	    in >> c >> x >> d >> y >> e >> z;
	    if ( ! in || number != (points.size() + 1) || 
		 c != ',' || d != ',' || e != ',') {
		cerr << argv[0] << ": error: cannot read line " 
		     << points.size() + 1 << " from file '" << parameters[ 0] 
		     << "'." <<endl;
		exit( 1);
	    }
	    points.push_back( Point( x, y, z));
	    in >> number;
	}
	in.close();
	vout << points.size() << " vertex coordinates read." << endl;

	if ( normals_file && ! no_normals) {
	    vout << "    ... next is normals file ..." << endl;
	    in.open( normals_filename);
	    if ( ! in) { 
		cerr << argv[0] << ": error: cannot open file '"
		     << normals_filename << "' for reading." <<endl;
		exit( 1);
	    }
	    in >> x;
	    while( in) {
		in >> y >> z;
		if ( ! in ) {
		    cerr << argv[0] << ": error: cannot read line " 
			 << points.size() + 1 << " from file '" 
			 << normals_filename << "'." <<endl;
		    exit( 1);
		}
		normals.push_back( Point( x, y, z));
		in >> x;
	    }
	    in.close();
	    vout << normals.size() << " normals read." << endl;
	    if ( normals.size() != points.size()) {
		cerr << argv[0] << ": error: number of points and normals "
		    "differ." << endl;
		exit( 1);
	    }
	}

	vout << "    ... next is element file ..." << endl;
	in.open( parameters[ 1]);
	if ( ! in) { 
	    cerr << argv[0] << ": error: cannot open file '"<< parameters[ 1]
	     << "' for reading." <<endl;
	    exit( 1);
	}
	char  part_name[16000];
	in >> part_name;
	while( in) {
	    in.get(c);
	    facets.push_back( Facet());
	    Facet& facet = (*(facets.end() - 1));
	    while( c == ' ') {
		in >> number;
		if ( number < 1 || number > points.size()) {
		    cerr << argv[0] << ": error: parsing line " 
			 << facets.size() << " from file '" << parameters[ 1] 
			 << "': index " << number << " is out of range." 
			 << endl;
		    exit( 1);
		}
		facet.push_back( number - 1);
		in.get(c);
	    }
	    in >> part_name;
	}
	in.close();
	vout << facets.size() << " facets read." << endl;
    }

    const char*  oname    = "cout";
    ostream*     p_out = &cout;
    ofstream     out;
    if ( nParameters > 2) {
	out.open( parameters[ 2]);
	p_out = &out;
	oname = parameters[2];
    }
    if ( (ascii_mesh || binary_mesh) && nParameters > 1) {
	out.open( parameters[ 1]);
	p_out = &out;
	oname = parameters[1];
    }
    if ( !*p_out) { 
	cerr << argv[0] << ": error: cannot open file '"<< oname
	     << "' for writing." <<endl;
	exit( 1);
    }

    vout << "CGAL_File_writer_OFF( " << (binary ? ", binary" : ", ASCII") 
	 << ") ...." << endl;
    CGAL_File_writer_OFF  writer( binary);
    writer.header( *p_out, points.size(), 0, facets.size(), normals.size()>0);
    Point_vector::iterator norm = normals.begin();
    for ( Point_vector::iterator p = points.begin(); p != points.end(); ++p) {
	writer.write_vertex( (*p).x(), (*p).y(), (*p).z());
	if ( normals.size()>0) {
	    writer.write_normal( (*norm).x(), (*norm).y(), (*norm).z());
	    ++norm;
	}
    }
    writer.write_facet_header();
    for ( Facet_vector::iterator fc = facets.begin(); fc!=facets.end(); ++fc) {
	writer.write_facet_begin( (*fc).size());
	for ( Facet::iterator fi = (*fc).begin(); fi != (*fc).end(); ++fi) {
	    writer.write_facet_vertex_index( *fi);
	}
	writer.write_facet_end();
    }
    writer.footer();
    vout << "    .... done." << endl;
    if ( !*p_out) { 
	cerr << argv[0] << " write error: while writing file '"<< oname 
	     << "'."  << endl;
	exit( 1);
    }

    return 0;
}

// EOF //
