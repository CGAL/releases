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
// file          : polyhedron_copy.C
// package       : $CGAL_Package: Polyhedron_IO 2.5 (29 Apr 1999) $
// revision      : $Revision: 1.3 $
// revision_date : $Date: 1999/03/09 22:18:32 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Copies a CGAL::Polyhedron_3 from OFF format to OFF format.
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
#include <CGAL/Cartesian.h>
#include <CGAL/Point_3.h>
#include <CGAL/Plane_3.h>
#include <CGAL/Halfedge_data_structure_polyhedron_default_3.h>
#include <CGAL/Polyhedron_default_traits_3.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>

using namespace std;

typedef  CGAL::Cartesian<double>                                R;
typedef  CGAL::Polyhedron_default_traits_3<R>                   Traits;
typedef  CGAL::Halfedge_data_structure_polyhedron_default_3<R>  HDS;
typedef  CGAL::Polyhedron_3<Traits,HDS>                         Polyhedron;

bool  verbose   = false;
bool  binary    = false;
bool  noc       = false;

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
        cerr << "       copy a polyhedron in OFF." << endl;
        cerr << "       -b      binary." << endl;
        cerr << "       -noc    no comments in file." << endl;
        cerr << "       -v      verbose." << endl;
        exit( ! help);
    }

    CGAL::Verbose_ostream vout( verbose);
    vout << argv[0] << ": verbosity on." << endl;

    const char*  name = "cin";
    istream*     p_in = &cin;
    ifstream     in;
    if ( n > 0) {
        in.open( filename[0]);
        p_in = &in;
        name = filename[0];
    }
    if ( !*p_in) { 
        cerr << argv[0] << ": error: cannot open file '"<< name
             << "' for reading." <<endl;
        exit( 1);
    }

    vout << "ifstream(" << name << ") >> CGAL::Polyhedron_3 ..." << endl;
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
    if ( n > 1) {
        out.open( filename[1]);
        p_out = &out;
        name = filename[1];
    }
    if ( !*p_out) { 
        cerr << argv[0] << ": error: cannot open file '"<< name
             << "' for writing." <<endl;
        exit( 1);
    }

    if ( binary) {
        vout << "CGAL::set_binary_mode( ofstream(" << name << "))" << endl;
        CGAL::set_binary_mode( *p_out);
    } else if ( noc) {
        vout << "CGAL::set_ascii_mode( ofstream(" << name << "))" << endl;
        CGAL::set_ascii_mode( *p_out);
    } else {
        vout << "CGAL::set_pretty_mode( ofstream(" << name << "))" << endl;
        CGAL::set_pretty_mode( *p_out);
    }

    vout << "ofstream(" << name << ") << CGAL::Polyhedron_3 ..." << endl;
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
