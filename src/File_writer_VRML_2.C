// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : src/File_writer_VRML_2.C
// package       : Polyhedron_IO (3.9)
// chapter       : $CGAL_Chapter: Support Library ... $
// source        : polyhedron_io.fw
// revision      : $Revision: 1.1.1.1 $
// revision_date : $Date: 2001/03/15 17:20:56 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Writer for polyhedral surfaces VRML_2.0 format (.wrl)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif // CGAL_BASIC_H
#ifndef CGAL_PROTECT_IOSTREAM
#include <iostream>
#define CGAL_PROTECT_IOSTREAM
#endif
#ifndef CGAL_IO_FILE_WRITER_VRML_2_H
#include <CGAL/IO/File_writer_VRML_2.h>
#endif // CGAL_IO_FILE_WRITER_VRML_2_H

CGAL_BEGIN_NAMESPACE

void
File_writer_VRML_2::
write_header( std::ostream& o,
              std::size_t   vertices,
              std::size_t   halfedges,
              std::size_t   facets) {
    m_out    = &o;
    m_facets = facets;

    out() << "        #-- Begin of Polyhedron_3\n";
    out() << "        # " << vertices  << " vertices\n";
    out() << "        # " << halfedges << " halfedges\n";
    out() << "        # " << facets    << " facets\n";
    out() << "        Group {\n"
             "            children [\n"
             "                Shape {\n"
             "                    appearance Appearance { material "
                                               "USE Material }\n"
             "                    geometry IndexedFaceSet {\n"
             "                        convex FALSE\n"
             "                        solid  FALSE\n"
             "                        coord  Coordinate {\n"
             "                            point [" << std::endl;
}

void
File_writer_VRML_2::
write_facet_header() const {
    out() << "                            ] #point\n"
             "                        } #coord Coordinate\n"
             "                        coordIndex  [" << std::endl;
}

void
File_writer_VRML_2::
write_footer() const {
    out() << "                        ] #coordIndex\n"
             "                    } #geometry\n"
             "                } #Shape\n"
             "            ] #children\n"
             "        } #Group" << std::endl;
}

CGAL_END_NAMESPACE
// EOF //
