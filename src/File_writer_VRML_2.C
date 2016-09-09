// ======================================================================
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
// file          : src/File_writer_VRML_2.C
// package       : Polyhedron_IO (1.11)
// chapter       : $CGAL_Chapter: Support Library ... $
// source        : polyhedron_io.fw
// revision      : $Revision: 1.8 $
// revision_date : $Date: 1998/10/08 22:46:22 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Writer for polyhedral surfaces VRML_2.0 format (.wrl)
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif // CGAL_BASIC_H
#ifndef CGAL_PROTECT_IOSTREAM_H
#include <iostream.h>
#define CGAL_PROTECT_IOSTREAM_H
#endif // CGAL_PROTECT_IOSTREAM_H
#ifndef CGAL_IO_FILE_WRITER_VRML_2_H
#include <CGAL/IO/File_writer_VRML_2.h>
#endif // CGAL_IO_FILE_WRITER_VRML_2_H

void
CGAL_File_writer_VRML_2::
write_header( ostream& o, size_t vertices, size_t halfedges,size_t facets){
    m_out    = &o;
    m_facets = facets;

    out() << "        #-- Begin of CGAL_Polyhedron_3\n";
    out() << "        # " << vertices  << " vertices\n";
    out() << "        # " << halfedges << " halfedges\n";
    out() << "        # " << facets    << " facets\n";
    out() << "        Group {\n"
             "            children [\n"
             "                Shape {\n"
             "                    appearance Appearance { material "
                                               "USE CGAL_Material }\n"
             "                    geometry IndexedFaceSet {\n"
             "                        convex FALSE\n"
             "                        solid  FALSE\n"
             "                        coord  Coordinate {\n"
             "                            point [" << endl;
}

void
CGAL_File_writer_VRML_2::
write_facet_header() const {
    out() << "                            ] #point\n"
             "                        } #coord Coordinate\n"
             "                        coordIndex  [" << endl;
}

void
CGAL_File_writer_VRML_2::
write_footer() const {
    out() << "                        ] #coordIndex\n"
             "                    } #geometry\n"
             "                } #Shape\n"
             "            ] #children\n"
             "        } #Group" << endl;
}
// EOF //
