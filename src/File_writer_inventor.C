// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : src/File_writer_inventor.C
// author(s)     : Lutz Kettner  
//
// email         : cgal@cs.uu.nl
//
// ============================================================================

#ifndef CGAL_IO_FILE_WRITER_INVENTOR_H
#include <CGAL/IO/File_writer_inventor.h>
#endif // CGAL_IO_FILE_WRITER_INVENTOR_H

void
CGAL_File_writer_inventor::
header( ostream& o, size_t vertices, size_t halfedges, size_t facets) {
    out = &o;
    _facets = facets;
    *out << "# " << vertices  << " vertices\n";
    *out << "# " << halfedges << " halfedges\n";
    *out << "# " << facets    << " facets\n\n";
    *out << "Separator {\n"
            "    Coordinate3 {\n"
            "        point   [" << endl;
}

void
CGAL_File_writer_inventor::
write_facet_header() const {
    *out << "        ] #point\n"
            "    } #Coordinate3\n"
            "    # " << _facets << " facets\n"
            "    IndexedFaceSet {\n"
            "        coordIndex [\n";
}

void
CGAL_File_writer_inventor::
footer() const {
    *out << "        ] #coordIndex\n"
            "    } #IndexedFaceSet\n"
            "} #Separator" << endl;
}
// EOF //
