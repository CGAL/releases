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
// file          : viewpoint2off.C
// package       : $CGAL_Package: Polyhedron_IO 1.11 (17 Dec 1998) $
// revision      : $Revision: 1.1 $
// revision_date : $Date: 1998/03/01 06:51:10 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Copies from Viewpoint ASCII format into OFF format.
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


#define MaxParameters          3
#define MaxOptionalParameters  2
#define ErrParameters          10000

bool  verbose      = false;
bool  binary       = false;
bool  skel         = false;
bool  noc          = false;
bool  binary_mesh  = false;
bool  ascii_mesh   = false;
bool  normals_file = false;
bool  no_normals   = false;

const char* normals_filename = 0;

// main function with standard unix commandline arguments
// ------------------------------------------------------
int main( int argc, char **argv) {
#if CGAL_CFG_INCOMPLETE_TYPE_BUG_5
    Point _work_around_incomplete_type;
#endif  // CGAL_CFG_INCOMPLETE_TYPE_BUG_5
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
	else if ( strcmp( "-mesh", argv[i]) == 0)
	    binary_mesh = true;
	else if ( strcmp( "-ascii", argv[i]) == 0)
	    ascii_mesh = true;
	else if ( strcmp( "-no_normals", argv[i]) == 0)
	    no_normals = true;
	else if ( strcmp( "-normals", argv[i]) == 0) {
	    normals_file = true;
	    i++;
	    if ( i < argc) {
		normals_filename = argv[i];
	    } else {
		cerr << argv[0] << ": error: -normals need a filename as "
		     "parameter." << endl;
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
	cerr << "Usage: " << argv[0] 
	     << " [<options>] <infile.coo> <infile.ele> [<outfile>]" << endl;
	cerr << "   or: " << argv[0] 
	     << " [<options>] <infile.msh> [<outfile>]" << endl;
	cerr << "       convert an object from Viewpoint formats into OFF." 
	     << endl;
	cerr << "       -mesh   forces input to be read from mesh file." 
	     << endl;
	cerr << "       -ascii  forces input to be read from ascii mesh file." 
	     << endl;
	cerr << "       -normals <filename>   reads normals file (in "
	        "polygon format)." << endl;
	cerr << "       -no_normals           ignore normals." << endl;
	cerr << "       -b      binary output (default is ASCII)." << endl;
	cerr << "       -skel   Geomview SKEL format." << endl;
	cerr << "       -noc    no comments in file." << endl;
	cerr << "       -v      verbose." << endl;
	exit( ! help);
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
    CGAL_File_header_OFF  header( binary, noc, skel, verbose);
    CGAL_File_writer_OFF  writer( header);
    writer.write_header( *p_out, points.size(), 0, facets.size(), 
			 normals.size()>0);
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
    writer.write_footer();
    vout << "    .... done." << endl;
    if ( !*p_out) { 
	cerr << argv[0] << " write error: while writing file '"<< oname 
	     << "'."  << endl;
	exit( 1);
    }
    return 0;
}

// EOF //
